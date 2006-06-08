// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_REFCOUNTER_HEADER
#define RAVL_REFCOUNTER_HEADER 1
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.API.Core.Reference Counting"
//! file="Ravl/Core/Base/RefCounter.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Charles Galambos"
//! example=exRefCounter.cc

#include "Ravl/Types.hh"
#include "Ravl/Atomic.hh"
#include "Ravl/Exception.hh"
#include "Ravl/Assert.hh"
#include "Ravl/StdHash.hh"

#if RAVL_HAVE_ANSICPPHEADERS
#include <typeinfo>
#else
#include <typeinfo.h>
#endif

//: Ravl library namespace.

namespace RavlN {  
  
  class BinIStreamC;
  class BinOStreamC;
  
  enum CreateBodyFlagT { CreateBodyE };
  
  // Forward declarations.
  
  template<class BodyT> class RCHandleC;
  
  //! userlevel=Normal
  //: Base class for all reference counted objects
  // This holds a count of the number of handles that
  // are available for this object.
  
  class RCBodyC {
  public:
    ~RCBodyC();
    //: Destructor.
    
    UIntT References() const;
    //: Access count of handles open to this object.
    
    RCBodyC &Copy() const;
    //: Make copy of body.
    // This should be provided in derived classes.
    // this funtion will issue an assertion failure if called.
    
    RCBodyC &DeepCopy(UIntT levels = ((UIntT) -1)) const;
    //: Make a deep copy of body.
    // This should be provided in derived classes.
    // this funtion will issue an assertion failure if called.
    
    void IncRefCounter()
    { ravl_atomic_inc(&counter); }
    //: Increment reference counter.
    
    bool DecRefCounter()
    { return ravl_atomic_dec_and_test(&counter) != 0; }
    //: Decrement reference counter.
    
  protected:    
    RCBodyC() 
    { ravl_atomic_set(&counter,0); }
    //: Default constructor.
    // Creates a handle with 0 reference counts.
    
  private:
    mutable ravl_atomic_t counter;
  };
  
  template<class DataT> class SmartPtrC;
  
  //! userlevel=Normal
  //: Base class for handles to reference counter objects
  
  template<class BodyT>
  class RCHandleC {
  public:
    RCHandleC()
      : body(0)
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    RCHandleC(const RCHandleC<BodyT> &oth)
      : body(oth.body)
    { 
      if(body != 0)
	body->IncRefCounter(); 
    }
    //: Copy Constructor.
    // Creates a new reference to 'oth'
    
    RCHandleC(CreateBodyFlagT)
      : body(new BodyT())
    { body->IncRefCounter(); }
    //: Constructor.
    // creates a body class with its default constructor.
    
    RCHandleC(istream &is)
      : body(new BodyT())
    { 
      body->IncRefCounter(); 
      is >> *body;
    }
    //: Load body from stream.
    
    ~RCHandleC() {
      if(body == 0)
	return;
      if(body->DecRefCounter())
	delete body;
    }
    //: Destructor.
    // Decrement reference count, and delete object if it reaches zero.
    
    bool Save(ostream &out) const
    { out << *body; return true; }
    //: Save body to stream.
    
    const RCHandleC<BodyT> &operator=(const RCHandleC<BodyT> &oth) { 
      if(oth.body != 0)
	oth.body->IncRefCounter();
      if(body != 0) {
	if(body->DecRefCounter())
	  delete body;
      }
      body = oth.body;
      return *this;
    }
    //: Assign handle.

    RCHandleC<BodyT> DeepCopy(UIntT levels = ((UIntT) -1)) const
    { return RCHandleC<BodyT>(Body().DeepCopy(levels)); }
    //: Do a deep copy of the object.
    
    bool operator==(const RCHandleC<BodyT> &oth) const
    { return body == oth.body; }
    //: Are handles to the same object ?
    
    bool operator!=(const RCHandleC<BodyT> &oth) const
    { return body != oth.body; }
    //: Are handles to different objects ?
    
    UIntT Hash() const
	{ return StdHash(reinterpret_cast<void *>(body)); }
    //: Default hash function.
    // This hashes on the address of the body.
    
    bool IsValid() const
    { return body != 0; }
    //: Test if this is a valid handle. 

    void Invalidate() { 
      if(body == 0) return ;
      if(body->DecRefCounter())
	delete body;
      body = 0;
    }
    //: Invalidate this handle.
    // Unattaches the body from the handle.
    
    template<class DT>
    bool IsHandleType(const DT &/*dummy*/) const
    { return (dynamic_cast<const DT *>(body) != 0); }
    //: Is handle of given type ?
    
    template<class DT>
    void CheckHandleType(const DT &dummy) const RAVL_THROW(ExceptionErrorCastC) { 
      if(!IsHandleType(dummy))
	throw ExceptionErrorCastC("RCHandleC::CheckRCHandleType(), Failed.",
				  typeid(Body()),
				  typeid(DT));
    }
    //: Check handle type. Throw an expception if not.
    
    void *VoidPtr() const
    { return body; }
    //: Access unique address for this object.
    // Used in PointerManagerC.  Not for general use
    // this interface may changed in future releases.
    
  private:
    BodyT *body;
    
  protected:
    RCHandleC(BodyT &bod)
      : body(&bod)
    { body->IncRefCounter(); }
    //: Body constructor.
    
    RCHandleC(const BodyT *bod)
      : body(const_cast<BodyT *>(bod))
    { if(body != 0) body->IncRefCounter(); }
    //: Body base constructor.
    // This is used where the body may be a null ptr, such as
    // in the virtual constructor after a failed load.
    
    RCHandleC(RCBodyC &bod)
      : body(&static_cast<BodyT &>(bod))
    { body->IncRefCounter(); }
    //: Body base constructor.
    
    BodyT &Body() { 
      RAVL_PARANOID(RavlAssertMsg(IsValid(),"Attempt to access invalid handle. "));
      return *body; 
    }
    //: Access body of object.
    
    const BodyT &Body() const { 
      RAVL_PARANOID(RavlAssertMsg(IsValid(),"Attempt to access invalid handle. "));
      return *body; 
    }
    //: Constant access to body of object.
    
    BodyT *BodyPtr()
    { return body; }
    //: Access body pointer.
    // Used in upcasting.
    
    const BodyT *BodyPtr() const
    { return body; }
    //: Access body pointer.
    // Used in upcasting.
    
    static BodyT *BodyPtr(RCHandleC<BodyT> &bod)
    { return bod.body; }
    //: Access body point from a derived class.
    
    static const BodyT *BodyPtr(const RCHandleC<BodyT> &bod)
    { return bod.body; }
    //: Access body point from a derived class.
    
  public:
    UIntT References() const
    { return Body().References(); }
    //: Find the number of references to the body of this object.
    
    friend class SmartPtrC<BodyT>; 
  };
  
  
  istream &operator>>(istream &,RCBodyC &obj);
  //: Input body.
  // No-op.
  
  ostream &operator<<(ostream &,const RCBodyC &obj);
  //: Output body.
  // No-op.
    
  template<class BodyT>
  ostream &operator<<(ostream &strm,const RCHandleC<BodyT> &obj) { 
    obj.Save(strm); 
    return strm;
  }
  //: Write a handle to a stream.
  
  template<class BodyT>
  istream &operator>>(istream &strm,RCHandleC<BodyT> &obj) {
    obj = RCHandleC<BodyT>(strm);
    return strm;
  }
  //: Read a handle from a stream.
  
}

#endif
