

#include "Ravl/Image/CornerDetectorHarris.hh"
#include "Ravl/Option.hh"
#include "Ravl/Image/DrawFrame.hh"
#include "Ravl/IO.hh"

using namespace RavlImageN;

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  int threshold = opt.Int("t",20,"Threshold. ");
  int w = opt.Int("w",3,"width of filter mask. ");
  StringC inf = opt.String("","test.ppm","Input image. ");
  StringC outf = opt.String("","out.ppm","Output image. ");
  opt.Check();
  
  // Setup corner detector.
  
  CornerDetectorHarrisC harris(threshold,w);
  
  // Load an image.
  
  ImageC<ByteT> img;
  if(!Load(inf,img)) {
    cerr << "Failed to load image '" << inf << "'\n";
    return 1;
  }
  
  // Find the corners.
  
  DListC<CornerC> corners = harris.Apply(img);
  
  // Draw boxes around the corners.
  
  ByteT val = 255;
  for(DLIterC<CornerC> it(corners);it;it++) {
    IndexRange2dC rect(it->Location(),5,5);
    DrawFrame(img,val,rect);
  }
  
  // Save image to a file.
  
  if(!Save(outf,img)) {
    cerr << "Failed to save image '" << inf << "'\n";
    return 1;
  }
  
  return 0;
}
