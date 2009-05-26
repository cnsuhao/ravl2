// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

%include "Ravl/Swig/Types.i"

%{
#ifdef SWIGPERL
#undef Copy
#endif

#include "Ravl/DList.hh"
#include "Ravl/DLIter.hh"

#ifdef SWIGPERL
#define Copy(s,d,n,t)   (MEM_WRAP_CHECK_(n,t) (void)memcpy((char*)(d),(const char*)(s), (n) * sizeof(t)))
#endif
%}

namespace RavlN {

  template<typename DataT>
  class DListC {
  public:
    DListC();
    void Empty();
    void InsFirst(const DataT &dat);
    void InsLast(const DataT &dat);
    DataT PopFirst();
    DataT PopLast();
    void MoveFirst(DListC<DataT> & lst);
    void MoveLast(DListC<DataT> & lst);
    DataT First();
    DataT Last();
    bool Del(const DataT &x);
    bool Contains(const DataT &x);
    DataT Nth(int n);
  };

  template<class DataT>
  class DLIterC {
  public:
    DLIterC();
    DLIterC(const DListC<DataT> &lst);
    bool IsValid() const;
    void First();
    void Last();
    bool IsElm() const;
    bool IsFirst() const;
    bool IsLast() const;
    void Next();
    void Prev();
    void NextCrc();
    void PrevCrc();
    void Nth(IntT n);
    DataT NextData();
    DataT PrevData();
    DataT NextCrcData();
    DataT PrevCrcData();
    DListC<DataT> Tail();
    DListC<DataT> Head();
    DListC<DataT> InclusiveTail();
    DListC<DataT> InclusiveHead();
    DataT Data();
    DataT *operator->();
  };

}

%define DLIST_TOLIST_TYPE(name, type, converter)

%template(DList ## name ## C) RavlN::DListC<type >;
%template(DList ## name ## IterC) RavlN::DLIterC<type >;

%inline %{
#if SWIGPYTHON
  PyObject *ToList(RavlN::DListC<type> list)
  {
    PyObject *obj = PyList_New(0);
    if (PyErr_Occurred())
      SWIG_fail;
    for (RavlN::DLIterC<type> it(list); it; it++)
    {
      PyObject *temp = converter(*it);
      if (PyErr_Occurred())
        SWIG_fail;
      PyList_Append(obj, temp);
    }
    return obj;
    fail:
    return NULL;
  }
#endif
%}

%enddef

DLIST_TOLIST_TYPE(Real,  RavlN::RealT,  PyFloat_FromDouble)
DLIST_TOLIST_TYPE(Int,   RavlN::IntT,   PyInt_FromLong)
DLIST_TOLIST_TYPE(UInt,  RavlN::UIntT,  PyInt_FromLong)
DLIST_TOLIST_TYPE(Int64, RavlN::Int64T, PyLong_FromLongLong)
DLIST_TOLIST_TYPE(Int16, RavlN::Int16T, PyInt_FromLong)
DLIST_TOLIST_TYPE(Byte,  RavlN::ByteT,  PyInt_FromLong)

%define DLIST_TOLIST_OBJECT(name, type)

%template(DList ## name ## C) RavlN::DListC<type >;
%template(DList ## name ## IterC) RavlN::DLIterC<type >;

%inline %{
#if SWIGPYTHON
  PyObject *ToList(RavlN::DListC<type> list)
  {
    PyObject *obj = PyList_New(0);
    if (PyErr_Occurred())
      SWIG_fail;
    {
      swig_type_info *typeInfo = SWIG_TypeQuery(#type " *");
      for (RavlN::DLIterC<type> it(list); it; it++)
      {
        PyObject *temp = SWIG_NewPointerObj((void*)&it.Data(), typeInfo, 0);
        if (PyErr_Occurred())
          SWIG_fail;
        PyList_Append(obj, temp);
      }
      return obj;
    }
    fail:
    return NULL;
  }
#endif
%}

%enddef
