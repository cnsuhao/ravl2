// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_POINTTRACKER_HEADER
#define RAVLIMAGE_POINTTRACKER_HEADER 1
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Images.Tracking"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/CornerDetectorHarris.hh"
#include "Ravl/DList.hh"
#include "Ravl/Image/PointTrack.hh"
#include "Ravl/Image/PointTrackModel.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Point tracker.
  
  class PointTrackerC {
  public:
    PointTrackerC(int cthreshold,int mwidth = 9,int mwidth = 10,int nthreshold = 50,int lifeTime = 2,int searchSize = 25);
    //: Constructor.
    // Matching width.
    
    DListC<PointTrackC> Apply(const ImageC<ByteT> &img);
    //: Returns a list of tracks.
    
    IntT Update(const ImageC<ByteT> &img);
    //: Update track with information from an image.
    
  protected:
    UIntT idAlloc;
    IntT frameCount;
    CornerDetectorHarrisC cornerDet;
    IntT mwidth;
    IntT mthreshold;
    IntT lifeTime;
    IntT searchSize;
    DListC<PointTrackModelC> tracks; // Set of tracks being considered.
  };
}


#endif
