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
//! file="Ravl/Image/Processing/Segmentation/FloodRegion.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/DrawFrame.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/BlkQueue.hh"
#include "Ravl/Boundary.hh"

namespace RavlImageN {

  template<class PixelT>
  class FloorRegionThresholdC {
  public:
    FloorRegionThresholdC()
    {}
    //: Default constructor.
    
    FloorRegionThresholdC(const PixelT &pix)
      : value(pix)
    {}
    //: Construct from pixel value.
    
    bool operator()(const PixelT &pix) const
    { return pix <= value; }
    //: Should pixel be included in the region ?
    
  protected:
    PixelT value;
  };
  
  //! userlevel=Normal
  //: Flood based region growing.
  // Grow a region from 'seed' including all connected pixel less than or equal to threshold, generate a boundry as the result.
  
  template<class PixelT,class InclusionTestT = FloorRegionThresholdC<PixelT> >
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
    
    IntT GrowRegion(const Index2dC &seed,const InclusionTestT &inclusionCriteria,BoundaryC &boundary,IntT maxSize = 0) {
      RavlAssert(pixQueue.IsEmpty());
      inclusionTest = inclusionCriteria;
      boundary = BoundaryC(); // Create a new boundry list
      if(!inclusionTest(img[seed]))
	return false; // Empty region.
      pixQueue.InsLast(seed);
      id++;
      IntT size = 0;
      if(maxSize == 0) {
	while(!pixQueue.IsEmpty()) {
	  AddPixels(boundary,pixQueue.GetFirst());
	  size++;
	}
      } else {
	while(!pixQueue.IsEmpty() && size < maxSize) {
	  AddPixels(boundary,pixQueue.GetFirst());
	  size++;
	}
	if(!pixQueue.IsEmpty()) {
	  pixQueue.Empty();
	  return false;
	}
      }
      return size;
    }
    //: Grow a region from 'seed' including all connected pixel less than or equal to threshold, generate a boundry as the result.
    // Returns the region size.

    template<typename MaskT>
    IntT GrowRegion(const Index2dC &seed,const InclusionTestT &inclusionCriteria,ImageC<MaskT> &mask,IntT padding = 0,IntT maxSize = 0) {
      inclusionTest = inclusionCriteria;
      RavlAssert(pixQueue.IsEmpty());
      if(!inclusionTest(img[seed]))
	return false; // Empty region.
      pixQueue.InsLast(seed);
      id++;
      IntT size = 0;
      IndexRange2dC rng(seed,1,1);
      if(maxSize <= 0) {
	while(!pixQueue.IsEmpty())
	  AddPixels(rng,pixQueue.GetFirst());
      } else {
	while(!pixQueue.IsEmpty() && size < maxSize) {
	  AddPixels(rng,pixQueue.GetFirst());
	  size++;
	}
	if(!pixQueue.IsEmpty()) {
	  pixQueue.Empty();
	  return false; // Region too big.
	}
      }
      mask = ImageC<MaskT>(rng.Expand(padding));
      if(padding > 0)
	DrawFrame(mask,(MaskT) 0,padding,mask.Frame());
      size = 0;
      for(Array2dIter2C<MaskT,IntT> it(mask,marki,rng);it;it++) {
	if(it.Data2() == id) {
	  size++;
	  it.Data1() = 1;
	} else
	  it.Data1() = 0;
      }
      return size;
    }
    //: Grow a region from 'seed' including all connected pixel less than or equal to threshold, generate a mask as the result.
    // The mask images are generated with a boundry
    // Returns the region size.
    
    ImageC<IntT> &MarkImage()
    { return marki; }
    //: Access marked pixel image.
    
    IntT MarkId() const
    { return id; }
    //: Access current region id.
    
  protected:
    ImageC<PixelT> img;
    ImageC<IntT> marki;
    IntT id;
    BlkQueueC<Index2dC> pixQueue;
    
    InclusionTestT inclusionTest;
    
    inline
    bool AddIfInside(Index2dC at) {
      if(!marki.Contains(at))
	return true;
      if(!inclusionTest(img[at]))
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
