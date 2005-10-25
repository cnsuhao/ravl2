// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_RCLAYER_HEADER
#define RAVL_RCLAYER_HEADER 1
//! author="Charles Galambos"
//! rcsid="$Id$"
//! docentry="Ravl.Core.Reference Counting"
//! lib=RavlCore
//! example=testRCLayer.cc

#include "Ravl/RCHandleV.hh"

namespace RavlN {
  enum RCLayerHandleT { RCLH_OWNER,RCLH_CALLBACK };
  
  //! userlevel=Develop
  //: Layered refrence counted body.
  // There are two classes of handles to a layered reference counted objects. Inferior handles
  // which just work like normal reference counted system. Owner handles operate on an
  // aditional counter (owners in RCLayerBodyC), then this counter drops to zero a method
  // ZeroOwners() is called which can be used to deconstruct the object and initiate the
  // deletion of the other handles.
  
  class RCLayerBodyC
    : public RCBodyVC
  {
  public:
    RCLayerBodyC()
    { ravl_atomic_set(&owners,0); }
    //: Default constructor.
    
    virtual void ZeroOwners();
    //: Called when owner handles drop to zero.
    
    void IncOwners() const
    { ravl_atomic_inc(&owners); }
    //: Increment owner reference counter.
    
    void DecOwners() {
      if(ravl_atomic_dec_and_test(&owners) != 0)
        ZeroOwners();
    }
    //: Decrement owner counter, if drops to zero call ZeroOwners().
    
    IntT OwnerHandles() const
    { return ravl_atomic_read(&owners); }
    //: Count the number of owner handles.
    
  protected:
    mutable ravl_atomic_t owners; // Count of owner handles
  };
  
  //! userlevel=Advanced
  //: Layered refrence counted handle.
  // There are two classes of handles to a layered reference counted objects. Inferior handles
  // which just work like normal reference counted system. Owner handles operate on an
  // aditional counter (owners in RCLayerBodyC), then this counter drops to zero a method
  // ZeroOwners() is called which can be used to deconstruct the object and initiate the
  // deletion of the other handles.
  
  template<class BodyT> 
  class RCLayerC 
    : private RCHandleVC<BodyT>
  {
  public:
    
    RCLayerC()
      : ownerHandle(false)
    {}
    //: Default constructor.
    
    RCLayerC(const RCLayerC<BodyT> &data)
      : RCHandleVC<BodyT>(data),
        ownerHandle(data.IsHandleOwner())
    {
      if(IsHandleOwner() && this->BodyPtr() != 0)
        this->BodyPtr()->IncOwners();      
    }
    //: Copy constructor.
    
    RCLayerC(BodyT &data,RCLayerHandleT handleType =RCLH_OWNER)
      : RCHandleVC<BodyT>(data),
        ownerHandle(handleType == RCLH_OWNER)
    {
      if(IsHandleOwner())
        data.IncOwners();
    }
    //: Constructor from a reference
    
    RCLayerC(const RCLayerC<BodyT> &data,RCLayerHandleT handleType)
      : RCHandleVC<BodyT>(data),
        ownerHandle(handleType == RCLH_OWNER)
    {
      if(IsHandleOwner() && this->BodyPtr() != 0)
        this->BodyPtr()->IncOwners();
    }
    //: Constructor from another handle and a handle type.
    
    RCLayerC(const BodyT *data,RCLayerHandleT handleType = RCLH_OWNER)
      : RCHandleVC<BodyT>(data),
        ownerHandle(ownerHandle == RCLH_OWNER)
    {
      if(IsHandleOwner() && data != 0)
        data->IncOwners();
    }
    //: Constructor from a pointer
    
    ~RCLayerC() {
      if(this->BodyPtr() != 0 && IsHandleOwner())
        this->BodyPtr()->DecOwners();
    }
    //: Destructor.
    
    const RCLayerC<BodyT> &operator=(const RCLayerC<BodyT> &oth) { 
      // Increment owners for incoming handle.
      if(oth.IsHandleOwner() && oth.BodyPtr() != 0)
        const_cast<BodyT *>(oth.BodyPtr())->IncOwners();
      // Decrement owners for old destination
      if(IsHandleOwner() && this->BodyPtr() != 0)
      this->BodyPtr()->DecOwners();
      ownerHandle = oth.IsHandleOwner();
      RCHandleVC<BodyT>::operator=(oth);
      return *this;
    }
    //: Assign handle.
    
    bool IsHandleOwner() const
    { return ownerHandle; }
    //: Is this a owner handle ?
    
    bool IsHandleCallback() const
    { return !ownerHandle; }
    //: Is this a callback handle ?
    
    bool IsValid() const
    { return RCHandleVC<BodyT>::IsValid(); }
    //: Is this a valid handle.
    
    void Invalidate() { 
      if(IsHandleOwner() && this->BodyPtr() != 0)
        this->BodyPtr()->DecOwners();      
      RCHandleVC<BodyT>::Invalidate();
    }
    //: Invalidate this handle.
    
    IntT OwnerHandles() const
    { return this->Body().OwnerHandles(); }
    //: Count the number of owner handles that currently exist.
    
    IntT References() const
    { return RCHandleVC<BodyT>::References(); }
    //: Get the number of referee
    
    BodyT *BodyPtr()
    { return RCHandleC<BodyT>::BodyPtr(); }
    //: Access body pointer.
    // Used in upcasting.
    
    const BodyT *BodyPtr() const
    { return RCHandleC<BodyT>::BodyPtr(); }
    //: Access body pointer.
    // Used in upcasting.
    
    static BodyT *BodyPtr(RCLayerC<BodyT> &bod)
    { return bod.BodyPtr(); }
    //: Access body point from a derived class.
    
    static const BodyT *BodyPtr(const RCLayerC<BodyT> &bod)
    { return bod.BodyPtr(); }
    //: Access body point from a derived class.
    
    bool operator==(const RCLayerC<BodyT> &data) const
    { return BodyPtr() == data.BodyPtr(); }
    //: Are these handles to the same object ?
    
    bool operator!=(const RCLayerC<BodyT> &data) const
    { return BodyPtr() != data.BodyPtr(); }
    //: Are these handles to different objects ?
    
  protected:
    BodyT &Body()
    { return RCHandleVC<BodyT>::Body(); }
    //: Access body.
    
    const BodyT &Body() const
    { return RCHandleVC<BodyT>::Body(); }
    //: Const acess to body.
    
  private:
    RCLayerC(const RCHandleC<BodyT> &handle)
      : RCHandleVC<BodyT>(handle),
        ownerHandle(false)
    { RavlAssert(0); }
    //: Base constructor.
    
    bool ownerHandle; // If true this is a owner
  };
}

#endif
