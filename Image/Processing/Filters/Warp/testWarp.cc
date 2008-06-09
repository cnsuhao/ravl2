#include "Ravl/Image/WarpAffine.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/IO.hh"

using namespace RavlN;
using namespace RavlImageN;

int testWarpAffine();


int main () {
  int ln;
  if((ln = testWarpAffine()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  return 0;
}

int testWarpAffine() {
  ImageC<RealT> im(ImageRectangleC(Index2dC(0,0), 8), 0);
  im[0][0] = 1;
  im[1][2] = 1;
  ImageC<RealT> out;
  Affine2dC M;

  //unit transformation; origin @ t.l. of pixel
  M  = Affine2dC(Vector2dC(1,1),0,Vector2dC(0,0)); 
  WarpAffineC<RealT> warp(im.Frame().Expand(-1), M);
  out = warp.Apply(im);
  for (Array2dIter2C<RealT,RealT>i(out,im,out.Frame()); i; ++i) if (Abs(i.Data1()-i.Data2()) > 1.0e-12)  return __LINE__;

  //unit transformation; origin @ centre of pixel
  warp.SetMidPixelCorrection(false);
  out = warp.Apply(im);
  for (Array2dIter2C<RealT,RealT>i(out,im,out.Frame()); i; ++i) if (Abs(i.Data1()-i.Data2()) > 1.0e-12)  return __LINE__;

  // rotate by +pi/2
  M  = Affine2dC(Vector2dC(1,1),RavlConstN::pi/2,Vector2dC(0,0)); //rotate by pi/2
  warp = WarpAffineC<RealT>(im.Frame().Expand(-1), M);
  warp.SetMidPixelCorrection(true);
  out = warp.Apply(im);
  if (Abs(out[2][-2] - 1) > 1.0e-12)  return __LINE__;

  // rotate by +pi/2
  M  = Affine2dC(Vector2dC(1,1),RavlConstN::pi/2,Vector2dC(0,0)); //rotate by pi/2
  warp = WarpAffineC<RealT>(im.Frame().Expand(-1), M);
  warp.SetMidPixelCorrection(false);
  out = warp.Apply(im);
  if (Abs(out[2][-1] - 1) > 1.0e-12)  return __LINE__;

  return 0;
}
