//! rcsid="$Id$"
//! author="Charles Galambos"

#include "Ravl/RCHandleV.hh"
#include "Ravl/Stream.hh"
#include "Ravl/BinStream.hh"

#if RAVL_HAVE_ANSICPPHEADERS
#include <typeinfo>
#else
#include <typeinfo.h>
#endif

namespace RavlN {
  /// RCBodyVC //////////////////////////////////////////
  
  //: Destructor.
  
  RCBodyVC::~RCBodyVC()
  {}
  
  const char *(*HandleNameMap)(const type_info &type) = 0;
  
  //: Save to stream out.
  
  bool RCBodyVC::Save(ostream &out) const {
    RavlAssert(HandleNameMap != 0);
    out << HandleNameMap(typeid(*this));
    return true;
  }
  
  //: Save to stream out.
  
  bool RCBodyVC::Save(BinOStreamC &out) const {
    RavlAssert(HandleNameMap != 0);
    out << HandleNameMap(typeid(*this));
    return true; 
  }
  
  //: Save to binary stream.
  
  RCBodyVC &RCBodyVC::Copy() const {
    RavlAssert(0);
    return *new RCBodyVC();
  }
  //: Make copy of body.
  
  RCBodyC &RCBodyVC::DeepCopy(UIntT levels) const {
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

};
