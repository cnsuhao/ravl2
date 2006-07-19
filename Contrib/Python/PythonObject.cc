// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, University of Surrey
// This code may be redistributed under the terms of the MIT
// License. See http://www.opensource.org/licenses/mit-license.html
// file-header-ends-here
////////////////////////////////////////////////
//! rcsid="$Id: Window.cc 5325 2006-01-23 11:40:28Z apanman $"
//! lib=RavlGUI
//! file="Ravl/Contrib/Python/PythonObject.cc"

#include "Ravl/PythonObject.hh"
#include "Ravl/String.hh"
#include "Ravl/Python.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN
{

  
  
  PythonObjectC::PythonObjectC(const PythonC &interpreter, PyObject *object) :
    m_interpreter(interpreter),
    m_object(object)
  {
    RavlAssert(m_interpreter.IsValid());
    
    // Ref counter for the Python object is either incremented by the 
    // function that returns the object, or incremented externally if 'borrowed'
  }


  
  PythonObjectC::PythonObjectC(const PythonObjectC &copy)
  {
    RavlAssert(copy.m_interpreter.IsValid());
    
    // Up the ref counter on the interpreter to ensure it remains 
    // until the object is no longer needed
    m_interpreter = copy.m_interpreter;
    
    if (Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      m_object = copy.m_object;
      if (m_object)
      {
        ONDEBUG(if (m_object) cerr << "PythonObjectC::PythonObjectC(copy) INCREF" << endl);
        Py_INCREF(m_object);
      }
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();
    }
  }
  
  
  
  PythonObjectC::~PythonObjectC()
  {
    RavlAssert(m_interpreter.IsValid());

    if (Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      ONDEBUG(if (m_object) cerr << "PythonObjectC::~PythonObjectC DECREF" << endl);
      Py_XDECREF(m_object);

      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();
    }
  }


  
  PythonObjectC &PythonObjectC::operator= (const PythonObjectC &rhs)
  {
    RavlAssert(m_interpreter.IsValid());

    if (Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      ONDEBUG(if (m_object) cerr << "PythonObjectC::operator= DECREF" << endl);
      Py_XDECREF(m_object);
      
      m_object = rhs.m_object;
      
      if (m_object)
      {
        ONDEBUG(if (m_object) cerr << "PythonObjectC::operator= INCREF" << endl);
        Py_INCREF(m_object);
      }
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();
    }
    
    return *this;
  }
  
  
  
  bool PythonObjectC::BuildInt(const IntT val)
  {
    RavlAssert(m_interpreter.IsValid());

    if (Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      Py_XDECREF(m_object);
      m_object = NULL;
      
      m_object = PyInt_FromLong(val);
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();
      
      return (m_object != NULL);
    }
    
    return false;
  }


  
  bool PythonObjectC::BuildInt64(const Int64T val)
  {
    RavlAssert(m_interpreter.IsValid());

    if (Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      Py_XDECREF(m_object);
      m_object = NULL;
      
      m_object = PyLong_FromLongLong(val);
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();
      
      return (m_object != NULL);
    }
    
    return false;
  }


  
  bool PythonObjectC::BuildReal(const RealT val)
  {
    RavlAssert(m_interpreter.IsValid());

    if (Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      Py_XDECREF(m_object);
      m_object = NULL;
      
      m_object = PyFloat_FromDouble(val);
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();
      
      return (m_object != NULL);
    }
    
    return false;
  }


  
  bool PythonObjectC::BuildString(const StringC &val)
  {
    RavlAssert(m_interpreter.IsValid());

    if (Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      Py_XDECREF(m_object);
      m_object = NULL;
      
      m_object = PyString_FromString(val.chars());
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();
      
      return (m_object != NULL);
    }
    
    return false;
  }


  
  bool PythonObjectC::BuildTuple(const DListC<PythonObjectC> &valList)
  {
    RavlAssert(m_interpreter.IsValid());

    if (Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      Py_XDECREF(m_object);
      m_object = NULL;
      
      if (valList.Size() > 0)
      {
        ONDEBUG(cerr << "PythonObjectC::BuildTuple size=" << valList.Size() << endl);
        m_object = PyTuple_New(valList.Size());
        
        if (m_object)
        {
          UIntT pos = 0;
          for (DLIterC<PythonObjectC> it(valList); it; it++)
          {
            if (it->IsValid())
            {
              PyTuple_SetItem(m_object, pos, it->m_object);
              ONDEBUG(cerr << "PythonObjectC::BuildTuple adding item " << (ret == 0 ? "OK" : "FAILED") << endl);
              Py_INCREF(it->m_object); // Reference is stolen by SetItem
            }
            else
              break;
            
            pos++;
          }
          
          if (pos != valList.Size())
          {
            Py_DECREF(m_object);
            m_object = NULL;
          }
        }
      }
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();
      
      return (m_object != NULL);
    }
    
    return false;
  }
  
  
  
  bool PythonObjectC::IsInt()
  {
    RavlAssert(m_interpreter.IsValid());

    if (IsValid() && Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      bool ret = PyInt_Check(m_object);
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();

      return ret;
    }
    
    return false;
  }
  
  
  
  IntT PythonObjectC::Int()
  {
    RavlAssert(m_interpreter.IsValid());

    if (IsValid() && Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      IntT ret = PyInt_AsLong(m_object);
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();

      return ret;
    }
    
    return -1;
  }
  
  
  
  bool PythonObjectC::IsInt64()
  {
    RavlAssert(m_interpreter.IsValid());

    if (IsValid() && Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      bool ret = PyLong_Check(m_object);
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();

      return ret;
    }
    
    return false;
  }
  
  
  
  Int64T PythonObjectC::Int64()
  {
    RavlAssert(m_interpreter.IsValid());

    if (IsValid() && Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      Int64T ret = PyLong_AsLongLong(m_object);
      if (PyErr_Occurred())
      {
        cerr << "PythonObjectC::Int64 error retrieving 64-bit int" << endl;
        PyErr_Clear();
        ret = -1;
      }
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();

      return ret;
    }
    
    return -1;
  }
  
  
  
  bool PythonObjectC::IsReal()
  {
    RavlAssert(m_interpreter.IsValid());

    if (IsValid() && Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      bool ret = PyFloat_Check(m_object);
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();

      return ret;
    }
    
    return false;
  }
  
  
  
  RealT PythonObjectC::Real()
  {
    RavlAssert(m_interpreter.IsValid());

    if (IsValid() && Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      RealT ret = PyFloat_AsDouble(m_object);
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();

      return ret;
    }
    
    return -1;
  }
  
  
  
  bool PythonObjectC::IsString()
  {
    RavlAssert(m_interpreter.IsValid());

    if (IsValid() && Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      bool ret = PyString_Check(m_object);
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();

      return ret;
    }
    
    return false;
  }
  
  
  
  StringC PythonObjectC::String()
  {
    RavlAssert(m_interpreter.IsValid());

    if (IsValid() && Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      char *str = PyString_AsString(m_object);
      StringC ret;
      if (str)
        ret = StringC(str);
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();

      return ret;
    }
    
    return StringC();
  }
  
  

  bool PythonObjectC::IsTuple()
  {
    RavlAssert(m_interpreter.IsValid());

    if (IsValid() && Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      bool ret = PyTuple_Check(m_object);
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();

      return ret;
    }
    
    return false;
  }


  
  DListC<PythonObjectC> PythonObjectC::Tuple()
  {
    RavlAssert(m_interpreter.IsValid());

    if (IsValid() && Py_IsInitialized())
    {
      PyEval_AcquireLock();
      PyThreadState_Swap(m_interpreter.GetThreadState());
      
      DListC<PythonObjectC> ret;
      for (IntT i = 0; i < PyTuple_Size(m_object); i++)
      {
        PyObject *item = PyTuple_GetItem(m_object, i);
        if (item)
        {
          Py_INCREF(item); // GetItem returns borrowed reference
          ret.InsLast(PythonObjectC(m_interpreter, item));
        }
      }
      
      PyThreadState_Swap(NULL);
      PyEval_ReleaseLock();

      return ret;
    }
    
    return DListC<PythonObjectC>();
  }


  
}
