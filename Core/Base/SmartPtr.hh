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
//! author="Charles Galambos"
//! docentry="Ravl.API.Core.Reference Counting"
//! file="Ravl/Core/Base/SmartPtr.hh"

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

    SmartPtrC(DataT *data)
      : RCHandleC<DataT>(data)
    {}
    //: Construct from data.
    
    DataT *BodyPtr()
    { return this->body; }
    //: Access pointer to body.
    
    const DataT *BodyPtr() const
    { return this->body; }
    //: Access pointer to body.
    
    DataT *operator->()
    { return &RCHandleC<DataT>::Body(); }
    //: Access body.
    
    const DataT *operator->() const
    { return &RCHandleC<DataT>::Body(); }
    //: Access body.
    
    operator DataT *()
    { return this->body; }
    //: Access body.
    
    operator const DataT *() const
    { return this->body; }
    //: Access body.
    
    const SmartPtrC<DataT> &operator=(const DataT *other) {
      DataT *oth = const_cast<DataT *>(other);
      if(oth != 0)
	oth->IncRefCounter();
      if(this->body != 0) {
	if(this->body->DecRefCounter())
	  delete this->body;
      }
      this->body = oth;
      return *this;
    }
    //: Assign handle.
    
    void reset()
    { this->Invalidate(); }
    //: Boost compatibility. Release handle
    
    void reset(const DataT *other) 
    { (*this) = other; }
    //: Boost compatibilty. Assign to another object.
    
    DataT *get()
    { return this->body; }
    //: Boost compatibility. Get Ptr.
    
    
  };

}
#endif
