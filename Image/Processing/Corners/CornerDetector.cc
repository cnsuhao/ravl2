////////////////////////////////////////////////////////////////
//! rcsid="$Id$"


#include "Ravl/Image/CornerDetector.hh"

namespace RavlImageN {

  //: Default constructor.
  
  CornerDetectorBodyC::CornerDetectorBodyC()
  {}
  
  //: Get a list of corners from 'img'
  
  DListC<CornerC> CornerDetectorBodyC::Apply(const ImageC<ByteT> &img) {
    DListC<CornerC> ret;
    RavlAssertMsg(0,"CornerDetectorBodyC::Apply(), Abstract method called. ");
    return ret;
  }
  
}
