// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_IMAGETRACKER_HEADER
#define RAVLIMAGE_IMAGETRACKER_HEADER 1
//! rcsid="$Id$"
//! lib=RavlImageProc
//! docentry="Ravl.Images.Tracking"
//! file="Ravl/Image/Processing/Tracking/ImageTracker.hh"

#include "Ravl/Pair.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/CornerDetectorSusan.hh"
#include "Ravl/Projection2d.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Track an image against a larger mosiac image.
  
  class ImageTrackerC {
  public:
    ImageTrackerC(IntT nPatchSize,IntT aSearchSize,IntT matchThreshold);
    //: Constructor.
    //!param: patchSize - Size of patches around each corner to match
    //!param: aSearchSize - Size of search area. i.e. maximum motion to allow for.
    //!param: matchThreshold - Threshold for accepting a match.
    
    DListC<PairC<Point2dC> > TrackImage(const ImageC<ByteT> &mosaic,const ImageC<ByteT> &data,const Projection2dC &proj);
    //: Track an image in a larger one.
    //!param: mosiac - Large mosaic image
    //!param: data - Smaller target image
    //!param: proj - Estimate of the position of the smaller image.
    //!return: List of point pairs, one from 'data' image and corresponding point in the 'mosaic'.
    
  protected:
    CornerDetectorSusanC cornerDet;
    IntT patchSize;
    IntT searchSize;
    IntT matchThreshold;
  };

}


#endif
