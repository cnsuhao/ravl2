// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_REFCOUNTER_HH
#define RAVL_REFCOUNTER_HH
////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Reference Counting"
//! file="Ravl/Core/Base/HandleRefCounter.hh"
//! lib=RavlCore
//! userlevel=Default
//! author=""
//! date=""

#include "Ravl/RefCounter.hh"
#include "Ravl/Trigger.hh"

//: Ravl library namespace.

namespace RavlN {  
  
  class HandleRefCounterC;
  
  //! userlevel=Advanced
  //: Handle based reference counter.
  
  class HandleRefCounterBodyC
    : public RCBodyVC
  {
  public:
    HandleRefCounterBodyC()
      {}
    //: Default constructor.
    
    HandleRefCounterBodyC(const TriggerC &ntrig)
      : trig(ntrig)
      {}
    //: Constructor.
    
    virtual ~HandleRefCounterBodyC();
    //: Destructor.
    
  protected:
    TriggerC trig;
    friend class HandleRefCounterC;
  };
    
  //! userlevel=Normal
  //: Handle based reference counter.
  // The class RefCounterC is a reference counter which should be always
  // inherited if a class contains pointers to allocated memory and the 
  // memory is shared by several objects. All constructors, a destructor,
  // and an assigment operator must be modified in such class. The destructor
  // is not virtual, therefore the class should be inherited as private
  // or protected.
  // <p>
  // The RefCounterC class allocates its own memory separately from 
  // the memory of the object.
  
  class HandleRefCounterC 
    :  public RCHandleC<HandleRefCounterBodyC>
  {
  public:
    HandleRefCounterC()
      : RCHandleC<HandleRefCounterBodyC>(*new HandleRefCounterBodyC())
      {}
    //: Creates the reference counter.
    
    HandleRefCounterC(const TriggerC &ntrig)
      : RCHandleC<HandleRefCounterBodyC>(*new HandleRefCounterBodyC(ntrig))
      {}
    //: Creates the reference counter and initializes it.
    // 'func' is triggered when references of the object reach 0.
    
    inline
    void SetDestructionOp(const TriggerC &ntrig) {
      Body().trig = ntrig;
    }
    //: Set trigger to call on delete.
    
    inline UIntT References() const
      { return Body().References(); }
    //: Returns the number of references to this object.  

  };
  
  
   
}


#endif




