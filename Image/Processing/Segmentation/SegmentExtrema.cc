// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImageProc
//! author="Charles Galambos, based on code by Jiri Matas."

#include "Ravl/Image/SegmentExtrema.hh"
#include "Ravl/Image/DrawFrame.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/IO.hh"
#include <string.h>

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {

  //: Destructor.
  
  SegmentExtremaC::~SegmentExtremaC() {
    ReallocRegionMap(0);
  }

  //: Delete the current region set, free any memory used.
  
  void SegmentExtremaC::ReallocRegionMap(IntT size) {
    if(size == 0)
      regionMap = SArray1dC<ExtremaRegionC>();
    else 
      regionMap = SArray1dC<ExtremaRegionC>(size);
  }
  
  //: Apply operation to image.
  
  DListC<BoundaryC> SegmentExtremaC::Apply(const ImageC<ByteT> &nimg) {
    SortPixels(nimg);
    GenerateRegions();
    Thresholds();
    return GrowRegions();
  }
  
  //: Setup structures for a given image size.
  
  void SegmentExtremaC::SetupImage(const IndexRange2dC &rect) {
    IndexRange2dC imgRect = rect.Expand(1);
    labelAlloc = 0; // Reset region allocation counter.
    if(imgRect == pixs.Frame())
      return ; // Done already.
    
    // Allocate ChainPixelC image.
    pixs = ImageC<ChainPixelC>(imgRect);
    origin = &(pixs[img.Frame().Origin()]);
    stride = imgRect.Cols();
    
    // Put a frame of zero labels around the edge.
    ChainPixelC zeroPix;
    zeroPix.region = 0;
    zeroPix.next = 0;
    DrawFrame(pixs,zeroPix,imgRect);
    
    // Create region map.
    ReallocRegionMap(img.Frame().Area()/2);
    
    // ...
    maxSize = img.Frame().Area();
  }
  
  //: Build a list from a byte image.
  
  bool SegmentExtremaC::SortPixels(const ImageC<ByteT> &nimg) {
    limitMaxValue = 256;
    img = nimg;
    SetupImage(nimg.Frame());
    
    // Create lists of pixels with the same value.
    
    if(levels.Size() != 256)
      levels = SArray1dC<ChainPixelC *>(256);
    levels.Fill(0);    
    Array2dIter2C<ByteT,ChainPixelC> it(img,pixs,img.Frame());
    ByteT lmin = it.Data1();
    ByteT lmax = it.Data1();
    for(;it;it++) {
      ByteT val = it.Data1();
      ChainPixelC * &tmp = levels[val]; 
      it.Data2().next = tmp;
      tmp = &it.Data2();
      it.Data2().region = 0;
      if(val < lmin)
	lmin = val;
      if(val > lmax)
	lmax = val;
    }
    valueRange.Min() = (IntT) lmin;
    valueRange.Max() = (IntT) lmax;
    //ONDEBUG(cerr << "Pixel value value range=" << valueRange << " Stride=" << stride << " Area=" << img.Frame().Area() <<"\n");
    return true;
  }
  
  //: Find matching label.
  inline
  ExtremaRegionC * SegmentExtremaC::FindLabel(ChainPixelC *cp) {
    register ExtremaRegionC *lab = cp->region;
    if(lab == 0 || lab->merge == 0) return lab;
    register ExtremaRegionC *at = lab->merge;
    if(at->merge == 0) return at;
    do {
      at = at->merge;
    } while(at->merge != 0);
    // Relabel mappings.
    do {
      register ExtremaRegionC *tmp = lab;
      lab = lab->merge;
      tmp->merge = at;
    } while(lab != at);
    cp->region = at; // This makes things run slightly faster, but we loose info about the pixel.
    return at;
  }

  //: Find the labels around the pixel 'pix'
  // put the results into 'labelArray' which must be at least 4 labels long.
  // The number of labels found is returned.
  inline
  int SegmentExtremaC::ConnectedLabels(ChainPixelC *pix,ExtremaRegionC **labelArray) {
    //cerr << "SegmentExtremaC::ConnectedLabels(), Pix=" << ((void *) pix) << "\n";
    IntT n = 0;
    ExtremaRegionC *l1 = FindLabel(pix + 1);
    ExtremaRegionC *l2 = FindLabel(pix - 1);
    ExtremaRegionC *l3 = FindLabel(pix + stride);
    ExtremaRegionC *l4 = FindLabel(pix - stride);
    if (l1!=0 )                               { labelArray[n++]=l1; }
    if (l2!=0 && l2!=l1)                      { labelArray[n++]=l2; }
    if (l3!=0 && l3!=l1 && l3!=l2)            { labelArray[n++]=l3; }
    if (l4!=0 && l4!=l1 && l4!=l2 && l4!=l3)  { labelArray[n++]=l4; }
    return n;
  }
  
  //: Add a new region.
  inline
  void SegmentExtremaC::AddRegion(ChainPixelC *pix,IntT level) {
    ExtremaRegionC &region = regionMap[labelAlloc++];
    pix->region = &region;
    //cerr << "SegmentExtremaC::AddRegion(), Pix=" << (void *) pix << " Region=" << (void *) &region << "\n";
    IntT offset = pix - origin;
    region.total = 0;
    region.merge = 0; //&region;
    region.minValue = level;
    region.maxValue = valueRange.Max().V();
    region.minat = Index2dC(offset / stride,offset % stride);
    if(region.hist == 0)
      region.hist = new IntT [limitMaxValue];
    memset(&(region.hist[level]),0,valueRange.Max().V() - level);
    region.hist[level] = 1;
    region.total = 1;
    region.thresh = 0;
    region.closed = 0;
  }
  
  //: Add pixel to region.
  
  inline
  void SegmentExtremaC::AddPixel(ChainPixelC *pix,IntT level,ExtremaRegionC *reg) {
    reg->hist[level]++;
    reg->total++;
    pix->region = reg;
  }

  //: Add pixel to region.
  
  inline
  void SegmentExtremaC::MergeRegions(ChainPixelC *pix,IntT level,ExtremaRegionC **labels,IntT n) {
    ExtremaRegionC *max = labels[0];
    IntT maxValue = labels[0]->total;
    
    // Find largest region.
    int i;
    for(i = 1;i < n;i++) {
      IntT tot = labels[i]->total;
      if(maxValue < tot) {
	max = labels[i];
	maxValue = tot;
      }
    }
    
    // Merge regions, and finalise
    ExtremaRegionC &nr = *max;
    for(i = 0;i < n;i++) {
      if(labels[i] == max)
	continue;
      ExtremaRegionC &oldr = *labels[i];
      oldr.maxValue = level;
      oldr.merge = max;
      oldr.closed = max;
      nr.total += oldr.total;
      nr.hist[level] += oldr.total;
    }
    AddPixel(pix,level,max);
  }
  
  //: Generate regions.
  
  void SegmentExtremaC::GenerateRegions() {
    ChainPixelC *at;
    IntT n, clevel = 0;
    ExtremaRegionC *labels[4];
    for(SArray1dIterC<ChainPixelC *> lit(levels);lit;lit++,clevel++) {
      //ONDEBUG(cerr << "Level=" << clevel << " \n");
      for(at = *lit;at != 0;at = at->next) {
	// Got a pixel.
	//ONDEBUG(cerr << "Pixel=" << (void *) at << " Region=" << at->region << "\n");
	n = ConnectedLabels(at,labels);
 	switch(n) {
	case 0: AddRegion(at,clevel);  break;
	case 1: AddPixel(at,clevel,labels[0]); break;
	default: MergeRegions(at,clevel,labels,n); break;
	}
      }
    }
    //cerr << "Regions labeled = " << labelAlloc << "\n";
  }
  
  //: Generate thresholds
  
  void SegmentExtremaC::Thresholds2() {
    cerr << "SegmentExtremaC::Thresholds2() Called. Margin=" << minMargin << "\n";
    Array1dC<IntT> chist(0,256);
    Array1dC<RealT> nhist(0,256);
    for(SArray1dIterC<ExtremaRegionC> it(regionMap,labelAlloc);it;it++) {
      if(it->total < minSize) {
	it->nThresh = 0;// Ingore these regions.
	continue; 
      }
      ExtremaThresholdC *newthresh = new ExtremaThresholdC[512];
      it->nThresh = 0;
      it->thresh = newthresh;
      IntT maxValue = it->maxValue;
      IntT sum = 0;
      IntT i;
      cerr << "Hist:";
      RealT last = 0;
      IntT lastMax = it->minValue;
      IntT lastAt = it->minValue;
      bool isLow = true;
      for(i = it->minValue;i <= maxValue;i++) {
	sum += it->hist[i];
	chist[i] = sum;
	RealT val = (RealT) it->hist[i] / Sqrt(chist[i]);
	nhist[i] = val;
	if(isLow) {
	  if(val < last) {
	    lastAt = i;
	    last = val;
	    continue;
	  }
	  if(val > (last + minMargin) ) {
	    cerr << "\nThresh=" << lastAt << "\n";
 	    isLow = false;
	    newthresh[it->nThresh++].thresh = lastAt;
	  }
	} else {
	  if(val > last) {
	    lastAt = i;
	    last = val;
	    continue;
	  }
	  if(val  < (last - minMargin) ) {
	    cerr << "\nMax at=" << val << "\n";
	    isLow = true;
	    lastMax = i;
	    last = val;
	  }
	}
	cerr << " " << nhist[i];	
      }
      cerr << "\n";
      //      it->nThresh = 0;// Ingore these regions.
    }
  }
  
  //: Generate thresholds
  
  void SegmentExtremaC::Thresholds() {
    //cerr << "SegmentExtremaC::Thresholds() ********************************************** \n";
    ExtremaThresholdC thresh[257];
    IntT nthresh;
    Array1dC<IntT> chist(0,257);
    for(SArray1dIterC<ExtremaRegionC> it(regionMap,labelAlloc);it;it++) {
      if(it->total < minSize) {
	it->nThresh = 0;// Ingore these regions.
	continue; 
      }
      if((it->maxValue - it->minValue) < 2)
	continue; // Not enough levels in the region.
#if 0
      ExtremaThresholdC *newthresh = new ExtremaThresholdC[2];
      it->thresh = newthresh;
      it->thresh[0].thresh = (it->maxValue + it->minValue)/2; 
      it->nThresh = 1; 
#else
      // Build the cumulative histogram.
      IntT maxValue = it->maxValue;
      IntT sum = 0;
      IntT i;
#if 0
      //cerr << "Hist= " << it->minValue << " :";
      for(i = it->minValue;i <= maxValue;i++) {
	sum += it->hist[i];
	chist[i] = sum;
	//cerr << " " << it->hist[i] ;
      }
#else
      // Smooth the histogram.
      sum = (it->hist[it->minValue] + it->hist[it->minValue+1]) / 2;
      chist[it->minValue] = sum;
      for(i = it->minValue+1;i < maxValue;i++) {
	sum += (it->hist[i] + it->hist[i-1] + it->hist[i+1])/3;
	chist[i] = sum;
	//cerr << " " << it->hist[i] ;
      }
      sum += (it->hist[maxValue] + it->hist[maxValue-1]) / 2;
      chist[maxValue] = sum;
#endif
      //cerr << "\n";
      IntT up;
      // look for threshold that guarantee area bigger than minSize.
      for(i = it->minValue; i <= maxValue;i++)
	if(chist[i] >= minSize) break; 
      // Find thresholds.
      nthresh = 0;
      //cerr << "Min=" << it->minValue << " Max=" << maxValue << " Init=" << i << "\n";
      for(up=i+1; up <= maxValue; i++) {
	int area_i = chist[i];
	if(area_i > maxSize) {
	  //cerr << "Size limit reached. \n";
	  break; // Quit if area is too large.
	}
	int half_perimeter_i = (int)(2 * sqrt((double)area_i));
	while((chist[up] - area_i) < half_perimeter_i && up <= maxValue)
	  up++;
	
	int margin = up - i;
	//cerr << " Margin=" << margin << "\n";
	if(margin > minMargin ) { // && margin > prevMargin
	  ExtremaThresholdC &et = thresh[nthresh++];
	  et.pos = i;
 	  et.margin = margin;
	  et.thresh = i + margin/2;
	  // cerr << " Threshold=" << et.thresh << " " << chist[et.thresh] << "\n";
	}
      }
      ExtremaThresholdC *newthresh = new ExtremaThresholdC[nthresh];
      IntT nt = 0;
      if(nthresh > 2) {
	if(thresh[0].margin > thresh[1].margin)
	  newthresh[nt++] = thresh[0];
      }
      for(int j = 1;j < nthresh-1;j++) {
	//cerr << " Threshold=" << thresh[i].margin << "\n";
#if 1
	ExtremaThresholdC &next = thresh[j+1];
	ExtremaThresholdC &cur = thresh[j];
	ExtremaThresholdC &prev = thresh[j-1];
	if(next.margin < cur.margin && prev.margin < cur.margin) {
	  //cerr << " Using=" << thresh[i].margin << "\n";
	  newthresh[nt++] = cur;
	}
#else
	newthresh[nt++] = thresh[j];
#endif
      }
      if(nthresh > 2) {
	if(thresh[nthresh-2].margin < thresh[nthresh-1].margin)
	  newthresh[nt++] = thresh[nthresh-1];
      }
      if(nt > 0) {
	it->thresh = newthresh;
	it->nThresh = nt;
      } else {
	it->nThresh = 0;
	delete newthresh;
      }
#endif
      //cerr << "Thresholds=" << nthresh << " Kept=" << it->nThresh << "\n";
    }
    //cerr << "SegmentExtremaC::Thresholds() Interesting regions=" << regions <<" \n";
  }
  
  inline
  bool SegmentExtremaC::AddIfInside(BlkQueueC<Index2dC> &q,ImageC<IntT> &marki,IntT id,IntT thresh,Index2dC at) {
    if(!marki.Contains(at))
      return true;
    if(img[at] > thresh)
      return true; // Is outside the region.
    if(marki[at] != id) {
      // Put in to do list.
      marki[at] = id;
      q.InsLast(at);
    }
    return false;
  }
  
  inline 
  void SegmentExtremaC::AddPixels(BlkQueueC<Index2dC> &queue,DListC<EdgeC> &boundary,ImageC<IntT> &marki,IntT id,IntT thresh,Index2dC at) {
    if(AddIfInside(queue,marki,id,thresh,at + Index2dC(0,1)))
      boundary.InsLast(EdgeC(at,CR_UP));
    if(AddIfInside(queue,marki,id,thresh,at + Index2dC(0,-1)))
      boundary.InsLast(EdgeC(at,CR_DOWN));
    if(AddIfInside(queue,marki,id,thresh,at + Index2dC(1,0)))
      boundary.InsLast(EdgeC(at,CR_RIGHT));
    if(AddIfInside(queue,marki,id,thresh,at + Index2dC(-1,0)))
      boundary.InsLast(EdgeC(at,CR_LEFT));
  }
  
  //: Grow a single region.
  
  DListC<BoundaryC> SegmentExtremaC::GrowRegion(ExtremaRegionC &region,ImageC<IntT> &marki,IntT &id) {
    DListC<BoundaryC> ret;
    BlkQueueC<Index2dC> queue;
    //cerr << " Thresholds=" << region.nThresh << "\n";
    BoundaryC last;
    for(int i = 0;i < region.nThresh;i++) {
      queue.InsLast(region.minat);
      DListC<EdgeC> boundary;
      int thresh = region.thresh[i].thresh;
      //cerr << "Thresh=" << thresh << "\n";
      id++;
      queue.InsLast(region.minat);
#if 0
      if(!last.IsEmpty()) {
	for(DLIterC<EdgeC> it(last);it;it++)
	  AddPixels(queue,boundary,marki,thresh,it->LPixel());
      }
#endif
      while(!queue.IsEmpty())
	AddPixels(queue,boundary,marki,id,thresh,queue.GetFirst());
      last = BoundaryC(boundary,true);
      ret.InsLast(last);
    }
    return ret;
  }
  
  //: Grow regions.
  
  DListC<BoundaryC> SegmentExtremaC::GrowRegions() {
    //cerr << "SegmentExtremaC::GrowRegions() \n";
    ImageC<IntT> marki(img.Frame());
    marki.Fill(0);
    IntT id = 0;
    ImageC<ByteT> dimg(pixs.Frame());
    dimg.Fill(0);
    
    DListC<BoundaryC> bounds;
    for(SArray1dIterC<ExtremaRegionC> it(regionMap,labelAlloc-1);it;it++) {
      if(it->nThresh > 0)
	bounds += GrowRegion(*it,marki,id);
      if(it->thresh != 0) {
	delete [] it->thresh;
	it->thresh = 0;
      }
    }
    
    return bounds;
  }
  
}
