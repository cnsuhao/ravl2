// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLYUVVALUE_HEADER
#define RAVLYUVVALUE_HEADER
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/YUVValue.hh"
//! lib=RavlImage
//! userlevel=Default
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/TFVector.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: YUV Pixel base class.
  
  template<class CompT>
  class YUVValueC 
    : public TFVectorC<CompT,3>
  {
  public:
    YUVValueC()
      {}
    //: Default constructor.
    // Creates an undefined value.

    YUVValueC(const CompT &y,const CompT &u,const CompT &v) {
      data[0] =y;
      data[1] =u;
      data[2] =v;
    }
    //: Construct from component values.

    template<class OCompT>
    YUVValueC(YUVValueC<OCompT> &oth) {
      data[0] = oth.Y();
      data[1] = oth.U();
      data[2] = oth.V();
    }
    //: Construct from another component type.
    
    inline const CompT & Y() const
      { return data[0]; }
    // Returns the level of the Y component.
    
    inline const CompT & U() const
      { return data[1]; }
    // Returns the level of the U component.
    
    inline const CompT & V() const
      { return data[2]; }
    // Returns the level of the V component.
    
    inline CompT & Y() 
      { return data[0]; }
    // Returns the level of the Y component.
    
    inline CompT & U()
      { return data[1]; }
    // Returns the level of the U component.
    
    inline CompT & V()
      { return data[2]; }
    // Returns the level of the V component.

  };
}

#endif
