#include "Ravl/Image/GaussConvolve2d.hh"
#include "Ravl/RandomGauss.hh"
#include "Ravl/IO.hh"
#include "Ravl/Polygon2d.hh"
#include "Ravl/Image/WarpAffine.hh"
#include "Ravl/Image/LMSOpticFlow.hh"

using namespace RavlN;
using namespace RavlImageN;

int testRegisterAffineOpticFlow();

int main() {
  int ln;
  if((ln = testRegisterAffineOpticFlow()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  return 0;
}

int testRegisterAffineOpticFlow() {
  cerr << "testRegisterAffineOpticFlow(), Called. \n";
  // create image
  ImageC<RealT> image(100,100);
  RandomGaussC randomGauss;
  // fill image with random values
  for (Array2dIterC<RealT> it(image); it; it++)
    *it = randomGauss.Generate();
  // and smooth it
  GaussConvolve2dC<RealT> gaussConvolve2d(5);
  image = gaussConvolve2d.Apply(image);
//  RavlN::Save("@X", image);
  // define a window into the image which is the region of interest
  IndexRange2dC idealRange(25,75,25,75);
  ImageC<RealT> patch(image,idealRange);
  Polygon2dC idealOutline = RealRange2dC(idealRange);
  // randomly perturb the corners
  Polygon2dC corruptedOutline;
  for (DLIterC<Point2dC> it(idealOutline); it; it++)
    corruptedOutline.InsLast(*it + Point2dC(randomGauss.Generate()*1,randomGauss.Generate()*1));
  cerr << idealOutline << endl << corruptedOutline << endl;
  // and get a transform from the ideal outline to the corrupted outline
  Affine2dC transformToScene = FitAffine(idealOutline, corruptedOutline);

  // now we are going to create an alternate scene by warping the image
  ImageC<RealT> warpedScene(patch.Frame());
  WarpAffineC<RealT,RealT,RealT> warp(patch.Frame(),transformToScene);
  warp.Apply(image,warpedScene);
//  RavlN::Save("@X:scene", warpedScene);
  // now use LMSOpticFlow to calculate the motion from patch to warped scene
  LMSOpticFlowC opticFlow;
  opticFlow.Estimate(PairC<ImageC<RealT> >(patch,warpedScene));
  // for what it is worth, draw the motion image
  ImageC<ByteYUVValueC> motionImage;
  opticFlow.DrawMotion(patch,motionImage);
//  RavlN::Save("@X:motion", motionImage);
  // calculate where each point in patch has moved to in warped scene, creating
  // two point sets, origin and destination. use them to calculate an affine
  // transform which should describe the global motion
  DListC<Point2dC> startPoints,endPoints;
  for (Array2dIterC<Vector2dC> it(opticFlow.Motion()); it; it++) {
    Index2dC index = it.Index();
    Point2dC point (index.Row(),index.Col());
    startPoints.InsLast(point);
    endPoints.InsLast(point + *it);
// note that it seems that the vectors are all awfully small! I would expect motions
// closer to 1 in magnitude.
//cerr << *it << " ";
  }
  Affine2dC correction = FitAffine(startPoints,endPoints);
  // now apply the correction to the original transform to hopefully correct it
  transformToScene = transformToScene * correction;
  cerr << "The following should be the unit transform\n";
  cerr << transformToScene << endl;
  // note that transformToScene should ideally now be the unit transform or thereabouts!
  if (transformToScene.Translation().SumOfSqr() > 0.1)
    return __LINE__;
  if ((transformToScene.SRMatrix() - Matrix2dC::I()).SumOfSqr() > 0.1)
    return __LINE__;
  return 0;
}
