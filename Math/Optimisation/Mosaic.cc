
#include "Ravl/Option.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/Image/PointTracker.hh"
#include "Ravl/Image/DrawFrame.hh"
#include "Ravl/Observation.hh"
#include "Ravl/RCHash.hh"
#include "Ravl/Ransac.hh"
#include "Ravl/ObservationManager.hh"
#include "Ravl/FitHomog2dPoints.hh"
#include "Ravl/EvaluateNumInliers.hh"
#include "Ravl/ObservationHomog2dPoint.hh"
#include "Ravl/LevenbergMarquardt.hh"
#include "Ravl/StateVectorHomog2d.hh"
#include "WarpProjective.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/IO.hh"
#include "Ravl/Image/ImgIO.hh"

#if 0
// Display stuff
#include "Ravl/GUI/DPDisplayObj.hh"
#include "Ravl/GUI/DPDisplayImage.hh"
#endif

using namespace RavlN;
using namespace RavlImageN;

#define ZHOMOG 100.0

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  int cthreshold = opt.Int("ct",800,"Corner threshold. ");
  int cwidth     = opt.Int("cw",7,"Corner filter width. ");
  int mthreshold = opt.Int("mt",20,"Match threshold. ");
  int mwidth     = opt.Int("mw",15,"Tracker feature width. ");
  int lifeTime   = opt.Int("ml",8,"Lifetime of a point without a match in the incoming images. ");
  int searchSize = opt.Int("ss",25,"Search size. How far to look from the predicted position of the feature.");
  StringC ifn = opt.String("","@V4LH:/dev/video0","Input sequence. ");
  StringC ofn = opt.String("","@X","Output sequence. ");
  opt.Check();
  
  // Open an input stream.
  DPIPortC<ImageC<ByteRGBValueC> > inp;
  if(!OpenISequence(inp,ifn)) {
    cerr << "Failed to open input '" << ifn << "'\n";
    return 1;
  }
  
  // Open an output stream.
  DPOPortC<ImageC<ByteRGBValueC> > outp;
  if(!OpenOSequence(outp,ofn,"")) {
    cerr << "Failed to open output '" << ofn << "'\n";
    return 1;
  }
  
  // Create a tracker.
  PointTrackerC tracker(cthreshold,cwidth,mthreshold,mwidth,lifeTime,searchSize);
  
  ImageC<ByteRGBValueC> img;
  RCHashC<UIntT,Point2dC> last;
  
  MatrixRSC epos(2);
  epos[0][0] = 1;
  epos[1][1] = 1;
  epos[1][0] = 0;
  epos[0][1] = 0;

  FitHomog2dPointsC fitHomog2d(ZHOMOG,ZHOMOG);
  EvaluateNumInliersC evalInliers(0.1);

  if(!inp.Get(img))
    return 1;

  IndexRange2dC rect(img.Frame());

  // convert image to grey level
  ImageC<ByteT> grey_img = RGBImageCT2ByteImageCT(img);
  DListC<PointTrackC> corners = tracker.Apply(grey_img);

  // build initial hash table
  for(DLIterC<PointTrackC> it(corners);it;it++)
    last[it->ID()] = it->Location();

  // initialise accumulated motion
  Matrix3dC Psum(1,0,0,
		 0,1,0,
		 0,0,1);

  for(;;) {
    // Read an image from the input.
    if(!inp.Get(img))
      break;
    img = ImageC<ByteRGBValueC>(img,rect);
    grey_img = RGBImageCT2ByteImageCT(img);

    // Apply tracker.
    corners = tracker.Apply(grey_img);
    
    // Generate an observation set for tracked points.
    DListC<ObservationC> obsList;
    RCHashC<UIntT,Point2dC> newpnts;
    for(DLIterC<PointTrackC> it(corners);it;it++) {
#if 0
      cout << "Confidence: " << it->Confidence() << endl;
      if(it->Confidence() < 0.1)
	continue; // Filter out points we haven't got recent info on.
#endif
      newpnts[it->ID()] = it->Location();
      Point2dC lat;
      if(!last.Lookup(it->ID(),lat))
	continue; // Matching point not found.
      obsList.InsLast(ObservationHomog2dPointC(it->Location(),epos,lat,epos));
    }
    
    last = newpnts;
    
    ObservationListManagerC obsListManager(obsList);
    RansacC ransac(obsListManager,fitHomog2d,evalInliers);

    for(int i = 0;i <100;i++) {
      ransac.ProcessSample(8);
    }

    // Draw red boxes around the corners.
    ByteRGBValueC val(255,0,0);
    for(DLIterC<PointTrackC> it(corners);it;it++) {
      IndexRange2dC rect(it->Location(),5,5);
      DrawFrame(img,val,rect);
    }

    // select observations compatible with solution
    DListC<ObservationC> compatible_obs_list = evalInliers.CompatibleObservations(ransac.GetSolution(),obsList);

    // initialise Levenberg-Marquardt algorithm
    StateVectorHomog2dC sv = ransac.GetSolution();
    LevenbergMarquardtC lm = LevenbergMarquardtC(sv, compatible_obs_list);

    cout << "2D homography fitting: Initial residual=" << lm.GetResidual() << endl;
    cout << "Selected " << compatible_obs_list.Size() << " observations using RANSAC" << endl;
    VectorC x = lm.SolutionVector();
    x *= 1.0/x[8];

    // apply iterations
    RealT lambda = 100.0;
    for ( int i = 0; i < 20; i++ ) {
      bool accepted = lm.Iteration(compatible_obs_list, lambda);
      if ( accepted )
	// iteration succeeded in reducing the residual
	lambda /= 10.0;
      else
	// iteration failed to reduce the residual
	lambda *= 10.0;

      cout << " Accepted=" << accepted << " Residual=" << lm.GetResidual();
      cout << " DOF=" << 2*compatible_obs_list.Size()-8 << endl;
    }

    // get solution homography
    sv = lm.GetSolution();
    Matrix3dC P = sv.GetHomog();
    P /= P[2][2];

    cout << "Solution: (" << P[0][0] << " " << P[0][1] << " " << P[0][2] << ")" << endl;
    cout << "          (" << P[1][0] << " " << P[1][1] << " " << P[1][2] << ")" << endl;
    cout << "          (" << P[2][0] << " " << P[2][1] << " " << P[2][2] << ")" << endl;

    // accumulate homography
    Psum = P*Psum;

    // projective warp
    ImageC<ByteT> warped = grey_img.Copy();
    //warped.Fill(0);
    WarpProjectiveC<ByteT,ByteT> pwarp(rect,Psum,ZHOMOG,ZHOMOG,true);
    cout << "Width=" << warped.Cols() << " Height=" << warped.Rows() << endl;
    pwarp.Apply(grey_img,warped);
    cout << "Width=" << warped.Cols() << " Height=" << warped.Rows() << endl;
    Save("warped.pgm",warped);

    // Draw green boxes around the selected corners
    val = ByteRGBValueC(0,255,0);
    for(DLIterC<ObservationC> it(compatible_obs_list);it;it++) {
      const VectorC &z=it->GetZ();
      Point2dC p(z[0],z[1]);
      IndexRange2dC rect(p,8,8);
      DrawFrame(img,val,rect);
    }

    // Write an image out.
    outp.Put(img);
  }

  return 0;
}
