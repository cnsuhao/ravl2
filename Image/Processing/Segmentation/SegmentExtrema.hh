// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_IMAGELEVELLIST_HEADER
#define RAVLIMAGE_IMAGELEVELLIST_HEADER 1
//! rcsid="$Id$"
//! lib=RavlImageProc
//! author="Charles Galambos, based on code by Jiri Matas."
//! docentry="Ravl.Images.Segmentation"
//! userlevel=Normal

#include "Ravl/Image/Image.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/BlkQueue.hh"
#include "Ravl/Boundary.hh"

namespace RavlImageN {
  

  //! userlevel=Develop
  //: Extrema threshold information.
  
  class ExtremaThresholdC {
  public:
    int thresh;
    int pos;
    int margin;
  };
  
  //! userlevel=Develop
  //: Extremal region
  
  class ExtremaRegionC {
  public:
    ExtremaRegionC()
      : hist(0),
	thresh(0)
    {}
    //: Constructor.
    
    ~ExtremaRegionC() {
      if(hist != 0)
	delete [] hist;
      if(thresh != 0)
	delete [] thresh;
    }
    //: Destructor.
    
    ExtremaRegionC *merge;
    IntT *hist; // Histogram of levels.
    IntT total;
    
    ExtremaThresholdC *thresh; // Thresholds
    IntT nThresh; // Number of thresholds.
    
    IntT maxValue;
    IntT minValue;
    Index2dC minat;
    ExtremaRegionC *closed;
  };
  
  //! userlevel=Develop
  //: Extremal pixel list.
  
  class ChainPixelC {
  public:
    ExtremaRegionC *region;
    ChainPixelC *next;
  };

  //! userlevel=Normal
  //: Extremal region segmentation.
  // Refrence: J Matas. BMVC 2002
  
  class SegmentExtremaC {
  public:
    SegmentExtremaC(IntT nMinSize,RealT nMinMargin,IntT nlimitMaxValue = 0)
      : minSize(nMinSize),
	minMargin(nMinMargin),
	limitMaxValue(nlimitMaxValue)
    {}
    //: Default constructor.
    
    ~SegmentExtremaC();
    //: Destructor.
    
    DListC<BoundaryC> Apply(const ImageC<ByteT> &img);
    //: Apply operation to img.
    
    void SetupImage(const IndexRange2dC &rect);
    //: Setup structures for a given image size.
    
    bool SortPixels(const ImageC<ByteT> &img);
    //: Build a list from a byte image.
    
    void GenerateRegions();
    //: Generate regions.
    
    UIntT Levels() const 
    { return levels.Size(); }
    //: Get number of levels being considered.
    
    SArray1dC<ChainPixelC *> &LevelSets()
    { return levels; }
    //: Access level set array.
    
  protected:
    void ReallocRegionMap(IntT size);
    //: Reallocate the current region set, free any memory used.
    
    //inline 
    static ExtremaRegionC *FindLabel(ChainPixelC *lab);
    //: Find matching label.
    
    //inline 
    int ConnectedLabels(ChainPixelC *pix,ExtremaRegionC **labelArray);
    //: Find the labels around the pixel 'pix'
    // put the results into 'labelArray' which must be at least 4 labels long.
    // The number of labels found is returned.
    
    //inline 
    void AddRegion(ChainPixelC *pix,IntT level);
    //: Add a new region.
    
    //inline 
    void AddPixel(ChainPixelC *pix,IntT level,ExtremaRegionC *reg);
    //: Add pixel to region.
    
    void MergeRegions(ChainPixelC *pix,IntT level,ExtremaRegionC **labels,IntT n);
    //: Add pixel to region.

    void Thresholds();
    //: Generate thresholds
    
    void Thresholds2();
    //: Generate thresholds
    
    DListC<BoundaryC> GrowRegions();
    //: Grow regions.
    
    DListC<BoundaryC> GrowRegion(ExtremaRegionC &region,ImageC<IntT> &marki,IntT &id);
    //: Grow a single region.
    
    bool AddIfInside(BlkQueueC<Index2dC> &q,ImageC<IntT> &marki,IntT id,IntT thresh,Index2dC at);
    //: Add pixel to region.
    
    void AddPixels(BlkQueueC<Index2dC> &queue,DListC<EdgeC> &boundary,ImageC<IntT> &marki,IntT id,IntT thresh,Index2dC at);
    //: Check a point if its in a rectangle.
    
    void PeakDetection(Array1dC<RealT> &real);
    //: Peak detection.
    
    ImageC<ChainPixelC> pixs;
    ImageC<ByteT> img;
    SArray1dC<ChainPixelC *> levels;
    SArray1dC<ExtremaRegionC> regionMap;
    UIntT stride; // Image stride.
    UIntT labelAlloc;
    IndexRangeC valueRange; // Range of pixel values.
    ChainPixelC *origin;
    
    // Paramiters.
    
    IntT minSize;
    IntT maxSize;
    RealT minMargin;
    IntT limitMaxValue; // Maximum image value that will be encountered.
  };

}


#endif
