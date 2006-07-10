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
  

  
  PythonBodyC::PythonBodyC()
  {
    ONDEBUG(cerr << "PythonBodyC::PythonBodyC" << endl);
    Py_Initialize();

    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      PyObject *mainModule = PyImport_AddModule("__main__");
      if (mainModule)
      {
        Py_INCREF(mainModule); // AddModule returns borrowed reference
        m_modules.Update("__main__", mainModule);
        
        PyGILState_Release(m_lock);
      }
      else
      {
        cerr << "PythonBodyC::PythonBodyC failed to initialise main environment" << endl;
        Py_Finalize();
      }
    }
    else
    {
      cerr << "PythonBodyC::PythonBodyC failed to initialise Python interpreter" << endl;
    }
  }
  
  
  
  PythonBodyC::~PythonBodyC()
  {
    ONDEBUG(cerr << "PythonBodyC::~PythonBodyC" << endl);
    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      for (HashIterC<StringC, PyObject*> it(m_modules); it; it++)
      {
        ONDEBUG(cerr << "PythonBodyC::~PythonBodyC DECREF module=" << it.Key() << endl);
        Py_DECREF(it.Data());
      }
      
      PyGILState_Release(m_lock);
    }
                                                          
    Py_Finalize();
  }
  
  
  
  void PythonBodyC::AppendSystemPath(const StringC &path)
  {
    ONDEBUG(cerr << "PythonBodyC::AppendSystemPath path=" << path << endl);
    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
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
          }
          Py_DECREF(sysPath);
        }
      }
      
      PyGILState_Release(m_lock);
    }
  }
  
  
  
  bool PythonBodyC::Import(const StringC &module)
  {
    ONDEBUG(cerr << "PythonBodyC::Import name=" << module << endl);
    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      PyObject *modulePtr = PyImport_ImportModule(const_cast<char*>(module.chars()));
      if (modulePtr)
      {
        ONDEBUG(cerr << "PythonBodyC::Import imported=" << module << endl);
        m_modules.Update(module, modulePtr);
      }
      
      PyGILState_Release(m_lock);
      
      if (modulePtr)
        return true;
    }
    
    return false;
  }
  
  
  
  PythonObjectC PythonBodyC::Call(const StringC &module, const StringC &name, PythonObjectC args)
  {
    ONDEBUG(cerr << "PythonBodyC::Call module=" << module << " name=" << name << endl);
    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      PyObject *ret = NULL;
      PyObject *modulePtr = NULL;
      if (m_modules.Lookup(module, modulePtr))
      {
        PyObject *func = PyObject_GetAttrString(modulePtr, const_cast<char*>(name.chars()));
        if (func && PyCallable_Check(func))
        {
          if (args.IsValid())
          {
            if (args.IsTuple())
            {
              ret = PyObject_CallObject(func, args.m_object);
              
              ONDEBUG(cerr << "PythonBodyC::Call name='" << name << "' args=" << PyTuple_Size(args.m_object) << " " << (ret ? "OK" : "FAILED") << endl);
            }
            else
              cerr << "PythonBodyC::Call tuple not supplied as arguments" << endl;
          }
          else
          {
            ret = PyObject_CallObject(func, NULL);
            
            ONDEBUG(cerr << "PythonBodyC::Call name='" << name << "' " << (ret ? "OK" : "FAILED") << endl);
          }
          
          Py_DECREF(func);
        }
        else
          cerr << "PythonBodyC::Call failed to find function '"  << name << "'" << endl;
      }
      
      PyGILState_Release(m_lock);
      
      return PythonObjectC(ret);
    }
    
    return PythonObjectC();
  }
  
  
  
  bool PythonBodyC::Run(const StringC &script)
  {
    ONDEBUG(cerr << "PythonBodyC::Run" << endl);
    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      PyObject *ret = NULL;
      PyObject *mainDict = GetModuleDictionary("__main__");
      if (mainDict)
      {
        ret = PyRun_String(script, Py_file_input, mainDict, mainDict);
      }
      
      PyGILState_Release(m_lock);
      
      return (ret != NULL);
    }
    
    return false;
  }
  
  
  
  PythonObjectC PythonBodyC::GetGlobal(const StringC &name)
  {
    ONDEBUG(cerr << "PythonBodyC::GetGlobal name=" << name << endl);
    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      PyObject *object = NULL;
      PyObject *mainDict = GetModuleDictionary("__main__");
      if (mainDict)
      {
        object = PyDict_GetItemString(mainDict, name);
        ONDEBUG(if (object == NULL) cerr << "PythonBodyC::GetGlobal failed to find '" << name << "' in globals" << endl);
      }
      
      PyGILState_Release(m_lock);
      
      return PythonObjectC(object);
    }
    
    return PythonObjectC();
  }
  
  
  
  PyObject *PythonBodyC::GetModuleDictionary(const StringC &name)
  {
    ONDEBUG(cerr << "PythonBodyC::GetModuleDictionary name=" << name << endl);
    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      PyObject *mainModule = NULL;
      PyObject *mainDict = NULL;
      if (m_modules.Lookup(name, mainModule))
      {
        mainDict = PyObject_GetAttrString(mainModule, "__dict__");
      }

      PyGILState_Release(m_lock);
      
      return mainDict;
    }
    
    return NULL;
  }
  
  
  
}
