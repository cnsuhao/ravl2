
#include "Ravl/Image/SegmentExtrema.hh"
#include "Ravl/Image/DrawFrame.hh"
#include "Ravl/IO.hh"

using namespace RavlImageN;

int testSegmentExtrema();

int main() {
  int ln;
  if((ln = testSegmentExtrema()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  return 0;
}

int testSegmentExtrema() {
  ImageC<ByteT> img(100,100);
  img.Fill(196);
  DrawFrame(img,(ByteT) 128,IndexRange2dC(10,90,10,90),true);
  DrawFrame(img,(ByteT) 196,IndexRange2dC(20,30,20,30),true);
  DrawFrame(img,(ByteT) 64,IndexRange2dC(20,30,40,50),true);
  DrawFrame(img,(ByteT) 196,IndexRange2dC(40,50,40,50),true);
  SegmentExtremaC<ByteT> segExt(5);
  DListC<BoundaryC> bnd = segExt.Apply(img);
  DListC<ImageC<IntT> > segs = segExt.ApplyMask(img);
  cerr << "Bounds=" << bnd.Size() << " " << segs.Size() << "\n";

  for(DLIterC<ImageC<IntT> > it(segs);it;it++) {
    IndexRange2dC frame = it->Frame();
    frame.ClipBy(img.Frame());
    for(Array2dIter2C<ByteT,IntT> iit(img,*it,frame);iit;iit++) 
      if(iit.Data2() != 0) iit.Data1() = 255;
  }
  Save("@X",img);
  
  return 0;
}
