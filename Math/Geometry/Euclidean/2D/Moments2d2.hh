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
#include "Ravl/Point2d.hh"
#include "Ravl/Vector2d.hh"

namespace RavlN {

  class Matrix2dC;
  
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

    inline Moments2d2C(RealT nm00,RealT nm10,RealT nm01,RealT nm20,RealT nm11,RealT nm02)
      : m00(nm00), m10(nm10), m01(nm01), m20(nm20), m11(nm11), m02(nm02)
    {}
    //: Constructor from a set of values.
    
    inline void AddPixel (const Index2dC &pxl);
    //: Adds a pixel to the object and updates sums.
    
    inline void AddPixel (const Point2dC &pxl,RealT weight = 1);
    //: Adds a position with a weight to the object and updates sums.
    
    const Moments2d2C &operator+=(const Index2dC &pxl)
    { AddPixel(pxl); return *this; }
    //: Add pixel to set.
    
    const Moments2d2C &operator+=(const Point2dC &point)
    { AddPixel(point); return *this; }
    //: Add pixel to set.
    
    Vector2dC PrincipalAxis() const;
    //: Calculate the size of the principle axis.
    // It returns the new values for M02 and M20, 
    // the largest is the first element of the vector.
    
    static RealT Elongatedness(const Vector2dC &principalAxis) {
      RealT sumM = principalAxis[0] + principalAxis[1];
      return (sumM!=0) ? Abs((principalAxis[0] - principalAxis[1]) / sumM) : 0 ;
    }
    //: Returns the ratio of the difference and the sum of moments m02 and m20.
    // The value 0 means that objects is a symmetrical object,
    // the value 1 corresponds to a one-dimensional object. 
    
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
    
    Matrix2dC Covariance() const;
    //: Return the covariance matrix.
    
    Point2dC Centroid()
    { return Point2dC(CentroidX(),CentroidY()); }
    //: Calculate the centroid.
    
    Moments2d2C operator+(const Moments2d2C &m) const
    { return Moments2d2C(m00 + m.M00(),m10 + m.M10(),m01 + m.M01(),m20 + m.M20(),m11 + m.M11(),m02 + m.M02()); }
    //: Add to sets of moments together.

    Moments2d2C operator-(const Moments2d2C &m) const
    { return Moments2d2C(m00 - m.M00(),m10 - m.M10(),m01 - m.M01(),m20 - m.M20(),m11 - m.M11(),m02 - m.M02()); }
    //: Subtract one set of moments from another.
    
    const Moments2d2C &operator+=(const Moments2d2C &m);
    //: Add to sets of moments to this one.
    
    const Moments2d2C &operator-=(const Moments2d2C &m);
    //: Subtract a set of moments to this one.
    
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
    RealT a = pxl[0];
    RealT b = pxl[1];
    
    m00++;
    m01 += b;
    m10 += a;
    m11 += a*b;
    m02 += b*b;
    m20 += a*a;
  }
  
  //: Adds a position with a weight to the object and updates sums.
  
  void Moments2d2C::AddPixel (const Point2dC &pxl,RealT weight) {
    RealT a = pxl[0];
    RealT b = pxl[1];
    
    m00 += weight;
    RealT wa = a * weight;
    RealT wb = b * weight;
    m01 += wb;
    m10 += wa;
    m11 += a*wb;
    m02 += b*wb;
    m20 += a*wa;
  }
  
  inline
  const Moments2d2C &Moments2d2C::operator+=(const Moments2d2C &m) {
    m00 += m.M00();
    m10 += m.M10();
    m01 += m.M01();
    m20 += m.M20(); 
    m11 += m.M11();
    m02 += m.M02();
    return *this;
  }
  
  inline
  const Moments2d2C &Moments2d2C::operator-=(const Moments2d2C &m) {
    m00 -= m.M00();
    m10 -= m.M10();
    m01 -= m.M01();
    m20 -= m.M20(); 
    m11 -= m.M11();
    m02 -= m.M02();
    return *this;
  }

}
#endif
