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
//! docentry="Ravl.Core.Reference Counting"
//! file="Ravl/Core/Base/RefCounter.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Charles Galambos"
//! example=exRefCounter.cc

#include "Ravl/Types.hh"
#include "Ravl/Atomic.hh"
#include "Ravl/Exception.hh"
#include "Ravl/Assert.hh"

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
  template<class BodyT> ostream &operator<<(ostream &strm,const RCHandleC<BodyT> &obj);
  template<class BodyT> istream &operator>>(istream &strm,RCHandleC<BodyT> &obj);
  
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
    
    ~RCHandleC() {
      if(body == 0)
	return;
      if(body->DecRefCounter())
	delete body;
    }
    //: Destructor.
    // Decrement reference count, and delete object if it reaches zero.
    
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
    { return ((UIntT) body) >> 2; }
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
    { return (dynamic_cast<const DT *>(&Body()) != 0); }
    //: Is handle of given type ?

    template<class DT>
    void CheckHandleType(const DT &dummy) const throw(ExceptionErrorCastC) { 
      if(!IsHandleType(dummy))
	throw ExceptionErrorCastC("RCHandleC::CheckRCHandleType(), Failed.",
				  typeid(Body()),
				  typeid(DT));
    }
    //: Check handle type. Throw an expception if not.
    
  private:
    BodyT *body;
    
  protected:
    RCHandleC(BodyT &bod)
      : body(&bod)
    { body->IncRefCounter(); }
    //: Body constructor.
    
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
    
  public:
    UIntT References() const
    { return Body().References(); }
    //: Find the number of references to the body of this object.
    
    
#if RAVL_NEW_ANSI_CXX_DRAFT
    friend ostream &operator<< <>(ostream &strm,const RCHandleC<BodyT> &obj);
    friend istream &operator>> <>(istream &strm,RCHandleC<BodyT> &obj);
#else
    friend ostream &operator<<(ostream &strm,const RCHandleC<BodyT> &obj);
    friend istream &operator>>(istream &strm,RCHandleC<BodyT> &obj);
#endif
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
    strm << obj.Body(); 
    return strm;
  }
  //: Write a handle to a stream.

  template<class BodyT>
  istream &operator>>(istream &strm,RCHandleC<BodyT> &obj) {
    if(!obj.IsValid())
      obj = RCHandleC<BodyT>(CreateBodyE);
    strm >> obj.Body(); 
    return strm;
  }
  //: Read a handle from a stream.
  
}

#endif
