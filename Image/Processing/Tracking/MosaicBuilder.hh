// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_MOSAICBUILDER_HEADER
#define RAVLIMAGE_MOSAICBUILDER_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Images.Tracking"
//! file="Ravl/Image/Processing/Tracking/MosaicBuilder.hh"
//! lib=RavlImageProc
//! example="mosaic.cc"

#include "Ravl/Image/PointTracker.hh"
#include "Ravl/MatrixRS.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/EvaluateNumInliers.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/ByteRGBMedian.hh"
#include "Ravl/RCHash.hh"
#include "Ravl/FitHomog2dPoints.hh"
#include "Ravl/Matrix3d.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //! autoLink=on
  //: Mosaic building class
  class MosaicBuilderC
  {
  public:
    MosaicBuilderC(IntT cthreshold,
		   IntT cwidth,
		   IntT mthreshold,
		   IntT mwidth,
		   IntT lifeTime,
		   IntT searchSize,
		   IntT newFreq,
		   IntT borderC, IntT borderR,
		   RealT zhomog,
		   IntT cropT, IntT cropB, IntT cropL, IntT cropR,
		   const Point2dC &npointTL,
		   const Point2dC &npointTR,
		   const Point2dC &npointBL,
		   const Point2dC &npointBR,
		   IntT maxFrames);
    //: Constructor
    // Initialises mosaic builder

    bool Apply(const ImageC<ByteRGBValueC> &img);
    //: Add an image to the mosaic.

    Matrix3dC GetMotion(IntT frame) const;
    //: Returns the 2D projective motion relative to the first frame.

    const ImageC<ByteRGBMedianC> & GetMosaic() const;
    //: Returns the mosaic image

    const IndexRange2dC & GetCropRect() const;
    //: Returns the crop rectangle

  private:
    // stored parameters
    IntT borderC, borderR;
    IntT cropT, cropB, cropL, cropR;
    Point2dC pointTL, pointTR, pointBL, pointBR;
    IntT maxFrames;
    RealT zhomog;

    // stored data
    SArray1dC<Matrix3dC> Parray;
    PointTrackerC tracker;
    MatrixRSC epos;
    ImageC<ByteRGBValueC> img;
    FitHomog2dPointsC fitHomog2d;
    EvaluateNumInliersC evalInliers;
    IndexRange2dC rect, mosaicRect;
    ImageC<ByteT> greyImg;
    RCHashC<UIntT,PointTrackC> corners, last;
    Matrix3dC Psum, Pmosaic;
    ImageC<ByteRGBMedianC> mosaic;
    int frameNo;
  };
}


#endif
