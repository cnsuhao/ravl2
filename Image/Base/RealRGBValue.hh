// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLREALRGBVALUE_HEADER
#define RAVLREALRGBVALUE_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/RealRGBValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/Image/RGBValue.hh"

namespace RavlN {
  
  //: Real RGB value class.
  
  class RealRGBValueC
    : public RGBValueC<RealT>
  {
  public:
    RealRGBValueC()
      {}
    //: Default constructor.
    // creates an undefined RGB pixel.
    
    RealRGBValueC(RealT r,RealT g, RealT b)
      : RGBValueC<RealT>(r,g,b)
      {}
    //: Construct from components.
    
    RealRGBValueC(const RGBValueC<RealT> &oth)
      : RGBValueC<RealT>(oth)
      {}
    //: Default constructor.
    // creates an undefined RGB pixel.
    
  };

}

#endif
