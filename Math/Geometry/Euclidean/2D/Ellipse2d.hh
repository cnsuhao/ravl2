// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ELLIPSE2D_HEADER
#define RAVL_ELLIPSE2D_HEADER 1
//! author="Charles Galambos"
//! docentry="Ravl.Math.Geometry.2D"
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/Point2d.hh"
#include "Ravl/Affine2d.hh"
#include "Ravl/Math.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Ellipse .
  
  class Ellipse2dC {
  public:
    Ellipse2dC()
    {}
    //: Default constructor.
    
    Ellipse2dC(const Affine2dC &np)
      : p(p)
    {}
    //: Construct from affine transform from unit circle centered on the origin
    //!param: np - Transform from unit circle centered on the origin
    
    Point2dC Point(RealT angle)
    { return p * Point2dC(Sin(angle),Cos(angle)); }
    //: Compute point on ellipse.
    
    const Affine2dC &Projection() const
    { return p; }
    //: Access as projection from unit circle centered on the origin
    
    inline Point2dC Centre() const
    { return p.Translation(); }
    //: Centre of the ellipse.
    
  protected:    
    Affine2dC p; // Projection from unit circle.
  };
  
  ostream &operator<<(ostream &s,const Ellipse2dC &obj);
  //: Write ellipse to text stream.
  
  istream &operator>>(istream &s,Ellipse2dC &obj);
  //: Read ellipse from text stream.
  
  BinOStreamC &operator<<(BinOStreamC &s,const Ellipse2dC &obj);
  //: Write ellipse to binary stream.
  
  BinIStreamC &operator>>(BinIStreamC &s,Ellipse2dC &obj);
  //: Read ellipse from binary stream.
  
}


#endif
