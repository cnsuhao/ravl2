// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLRGBAVALUE_HEADER
#define RAVLRGBAVALUE_HEADER
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/RGBAValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/TFVector.hh"
#include "Ravl/Image/RGBValue.hh"

namespace RavlImageN {
  
  //: RGBA Pixel.
  
  template<class CompT>
  class RGBAValueC 
    : public TFVectorC<CompT,4>
  {
  public:
    RGBAValueC()
      {}
    //: Default constructor.
    // Creates an undefined value.
    
    RGBAValueC(const CompT &r,const CompT &g,const CompT &b,const CompT &a = CompT()) {
      data[0] =r;
      data[1] =g;
      data[2] =b;
      data[3] =a;
    }
    //: Construct from component values.
    
    template<class OCompT>
    RGBAValueC(const RGBAValueC<OCompT> &oth) {
      data[0] = oth.Red();
      data[1] = oth.Green();
      data[2] = oth.Blue();
      data[3] = oth.Alpha();
    }
    //: Construct from another component type.
    
    template<class OCompT>
    RGBAValueC(RGBValueC<OCompT> &oth,const CompT &alpha = CompT()) {
      data[0] = oth.Red();
      data[1] = oth.Green();
      data[2] = oth.Blue();
      data[3] = alpha;
    }
    //: Construct from another 3 rgb pixel.
    
    inline const CompT & Red() const
      { return data[0]; }
    // Returns the level of the red component.
    
    inline const CompT & Green() const
      { return data[1]; }
    // Returns the level of the green component.
    
    inline const CompT & Blue() const
      { return data[2]; }
    // Returns the level of the blue component.

    inline const CompT & Alpha() const
      { return data[3]; }
    // Returns the level of the alpha component.
    
    inline CompT & Red() 
      { return data[0]; }
    // Returns the level of the red component.
    
    inline CompT & Green()
      { return data[1]; }
    // Returns the level of the green component.
    
    inline CompT & Blue()
      { return data[2]; }
    // Returns the level of the blue component.

    inline CompT & Alpha()
      { return data[3]; }
    // Returns the level of the alpha component.

  };
}

#endif
