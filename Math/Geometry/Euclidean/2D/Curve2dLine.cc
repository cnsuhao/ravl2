//////////////////////////////////////////////////////
// Parametric Line.
// $Id$

#include "Ravl/Curve2dLine.hh"
#include "Ravl/IndexRange2d.hh"
//#include "Ravl/LinearS2.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  void Curve2dLineC::GetLimits(RealT &Low,RealT &High,const IndexRange2dC &Rect) const {
    Vector2dC unit = Tangent(0);
    RealT ux = fabs(unit.X());
    RealT uy = fabs(unit.Y());
    RealT x1,y1,x2,y2;
    if(ux > uy) {
      x1 = Rect.Origin().Row();
      y1 = ValueY(x1);
      x2 = Rect.End().Row();
      y2 = ValueY(x2);
    } else {
      y1 = Rect.Origin().Col();
      x1 = ValueX(y1);
      y2 = Rect.End().Col();
      x2 = ValueX(y2);    
    }
    Low = Closest(Point2dC(x1,y1));
    High = Closest(Point2dC(x2,y2));
    if(Low > High) {
      RealT Tmp = Low;
      Low = High;
      High = Tmp;
    }
  }
  
  ///////////////////////
  // Write GF file.
  
  bool Curve2dLineC::WriteGF(ostream &Out) const {
    // Write end points of line
    Out << (*this);
    return true;
  }
  
  ///////////////////////
  // Write GF file header.  
  
  bool Curve2dLineC::WriteGFHeader(ostream &Out) {
    Out << "lineABC ";
    return true;
  }
  
  ///////////////////////
  // Print to ostream.
  
  void Curve2dLineC::Print(ostream &out) const {
    out << "LineABC:" << ((const LineABC2dC &) *this);
  }
  
  ///////////////////////
  // Write line out to stream
  
  ostream & operator<<(ostream & outS, const Curve2dLineC & line) {
    outS << ((const LineABC2dC &) line);
    return outS;
  }
  
}
