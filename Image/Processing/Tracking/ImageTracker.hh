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

#include "Ravl/Pair.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/CornerDetectorSusan.hh"
#include "Ravl/Projection2d.hh"

namespace RavlImageN {
  
  //: Track 
  
  class ImageTrackerC {
  public:
    ImageTrackerC(IntT nPatchSize,IntT aSearchSize,IntT matchThreshold);
    //: Constructor.
    
    DListC<PairC<Point2dC> > TrackImage(const ImageC<ByteT> &mosaic,const ImageC<ByteT> &data,const Projection2dC &aff);
    //: Track an image in a larger one.
    
  protected:
    CornerDetectorSusanC cornerDet;
    IntT patchSize;
    IntT searchSize;
    IntT matchThreshold;
  };

}


#endif
