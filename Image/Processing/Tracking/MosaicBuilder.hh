// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_MOSAICBUILDER_HEADER
#define RAVLMATH_MOSAICBUILDER_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation"
//! example="Mosaic.cc"
//! lib=RavlOptimise

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

namespace RavlN {
  using namespace RavlImageN;
  
  //! userlevel=Normal
  //! autoLink=on
  //: Mosaic building class
  class MosaicBuilderC
  {
  public:
    MosaicBuilderC(int cthreshold,
		   int cwidth,
		   int mthreshold,
		   int mwidth,
		   int lifeTime,
		   int searchSize,
		   int newFreq,
		   int borderC, int borderR,
		   double zhomog,
		   int cropT, int cropB, int cropL, int cropR,
		   const Tuple2C<RealT,RealT> &npointTL,
		   const Tuple2C<RealT,RealT> &npointTR,
		   const Tuple2C<RealT,RealT> &npointBL,
		   const Tuple2C<RealT,RealT> &npointBR,
		   int maxFrames);
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
    Tuple2C<RealT,RealT> pointTL, pointTR, pointBL, pointBR;
    IntT maxFrames;
    RealT zhomog;

    // stored data
    SArray1dC<Matrix3dC> Parray;
    PointTrackerC tracker;
    MatrixRSC epos;
    ImageC<ByteRGBValueC> img;
    FitHomog2dPointsC fitHomog2d;
    EvaluateNumInliersC evalInliers;
    IndexRange2dC rect, mosaic_rect;
    ImageC<ByteT> grey_img;
    RCHashC<UIntT,PointTrackC> corners, last;
    Matrix3dC Psum, Pmosaic;
    ImageC<ByteRGBMedianC> mosaic;
    int frameNo;
  };
}


#endif
