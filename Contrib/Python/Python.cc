// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, University of Surrey
// This code may be redistributed under the terms of the MIT
// License. See http://www.opensource.org/licenses/mit-license.html
// file-header-ends-here
////////////////////////////////////////////////
//! rcsid="$Id: Window.cc 5325 2006-01-23 11:40:28Z apanman $"
//! lib=RavlGUI
//! file="Ravl/Contrib/Python/Python.cc"

#include "Ravl/Python.hh"
#include "Ravl/PythonObject.hh"
#include "Ravl/HashIter.hh"
#include <iostream>

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
        
        CheckError();
        
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
        cerr << "PythonBodyC::PythonBodyC(" << this << ") failed to create Python sub-interpreter" << endl;
      }
      
      CheckError();
      
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
    
    bool ret = false;
    
    if (Py_IsInitialized())
    {
      MutexLockC lock(m_lock);
      
      PyEval_AcquireLock();
      PyThreadState_Swap(m_threadState);
      
      PyObject *sysModule = PyImport_AddModule("sys");
      if (sysModule)
      {
        PyObject *sysPath = PyObject_GetAttrString(sysModule, "path");
        if (sysPath)
        {
          PyObject *newPath = PyString_FromString(const_cast<char*>(path.chars()));
          if (newPath)
          {
            PyList_Append(sysPath, newPath);
            Py_DECREF(newPath);
            
            ret = true;
          }
          Py_DECREF(sysPath);
        }
      }
      
      CheckError();
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();
    }
    
    return ret;
  }
  
  
  
  bool PythonBodyC::Import(const StringC &module)
  {
    ONDEBUG(cerr << "PythonBodyC::Import(" << this << ") name=" << module << endl);
    RavlAssert(m_threadState);
    
    if (Py_IsInitialized())
    {
      MutexLockC lock(m_lock);
      
      PyEval_AcquireLock();
      PyThreadState_Swap(m_threadState);
      
      PyObject *modulePtr = PyImport_ImportModule(const_cast<char*>(module.chars()));
      if (modulePtr)
      {
        ONDEBUG(cerr << "  PythonBodyC::Import(" << this << ") imported=" << module << endl);
        m_modules.Update(module, modulePtr);
      }

      bool result = !CheckError() && modulePtr;
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();
      
      return result;
    }
    
    return false;
  }
  
  
  
  PythonObjectC PythonBodyC::NewObject()
  {
    return PythonObjectC(PythonC(*this));
  }
  
  
  
  PythonObjectC PythonBodyC::Call(const StringC &module, const StringC &name)
  {
    return Call(module, name, PythonObjectC(PythonC(*this)));
  }
  
  
  
  PythonObjectC PythonBodyC::Call(const StringC &module, const StringC &name, const PythonObjectC &args)
  {
    ONDEBUG(cerr << "PythonBodyC::Call(" << this << ") module=" << module << " name=" << name << endl);
    RavlAssert(m_threadState);
    
    if (Py_IsInitialized())
    {
      MutexLockC lock(m_lock);
      
      PyEval_AcquireLock();
      PyThreadState_Swap(m_threadState);
      
      PyObject *ret = NULL;
      PyObject *modulePtr = NULL;
      if (m_modules.Lookup(module, modulePtr))
      {
        PyObject *func = PyObject_GetAttrString(modulePtr, const_cast<char*>(name.chars()));
        if (func && PyCallable_Check(func))
        {
          if (args.GetObject())
          {
            if (PyTuple_Check(args.GetObject()))
            {
              ret = PyObject_CallObject(func, args.GetObject());
              
              ONDEBUG(cerr << "  PythonBodyC::Call(" << this << ") name='" << name << "' args=" << PyTuple_Size(args.GetObject()) << " " << (ret ? "OK" : "FAILED") << endl);
            }
            else
              cerr << "PythonBodyC::Call tuple not supplied as arguments" << endl;
          }
          else
          {
            ret = PyObject_CallObject(func, NULL);
            
            ONDEBUG(cerr << "  PythonBodyC::Call(" << this << ") name='" << name << "' " << (ret ? "OK" : "FAILED") << endl);
          }
          
          Py_DECREF(func);
        }
        else
          cerr << "PythonBodyC::Call(" << this << ") failed to find function '"  << name << "'" << endl;
      }
      
      CheckError();
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();
      
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
      
      PyEval_AcquireLock();
      PyThreadState_Swap(m_threadState);

      int ret = PyRun_SimpleString(script);
      
      bool result = !CheckError() && (ret == 0);
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();
      
      return result;
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
      
      PyEval_AcquireLock();
      PyThreadState_Swap(m_threadState);
      
      PyObject *object = NULL;
      PyObject *mainDict = GetModuleDictionary("__main__");
      if (mainDict)
      {
        object = PyDict_GetItemString(mainDict, name);
        ONDEBUG(if (object == NULL) cerr << "  PythonBodyC::GetGlobal(" << this << ") failed to find '" << name << "' in globals" << endl);
      }
      
      CheckError();
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();
      
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
      mainDict = PyObject_GetAttrString(mainModule, "__dict__");
    }

    return mainDict;
  }
  
  
  
  void PythonBodyC::GetError(StringC &type, StringC &value, StringC &trace)
  {
  	type = m_exceptionType.Copy();
  	value = m_exceptionValue.Copy();
  	trace = m_exceptionTrace.Copy();
  }
  
  
  
  bool PythonBodyC::CheckError()
  {
    if (PyErr_Occurred())
    {
    	// Pointers for fetched exception details
    	PyObject *exType = NULL;
    	PyObject *exValue = NULL;
    	PyObject *exTrace = NULL;
    	PyErr_Fetch(&exType, &exValue, &exTrace);
    	
    	// If the object exists, create and store a string representation of it
  		m_exceptionType = (exType ? GetObjectAsString(exType) : StringC());
  		m_exceptionValue = (exValue ? GetObjectAsString(exValue) : StringC());
  		m_exceptionTrace = (exTrace ? GetTraceAsString(exTrace) : StringC());
    	
  		// Clear the exception objects (XDECREF as they may be NULL)
  		Py_XDECREF(exType);
  		Py_XDECREF(exValue);
  		Py_XDECREF(exTrace);
    	
  		// Clear the exception flags
      PyErr_Clear();
      
      return true;
    }
    
    return false;
  }
  
  
  
  StringC PythonBodyC::GetObjectAsString(PyObject *object)
  {
  	RavlAssert(object != NULL);
  	
  	PyObject *objectStr = NULL;
  	if ((objectStr = PyObject_Str(object)) != NULL)
  	{
  		const char * const chars = PyString_AsString(objectStr);
  		StringC str(chars);
  		
  		Py_DECREF(objectStr);
  		
  		return str;
    }
  	
  	return StringC();
  }
  
  
  
  StringC PythonBodyC::GetTraceAsString(PyObject *object)
  {
  	RavlAssert(object != NULL);
  	
  	StringC ret;
  	
  	// Import the traceback module to do the formatting
    PyObject *traceModule = PyImport_AddModule("traceback");
    if (traceModule)
    {
    	// 'formatRet = traceback.format_tb(sys.exc_traceback)'
    	PyObject *formatRet = PyObject_CallMethod(traceModule, "format_tb", "O", object);
    	if (formatRet)
    	{
    		// 'joinRet = "".join(formatRet)'
      	PyObject *emptyStr = PyString_FromString("");
      	PyObject *joinRet = PyObject_CallMethod(emptyStr, "join", "O", formatRet);
      	if (joinRet)
      	{
      		const char * const chars = PyString_AsString(joinRet);
      		ret = StringC(chars);
      		
      		Py_DECREF(joinRet);
      	}
      	
      	Py_DECREF(emptyStr);
      	Py_DECREF(formatRet);
    	}

      Py_DECREF(traceModule);
    }
    
    return ret;
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
