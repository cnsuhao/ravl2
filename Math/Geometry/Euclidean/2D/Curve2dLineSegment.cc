//////////////////////////////////////////////////////
// Parametric Line Segment.
// $Id$

#include "Ravl/Curve2dLineSegment.hh"
#include "Ravl/Assert.hh"
#include "Ravl/SArray1d.hh"
#include <iostream.h>

namespace RavlN {

  ostream &operator<<(ostream &strm,const Curve2dLineSegmentC &dat) {
    strm << dat.StartPnt() << ' ' << dat.EndPnt();
    return strm;
  }
  //: Stream output.
  
  istream &operator>>(istream &strm,Curve2dLineSegmentC &dat) {
    Point2dC p1,p2;
    strm >> p1 >> p2;
    dat = Curve2dLineSegmentC (p1,p2);
    return strm;
  }
  //: Stream input.
  
  //////////////////////////
  // Make a line that fits points.
  
  RealT Curve2dLineSegmentC::FitLSQ(const SArray1dC<Point2dC> &Pnts) {
    if(Pnts.Size() < 1) {
      Ends[0] = 0;
      Ends[1] = 0;
      return 0;
    }
    RealT err = Curve2dLineC::FitLSQ(Pnts);
    Ends[0] = Closest(Pnts[0]);
    Ends[1] = Closest(Pnts[Pnts.Size()-1]);
    return err;
  }
  
  //////////////////////////////////
  // This is designed to be used to match lines.
  // It returns the sum of the distances between the
  // closest end points.
  
  RealT Curve2dLineSegmentC::Compair(Curve2dLineSegmentC &oth) {
    Point2dC a1 = StartPnt();
    Point2dC a2 = EndPnt();
    Point2dC b1 = oth.StartPnt();
    Point2dC b2 = oth.EndPnt();
    RealT d1 = a1.EuclidDistance(b1) + a2.EuclidDistance(b2);
    RealT d2 = a1.EuclidDistance(b2) + a2.EuclidDistance(b1);
    return Min(d1,d2);
  }
  
  ///////////////////////
    
  // Write GF file.
    
  bool Curve2dLineSegmentC::WriteGF(ostream &Out) const {
    // Write end points of line
    Point2dC Pnt0(Point(Ends[0]));
    Point2dC Pnt1(Point(Ends[1]));
    Out << Pnt0.Y() << " " << Pnt0.X() << " ";
    Out << Pnt1.Y() << " " << Pnt1.X() << " ";
    return true;
  }
  
  /////////////////////////
  // Write GF file.  
  
  bool Curve2dLineSegmentC::WriteGFHeader(ostream &Out) {
    Out << "line ";
    return true;
  }
}
