// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2010, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

%{
#ifdef SWIGPERL
#undef Copy
#endif

#include "Ravl/SmartPtr.hh"

#ifdef SWIGPERL
#define Copy(s,d,n,t)   (MEM_WRAP_CHECK_(n,t) (void)memcpy((char*)(d),(const char*)(s), (n) * sizeof(t)))
#endif
%}

namespace RavlN {

  template<typename DataT>
  class SmartPtrC {
  public:
    SmartPtrC();
    SmartPtrC(const DataT *data);
    DataT *operator->();
    void Invalidate();
    bool IsValid();
    void reset();
    void reset(const DataT *other);
    DataT *get();
  };
}

%define RAVL_SMART_POINTER(name, type)
%template(name ## H) RavlN::SmartPtrC<type >;
%enddef
