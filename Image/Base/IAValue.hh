// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIAVALUE_HEADER
#define RAVLIAVALUE_HEADER 1
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/IAValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/TFVector.hh"

namespace RavlImageN {
  using namespace RavlN;
  
  //: Image & Alpha Pixel.
  
  template<class CompT>
  class IAValueC 
    : public TFVectorC<CompT,2>
  {
  public:
    IAValueC()
      {}
    //: Default constructor.
    // Creates an undefined value.
    
    IAValueC(const CompT &i,const CompT &a) {
      data[0] =i;
      data[1] =a;
    }
    //: Construct from component values.
    
    inline const CompT & Intensity() const
      { return data[0]; }
    // Returns the level of the intensity component.
    
    inline const CompT & Alpha() const
      { return data[1]; }
    // Returns the level of the alpha component.

    inline CompT & Intensity()
      { return data[0]; }
    // Returns the level of the intensity component.
    
    inline CompT & Alpha()
      { return data[1]; }
    // Returns the level of the alpha component.
    

  };
}

#endif
