// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDPENTITY_HEADER
#define RAVLDPENTITY_HEADER 1
////////////////////////////////////////////////////
//! userlevel=Develop
//! example=exDataProc.cc
//! file="Ravl/Core/IO/Entity.hh"
//! lib=RavlIO
//! author="Charles Galambos"
//! date="16/06/98"
//! docentry="Ravl.Core.Data Processing"
//! rcsid="$Id$"

#include "Ravl/RefCounter.hh"

namespace RavlN {
  //! userlevel=Develop
  //: Data processing entity body.
  
  class DPEntityBodyC 
    : public RCBodyVC
  {
  public:
    DPEntityBodyC() 
      {}
    //: Default constructor.
    
    DPEntityBodyC(const DPEntityBodyC &oth)
      : RCBodyVC (oth)
      {}
    //: Copy constructor.
    
    DPEntityBodyC(istream &in) 
      {}
    //: Stream constructor.
    
    virtual bool Save(ostream &out) const; 
    //: Save to ostream.  
    
    virtual RCBodyVC &Copy() const;
    //: Creat a copy of this object.
  };
  
  //! userlevel=Advanced
  //: Data processing entity.
  
  class DPEntityC 
    : public RCHandleC<DPEntityBodyC> 
  {
  public:
    DPEntityC(bool ) {}
    //: Default constructor.
    // This is explicit to avoid problems with 
    // virtual derived classes using the wrong constructor.
    
    DPEntityC(const DPEntityC &oth) 
      : RCHandleC<DPEntityBodyC>(oth)
      {}
    //: Copy constructor.
    
    DPEntityC(DPEntityBodyC &nbod) 
      : RCHandleC<DPEntityBodyC>(nbod)
      {}
    //: Constructor.

    DPEntityC(const RCAbstractC &abst);
    //: Constructor from an abstract handle.
    
    DPEntityC(istream &in);
    //: Load from stream using virtual constructor.
    
    inline const DPEntityC &operator= (const DPEntityC &dat) 
      { RCHandleC<DPEntityBodyC>::operator= (dat); return *this; }
    //: Assignment.
    
    inline DPEntityBodyC& Body() 
      { return RCHandleC<DPEntityBodyC>::Body(); }
    //: Access body.
    
    inline const DPEntityBodyC& Body() const
      { return RCHandleC<DPEntityBodyC>::Body(); }
    //: Access body.
    
    inline bool Save(ostream &out) const
      { return Body().Save(out); }
  };
  
  // Stream operators.
  
  inline istream &operator>>(istream &in,DPEntityC &obj) {
    obj = DPEntityC(in);
    return in;
  }
  
  inline ostream &operator<<(ostream &out,const DPEntityC &obj) {
    obj.Save(out);
    return out;
  }
  
}
#endif
