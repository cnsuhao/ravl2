// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_FLOODREGION_HEADER
#define RAVLIMAGE_FLOODREGION_HEADER 1
//! rcsid="$Id$"
//! lib=RavlImageProc
//! author="Charles Galambos, based on code by Jiri Matas."
//! docentry="Ravl.Images.Segmentation"
//! userlevel=Normal

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/DrawFrame.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/BlkQueue.hh"
#include "Ravl/Boundary.hh"

namespace RavlImageN {

  //! userlevel=Normal
  //: Flood based region growing.
  // Grow a region from 'seed' including all connected pixel less than or equal to threshold, generate a boundry as the result.
  
  template<class PixelT>
  class FloodRegionC {
  public:
    FloodRegionC(const ImageC<PixelT> &nimg)
    { SetupImage(nimg); }
    //: Constructor with image to segment.
    
    const ImageC<PixelT> &Image() const
    { return img; }
    //: Access the image we're currently segmenting.
    
    bool SetupImage(const ImageC<PixelT> &nimg) {
      img = nimg;
      if(marki.Frame() != img.Frame()) {
	marki = ImageC<IntT>(img.Frame());
	marki.Fill(0);
	id = 1;
      }
      return true;
    }
    //: Setup new image for processing.
    
    bool GrowRegion(const Index2dC &seed,PixelT threshold,BoundaryC &boundary) {
      RavlAssert(pixQueue.IsEmpty());
      thresh = threshold;
      boundary = BoundaryC(); // Create a new boundry list
      if(img[seed] > thresh)
	return false; // Empty region.
      pixQueue.InsLast(seed);
      id++;
      while(!pixQueue.IsEmpty())
	AddPixels(boundary,pixQueue.GetFirst());
      return true;
    }
    //: Grow a region from 'seed' including all connected pixel less than or equal to threshold, generate a boundry as the result.
    // Returns false if the region has zero size.
    
    bool GrowRegion(const Index2dC &seed,PixelT threshold,ImageC<IntT> &mask,IntT padding = 0) {
      RavlAssert(pixQueue.IsEmpty());
      thresh = threshold;
      if(img[seed] > thresh)
	return false; // Empty region.
      pixQueue.InsLast(seed);
      id++;
      IndexRange2dC rng(seed,1,1);
      while(!queue.IsEmpty())
	AddPixels(rng,queue.GetFirst());
      mask = ImageC<ByteT>(rng.Expand(padding));
      if(padding > 0)
	DrawFrame(mask,0,padding,mask.Frame());
      for(Array2dIter2C<IntT,IntT> it(mask,marki,rng);it;it++)
	it.Data1() = it.Data2() == id ? 0 : 1;
      return true;
    }
    //: Grow a region from 'seed' including all connected pixel less than or equal to threshold, generate a mask as the result.
    // The mask images are generated with a boundry
    // Returns false if the region has zero size.
    
  protected:
    ImageC<PixelT> img;
    ImageC<IntT> marki;
    IntT id;
    BlkQueueC<Index2dC> pixQueue;
    IntT thresh;  // Current threshold
    
    inline
    bool AddIfInside(Index2dC at) {
      if(!marki.Contains(at))
	return true;
      if(img[at] > thresh)
	return true; // Is outside the region.
      if(marki[at] != id) {
	// Put in to do list.
	marki[at] = id;
	pixQueue.InsLast(at);
      }
      return false;
    }
    //: Add a pixel to a region if its inside it.
    
    inline 
    void AddPixels(DListC<EdgeC> &boundary,Index2dC at) {
      if(AddIfInside(at + Index2dC(0,1)))
	boundary.InsLast(EdgeC(at,CR_UP));
      if(AddIfInside(at + Index2dC(0,-1)))
	boundary.InsLast(EdgeC(at,CR_DOWN));
      if(AddIfInside(at + Index2dC(1,0)))
	boundary.InsLast(EdgeC(at,CR_RIGHT));
      if(AddIfInside(at + Index2dC(-1,0)))
	boundary.InsLast(EdgeC(at,CR_LEFT));
    }
    //: Add pixels with a boundry.
    
    inline 
    void AddPixels(IndexRange2dC &rng,Index2dC at) {
      rng.Involve(at);
      AddIfInside(at + Index2dC(0,1));
      AddIfInside(at + Index2dC(0,-1));
      AddIfInside(at + Index2dC(1,0));
      AddIfInside(at + Index2dC(-1,0));
    }
    //: Add pixels to a region.
    
  };
}

#endif
