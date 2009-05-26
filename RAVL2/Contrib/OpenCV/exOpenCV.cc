#include "Ravl/Image/OpenCVConvert.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/IO.hh"


using namespace RavlN;
using namespace RavlImageN;

int main()
{
  ImageC<RealRGBValueC> src(100,200);
  src.Fill(RealRGBValueC(200,100,150));
  IplImage* im = 0;
  cout << "RAVL 2 CV: " << RavlImage2IplImage(src, im) << endl;
  ImageC<ByteRGBValueC> out;
  cout << "CV 2 RAVL: " << IplImage2RavlImage(im, out) << endl;
  cvReleaseImage(&im);
  Save("@X", out);
}
