// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImageProc

#include "Ravl/Image/ImageTracker.hh"
#include "Ravl/Image/WarpProjective.hh"
#include "Ravl/Image/MatchPatch.hh"

namespace RavlImageN {
  
  //: Constructor.
  
  ImageTrackerC::ImageTrackerC(IntT nPatchSize,IntT aSearchSize,IntT nMatchThreshold)
    : patchSize(nPatchSize),
      searchSize(aSearchSize),
      matchThreshold(nMatchThreshold)
  {}
  
  DListC<PairC<Point2dC> > ImageTrackerC::TrackImage(const ImageC<ByteT> &mosaic,const ImageC<ByteT> &data,const Projection2dC &proj) {
    DListC<PairC<Point2dC> > ret;
    // Find corners.
    
    DListC<CornerC> corners = cornerDet.Apply(mosaic);
    
    WarpProjectiveC<ByteT> warp(proj);
    
    // Generate patches.

    Point2dC rat;  
    IntT sum;
    
    for(DLIterC<CornerC> it(corners);it;it++) {
      Point2dC cpnt = it->Location();
      
      // Project corner into mosiac space.
      Point2dC projLoc = proj * cpnt;
      
      // Create a patch
      IndexRange2dC fr(projLoc,patchSize,patchSize);
      ImageC<ByteT> patch(fr);
      warp.Apply(data,patch);
      
      // Match patches to original image.
      SearchMinAbsDifferenceCreep(patch,mosaic,projLoc,rat,sum,searchSize);
      
      // Put matches in the list.
      if(score < matchThreshold)
	ret.InsLast(PairC<Point2dC>(cpnt,rat));
    }
    
    return ret;
  }
  
}
