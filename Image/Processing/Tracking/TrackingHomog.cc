// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include "Ravl/Image/TrackingHomog.hh"
#include "Ravl/IO.hh"
#include "Ravl/Image/ImgIO.hh"
#include "Ravl/Ransac.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/ObservationHomog2dPoint.hh"
#include "Ravl/LevenbergMarquardt.hh"
#include "Ravl/ObservationManager.hh"
#include "Ravl/StateVectorHomog2d.hh"
//! rcsid="$Id: TrackingHomog.cc 7508 2010-02-11 15:00:10Z ees1wc $"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Tracking/TrackingHomog.cc"

namespace RavlImageN {


  TrackingHomogBodyC::TrackingHomogBodyC(bool nVerbose)
    : tracker(30,7,20,17,8,25,1),
      zhomog(100), fitHomog2d(zhomog,zhomog), // 100 is default projective scale
      epos(MatrixRSC::Identity(2)), // set corner error covariance matrix to 2x2 identity
      evalInliers(1.0,2.0),
      verbose(nVerbose)
  {}


  bool TrackingHomogBodyC::SetMask(const StringC& fileName) {
    if (!Load(fileName, mask)) {
      cerr << "Failed to load file: " << fileName << endl;
      return false;
    }
    return true;
  }


  Projection2dC TrackingHomogBodyC::Apply(const ImageC<ByteT> &img) {
    // Apply tracker to image.
    corners = tracker.Apply(img);
    // Generate an observation set for tracked points.
    DListC<ObservationC> obsList;
    for(HashIterC<UIntT,PointTrackC> it(corners);it;it++) {
      //      cout << "Confidence: " << it->Confidence() << endl;
      if(it->Confidence() < 0.1)
	continue; // Filter out points we haven't got recent info on.
      PointTrackC lat;
      if(!last.Lookup(it->ID(),lat))
	continue; // Matching point not found.
      
      const Point2dC& loc1=lat.Location();
      const Point2dC& loc2=it->Location();
      if (mask.IsEmpty() || (mask.Contains(loc1) && mask[Index2dC(loc1)])) {
	obsList.InsLast(ObservationHomog2dPointC(
            Vector2dC(loc1[0],loc1[1]),epos,Vector2dC(loc2[0],loc2[1]),epos));
      }
    }
    
    last = corners;

    ObservationListManagerC obsListManager(obsList);
    RansacC ransac(obsListManager,fitHomog2d,evalInliers);

    for(int i = 0;i <100;i++) {
      try {
	ransac.ProcessSample(8);
      }
      catch (ExceptionC ex) {
	cerr << "Ravl Exception caught in RansacC::ProcessSample\n"
	     << ex.Text() << endl;
      }  
    }

    // carry on optimising solution if Ransac succeeding
    if(!ransac.GetSolution().IsValid()) {
      
      if (verbose)  cout << "Failed to find a solution" << endl;
      return Projection2dC();  // null projection
    }

    // select observations compatible with solution
    compatibleObsList = evalInliers.CompatibleObservations(ransac.GetSolution(),obsList);

    // initialise Levenberg-Marquardt algorithm
    StateVectorHomog2dC sv = ransac.GetSolution();
    LevenbergMarquardtC lm = LevenbergMarquardtC(sv, compatibleObsList);
      
    if (verbose) {
      cout << "2D homography fitting: Initial residual=" << lm.GetResidual()
	   << "\nSelected " << compatibleObsList.Size()
	   << " observations using RANSAC" << endl;
    }
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
	  
	if (verbose) {
	  cout << " Accepted=" << accepted << " Residual=" << lm.GetResidual()
	       << " DOF=" << 2*compatibleObsList.Size()-8 << endl;
	}
      }
    } catch(...) {
      // Failed to find a solution.
      cerr << "Caught exception from LevenbergMarquardtC. \n";
      return Projection2dC();  // null projection
    }

    // get solution homography
    sv = lm.GetSolution();
    Matrix3dC P = sv.GetHomog();
    P /= P[2][2];

    if (verbose)  cout << "Solution:\n" << P << endl;

    return Projection2dC(P, zhomog, zhomog);
  }

}
