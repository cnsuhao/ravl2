// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SMARTLAYERPTR_HEADER 
#define RAVL_SMARTLAYERPTR_HEADER 1
//! rcsid="$Id: SmartPtr.hh 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlCore
//! author="Charles Galambos"
//! docentry="Ravl.API.Core.Reference Counting"
//! file="Ravl/Core/Base/SmartLayerPtr.hh"

#include "Ravl/RCLayer.hh"
#include "Ravl/SmartPtr.hh"

namespace RavlN {
  
  //! userlevel=Advanced
  //: Callback ptr.
  // See RCLayerC for an explanation of the difference between this and a plain SmartPtrC.
  
  template<class DataT>
  class SmartCallbackPtrC 
    : public SmartPtrC<DataT>
  {
  public:
    SmartCallbackPtrC()
    {}
    //: Default constructor.
    
    SmartCallbackPtrC(const RCHandleC<DataT> &handle)
      : SmartPtrC<DataT>(handle)
    {}
    //: Construct from a normal handle.
    
    SmartCallbackPtrC(DataT &data)
      : SmartPtrC<DataT>(data)
    {}
    //: Construct from data.

    SmartCallbackPtrC(DataT *data)
      : SmartPtrC<DataT>(data)
    {}
    //: Construct from data.
    
    SmartCallbackPtrC(const DataT *data)
      : SmartPtrC<DataT>(data)
    {}
    //: Construct from data.
    
  };
  
  //! userlevel=Advanced
  //: Smart owner pointer.
  // See RCLayerC for an explanation of the difference between this and a plain SmartPtrC.
  
  template<class DataT>
  class SmartOwnerPtrC
    : public RCLayerC<DataT>
  {
  public:
    SmartOwnerPtrC()
    {}
    //: Default constructor.
    
    SmartOwnerPtrC(const SmartCallbackPtrC<DataT> &handle,RCLayerHandleT handleType)
      : RCLayerC<DataT>(handle.BodyPtr(),handleType)
    {}
    //: Construct from a normal handle.
    // This assumes the handle is a callback handle.
    
    SmartOwnerPtrC(const RCHandleC<DataT> &handle,RCLayerHandleT handleType = RCLH_OWNER)
      : RCLayerC<DataT>(handle,handleType)
    {}
    //: Construct from a normal handle.
    // Constructs an owner handle by default.
    
    SmartOwnerPtrC(DataT &data,RCLayerHandleT handleType = RCLH_OWNER)
      : RCLayerC<DataT>(data,handleType)
    {}
    //: Construct from data.
    // Constructs an owner handle by default.
    
    SmartOwnerPtrC(DataT *data,RCLayerHandleT handleType = RCLH_OWNER)
      : RCLayerC<DataT>(data,handleType)
    {}
    //: Construct from data.
    // Constructs an owner handle by default.

    SmartOwnerPtrC(const DataT *data,RCLayerHandleT handleType = RCLH_OWNER)
      : RCLayerC<DataT>(data,handleType)
    {}
    //: Construct from data.
    // Constructs an owner handle by default.
    
    DataT *BodyPtr()
    { return RCLayerC<DataT>::BodyPtr(); }
    //: Access pointer to body.
    
    const DataT *BodyPtr() const
    { return RCLayerC<DataT>::BodyPtr(); }
    //: Access pointer to body.
    
    DataT *operator->()
    { return RCLayerC<DataT>::BodyPtr(); }
    //: Access body.
    
    const DataT *operator->() const
    { return RCLayerC<DataT>::BodyPtr(); }
    //: Access body.
    
    operator DataT *()
    { return RCLayerC<DataT>::BodyPtr(); }
    //: Access body.
    
    operator const DataT *() const
    { return RCLayerC<DataT>::BodyPtr(); }
    //: Access body.
    
    UIntT Hash() const 
    { return StdHash(reinterpret_cast<const void *>(BodyPtr())); }
    //: Compute hash value for handle.
  };

}
#endif
