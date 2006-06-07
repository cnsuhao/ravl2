// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlDPDisplay
//! file="Ravl/GUI/DPDisplay/DPDisplayObj.cc"

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

  //: Save to a file.
  
  bool DPDisplayObjBodyC::Save(const StringC &str) const {
    ONDEBUG(cerr << "DPDisplayObjBodyC::Save(), Called. \n");
    return false;
  }

  BinOStreamC &operator<<(BinOStreamC &strm,const DPDisplayObjC &obj) {
    RavlAssertMsg(0,"not implemented");
    return strm;
  }
  
  //: Read from binary stream.
  // NOT IMPLEMENTED.
  
  BinIStreamC &operator>>(BinIStreamC &strm,DPDisplayObjC &obj) {
    RavlAssertMsg(0,"not implemented");
    return strm;
  }

  //: Write to stream.
  // NOT IMPLEMENTED.
  
  ostream &operator<<(ostream &strm,const DPDisplayObjC  &obj) {
    RavlAssertMsg(0,"not implemented");
    return strm;
  }

  //: Read from stream.
  // NOT IMPLEMENTED.

  istream &operator>>(istream &strm,DPDisplayObjC  &obj) {
    RavlAssertMsg(0,"not implemented");
    return strm;
  }

}
