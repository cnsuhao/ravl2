

#include "Ravl/Boundary.hh"
#include "Ravl/Stream.hh"

using namespace RavlN;

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

int testBoundry();
int testEdge();

int main() {
  int ln;
  if((ln = testEdge()) != 0) {
    cerr << "Test failed at line " << ln << "\n";
    return 1;
  }
  if((ln = testBoundry()) != 0) {
    cerr << "Test failed at line " << ln << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

int testEdge() {
  EdgeC edge(Index2dC(5,6),CR_DOWN);
  Index2dC at = edge.RPixel();
  // Go around a pixel clockwise.
  ONDEBUG(cerr << "iAt=" << at << "\n");
  for(int i = 0;i < 5;i++) {
    edge.Begin() = edge.End();
    edge.TurnClock();
    ONDEBUG(cerr << "At=" << edge.RPixel() << " Code:" << edge.Code() << "\n");
    //if(at == edge.RPixel()) return __LINE__;
  }
  // Go around a pixel counter clockwise.
  edge = EdgeC(Index2dC(5,6),CR_DOWN);
  at = edge.LPixel();  
  ONDEBUG(cerr << "iAt=" << at << "\n");
  for(int i = 0;i < 5;i++) {
    edge.Begin() = edge.End();
    edge.TurnCClock();
    ONDEBUG(cerr << "At=" << edge.LPixel() << " Code:" << edge.Code() << "\n");
    if(at != edge.LPixel()) return __LINE__;
  }
  return 0;
}

int testBoundry() {
  IndexRange2dC rect(IndexRangeC(1,3),IndexRangeC(2,4));
  BoundaryC bnd(rect,true);
  //cout << "Bounds:\n " << bnd << "\n";
  if(bnd.Size() != 12) return __LINE__;
  ONDEBUG(cout << "Area=" << bnd.Area() << "\n");
  if(bnd.Area() != - (IntT) rect.Area()) return __LINE__;
  bnd.BReverse();
  if(bnd.Area() != - (IntT) rect.Area()) return __LINE__;  
  bnd.Invert();
  ONDEBUG(cout << "RArea=" << bnd.Area() << "\n");
  if(bnd.Area() != (IntT) rect.Area()) return __LINE__;
  
  IndexRange2dC bb = bnd.BoundingBox();
  ONDEBUG(cerr << "Bounding box=" << bb << "\n");
  if(bb != rect) return __LINE__;
  
  return 0;
}


