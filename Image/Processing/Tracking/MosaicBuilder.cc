// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlOptimise

#include "Ravl/Image/MosaicBuilder.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Image/WarpProjective.hh"
#include "Ravl/ObservationHomog2dPoint.hh"
#include "Ravl/LevenbergMarquardt.hh"
#include "Ravl/ObservationManager.hh"
#include "Ravl/StateVectorHomog2d.hh"
#include "Ravl/Ransac.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/Image/ImageConv.hh"

#define DODEBUG 1
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
  MosaicBuilderC::MosaicBuilderC(int cthreshold,
				 int cwidth,
				 int mthreshold,
				 int mwidth,
				 int lifeTime,
				 int searchSize,
				 int newFreq,
				 int nborderC, int nborderR,
				 double nzhomog,
				 int ncropT, int ncropB,
				 int ncropL, int ncropR,
				 const Tuple2C<RealT,RealT> &npointTL,
				 const Tuple2C<RealT,RealT> &npointTR,
				 const Tuple2C<RealT,RealT> &npointBL,
				 const Tuple2C<RealT,RealT> &npointBR,
				 int nmaxFrames)
    : borderC(nborderC), borderR(nborderR),
      cropT(ncropT), cropB(ncropB), cropL(ncropL), cropR(ncropR),
      pointTL(npointTL), pointTR(npointTR),
      pointBL(npointBL), pointBR(npointBR),
      maxFrames(nmaxFrames),
      zhomog(nzhomog),
      Parray((nmaxFrames>0) ? nmaxFrames : 1),
      tracker(cthreshold,cwidth,mthreshold,mwidth,lifeTime,
	      searchSize,newFreq),
      epos(2),
      fitHomog2d(zhomog,zhomog),
      evalInliers(1.0,2.0)
  {
    // set corner error covariance matrix to 2x2 identity
    epos[0][0] = 1;
    epos[1][1] = 1;
    epos[1][0] = 0;
    epos[0][1] = 0;

    // compute homography mapping first image coordinates to mosaic coordinates
    Pmosaic = Matrix3dC(1.0,0.0,-borderR,
			0.0,1.0,-borderC,
			0.0,0.0,zhomog);

    // we will initialise the frame number when the first image is read
    frameNo = -1;
  }
  
  //: Add an image to the mosaic.
  bool MosaicBuilderC::Apply(const ImageC<ByteRGBValueC> &img)
  {
    if ( frameNo<0 ) {

      // set frame from first image
      rect = IndexRange2dC(img.Frame());

      // adjust frame for cropping region
      rect.TRow() += cropT; rect.BRow() -= cropB;
      rect.LCol() += cropL; rect.RCol() -= cropR;

      // crop image
      ImageC<ByteRGBValueC> cropped_img(img,rect);
      
      // convert image to grey level
      grey_img = RGBImageCT2ByteImageCT(cropped_img);

      // initialise tracker
      corners = tracker.Apply(grey_img);
      last = corners;

      // create initially empty mosaic
      mosaic_rect=rect;
      mosaic_rect.BRow() += 2*borderR;
      mosaic_rect.RCol() += 2*borderC;
  
      mosaic = ImageC<ByteRGBMedianC>(mosaic_rect);
      ByteRGBValueC val(0,0,0);
      for(Array2dIterC<ByteRGBMedianC> it(mosaic); it;it++ )
	*it = ByteRGBMedianC(val);
  
      // initialise accumulated motion
      SArray1dC<Vector2dC> p1(4), p2(4);
      MatrixC A(8,8);
      A.Fill(0.0);
      VectorC b(8);

      p1[0][0] =               0.0; p1[0][1] =               0.0;
      p1[1][0] =               0.0; p1[1][1] = (RealT)img.Cols();
      p1[2][0] = (RealT)img.Rows(); p1[2][1] =               0.0;
      p1[3][0] = (RealT)img.Rows(); p1[3][1] = (RealT)img.Cols();
      p2[0][0] = pointTL.Data1()*(RealT)img.Rows();
      p2[0][1] = pointTL.Data2()*(RealT)img.Cols();
      p2[1][0] = pointTR.Data1()*(RealT)img.Rows();
      p2[1][1] = pointTR.Data2()*(RealT)img.Cols();
      p2[2][0] = pointBL.Data1()*(RealT)img.Rows();
      p2[2][1] = pointBL.Data2()*(RealT)img.Cols();
      p2[3][0] = pointBR.Data1()*(RealT)img.Rows();
      p2[3][1] = pointBR.Data2()*(RealT)img.Cols();

      for(IntT i=0; i < 4; i++) {
	A[i*2][0] = p1[i][0]*zhomog; A[i*2][1] = p1[i][1]*zhomog;
	A[i*2][2] = zhomog*zhomog;
	A[i*2][6] = -p1[i][0]*p2[i][0]; A[i*2][7] = -p1[i][1]*p2[i][0];
	b[i*2] = zhomog*p2[i][0];
	A[i*2+1][3] = p1[i][0]*zhomog; A[i*2+1][4] = p1[i][1]*zhomog;
	A[i*2+1][5] = zhomog*zhomog;
	A[i*2+1][6] = -p1[i][0]*p2[i][1]; A[i*2+1][7] = -p1[i][1]*p2[i][1];
	b[i*2+1] = zhomog*p2[i][1];
      }

      // solve for solution vector
      SolveIP(A,b);
      Psum = Matrix3dC(b[0], b[1], b[2],
		       b[3], b[4], b[5],
		       b[6], b[7], 1.0);
      Psum = Psum.Inverse();

      // projective warp of first image
      Matrix3dC Psm=Psum*Pmosaic;
      if(maxFrames>0)Parray[0]=Psm;
      Psm = Psm.Inverse();
      WarpProjectiveC<ByteRGBValueC,ByteRGBMedianC,PixelMixerRecursiveC<ByteRGBValueC,ByteRGBMedianC> > pwarp(mosaic_rect,Psm,zhomog,1.0,false);
      pwarp.Apply(cropped_img,mosaic);

      frameNo=0;
      return true;
    }

    // not the first image
    frameNo++;
    ImageC<ByteRGBValueC> cropped_img(img,rect);

    // convert image to grey level
    grey_img = RGBImageCT2ByteImageCT(cropped_img);

    // Apply tracker.
    corners = tracker.Apply(grey_img);
    
    // Generate an observation set for tracked points.
    DListC<ObservationC> obsList;
    for(HashIterC<UIntT,PointTrackC> it(corners);it;it++) {
      //      cout << "Confidence: " << it->Confidence() << endl;
      if(it->Confidence() < 0.1)
	continue; // Filter out points we haven't got recent info on.
      PointTrackC lat;
      if(!last.Lookup(it->ID(),lat))
	continue; // Matching point not found.
      obsList.InsLast(ObservationHomog2dPointC(lat.Location(),epos,it->Location(),epos));
    }
    
    last = corners;

    ObservationListManagerC obsListManager(obsList);
    RansacC ransac(obsListManager,fitHomog2d,evalInliers);

    for(int i = 0;i <100;i++) {
      ransac.ProcessSample(8);
    }

    // carry on optimising solution if Ransac succeeding
    if(!ransac.GetSolution().IsValid()) {
      
      // failed to find a solution
      frameNo = -1;
      return false;
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
    try {
      // apply iterations
      RealT lambda = 100.0;
      for ( int i = 0; i < 4; i++ ) {
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

    // accumulate homography
    Psum = P*Psum;

    // compute homography to map image onto mosaic

    // projective warp, combining new image with mosaic
    Matrix3dC Psm=Psum*Pmosaic;
    if(maxFrames>0)Parray[frameNo]=Psm;
    Psm = Psm.Inverse();
    WarpProjectiveC<ByteRGBValueC,ByteRGBMedianC,PixelMixerRecursiveC<ByteRGBValueC,ByteRGBMedianC> > pwarp(mosaic_rect,Psm,zhomog,1.0,false);
    pwarp.Apply(cropped_img,mosaic);

#if DODEBUG
    ImageC<ByteRGBValueC> timg(img.Copy());

    // Draw red boxes around the corners.
    ByteRGBValueC val(255,0,0);
    for(HashIterC<UIntT,PointTrackC> it(corners);it;it++) {
      DrawCross(timg,val,it->Location());
    }

    // Draw green crosses around the selected corners
    val = ByteRGBValueC(0,255,0);
    for(DLIterC<ObservationC> it(compatible_obs_list);it;it++) {
      const VectorC &z=it->GetZ();
      Point2dC p(z[0],z[1]);
      IndexRange2dC rect(p,5,5);
      DrawFrame(timg,val,rect);
    }

    // Write the image with tracks out.
    Save("@X:Matches",timg);
#endif

    return true;
  }

  //: Returns the 2D projective motion relative to the first frame.
  Matrix3dC MosaicBuilderC::GetMotion(IntT frame) const
  {
    RavlAssertMsg(maxFrames>0 && frame>=0 && frame<=frameNo,
		  "in MosaicBuilderC::GetMotion()");
    return Parray[frame];
  }

  //: Returns the mosaic image
  const ImageC<ByteRGBMedianC> & MosaicBuilderC::GetMosaic() const
  {
    return mosaic;
  }

  //: Returns the crop rectangle
  const IndexRange2dC & MosaicBuilderC::GetCropRect() const
  {
    return rect;
  }
}
