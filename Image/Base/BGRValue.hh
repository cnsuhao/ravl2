// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_BGRVALUE_HEADER
#define RAVLIMAGE_BGRVALUE_HEADER 1
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! docentry="Ravl.Images.Pixel Types"
//! userlevel=Normal
//! lib=RavlImage
//! file="Ravl/Image/Base/BGRValue.hh"

#include "Ravl/Image/RGBValue.hh"

namespace RavlImageN {
  
  using namespace RavlN;
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using RavlN::BinIStreamC;
  using RavlN::BinOStreamC;
  using RavlN::TFVectorC;
#endif


  //: BGRA Pixel.
  
  template<class CompT>
  class BGRValueC
    : public TFVectorC<CompT,3>
  {
  public:
    // Constructors, copies, assigment, setting, and destructor
    // --------------------------------------------------------
    
    inline BGRValueC(CompT r = 0,
		     CompT g = 0,
		     CompT b = 0) {
      data[2] = r;
      data[1] = g;
      data[0] = b;
    }
    //: Constructs a colour from four colour components. 
    // Note: the arguments are given in the order r,g,b,a.
    
    BGRValueC(const RGBValueC<CompT> & rgb) {
      data[2] = rgb.Red();
      data[1] = rgb.Green();
      data[0] = rgb.Blue();
    }
    // Creates the colour from the triple RGB colour 'rgb' and the fourth
    // colour component 'x'.
    
    inline
    RGBValueC<CompT> RGB() const
    { return RGBValueC<CompT>(Red(),Green(),Blue()); }
    //: Get a RGB pixel value.
    
    inline const CompT & Red() const
    { return data[2]; }
    // Returns the level of the red component.
    
    inline const CompT & Green() const
    { return data[1]; }
    // Returns the level of the green component.
    
    inline const CompT & Blue() const
    { return data[0]; }
    // Returns the level of the blue component.
    
    inline CompT & Red()
    { return data[2]; }
    // Access to the red component.
    
    inline CompT & Green()
    { return data[1]; }
    // Access to the green component.
    
    inline CompT & Blue()
    { return data[0]; }
    // Access to the blue component.
    
  };
  
}
#endif
