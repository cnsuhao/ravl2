// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/Designer.hh"

namespace RavlN {
  
  VectorC DesignerBodyC::Paramiters() {
    RavlAssertMsg(0,"DesignerBodyC::Paramiters(), Abstract method called. \n");
    return VectorC();
  }
  //: Get the current paramiters.
  
  VectorC DesignerBodyC::Paramiters(const VectorC &params) {
    RavlAssertMsg(0,"DesignerBodyC::Paramiters(const VectorC &), Abstract method called. \n");
    return params;
  }
  //: Set the current paramiters.
  // Returns the current paramiters, which may not be exactly those
  // set in 'params', but will be the closest legal values.

}
