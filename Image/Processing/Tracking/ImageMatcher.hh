// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_IMAGEMATCHER_HEADER
#define RAVLMATH_IMAGEMATCHER_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Images.Tracking"
//! file="Ravl/Image/Processing/Tracking/ImageMatcher.hh"
//! lib=RavlImageProc
//! example="mosaic.cc"

#include "Ravl/Image/ImageTracker.hh"
#include "Ravl/Matrix3d.hh"

namespace RavlImageN {
  using namespace RavlImageN;
  
  //! userlevel=Normal
  //! autoLink=on
  //: Matches images to a template image using projective transform
  // Given an inital homography between the two images, this class will improve the homography.  It uses a corner detector together with RANSAC to compute the transformation.

  class ImageMatcherC
  {
  public:
    ImageMatcherC(const ImageC<ByteT> &imageTemplate,
		  IntT cropT=0, IntT cropB=0, IntT cropL=0, IntT cropR=0,
		  IntT matchPatchSize=17,
		  IntT matchSearchSize=25,
		  IntT matchThreshold=20,
		  RealT zhomogTemplate=1.0,
		  RealT zhomogImage=1.0);
    //: Constructor
    // Initialises image matcher

    bool Apply(const ImageC<ByteT> &img, Projection2dC &proj);
    //: Matches an image to the template.
    // proj is the initial estimate of the motion, usually provided by the
    // previous call. proj will be updated to the computed motion.

  private:
    // stored parameters
    IntT cropT, cropB, cropL, cropR;
    RealT zhomogTemplate, zhomogImage;

    // stored data
    ImageC<ByteT> imageTemplate;
    ImageTrackerC tracker;
  };
}


#endif
