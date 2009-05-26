// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_RCABSTRACT_HEADER
#define RAVL_RCABSTRACT_HEADER 1
//////////////////////////////////////////////////
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.API.Core.Reference Counting"
//! file="Ravl/Core/Base/RCAbstract.hh"
//! lib=RavlCore
//! rcsid="$Id$"
//! date="28/05/1998"

#include "Ravl/RCBodyV.hh"

#if RAVL_HAVE_ANSICPPHEADERS
#include <typeinfo>
#else
#include <typeinfo.h>
#endif 

namespace RavlN {
  //: Abstract handle class for any object derived from 
  //: RCBodyVC.
  // See RCWrapC<> for example.
  
  class RCAbstractC 
    : public RCHandleC<RCBodyVC> 
  {
  public:  
    RCAbstractC() {}
    //: Default constructor.
    
    RCAbstractC(const RCAbstractC &oth)
      : RCHandleC<RCBodyVC>(oth)
    {}
    //: Copy constructor.
    
    RCAbstractC(RCBodyVC &oth)
      : RCHandleC<RCBodyVC>(oth)
    {}
    //: Constructor.
    
    RCAbstractC(istream &in)
      : RCHandleC<RCBodyVC>(*new RCBodyVC())
    {}
    //: Constructor.
    
    inline RCAbstractC Copy() const;
    //: Copy object contents.
    // FIXME :- Use RTTI to check copy is full.
    
    inline bool Save(ostream &out) const
    { return Body().Save(out); }
    //: Save to stream.
    
    const type_info &BodyType() const 
    { return typeid(Body()); }
    //: Type of object held.
    
    void Dump(ostream &out) const;
    //: Dump info about handle

    RCBodyVC &Body()
    { return RCHandleC<RCBodyVC>::Body(); }
    //: Access body.

    const RCBodyVC &Body() const
    { return RCHandleC<RCBodyVC>::Body(); }
    //: Access body.

    RCBodyVC *BodyPtr()
    { return RCHandleC<RCBodyVC>::BodyPtr(); }
    //: Access body.

    const RCBodyVC *BodyPtr() const
    { return RCHandleC<RCBodyVC>::BodyPtr(); }
    //: Access body.
    
  };
  
  //////////////////////////////////////////////////////
  
  inline 
  RCAbstractC 
  RCAbstractC::Copy() const  {
    if(!IsValid()) // Check it a valid handle !
      return RCAbstractC();
    return RCAbstractC(Body().Copy()); 
  }
}
#endif
