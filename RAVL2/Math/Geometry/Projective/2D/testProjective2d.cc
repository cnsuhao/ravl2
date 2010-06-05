#include "Ravl/PLine2d.hh"
#include "Ravl/PPoint2d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/Stream.hh"
#include "Ravl/RealRange2d.hh"
#include "Ravl/LinePP2d.hh"

using namespace RavlN;

int testPLine2d();

int main() {
  int lineNo;

  if((lineNo = testPLine2d()) != 0) {
    cerr << "Test failed on line " << lineNo << "\n";
    return 1;
  }
}


int testPLine2d() {
  PLine2dC a(Point2dC(1.0,0.0),Point2dC(0.0,sqrt(3.0)));
  PLine2dC b(Point2dC(0.0,0.0),Point2dC(sqrt(3.0),1.0));

  Point2dC p = a.Intersection(b).Point2d();
  if (p.EuclidDistance(Point2dC(0.75,0.25*sqrt(3.0))) > 1.0e-6) return __LINE__;

  p = a.ClosestPointToOrigin().Point2d();
  if (p.EuclidDistance(Point2dC(0.75,0.25*sqrt(3.0))) > 1.0e-6) return __LINE__;

  if (Abs(a.Distance(Point2dC(0.0,0.0)) - 0.5*sqrt(3.0)) > 1.0e-6) return __LINE__;

  IndexRange2dC rect(-10,-1,2,3);
  LinePP2dC result;
  if (a.ClipBy(result, rect)) return __LINE__;

  rect = IndexRange2dC(0,1,0,2);
  if (!a.ClipBy(result, rect)) return __LINE__;
  if (result.P1().EuclidDistance(Point2dC(0.0,sqrt(3.0))) > 1.0e-6) return __LINE__;
  if (result.P2().EuclidDistance(Point2dC(1.0,0.0)) > 1.0e-6) return __LINE__;

  return 0;
}
