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

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN
{
  

  
  PythonObjectC::PythonObjectC() :
    m_object(NULL)
  {
  }


  
  PythonObjectC::PythonObjectC(PyObject *object) :
    m_object(object)
  {
    // Ref counter is either incremented by the function that returns the 
    // object, or incremented externally if 'borrowed'
  }


  
  PythonObjectC::PythonObjectC(const PythonObjectC &copy)
  {
    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      m_object = copy.m_object;
      if (m_object)
      {
        ONDEBUG(if (m_object) cerr << "PythonObjectC::PythonObjectC(copy) INCREF" << endl);
        Py_INCREF(m_object);
      }
      
      PyGILState_Release(m_lock);
    }
  }
  
  
  
  PythonObjectC::PythonObjectC(const IntT val) :
    m_object(NULL)
  {
    BuildInt(val);
  }


  
  PythonObjectC::PythonObjectC(const Int64T val) :
    m_object(NULL)
  {
    BuildInt64(val);
  }


  
  PythonObjectC::PythonObjectC(const RealT val) :
    m_object(NULL)
  {
    BuildReal(val);
  }


  
  PythonObjectC::PythonObjectC(const StringC &val) :
    m_object(NULL)
  {
    BuildString(val);
  }


  
  PythonObjectC::PythonObjectC(const DListC<PythonObjectC> &valList) :
    m_object(NULL)
  {
    BuildTuple(valList);
  }
  
  
  
  PythonObjectC::~PythonObjectC()
  {
    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      ONDEBUG(if (m_object) cerr << "PythonObjectC::~PythonObjectC DECREF" << endl);
      Py_XDECREF(m_object);
      
      PyGILState_Release(m_lock);
    }
  }


  
  PythonObjectC &PythonObjectC::operator= (const PythonObjectC &rhs)
  {
    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      ONDEBUG(if (m_object) cerr << "PythonObjectC::operator= DECREF" << endl);
      Py_XDECREF(m_object);
      
      m_object = rhs.m_object;
      
      if (m_object)
      {
        ONDEBUG(if (m_object) cerr << "PythonObjectC::operator= INCREF" << endl);
        Py_INCREF(m_object);
      }
      
      PyGILState_Release(m_lock);
    }
    
    return *this;
  }
  
  
  
  bool PythonObjectC::BuildInt(const IntT val)
  {
    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      Py_XDECREF(m_object);
      m_object = NULL;
      
      m_object = PyInt_FromLong(val);
      
      PyGILState_Release(m_lock);
      
      return (m_object != NULL);
    }
    
    return false;
  }


  
  bool PythonObjectC::BuildInt64(const Int64T val)
  {
    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      Py_XDECREF(m_object);
      m_object = NULL;
      
      m_object = PyLong_FromLongLong(val);
      
      PyGILState_Release(m_lock);
      
      return (m_object != NULL);
    }
    
    return false;
  }


  
  bool PythonObjectC::BuildReal(const RealT val)
  {
    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      Py_XDECREF(m_object);
      m_object = NULL;
      
      m_object = PyFloat_FromDouble(val);
      
      PyGILState_Release(m_lock);
      
      return (m_object != NULL);
    }
    
    return false;
  }


  
  bool PythonObjectC::BuildString(const StringC &val)
  {
    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      Py_XDECREF(m_object);
      m_object = NULL;
      
      m_object = PyString_FromString(val.chars());
      
      PyGILState_Release(m_lock);
      
      return (m_object != NULL);
    }
    
    return false;
  }


  
  bool PythonObjectC::BuildTuple(const DListC<PythonObjectC> &valList)
  {
    if (Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
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
              IntT ret = PyTuple_SetItem(m_object, pos, it->m_object);
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
      
      PyGILState_Release(m_lock);
      
      return (m_object != NULL);
    }
    
    return false;
  }
  
  
  
  bool PythonObjectC::IsInt()
  {
    if (IsValid() && Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      bool ret = PyInt_Check(m_object);
      
      PyGILState_Release(m_lock);
      return ret;
    }
    
    return false;
  }
  
  
  
  IntT PythonObjectC::Int()
  {
    if (IsValid() && Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      IntT ret = PyInt_AsLong(m_object);
      
      PyGILState_Release(m_lock);
      return ret;
    }
    
    return -1;
  }
  
  
  
  bool PythonObjectC::IsInt64()
  {
    if (IsValid() && Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      bool ret = PyLong_Check(m_object);
      
      PyGILState_Release(m_lock);
      return ret;
    }
    
    return false;
  }
  
  
  
  Int64T PythonObjectC::Int64()
  {
    if (IsValid() && Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      Int64T ret = PyLong_AsLongLong(m_object);
      if (PyErr_Occurred())
      {
        cerr << "PythonObjectC::Int64 error retrieving 64-bit int" << endl;
        PyErr_Clear();
        ret = -1;
      }
      
      PyGILState_Release(m_lock);
      return ret;
    }
    
    return -1;
  }
  
  
  
  bool PythonObjectC::IsReal()
  {
    if (IsValid() && Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      bool ret = PyFloat_Check(m_object);
      
      PyGILState_Release(m_lock);
      return ret;
    }
    
    return false;
  }
  
  
  
  RealT PythonObjectC::Real()
  {
    if (IsValid() && Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      RealT ret = PyFloat_AsDouble(m_object);
      
      PyGILState_Release(m_lock);
      return ret;
    }
    
    return -1;
  }
  
  
  
  bool PythonObjectC::IsString()
  {
    if (IsValid() && Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      bool ret = PyString_Check(m_object);
      
      PyGILState_Release(m_lock);
      return ret;
    }
    
    return false;
  }
  
  
  
  StringC PythonObjectC::String()
  {
    if (IsValid() && Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      char *str = PyString_AsString(m_object);
      StringC ret;
      if (str)
        ret = StringC(str);
      
      PyGILState_Release(m_lock);
      return ret;
    }
    
    return StringC();
  }
  
  

  bool PythonObjectC::IsTuple()
  {
    if (IsValid() && Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      bool ret = PyTuple_Check(m_object);
      
      PyGILState_Release(m_lock);
      return ret;
    }
    
    return false;
  }


  
  DListC<PythonObjectC> PythonObjectC::Tuple()
  {
    if (IsValid() && Py_IsInitialized())
    {
      m_lock = PyGILState_Ensure();
      
      DListC<PythonObjectC> ret;
      for (IntT i = 0; i < PyTuple_Size(m_object); i++)
      {
        PyObject *item = PyTuple_GetItem(m_object, i);
        if (item)
        {
          Py_INCREF(item); // GetItem returns borrowed reference
          ret.InsLast(PythonObjectC(item));
        }
      }
      
      PyGILState_Release(m_lock);
      return ret;
    }
    
    return DListC<PythonObjectC>();
  }


  
}
