// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FUNCTIONREGISTER_HEADER
#define RAVL_FUNCTIONREGISTER_HEADER 1
//////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlCore

#include "Ravl/Types.hh"
#include "Ravl/BiHash.hh"

#if RAVL_HAVE_ANSICPPHEADERS
#include <typeinfo>
#else
#include <typeinfo.h>
#endif

namespace RavlN {
  
  bool BaseFunctionRegister(const char *name,void *ptr,int size,const type_info &ti);
  //! userlevel=Develop
  //: Register function pointer.
  
  bool BaseFunctionLookupByName(const char *name,void *ptr,int size,const type_info &ti);
  //: Register function pointer.

  const char *BaseFunctionLookupByPointer(void *ptr,int size,const type_info &ti);
  //: Lookup function by pointer.
  
  template<class DataT>
  bool RegisterFunction(const char *name,DataT funcPtr)
  { return BaseFunctionRegister(name,(void *) &funcPtr,sizeof(funcPtr),typeid(DataT)); }
  //! userlevel=Normal
  //: Register function ptr.
  
  template<class DataT>
  bool LookupFunctionByName(const char *name,DataT &funcPtr)
  { return BaseFunctionLookupByName(name,(void *) &funcPtr,sizeof(funcPtr),typeid(DataT)); }
  //: Lookup function pointer by name.
  
  template<class DataT>
  const char *LookupFunctionByPointer(DataT &funcPtr)
  { return BaseFunctionLookupByPointer((void *) &funcPtr,sizeof(funcPtr),typeid(DataT)); }
  //: Lookup function name by pointer.
  
}

#endif
