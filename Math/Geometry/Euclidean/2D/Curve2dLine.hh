#ifndef RAVL_CURVE2DLINE_HEADER
#define RAVL_CURVE2DLINE_HEADER 1
//////////////////////////////////////////////////////
//! docentry="Ravl.Geometry.2D"
//! userlevel=Normal
//! rcsid="$Id$"
//! file="amma/Geometry/AnGeo2/PCLine.hh"
//! lib=Mag2
//! author="Charles Galambos"
//! date="26/08/98"

#include "Ravl/LineABC2d.hh"
#include "Ravl/StdConst.hh"
//#include "Ravl/Angle.hh"

namespace RavlN {
  class IndexRange2dC;
  template<class DataT> class SArray1dC;
  
  //: Parametric Line.
  // This class modifies the line equation so it always
  // has a unit normal.
  
  class Curve2dLineC : public LineABC2dC {
  public:
    inline Curve2dLineC()
    {}
    //: Default constructor.
    
    inline Curve2dLineC(const SArray1dC<Point2dC> &Pnts)
    { FitLSQ(Pnts); }
    //: Make a line that best fits the given points.
    
    inline Curve2dLineC(Point2dC p1,Point2dC p2)
      : LineABC2dC(p1,p2)
    { MakeUnitNormal(); }
    //: Make a line passing through two pixels.
    
    inline Curve2dLineC(const LineABC2dC &Line)
      : LineABC2dC(Line)
    { MakeUnitNormal(); }
    //: From a line.
    
    inline Curve2dLineC(RealT row,RealT theta) {
      theta += RavlConstN::pi/2;
      Vector2dC ang(Cos(theta),Sin(theta)); // Direction of line.
      ((LineABC2dC &) (*this)) = LineABC2dC(Point2dC(row,0),ang);
      MakeUnitNormal();
    }
    
    //: From Y axis crossing point and angle.
    
    inline Curve2dLineC(Point2dC mid,Vector2dC dir)
      : LineABC2dC(mid,dir)
    { MakeUnitNormal(); }
    //: From a point and a direction.
    
    inline Curve2dLineC(RealT a,RealT b,RealT c)
      : LineABC2dC(a,b,c)
    {}
    //: From paramiters.
    
    RealT FitLSQ(const SArray1dC<Point2dC> &Pnts);
    //: Make a line that fits points.
    
    inline RealT Fit(const SArray1dC<Point2dC> &Pnts) 
    { return FitLSQ(Pnts); }
    //: Default fitting method.
    
    RealT AssessFit(const SArray1dC<Point2dC> &Pnts);
    //: Measure error for fit.
    
#if 0
    AngleC Angle() 
    { return AngleC(Normal().Perpendicular().Angle(),StdConstC::pi*2); };
    //: Get angle of line.
#endif
    
    inline const Curve2dLineC &operator=(const LineABC2dC &It) {
      ((LineABC2dC &) (*this)) = It;
      MakeUnitNormal();
      return *this;
    }
    //: Assign from a plain LineABC.
    
    inline Vector2dC Tangent(RealT /*p*/) const 
    { return Normal().Perpendicular(); }
    //: Tangent to curve at p
    
    inline Vector2dC UnitTangent(RealT /*p*/) const 
    { return Normal().Perpendicular(); }
    //: Tangent to curve at p
    
    inline Vector2dC UnitNormal() const
    { return Normal(); }
    //: Get the unit normal.
    
    inline Point2dC Point(RealT p) const {
      return (Normal().Perpendicular()*p)-(Normal()*C()); 
    }
    
    //: Localion of curve at p
    
    inline RealT Closest(Point2dC Pnt) const;
    //: Parametric value of closest point on curve to Pnt.
    
    void GetLimits(RealT &Low,RealT &High,const IndexRange2dC &Rect) const;
    //: Get limits of paramiter if shape is within Rect.
    
    inline char *GetName() const { return "Curve2dLine"; }
    //: Name of primitive.
    
    inline IntT CodeSize() const { return 30; }
    //: Estimated bits to code primitive.
    
    bool WriteGF(ostream &Out) const;
    //: Write GF file.
    
    static bool WriteGFHeader(ostream &Out);
    //: Write GF file.  
    
    void Print(ostream &out) const;
    //: Print to ostream.
  };
  
  ostream & operator<<(ostream & outS, const Curve2dLineC & index);
  // Sends the Curve2dLineC into the output stream.
  
  inline RealT Curve2dLineC::Closest(Point2dC Pnt) const { 
    // FIXME :- Could this be simplified ??
    Point2dC Where = Projection(Pnt); // Get a point actualy on the line.
    if(fabs(B()) > fabs(A()))
      return ((Where.X() + (A() * C())) / -B());
    return ((Where.Y() + (B() * C())) / A());  
  }
  
}


#endif
