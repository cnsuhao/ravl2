// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! file="Ravl/Image/Processing/Tracking/MosaicBuilder.cc"
//! lib=RavlImageProc

#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array2dIter3.hh"
#include "Ravl/Projection2d.hh"
#include "Ravl/Ransac.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/ObservationHomog2dPoint.hh"
#include "Ravl/LevenbergMarquardt.hh"
#include "Ravl/ObservationManager.hh"
#include "Ravl/StateVectorHomog2d.hh"
#include "Ravl/Image/MosaicBuilder.hh"
#include "Ravl/Image/ImageMatcher.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Image/ForegroundSep.hh"
#include "Ravl/Image/WarpProjective.hh"
#include "Ravl/Image/RemoveDistortion.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Image/Erode.hh"
#include "Ravl/Image/Dilate.hh"
#include "Ravl/Image/RealRGBValue.hh"

#include "Ravl/IO.hh"
#include "Ravl/Image/ImgIO.hh"
#define DODEBUG 0
#if DODEBUG
#include "Ravl/Image/DrawCross.hh"
#include "Ravl/Image/DrawFrame.hh"
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {
  using namespace RavlN;

  //: Constructor for mosaic builder
  MosaicBuilderBodyC::MosaicBuilderBodyC(autoResizeT nresize, bool nVerbose)
    : resize(nresize),
      cropT(0), cropB(0), cropL(0), cropR(0),
      pointTL(0.0, 0.0), pointTR(0.0, 1.0),
      pointBL(1.0, 0.0), pointBR(1.0, 1.0),
      zhomog(100), mosaicZHomog(1),
      K1(0), K2(0), cx_ratio(0.5), cy_ratio(0.5), fx(1.0), fy(1.0),
      filterSubsample(1), Parray(0),
      tracker(30,7,20,17,8,25,1),
      epos(2),
      fitHomog2d(zhomog,zhomog),
      evalInliers(1.0,2.0),
      Pmosaic(1.0,0.0,0.0,
	      0.0,1.0,0.0,
	      0.0,0.0,zhomog),
      frameNo(0),
      verbose(nVerbose)
  {
    // set corner error covariance matrix to 2x2 identity
    epos[0][0] = 1; epos[1][1] = 1; epos[1][0] = 0; epos[0][1] = 0;
  }
  

  //: Deprecated constructor
  MosaicBuilderBodyC::MosaicBuilderBodyC(
	IntT cthreshold, IntT cwidth, IntT mthreshold, IntT mwidth,
	IntT lifeTime, IntT searchSize, IntT newFreq,
	IntT nborderC, IntT nborderR, RealT nzhomog,
	IntT ncropT, IntT ncropB, IntT ncropL, IntT ncropR,
	const Point2dC &npointTL, const Point2dC &npointTR,
	const Point2dC &npointBL, const Point2dC &npointBR,
	IntT nmaxFrames, const ImageC<bool>& nMask, bool nVerbose)
  : borderC(nborderC), borderR(nborderR), resize(none),
    cropT(ncropT), cropB(ncropB), cropL(ncropL), cropR(ncropR),
    pointTL(npointTL), pointTR(npointTR), pointBL(npointBL), pointBR(npointBR),
    zhomog(nzhomog), mosaicZHomog(1), 
    K1(0), K2(0), cx_ratio(0.5), cy_ratio(0.5), fx(1), fy(1),
    Parray(0),
    tracker(cthreshold,cwidth,mthreshold,mwidth,lifeTime,searchSize,newFreq),
    mask(nMask), epos(2), fitHomog2d(zhomog,zhomog), evalInliers(1.0,2.0),
    Pmosaic(1.0,0.0,0,
            0.0,1.0,0,
	    0.0,0.0,zhomog),
    frameNo(0),
    verbose(nVerbose)
  {
    // set corner error covariance matrix to 2x2 identity
    epos[0][0] = 1; epos[1][1] = 1; epos[1][0] = 0; epos[0][1] = 0;

  }


  //: Set binary mask to exclude regions from tracker
  bool MosaicBuilderBodyC::SetMask(const StringC& fileName) {
    if (!Load(fileName, mask)) {
      cerr << "Failed to load file: " << fileName << endl;
      return false;
    }
    return true;
  }


  //: Creates the mosaic from a sequence
  bool MosaicBuilderBodyC::GrowMosaic(const StringC& ipFile, IntT startFrame, UIntT noOfFrames) {
    // open i/p video stream
    if (!OpenSequence(ipFile, startFrame)) exit (-1);
    // Compute homographies & warp frames
    ImageC<ByteRGBValueC> img;
    if (resize == twopass) { // two-pass version
      for (; frameNo < noOfFrames; ++frameNo) {
	if (verbose)  cout << "Tracking frame " << frameNo << endl;
	if (!GetImage(img))  break;
	if (!PrepareFrame(img)) break; 
	if (!FindProj(img)) break;
	InvolveFrame(img.Rectangle(), Parray[frameNo]);
      }
      mosaic = ImageC<ByteRGBMedianC>(mosaicRect);
      input.Seek(startFrame);
      for (frameNo = 0; frameNo < Parray.Size(); ++frameNo) {
	if (!GetImage(img))  break;
	if (frameNo % filterSubsample == 0) {
	  if (verbose)  cout << "Warping frame " << frameNo << endl;
	  if (!PrepareFrame(img)) break;
	  WarpFrame(img);
	}
      }
    }
    else { // one-pass version
      while(frameNo < noOfFrames) {
	if (verbose)  cout << "Processing frame " << frameNo << endl;
	if (!GetImage(img))  break;
	if (!Apply(img)) break;
      }
    }
    return true;
  }


  //: Add an image to the mosaic.
  bool MosaicBuilderBodyC::Apply(ImageC<ByteRGBValueC> &img)
{
    if (!PrepareFrame(img)) return false; 
    if (!FindProj(img)) return false;  // process next image to get projection info
    if (frameNo % filterSubsample == 0) {
      // If we are resizing the mosaic as we go, and mosaic rectangle needs 
      // expanding, then we need to copy mosaic to a new, bigger image.
      if (InvolveFrame(img.Rectangle(),Parray[frameNo]) && (resize==onepass)) {
	if (verbose)  cout << "Mosaic was expanded" << endl;
	ExpandMosaic();
      }
      WarpFrame(img);
    }

#if DODEBUG
    ImageC<ByteRGBValueC> timg(img.Copy());

    // Draw red boxes around the corners.
    ByteRGBValueC val(255,0,0);
    for(HashIterC<UIntT,PointTrackC> cit(corners);cit;cit++) {
      DrawCross(timg,val,cit->Location());
    }
    
    // Draw green crosses around the selected corners
    val = ByteRGBValueC(0,255,0);
    for(DLIterC<ObservationC> oit(compatibleObsList);oit;oit++) {
      const VectorC &z=oit->GetZ();
      Point2dC p(z[0],z[1]);
      IndexRange2dC rect(p,5,5);
      DrawFrame(timg,val,rect);
    }

    // Write the image with tracks out.
    RavlN::Save("@X:Matches",timg);
#endif
    frameNo++;
    return true;
  }


  //: Open file for mosaicing
  bool MosaicBuilderBodyC::OpenSequence(const StringC& ipFile, IntT startFrame) {
    if(!OpenISequence(input,ipFile)) {
      cerr << "Failed to open input sequence `" << ipFile << "'" << endl;
      return false;
    }
    if (startFrame > 0)  input.Seek(startFrame);
    return true;
  }
  

  //: Gets next frame
  bool MosaicBuilderBodyC::PrepareFrame(ImageC<ByteRGBValueC>& img) {
    if (K1!=0.0 || K2!=0.0) {
      ImageC<ByteRGBValueC> linearImg(img.Copy());
      RemoveDistortionC<ByteRGBValueC,ByteRGBValueC> distortionRemover(
	cx_ratio*(RealT)img.Rows(), cy_ratio*(RealT)img.Cols(),
	fx, fy, K1, K2);
      distortionRemover.Apply(linearImg,img);
    }
    if (frameNo == 0) {
      // set frame from first image
      cropRect = IndexRange2dC(img.Frame());
      // adjust frame for cropping region
      cropRect.TRow() += cropT; cropRect.BRow() -= cropB;
      cropRect.LCol() += cropL; cropRect.RCol() -= cropR;
    }
    if (!cropRect.IsValid()) {
      cerr<<"Cropped image rectangle too small at frame no. "<<frameNo<<endl;
      img = ImageC<ByteRGBValueC>();
      return false;
    }
    img = ImageC<ByteRGBValueC>(img, cropRect);
    return true;
  }


  //: computes homography between current frame and mosaic
  bool MosaicBuilderBodyC::FindProj(const ImageC<ByteRGBValueC> &img) {
    // Apply tracker to luminance image.
    corners = tracker.Apply(RGBImageCT2ByteImageCT(img));
    // frame 0 is a special case
    if (frameNo == 0)  return Reset(img);

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
      ransac.ProcessSample(8);
    }

    // carry on optimising solution if Ransac succeeding
    if(!ransac.GetSolution().IsValid()) {
      
      cerr << "Failed to find a solution" << endl;
      frameNo = -1;
      return false;
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
      return false;
    }

    // get solution homography
    sv = lm.GetSolution();
    Matrix3dC P = sv.GetHomog();
    P /= P[2][2];
    if (verbose)  cout << "Solution:\n" << P << endl;

    // accumulate homography
    Psum = P*Psum;
    Parray.Append(Psum*Pmosaic);
    return true;
  }


  //: Expand mosaic rectangle to include projected frame corners
  bool MosaicBuilderBodyC::InvolveFrame(const IndexRange2dC& rect, const Matrix3dC& homog) {
    Projection2dC warp(homog.Inverse(), mosaicZHomog, zhomog);
    if (frameNo == 0) { 
      // initialise rectangle at pixel guaranteed in projected image
      mosaicRect = IndexRange2dC(warp.Project(rect.Center()), 1); 
    }
    IndexRange2dC oldRect = mosaicRect;
    mosaicRect.Involve(warp.Project(rect.TopLeft()));
    mosaicRect.Involve(warp.Project(rect.TopRight()));
    mosaicRect.Involve(warp.Project(rect.BottomLeft()));
    mosaicRect.Involve(warp.Project(rect.BottomRight()));
    if (frameNo == 0) {
      mosaicRect.TRow() -= borderR;
      mosaicRect.LCol() -= borderC;
      mosaicRect.BRow() += borderR;
      mosaicRect.RCol() += borderC;
    }
    return (oldRect != mosaicRect);
  }

  
  //: Expands mosaic to fit expanded mosaic rectangle
  void MosaicBuilderBodyC::ExpandMosaic() {
    // Create expanded mosaic with no median info in it
    ImageC<ByteRGBMedianC> newMosaic(mosaicRect);
    if (mosaic.IsValid()) {
      for(Array2dIter2C<ByteRGBMedianC,ByteRGBMedianC> it(mosaic, newMosaic, mosaic.Rectangle()); it;it++ )
	it.Data2() = it.Data1();
      mosaic = newMosaic;
    }
  }

  //: Warps current frame into mosaic coords
  void MosaicBuilderBodyC::WarpFrame(const ImageC<ByteRGBValueC>& img) {
    if (frameNo == 0) {
      mosaic = ImageC<ByteRGBMedianC>(mosaicRect);
    }
    WarpProjectiveC<ByteRGBValueC,ByteRGBMedianC,PixelMixerRecursiveC<ByteRGBValueC,ByteRGBMedianC> > pwarp(mosaic.Rectangle(),Parray[frameNo].Inverse(),zhomog,1.0,false);
    pwarp.Apply(img,mosaic);
  }


  // Generates foreground image sequence
  bool MosaicBuilderBodyC::GenerateForeground(IntT startFrame, UIntT noOfFrames, DPOPortC<ImageC<ByteRGBValueC> >& outp, int fgThreshold) {
    // find start of sequence
    input.Seek(startFrame);
    // set up foreground separator
    ForegroundSepC fgSep(GetMosaic(), fgThreshold);
    if (mask.IsValid()) fgSep.SetMask(mask);  // exclude unwanted regions
    ImageC<ByteRGBValueC> img;
    // compute foreground segmented image
    for(frameNo = 0; frameNo < noOfFrames; frameNo++) {

      // Read an image from the input, crop, & correct for lens distortion
      if(!input.Get(img))  break;
      PrepareFrame(img) ;
      // Separate out the f/g
      Matrix3dC homog (GetMotion(frameNo));
      img = fgSep.Apply(img, homog);
      // Write an image out.
      outp.Put(img);
    }
    return true;
  }

  //: Computes the homography between the first frame and the mosaic
  bool MosaicBuilderBodyC::Reset(const ImageC<ByteRGBValueC> &img) {
    last = corners;
    
    // initialise accumulated motion Psum by solving for transformation
    // from mosaic coords to image coords
    //  p1 is array of frame corners
    //  p2 is array of corners of reference frame in the mosaic coords
    SArray1dC<Vector2dC> p1(4), p2(4);
    MatrixC A(8,8);
    A.Fill(0.0);
    VectorC b(8);
    
    p1[0][0] =               0.0; p1[0][1] =               0.0;
    p1[1][0] =               0.0; p1[1][1] = (RealT)img.Cols();
    p1[2][0] = (RealT)img.Rows(); p1[2][1] =               0.0;
    p1[3][0] = (RealT)img.Rows(); p1[3][1] = (RealT)img.Cols();
    p2[0][0] = pointTL[0] * (RealT)img.Rows();
    p2[0][1] = pointTL[1] * (RealT)img.Cols();
    p2[1][0] = pointTR[0] * (RealT)img.Rows();
    p2[1][1] = pointTR[1] * (RealT)img.Cols();
    p2[2][0] = pointBL[0] * (RealT)img.Rows();
    p2[2][1] = pointBL[1] * (RealT)img.Cols();
    p2[3][0] = pointBR[0] * (RealT)img.Rows();
    p2[3][1] = pointBR[1] * (RealT)img.Cols();
    
    for(IntT i=0; i < 4; i++) {
      A[i*2][0] = p1[i][0]*zhomog; 
      A[i*2][1] = p1[i][1]*zhomog;
      A[i*2][2] = zhomog*zhomog;
      A[i*2][6] = -p1[i][0]*p2[i][0];
      A[i*2][7] = -p1[i][1]*p2[i][0];
      b[i*2] = zhomog*p2[i][0];
      A[i*2+1][3] = p1[i][0]*zhomog;
      A[i*2+1][4] = p1[i][1]*zhomog;
      A[i*2+1][5] = zhomog*zhomog;
      A[i*2+1][6] = -p1[i][0]*p2[i][1];
      A[i*2+1][7] = -p1[i][1]*p2[i][1];
      b[i*2+1] = zhomog*p2[i][1];
    }
    
    // solve for solution vector
    SolveIP(A,b);
    Psum = Matrix3dC(b[0], b[1], b[2],
		     b[3], b[4], b[5],
		     b[6], b[7], 1.0);
    Psum = Psum.Inverse();
    Parray.Append(Psum*Pmosaic);
    // So at this point, Psum will transform a point from mosaic coords to frame 0 coords, using the "mosaic" coordinate system
    if (verbose) cout << "Initial homography:\n"<< Parray[0]<<endl;
    return true;    
  }
  
  //: Returns the mosaic image
  const ImageC<ByteRGBValueC> MosaicBuilderBodyC::GetMosaic() const { 
    return ByteRGBMedianImageC2ByteRGBImageCT(mosaic);
  }



}
