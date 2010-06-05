#include "Ravl/String.hh"
#include "Ravl/Image/WarpAffine.hh"
#include "Ravl/Image/WarpScale2d.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/OS/Date.hh"

using namespace RavlN; 
using namespace RavlImageN;

int Test1() {
  printf("Preparing array\n");
  //create image
  const int imgSize = 2048;
  ImageC<float> img(imgSize, imgSize);
  float val = 0.f;
  for(Array2dIterC<float> it(img);it;it++) {
    *it = val++;
  }

  int numIter = 5;
  printf("Testing...\n");
  for(float scale = 0.1; scale <= 2; scale += 0.1) {
    DateC start = DateC::NowLocal();
    for(int i = 0; i < numIter; i++) {
      ImageC<float> res;
      WarpScaleBilinear(img, Vector2dC(scale,scale), res);
    }
    RealT time = DateC::NowLocal().Double() - start.Double();
    long int numPixels = imgSize / scale * imgSize  / scale * numIter;
    printf("scale:%4.1f   time:%6.3f   iters:%3i   numPixels:%10li  speed:%6.4f\n", scale, float(time), numIter, numPixels, float(time/numPixels*1000000.));
    if(time < 5)
      numIter *= 2;
  }

  return 0;
}


int Test2() {
  printf("Test2\n");
  //create image
  ImageC<float> img(16, 16);
  img.Fill(0.);

  for(SizeT r = 4; r < 8; r++) {
    for(SizeT c = 4; c < 8; c++) {
      img[r][c] = 1;
    }
  }
  /*for(SizeT r = 0; r < 16; r++) {
    for(SizeT c = 0; c < 16; c++) {
      printf("%3g ", img[r][c]);
    }
    printf("\n");
  }*/

  Vector2dC scale(1.1,1.1);

  ImageC<float> res1(10, 10);
  WarpScaleBilinear(img, scale, res1);

  Affine2dC tr(scale, 0, RavlN::Vector2dC(0, 0));
  //cout << "transform:" << tr << endl;

  WarpAffineC<float, float, float, PixelMixerAssignC<float, float>, SampleBilinearC<float, float> >
                       warp(ImageRectangleC(10, 10), tr);
  warp.SetMidPixelCorrection(false);

  ImageC<float> res2;
  warp.Apply(img, res2);

  /*for(SizeT r = 0; r < 10; r++) {
    for(SizeT c = 0; c < 10; c++) {
      printf("%6g ", res1[r][c]);
    }
    printf("\n");
  }*/

  /*printf("\n");
  for(SizeT r = 0; r < 10; r++) {
    for(SizeT c = 0; c < 10; c++) {
      printf("%6g ", res2[r][c]);
    }
    printf("\n");
  }*/

  //printf("\n");
  for(SizeT r = 0; r < 10; r++) {
    for(SizeT c = 0; c < 10; c++) {
      //printf("%6g ", res1[r][c] - res2[r][c]);
      if(fabs(res1[r][c] - res2[r][c]) > 1e-6) {
        cerr << "Error at " << r << "  " << c << endl;
        return 1;
      }
    }
    //printf("\n");
  }

  return 0;
}


int main(int argc, char **argv)
{
  if(Test1() > 0) {
    cerr << "Error in test 1\n";
    return 1;
  }

  if(Test2() > 0) {
    cerr << "Error in test 2\n";
    return 1;
  }

  return 0;
}


