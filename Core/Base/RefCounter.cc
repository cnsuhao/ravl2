// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/RefCounter.hh"
#include "Ravl/Assert.hh"

namespace RavlN {
  
  /// RCBodyC //////////////////////////////////////////
  
  RCBodyC::~RCBodyC() {
    RavlAssert(ravl_atomic_read(&counter) == 0);
  }
  //: Destructor.

  //: Access count of handles open to this object.
  
  UIntT RCBodyC::References() const
  { return ravl_atomic_read(&counter); }
  
  //: Make copy of body.
  // This should be provided in derived classes.
  // this funtion will issue an assertion failure if called.

  RCBodyC &RCBodyC::Copy() const {
    RavlAssert(0);
    return *new RCBodyC();
  }
  
  istream &operator>>(istream &strm,RCBodyC &obj) {
    return strm;
  }
  //: Input body.
  // No-op.
  
  ostream &operator<<(ostream &strm,const RCBodyC &obj) {
    return strm;
  }
  //: Output body.
  // No-op.

  /// RCBodyVC //////////////////////////////////////////
  
  RCBodyVC::~RCBodyVC()
  {}
  //: Destructor.
  
  RCBodyVC &RCBodyVC::Copy() const {
    RavlAssert(0);
    return *new RCBodyVC();
  }
  //: Make copy of body.
  
  istream &operator>>(istream &strm,RCBodyVC &obj) {
    return strm;
  }
  //: Input virtual body.
  // No-op.

  ostream &operator<<(ostream &strm,const RCBodyVC &obj) {
    return strm;
  }
  //: Output virtual body.
  // No-op.

}
