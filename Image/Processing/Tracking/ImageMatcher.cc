// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! file="Ravl/Image/Processing/Tracking/ImageMatcher.cc"
//! lib=RavlImageProc

#include "Ravl/Image/ImageMatcher.hh"
#include "Ravl/FitHomog2dPoints.hh"
#include "Ravl/EvaluateNumInliers.hh"
#include "Ravl/ObservationManager.hh"
#include "Ravl/StateVectorHomog2d.hh"
#include "Ravl/ObservationHomog2dPoint.hh"
#include "Ravl/Ransac.hh"
#include "Ravl/LevenbergMarquardt.hh"

#define DODEBUG 0
#if DODEBUG
#include "Ravl/IO.hh"
#include "Ravl/Image/ImgIO.hh"
#include "Ravl/Image/DrawCross.hh"
#include "Ravl/Image/DrawFrame.hh"
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {
  using namespace RavlN;

  //: Constructor for mosaic builder
  ImageMatcherC::ImageMatcherC(const ImageC<ByteT> &nimageTemplate,
			       IntT ncropT, IntT ncropB,
			       IntT ncropL, IntT ncropR,
			       IntT matchPatchSize,
			       IntT matchSearchSize,
			       IntT matchThreshold,
			       RealT nzhomogTemplate,
			       RealT nzhomogImage)
    : cropT(ncropT), cropB(ncropB), cropL(ncropL), cropR(ncropR),
      zhomogTemplate(nzhomogTemplate),
      zhomogImage(nzhomogImage),
      imageTemplate(nimageTemplate),
      tracker(matchPatchSize,matchSearchSize,matchThreshold)
  {
  }
  
  //: Matches an image to the template.
  bool ImageMatcherC::Apply(const ImageC<ByteT> &img, Projection2dC &proj)
  {
    // set frame
    IndexRange2dC rect = IndexRange2dC(img.Frame());

    // adjust frame for cropping region
    rect.TRow() += cropT; rect.BRow() -= cropB;
    rect.LCol() += cropL; rect.RCol() -= cropR;

    // crop image and convert to grey level
    ImageC<ByteT> croppedImg = ImageC<ByteT>(img,rect);

    // compute corner matches to mosaic
    DListC<PairC<Point2dC> > matchList = tracker.TrackImage(imageTemplate,croppedImg,proj);

    // set corner error covariance matrix to 2x2 identity
    MatrixRSC epos(2);
    epos[0][0] = 1;
    epos[1][1] = 1;
    epos[1][0] = 0;
    epos[0][1] = 0;

    // RANSAC objects
    FitHomog2dPointsC fitHomog2d(zhomogImage,zhomogTemplate);
    EvaluateNumInliersC evalInliers(1.0,2.0);

    // Generate an observation set for tracked points.
    DListC<ObservationC> obsList;
    for(DLIterC<PairC<Point2dC> > it(matchList);it;it++) {
      const Point2dC& loc1=it->A();
      const Point2dC& loc2=it->B();
#if 0
      cout << "A=" << loc1 << " B=" << loc2 << endl;
#endif
      obsList.InsLast(ObservationHomog2dPointC(Vector2dC(loc1[0],loc1[1]),epos,
                                               Vector2dC(loc2[0],loc2[1]),epos));
    }

    ObservationListManagerC obsListManager(obsList);
    RansacC ransac(obsListManager,fitHomog2d,evalInliers);

    for(int i = 0;i <100;i++)
      ransac.ProcessSample(8);

    // carry on optimising solution if Ransac succeeding
    if(!ransac.GetSolution().IsValid())
      // failed to find a solution
      return false;

    // select observations compatible with solution
    DListC<ObservationC> compatibleObsList = evalInliers.CompatibleObservations(ransac.GetSolution(),obsList);

    // initialise Levenberg-Marquardt algorithm
    StateVectorHomog2dC sv = ransac.GetSolution();
    LevenbergMarquardtC lm = LevenbergMarquardtC(sv, compatibleObsList);

    cout << "2D homography fitting: Initial residual=" << lm.GetResidual() << endl;
    cout << "Selected " << compatibleObsList.Size() << " observations using RANSAC" << endl;
    VectorC x = lm.SolutionVector();
    x /= x[8];
    try {
      // apply iterations
      RealT lambda = 100.0;
      for ( int i = 0; i < 4; i++ ) {
        bool accepted = lm.Iteration(compatibleObsList, lambda);
        if ( accepted )
          // iteration succeeded in reducing the residual
          lambda /= 10.0;
        else
          // iteration failed to reduce the residual
          lambda *= 10.0;

        cout << " Accepted=" << accepted << " Residual=" << lm.GetResidual();
        cout << " DOF=" << 2*compatibleObsList.Size()-8 << endl;
      }
    } catch(...) {
      // Failed to find a solution.
      cerr << "Caught exception from LevenbergMarquardtC. \n";
      return false;
    }

    // get solution homography
    sv = lm.GetSolution();
    Matrix3dC P = sv.GetHomog();
    P /= P[2][2];

    cout << "Solution: (" << P[0][0] << " " << P[0][1] << " " << P[0][2] << ")" << endl;
    cout << "          (" << P[1][0] << " " << P[1][1] << " " << P[1][2] << ")" << endl;
    cout << "          (" << P[2][0] << " " << P[2][1] << " " << P[2][2] << ")" << endl;

    // update 2D projection from image onto template
    proj = Projection2dC(P.Inverse(),zhomogImage,zhomogTemplate);
    return true;
  }
}
