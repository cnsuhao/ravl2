// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SMARTPTR_HEADER 
#define RAVL_SMARTPTR_HEADER 1
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/RefCounter.hh"

namespace RavlN {
  
  //! userlevel=Advanced
  //: Smart pointer.
  
  template<class DataT>
  class SmartPtrC
    : public RCHandleC<DataT>
  {
  public:
    SmartPtrC()
    {}
    //: Default constructor.
    
    SmartPtrC(const RCHandleC<DataT> &handle)
      : RCHandleC<DataT>(handle)
    {}
    //: Construct from a normal handle.
    
    SmartPtrC(DataT &data)
      : RCHandleC<DataT>(data)
    {}
    //: Construct from data.
    
    DataT *BodyPtr()
    { return &RCHandleC<DataT>::Body(); }
    //: Access body.
    
    const DataT *BodyPtr() const
    { return &RCHandleC<DataT>::Body(); }
    //: Access body.

    DataT *operator->()
    { return &RCHandleC<DataT>::Body(); }
    //: Access body.
    
    const DataT *operator->() const
    { return &RCHandleC<DataT>::Body(); }
    //: Access body.
    
    operator DataT *()
    { return &RCHandleC<DataT>::Body(); }
    //: Access body.
    
    operator const DataT *() const
    { return &RCHandleC<DataT>::Body(); }
    //: Access body.
    
    const SmartPtrC<DataT> &operator=(const DataT *other) {
      DataT *oth = const_cast<DataT *>(other);
      if(oth != 0)
	oth->IncRefCounter();
      if(body != 0) {
	if(body->DecRefCounter())
	  delete body;
      }
      body = oth;
      return *this;
    }
    //: Assign handle.

  };

}
#endif
