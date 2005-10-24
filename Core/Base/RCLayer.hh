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
  enum RCLayerHandleT { RCLH_SUPERIOR,RCLH_INFERIOR };
  
  //! userlevel=Develop
  //: Layered refrence counted body.
  // There are two classes of handles to a layered reference counted objects. Inferior handles
  // which just work like normal reference counted system. Superior handles operate on an
  // aditional counter (superiors in RCLayerBodyC), then this counter drops to zero a method
  // ZeroSuperiors() is called which can be used to deconstruct the object and initiate the
  // deletion of the other handles.
  
  class RCLayerBodyC
    : public RCBodyVC
  {
  public:
    RCLayerBodyC()
    { ravl_atomic_set(&superiors,0); }
    //: Default constructor.
    
    virtual void ZeroSuperiors();
    //: Called when superior handles drop to zero.
    
    void IncSuperiors()
    { ravl_atomic_inc(&superiors); }
    //: Increment superior reference counter.
    
    void DecSuperiors() {
      if(ravl_atomic_dec_and_test(&superiors) != 0)
        ZeroSuperiors();
    }
    //: Decrement superior counter, if drops to zero call ZeroSuperiors().
    
    IntT Superiors() const
    { return ravl_atomic_read(&superiors); }
    //: Count the number of superior handles.
    
  protected:
    mutable ravl_atomic_t superiors; // Count of superior handles
  };
  
  //! userlevel=Advanced
  //: Layered refrence counted handle.
  // There are two classes of handles to a layered reference counted objects. Inferior handles
  // which just work like normal reference counted system. Superior handles operate on an
  // aditional counter (superiors in RCLayerBodyC), then this counter drops to zero a method
  // ZeroSuperiors() is called which can be used to deconstruct the object and initiate the
  // deletion of the other handles.
  
  template<class BodyT> 
  class RCLayerC 
    : private RCHandleC<BodyT>
  {
  public:
    
    RCLayerC()
      : superiorHandle(false)
    {}
    //: Default constructor.
    
    RCLayerC(const RCLayerC<BodyT> &data)
      : RCHandleC<BodyT>(data),
        superiorHandle(data.IsSuperior())
    {
      if(IsSuperior() && this->BodyPtr() != 0)
        this->BodyPtr()->IncSuperiors();      
    }
    //: Copy constructor.
    
    RCLayerC(BodyT &data,RCLayerHandleT handleType)
      : RCHandleC<BodyT>(data),
        superiorHandle(handleType == RCLH_SUPERIOR)
    {
      if(IsSuperior())
        data.IncSuperiors();
    }
    //: Constructor from a reference
    
    RCLayerC(const RCLayerC<BodyT> &data,RCLayerHandleT handleType)
      : RCHandleC<BodyT>(data),
        superiorHandle(handleType == RCLH_SUPERIOR)
    {
      if(IsSuperior() && this->BodyPtr() != 0)
        this->BodyPtr()->IncSuperiors();
    }
    //: Constructor from another handle and a handle type.
    
    RCLayerC(const BodyT *data,RCLayerHandleT handleType)
      : RCHandleC<BodyT>(data),
        superiorHandle(superiorHandle == RCLH_SUPERIOR)
    {
      if(IsSuperior() && data != 0)
        data->IncSuperiors();
    }
    //: Constructor from a pointer
    
    ~RCLayerC() {
      if(this->BodyPtr() != 0 && IsSuperior())
        this->BodyPtr()->DecSuperiors();
    }
    //: Destructor.
    
    const RCLayerC<BodyT> &operator=(const RCLayerC<BodyT> &oth) { 
      // Increment superiors for incoming handle.
      if(oth.IsSuperior() && oth.BodyPtr() != 0)
        const_cast<BodyT *>(oth.BodyPtr())->IncSuperiors();
      // Decrement superiors for old destination
      if(IsSuperior() && this->BodyPtr() != 0)
      this->BodyPtr()->DecSuperiors();
      superiorHandle = oth.IsSuperior();
      RCHandleC<BodyT>::operator=(oth);
      return *this;
    }
    //: Assign handle.

    bool IsSuperior() const
    { return superiorHandle; }
    //: Is this a superior handle ?
    
    bool IsValid() const
    { return RCHandleC<BodyT>::IsValid(); }
    //: Is this a valid handle.
    
    void Invalidate() { 
      if(IsSuperior() && this->BodyPtr() != 0)
        this->BodyPtr()->DecSuperiors();      
      RCHandleC<BodyT>::Invalidate();
    }
    //: Invalidate this handle.
    
    IntT Superiors() const
    { return this->Body().Superiors(); }
    //: Count the number of superior handles that currently exist.
  
    IntT References() const
    { return RCHandleC<BodyT>::References(); }
    //: Get the number of referee
    
  protected:
  
  private:
    RCLayerC(const RCHandleC<BodyT> &handle)
      : RCHandleC<BodyT>(handle),
        superiorHandle(false)
    { RavlAssert(0); }
    //: Base constructor.
    
    bool superiorHandle; // If true this is a superior
  };
}

#endif
