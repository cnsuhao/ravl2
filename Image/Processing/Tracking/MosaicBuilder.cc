// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! file="Ravl/Image/Processing/Tracking/MosaicBuilder.cc"
//! lib=RavlImageProc

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
  MosaicBuilderC::MosaicBuilderC(IntT cthreshold,
				 IntT cwidth,
				 IntT mthreshold,
				 IntT mwidth,
				 IntT lifeTime,
				 IntT searchSize,
				 IntT newFreq,
				 IntT nborderC, IntT nborderR,
				 RealT nzhomog,
				 IntT ncropT, IntT ncropB,
				 IntT ncropL, IntT ncropR,
				 const Point2dC &npointTL,
				 const Point2dC &npointTR,
				 const Point2dC &npointBL,
				 const Point2dC &npointBR,
				 IntT nmaxFrames)
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
      ImageC<ByteRGBValueC> croppedImg(img,rect);
      
      // convert image to grey level
      greyImg = RGBImageCT2ByteImageCT(croppedImg);

      // initialise tracker
      corners = tracker.Apply(greyImg);
      last = corners;

      // create initially empty mosaic
      mosaicRect=rect;
      mosaicRect.BRow() += 2*borderR;
      mosaicRect.RCol() += 2*borderC;
  
      mosaic = ImageC<ByteRGBMedianC>(mosaicRect);
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
      p2[0][0] = pointTL[0] * (RealT)img.Rows();
      p2[0][1] = pointTL[1] * (RealT)img.Cols();
      p2[1][0] = pointTR[0] * (RealT)img.Rows();
      p2[1][1] = pointTR[1] * (RealT)img.Cols();
      p2[2][0] = pointBL[0] * (RealT)img.Rows();
      p2[2][1] = pointBL[1] * (RealT)img.Cols();
      p2[3][0] = pointBR[0] * (RealT)img.Rows();
      p2[3][1] = pointBR[1] * (RealT)img.Cols();

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
      Matrix3dC Psm;
      MulM<RealT,3,3,3>(Psum,Pmosaic,Psm); // Odd format for Visual C++ fix..
      
      if(maxFrames>0) Parray[0]=Psm;
      Psm = Psm.Inverse();
      WarpProjectiveC<ByteRGBValueC,ByteRGBMedianC,PixelMixerRecursiveC<ByteRGBValueC,ByteRGBMedianC> > pwarp(mosaicRect,Psm,zhomog,1.0,false);
      pwarp.Apply(croppedImg,mosaic);

      frameNo=0;
      return true;
    }

    // not the first image
    frameNo++;
    ImageC<ByteRGBValueC> croppedImg(img,rect);

    // convert image to grey level
    greyImg = RGBImageCT2ByteImageCT(croppedImg);

    // Apply tracker.
    corners = tracker.Apply(greyImg);
    
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
      obsList.InsLast(ObservationHomog2dPointC(Vector2dC(loc1[0],loc1[1]),epos,
					       Vector2dC(loc2[0],loc2[1]),epos));
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

    // accumulate homography
    // Psum = P*Psum; Line changed to the following to help Visual C++.
    Matrix3dC temp;
    MulM<RealT,3,3,3>(P,Psum,temp);
    Psum = temp;
    
    // compute homography to map image onto mosaic

    // projective warp, combining new image with mosaic
    //Matrix3dC Psm=Psum*Pmosaic;  Line changed to the following to help Visual C++.
    Matrix3dC Psm;
    MulM<RealT,3,3,3>(Psum,Pmosaic,Psm);
    
    if(maxFrames>0)Parray[frameNo]=Psm;
    Psm = Psm.Inverse();
    WarpProjectiveC<ByteRGBValueC,ByteRGBMedianC,PixelMixerRecursiveC<ByteRGBValueC,ByteRGBMedianC> > pwarp(mosaicRect,Psm,zhomog,1.0,false);
    pwarp.Apply(croppedImg,mosaic);
    
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
