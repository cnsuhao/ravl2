// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// Python is used under the terms of the Python License
// Copyright (C) 2001, 2002, 2003, 2004 Python Software Foundation; All Rights Reserved
// file-header-ends-here
////////////////////////////////////////////////////////////////
//! file = "Ravl/Contrib/Python/Python.cc"
//! lib = RavlPython

#include "Ravl/Python.hh"
#include "Ravl/PythonObject.hh"
#include "Ravl/PythonLock.hh"
#include "Ravl/HashIter.hh"
#include <iostream>
#include "Ravl/PythonException.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN
{
  
  MutexC PythonBodyC::m_initLock;
  PythonC PythonBodyC::m_mainInterpreter;
  
  PythonBodyC::PythonBodyC() :
    m_subInterpreter(false),
    m_threadState(NULL)
  {
    MutexLockC lock(m_lock);
    MutexLockC initLock(m_initLock);
    
    ONDEBUG(cerr << "PythonBodyC::PythonBodyC(" << this << ")" << endl);
    
    if (!m_mainInterpreter.IsValid())
    {
      // Enable threads and initialise the only instance of the main Python interpreter
      Py_Initialize();
      PyEval_InitThreads();
    
      if (Py_IsInitialized())
      {
        ONDEBUG(cerr << "  PythonBodyC::PythonBodyC(" << this << ") initialised" << endl);
        
        // Store the pointer to the main Python interpreter
        m_mainInterpreter = PythonC(*this);
        
        // Get the main thread state
        m_mainThreadState = PyThreadState_Get();
        
        if (m_mainThreadState)
        {
          // Create a new thread state
          m_threadState = PyThreadState_New(m_mainThreadState->interp);

          if (m_threadState)
          {
            InitialiseEnvironment();
          }
          else
          {
            cerr << "PythonBodyC::PythonBodyC(" << this << ") failed to initialise Python thread state" << endl;
          }
        }
        else
        {
          cerr << "PythonBodyC::PythonBodyC(" << this << ") failed to initialise Python interpreter state" << endl;
        }

        // TODO The thread state/lock release is a prime candidate for RAII
        // but PythonLockC is not suitable here
        try
        {
          CheckPythonException();
        }
        catch (PythonExceptionC &e)
        {
          PyThreadState_Swap(NULL);
          PyEval_ReleaseLock();
          throw;
        }
        
        PyThreadState_Swap(NULL);
        PyEval_ReleaseLock();
      }
      else
      {
        cerr << "PythonBodyC::PythonBodyC(" << this << ") failed to initialise Python interpreter" << endl;
      }
    }
    else
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(NULL);
      
      m_mainThreadState = Py_NewInterpreter();
      
      if (m_mainThreadState)
      {
        ONDEBUG(cerr << "  PythonBodyC::PythonBodyC(" << this << ") sub-interpreter created" << endl);
        
        // Note we are a Python sub-interpreter
        m_subInterpreter = true;
        
        // Create a new thread state
        m_threadState = PyThreadState_New(m_mainThreadState->interp);
        
        if (m_threadState)
        {
          InitialiseEnvironment();
        }
        else
        {
          cerr << "PythonBodyC::PythonBodyC(" << this << ") failed to initialise Python sub-thread state" << endl;
        }
      }
      else
      {
        cerr << "PythonBodyC::PythonBodyC(" << this << ") failed to initialise Python sub-interpreter" << endl;
      }
      
      // TODO The thread state/lock release is a prime candidate for RAII
      // but PythonLockC is not suitable here
      try
      {
        CheckPythonException();
      }
      catch (PythonExceptionC &e)
      {
        PyThreadState_Swap(NULL);
        PyEval_ReleaseLock();
        throw;
      }

      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();
    }
  }
  
  PythonBodyC::~PythonBodyC()
  {
    MutexLockC lock(m_lock);
    MutexLockC initLock(m_initLock);
  
    ONDEBUG(cerr << "PythonBodyC::~PythonBodyC(" << this << ")" << endl);

    if (Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_mainThreadState); // Doesn't matter if it's NULL

      for (HashIterC<StringC, PyObject*> it(m_modules); it; it++)
      {
        ONDEBUG(cerr << "  PythonBodyC::~PythonBodyC(" << this << ") DECREF module=" << it.Key() << endl);
        Py_DECREF(it.Data());
      }
      
      if (m_threadState)
      {
        PyThreadState_Clear(m_threadState);
        PyThreadState_Delete(m_threadState);
        
        m_threadState = NULL;
      }
      
      if (m_subInterpreter)
      {
        ONDEBUG(cerr << "  PythonBodyC::~PythonBodyC(" << this << ") sub-interpreter destroyed" << endl);
        
        if (m_mainThreadState)
        {
          Py_EndInterpreter(m_mainThreadState);
        }

        PyThreadState_Swap(NULL);
        PyEval_ReleaseLock();
      }
      else
      {
        ONDEBUG(cerr << "  PythonBodyC::~PythonBodyC(" << this << ") finalised" << endl);
        
        Py_Finalize();
      }
      
      m_mainThreadState = NULL;
    }
  }
  
  bool PythonBodyC::AppendSystemPath(const StringC &path)
  {
    ONDEBUG(cerr << "PythonBodyC::AppendSystemPath(" << this << ") path=" << path << endl);
    RavlAssert(m_threadState);
    
    if (Py_IsInitialized())
    {
      MutexLockC lock(m_lock);
      PythonLockC pythonLock(m_threadState);
      
      bool ret = false;
      
      // Returns NULL on failure and sets Python exception
      PyObject *sysModule = PyImport_AddModule("sys");
      if (sysModule)
      {
        // Returns NULL on failure
        PyObject *sysPath = PyObject_GetAttrString(sysModule, "path");
        if (sysPath)
        {
          // Returns NULL on failure
          PyObject *newPath = PyString_FromString(const_cast<char*>(path.chars()));
          if (newPath)
          {
            // Returns NULL on failure and sets Python exception
            PyList_Append(sysPath, newPath);
            Py_DECREF(newPath);
            
            ret = true;
          }
          Py_DECREF(sysPath);
        }
      }
      
      CheckPythonException();
      
      return ret;
    }
    
    return false;
  }
  
  bool PythonBodyC::Import(const StringC &module)
  {
    ONDEBUG(cerr << "PythonBodyC::Import(" << this << ") name=" << module << endl);
    RavlAssert(m_threadState);
    
    if (Py_IsInitialized())
    {
      MutexLockC lock(m_lock);
      PythonLockC pythonLock(m_threadState);
      
      bool ret = false;
      
      // Get the '__main__' module pointer
      PyObject *mainModule = NULL;
      if (m_modules.Lookup("__main__", mainModule))
      {
        // Import the module
        // Returns NULL on failure and sets Python exception
        PyObject *modulePtr = PyImport_ImportModule(const_cast<char*>(module.chars()));
        if (modulePtr)
        {
          // Returns 0 on success, -1 on error
          if (PyModule_AddObject(mainModule, const_cast<char*>(module.chars()), modulePtr) == 0)
          {
            ONDEBUG(cerr << "  PythonBodyC::Import(" << this << ") imported=" << module << endl);

            // PyModule_AddObject steals a reference, so increment ours so we can safely store it
            Py_INCREF(modulePtr);
            
            m_modules.Update(module, modulePtr);
            
            ret = true;
          }
          else
          {
            // We're not storing the module pointer, so release it
            Py_DECREF(modulePtr);
          }
        }
      }

      CheckPythonException();
      
      return ret;
    }
    
    return false;
  }
  
  PythonObjectC PythonBodyC::NewObject()
  {
    return PythonObjectC(PythonC(*this));
  }
  
  PythonObjectC PythonBodyC::Call(const StringC &module, const StringC &function)
  {
    return Call(module, function, PythonObjectC(PythonC(*this)));
  }
  
  PythonObjectC PythonBodyC::Call(const StringC &module, const StringC &function, const PythonObjectC &args)
  {
    ONDEBUG(cerr << "PythonBodyC::Call(" << this << ") module=" << module << " function=" << function << endl);
    RavlAssert(m_threadState);
    
    if (Py_IsInitialized())
    {
      MutexLockC lock(m_lock);
      PythonLockC pythonLock(m_threadState);
      
      PyObject *ret = NULL;
      PyObject *modulePtr = NULL;
      if (m_modules.Lookup(module, modulePtr))
      {
        // Returns NULL on failure
        PyObject *func = PyObject_GetAttrString(modulePtr, const_cast<char*>(function.chars()));
        
        // Returns 1 if callable, 0 otherwise
        if (func && PyCallable_Check(func))
        {
          if (args.GetObject())
          {
            if (PyTuple_Check(args.GetObject()))
            {
              // Returns NULL on failure, script may set an exception
              ret = PyObject_CallObject(func, args.GetObject());
              
              ONDEBUG(cerr << "  PythonBodyC::Call(" << this << ") function='" << function << "' args=" << PyTuple_Size(args.GetObject()) << " " << (ret ? "OK" : "FAILED") << endl);
            }
            else
            {
              cerr << "PythonBodyC::Call tuple not supplied as arguments" << endl;
            }
          }
          else
          {
            // Returns NULL on failure, script may set an exception
            ret = PyObject_CallObject(func, NULL);
            
            ONDEBUG(cerr << "  PythonBodyC::Call(" << this << ") function='" << function << "' " << (ret ? "OK" : "FAILED") << endl);
          }
          
          Py_DECREF(func);
        }
        else
        {
          cerr << "PythonBodyC::Call(" << this << ") failed to find function '"  << function << "'" << endl;
        }
      }
      
      CheckPythonException();
      
      return PythonObjectC(PythonC(*this), ret);
    }
    
    return PythonObjectC(PythonC(*this));
  }
  
  bool PythonBodyC::Run(const StringC &script)
  {
    ONDEBUG(cerr << "PythonBodyC::Run(" << this << ")" << endl);
    RavlAssert(m_threadState);
    
    if (Py_IsInitialized())
    {
      MutexLockC lock(m_lock);
      PythonLockC pythonLock(m_threadState);
      
      // Returns 0 on success, -1 on error
      // Python exceptions are not accessible
      bool ret = (PyRun_SimpleString(script) == 0);
      
      CheckPythonException();

      return ret;
    }
    
    return false;
  }
  
  PythonObjectC PythonBodyC::GetGlobal(const StringC &name)
  {
    ONDEBUG(cerr << "PythonBodyC::GetGlobal(" << this << ") name=" << name << endl);
    RavlAssert(m_threadState);
    
    if (Py_IsInitialized())
    {
      MutexLockC lock(m_lock);
      PythonLockC pythonLock(m_threadState);
      
      PyObject *object = NULL;
      PyObject *mainDict = GetModuleDictionary("__main__");
      if (mainDict)
      {
        // Return NULL on failure
        object = PyDict_GetItemString(mainDict, name);
        ONDEBUG(if (object == NULL) cerr << "  PythonBodyC::GetGlobal(" << this << ") failed to find '" << name << "' in globals" << endl);
      }
      
      CheckPythonException();
      
      return PythonObjectC(PythonC(*this), object);
    }
    
    return PythonObjectC(PythonC(*this));
  }
  
  void PythonBodyC::InitialiseEnvironment()
  {
    ONDEBUG(cerr << "PythonBodyC::InitialiseEnvironment(" << this << ")" << endl);
    RavlAssert(Py_IsInitialized());
    RavlAssert(m_threadState);
   
    // Get access to the main module
    // Returns NULL on failure and sets Python exception
    PyObject *mainModule = PyImport_AddModule("__main__");
    if (mainModule)
    {
      Py_INCREF(mainModule); // AddModule returns borrowed reference
      m_modules.Update("__main__", mainModule);
    }
    else
    {
      cerr << "PythonBodyC::PythonBodyC(" << this << ") failed to initialise main environment" << endl;
    }
  }
  
  PyObject *PythonBodyC::GetModuleDictionary(const StringC &name)
  {
    ONDEBUG(cerr << "PythonBodyC::GetModuleDictionary(" << this << ") name=" << name << endl);
    RavlAssert(Py_IsInitialized());
    RavlAssert(m_threadState);
    
    PyObject *mainModule = NULL;
    PyObject *mainDict = NULL;
    if (m_modules.Lookup(name, mainModule))
    {
      // Returns NULL on failure
      mainDict = PyObject_GetAttrString(mainModule, "__dict__");
    }

    return mainDict;
  }
  
  PythonObjectC PythonC::NewObject()
  {
    return Body().NewObject();
  }

  PythonObjectC PythonC::Call(const StringC &module, const StringC &name)
  {
    return Body().Call(module, name);
  }

  PythonObjectC PythonC::Call(const StringC &module, const StringC &name, const PythonObjectC &args)
  {
    return Body().Call(module, name, args);
  }

  PythonObjectC PythonC::GetGlobal(const StringC &name)
  {
    return Body().GetGlobal(name);
  }

}
