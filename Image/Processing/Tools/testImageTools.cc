
#include "Ravl/Image/Rectangle2dIter.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Image/Image.hh"

using namespace RavlN;
using namespace RavlImageN;

int testRectangle2dIter();

int main() {
  int ln;
  if((ln = testRectangle2dIter()) != 0) {
    cerr << "Error line numner '" << ln << "'\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

int testRectangle2dIter() {
  ImageRectangleC rect1(0,6,0,5);
  ImageRectangleC rect2(5,5);
  ImageC<int> data(rect1);
  data.Fill(1);
  cerr << "Area=" << rect2.Area() << "\n";
  int rects = 0;
  for(Rectangle2dIterC it(rect1,rect2);it;it++) {
    if(it.Window().Area() != rect2.Area()) return __LINE__;
    int x = 0;
    for(Array2dIterC<int> itx(data,it.Window());itx;itx++)
      x += *itx;
    cerr << "x=" << x << "\n";
    if(x != it.Window().Area()) return __LINE__;
    rects++;
  }
  if(rects != 6)
    return __LINE__;
  return 0;
}
