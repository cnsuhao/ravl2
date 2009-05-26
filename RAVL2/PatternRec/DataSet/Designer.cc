// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/Designer.cc"

#include "Ravl/PatternRec/Designer.hh"

namespace RavlN {

  //: Load from stream.
  
  DesignerBodyC::DesignerBodyC(istream &strm)
    : RCBodyVC(strm)
  {}
  
  //: Load from binary stream.
  
  DesignerBodyC::DesignerBodyC(BinIStreamC &strm)
    : RCBodyVC(strm)
  {}
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignerBodyC::Save (ostream &out) const 
  { return RCBodyVC::Save(out); }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignerBodyC::Save (BinOStreamC &out) const 
  { return RCBodyVC::Save(out); }
  
  VectorC DesignerBodyC::Parameters() {
    RavlAssertMsg(0,"DesignerBodyC::Parameters(), Abstract method called. \n");
    return VectorC();
  }
  //: Get the current paramiters.
  
  VectorC DesignerBodyC::Parameters(const VectorC &params) {
    RavlAssertMsg(0,"DesignerBodyC::Parameters(const VectorC &), Abstract method called. \n");
    return params;
  }
  //: Set the current paramiters.
  // Returns the current paramiters, which may not be exactly those
  // set in 'params', but will be the closest legal values.
  
  ////////////////////////////////////////////////////////////////////
  
  //: Load from stream.
  
  DesignerC::DesignerC(istream &strm)
    : RCHandleVC<DesignerBodyC>(RAVL_VIRTUALCONSTRUCTOR(strm,DesignerBodyC))
  {}
  
  //: Load from binary stream.
  
  DesignerC::DesignerC(BinIStreamC &strm)
    : RCHandleVC<DesignerBodyC>(RAVL_VIRTUALCONSTRUCTOR(strm,DesignerBodyC))
  {}

  
}
