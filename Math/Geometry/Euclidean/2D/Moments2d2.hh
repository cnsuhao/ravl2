// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_MOMENTS2D2_HEDAER
#define RAVL_MOMENTS2D2_HEDAER 1
////////////////////////////////////////////////////////////////////////////
//! file="amma/Image/Region/Mom012d2.hh"
//! lib=RavlMath
//! date="6/8/1995"
//! author="Radek Marik"
//! docentry="Image.Image Processing.Region Model"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Geometry.2D"

#include "Ravl/Types.hh"
#include "Ravl/Index2d.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: The first two  moments in 2D space
  
  class Moments2d2C
  {    
  public:
    inline Moments2d2C()
      : m00(0.0), m10(0.0), m01(0.0), m20(0.0), m11(0.0), m02(0.0)
    {}
    //: Default constructor
    // Creates the moment object with all moments set to be zero.
    
    inline void AddPixel (const Index2dC &pxl);
    //: Adds a pixel to the object and updates sums.
  
    inline const Moments2d2C & Centerlize();
    //: Recomputes the moments according to the centroid.
    
    const Moments2d2C & ToPrincipalAxis();
    //: Recomputes the moments according to the principal axis.
    // It is assumed that input moments are centerlized
    
    inline RealT Elongatedness() const;
    //: Returns the ratio of the difference and the sum of moments m02 and m20.
    // The value 0 means that objects is a symmetrical object,
    // the value 1 corresponds to a one-dimensional object. Is is assumed
    // that input moments are centeralized and rotated to the principal
    // axes.
    
    inline const Moments2d2C & Moments2d2() const
    { return *this; }
    //: Access moments.
    
    inline Moments2d2C & Moments2d2()
    { return *this; }
    //: Access moments.
    
    inline RealT M00() const
    { return m00; }
    //: Access 00 component.
    
    inline RealT M10() const
    { return m10; }
    //: Access 10 component.
    
    inline RealT M01() const
    { return m01; }
    //: Access 01 component.
    
    inline RealT M20() const
    { return m20; }
    //: Access 20 component.
    
    inline RealT M11() const
    { return m11; }
    //: Access 11 component.
    
    inline RealT M02() const
    { return m02; }
    //: Access 02 component.
    
    inline RealT & M00()
    { return m00; }
    //: Access 00 component.
    
    inline RealT & M10()
    { return m10; }
    //: Access 10 component.
   
    inline RealT & M01()
    { return m01; }
    //: Access 01 component.
    
    inline RealT & M20()
    { return m20; }
    //: Access 20 component.
    
    inline RealT & M11()
    { return m11; }
    //: Access 11 component.
    
    inline RealT & M02()
    { return m02; }
    //: Access 02 component.
    
    inline RealT Area() const
    { return m00; }
    //: Returns the moment m00, ie the area of the 2 dimensional object.
    
    inline RealT CentroidX() const
    { return M10()/M00(); }
    //: Returns the x co-ordinate of the centroid.
    // The M00 moment must be different 0.
  
    inline RealT CentroidY() const
    { return M01()/M00(); }
    //: Returns the y co-ordinate of the centroid.
    // The M00 moment must be different 0.
    
    
  private:
    RealT m00;
    RealT m10;
    RealT m01;
    RealT m20;
    RealT m11;
    RealT m02;
  
    friend istream & operator>>(istream & is, Moments2d2C & mom);
  };

  ostream &
  operator<<(ostream & os, const  Moments2d2C & mom);

  istream &
  operator>>(istream & is, Moments2d2C & mom);

}

#include "Ravl/Math.hh" //::Abs() 

namespace RavlN {
  
  inline
  void Moments2d2C::AddPixel (const Index2dC &pxl) {
    RealT row = pxl.Col();
    RealT col = pxl.Row();
    
    m00++;
    m01 += row;
    m10 += col;
    m11 += row*col;
    m02 += row*row;
    m20 += col*col;
  }
  
  inline 
  const Moments2d2C & Moments2d2C::Centerlize() {
    m20 -= m10*m10/m00;
    m02 -= m01*m01/m00;
    m11 -= m10*m01/m00;
    return *this; 
  }
  
  inline 
  RealT Moments2d2C::Elongatedness() const {
    RealT sumM = M20() + M02();
    return (sumM!=0) ? Abs((M20() - M02()) / sumM) : 0 ;
  }

}
#endif
