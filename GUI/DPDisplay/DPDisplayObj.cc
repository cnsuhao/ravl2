///////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/DPDisplayObj.hh"
#include "Ravl/TypeName.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {

  static TypeNameC type1(typeid(DPDisplayObjC),"DPDisplayObjC");  
  
  //: Default constructor.
  
  DPDisplayObjBodyC::DPDisplayObjBodyC()
  {}

  //: Draw object to canvas.
  
  bool DPDisplayObjBodyC::Draw(DPDisplayViewBodyC &canvas) {
    RavlAssertMsg(0,"DPDisplayObjBodyC::Draw(RawCanvasC &), Abstract method called. ");    
    return true;
  }
  
  //: Find bounding box for object.

  IndexRange2dC DPDisplayObjBodyC::Frame() const {
    RavlAssertMsg(0,"DPDisplayObjBodyC::Frame(), Abstract method called. ");
    return IndexRange2dC(0,0,0,0);
  }

  //: Query a point in the display.
  // Return true if point is within object.
  
  bool DPDisplayObjBodyC::Query(const Vector2dC &,StringC &) {
    ONDEBUG(cerr << "DPDisplayObjBodyC::Query(), Called. \n");
    return false;
  }

}
