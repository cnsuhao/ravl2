// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Segmentation/Segmentation.cc"

#include "Ravl/Image/Segmentation.hh"
#include "Ravl/Array2dSqr2Iter.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/SobolSequence.hh"

namespace RavlImageN {

  //: Generate a table of region adjacencies.
  
  SArray1dC<HSetC<UIntT> > SegmentationBodyC::Adjacency(bool biDir) {
    SArray1dC<HSetC<UIntT> > ret(labels);
    if(biDir) {
      for(Array2dSqr2IterC<UIntT> it(segmap);it;) {
	if(it.DataBR() != it.DataTR()) {
	  ret[it.DataBR()] += it.DataTR();
	  ret[it.DataTR()] += it.DataBR();
	}
	for(;it.Next();) { // The rest of the image row.
	  if(it.DataBR() != it.DataTR()) {
	    ret[it.DataBR()] += it.DataTR();
	    ret[it.DataTR()] += it.DataBR();
	  }
	  if(it.DataBR() != it.DataBL()) {
	    ret[it.DataBR()] += it.DataBL();
	    ret[it.DataBL()] += it.DataBR();
	  }
	}
      }
    } else {
      for(Array2dSqr2IterC<UIntT> it(segmap);it;) {
	if(it.DataBR() != it.DataTR()) {
	  if(it.DataBR() < it.DataTR())
	    ret[it.DataBR()] += it.DataTR();
	  else
	    ret[it.DataTR()] += it.DataBR();
	}
	for(;it.Next();) { // The rest of the image row.
	  if(it.DataBR() != it.DataTR()) {
	    if(it.DataBR() < it.DataTR())
	      ret[it.DataBR()] += it.DataTR();
	    else
	      ret[it.DataTR()] += it.DataBR();
	  }
	  if(it.DataBR() != it.DataBL()) {
	    if(it.DataBR() < it.DataBL())
	      ret[it.DataBR()] += it.DataBL();
	    else
	      ret[it.DataBL()] += it.DataBR();
	  }
	}
      }
    }
    return ret;
  }
  
  //: Generate a table of region adjacencies boundry lengths.
  // only adjacenies from regions with a smaller id to those 
  // with a larger ID are generated
  
  SArray1dC<HashC<UIntT,UIntC> > SegmentationBodyC::BoundryLength() {
    SArray1dC<HashC<UIntT,UIntC> > ret(labels);
    for(Array2dSqr2IterC<UIntT> it(segmap);it;) {
      if(it.DataBR() != it.DataTR()) {
	if(it.DataBR() < it.DataTR())
	  ret[it.DataBR()][it.DataTR()]++;
	else
	  ret[it.DataTR()][it.DataBR()]++;
      }
      for(;it.Next();) { // The rest of the image row.
	if(it.DataBR() != it.DataTR()) {
	  if(it.DataBR() < it.DataTR())
	    ret[it.DataBR()][it.DataTR()]++;
	  else
	    ret[it.DataTR()][it.DataBR()]++;
	}
	if(it.DataBR() != it.DataBL()) {
	  if(it.DataBR() < it.DataBL())
	    ret[it.DataBR()][it.DataBL()]++;
	  else
	    ret[it.DataBL()][it.DataBR()]++;
	}
      }
    }
    return ret;
  }
  
  
  //: recompute the areas from the original areas and a mapping.
  
  SArray1dC<UIntT> SegmentationBodyC::RedoArea(SArray1dC<UIntT> area,SArray1dC<UIntT> map) {
    SArray1dC<UIntT> ret(labels);
    ret.Fill(0);
    for(SArray1dIter2C<UIntT,UIntT> it(area,map);it;it++)
      ret[it.Data2()] += it.Data1();
    return ret;
  }
  
  //: Compute the areas of all the segmented regions.
  
  SArray1dC<UIntT> SegmentationBodyC::Areas() {
    // Compute areas of components
    SArray1dC<UIntT> area(labels);
    area.Fill(0);  // Initilisation
    for(Array2dIterC<UIntT> it(segmap);it;it++)
      area[*it]++;
    return area;
  }
  
  //: Make an array of labels mapping to themselves.
  
  SArray1dC<UIntT> SegmentationBodyC::IdentityLabel() {
    // Make an identity mapping.
    SArray1dC<UIntT> minLab(labels);
    UIntT c = 0;
    for(SArray1dIterC<UIntT> it(minLab);it;it++)
      *it = c++;
    return minLab;
  }
  
//: Compress labels.
  
  UIntT SegmentationBodyC::RelabelTable(SArray1dC<UIntT> &labelTable, UIntT currentMaxLabel) 
    // The 'labelTable' represents a look-up table for labels. 
    // Each item contains a new label which can be the same
    // as the index of the item or smaller. Such 'labelTable' contains
    // a forest of labels, every tree of labels represents one component
    // which should have the same label. It is valid that a root item
    // of a tree has the same label value as the item index.
  {
    SArray1dIterC<UIntT> it(labelTable,currentMaxLabel+1);
    // Make all trees of labels to be with depth one.
    for(;it;it++)
      *it = labelTable[*it];
    
    // Now all components in the 'labelTable' have a unique label.
    // But there can exist holes in the sequence of labels.
    
    // Squeeze the table. 
    UIntT n = 0;                     // the next new label  
    for(it.First();it;it++) {
      UIntT m = labelTable[*it];  // the label of the tree root
      
      // In the case m >= n the item with the index 'l' contains 
      // the root of the new tree,
      // because all processed roots have a label smaller than 'n'.
      // The root label 'm' has the same value as the index 'l'.
      // The root will be relabeled by a new label.
      *it = (m >= n) ? n++ : m;
    }
    
    return n - 1;  // the new last used label
  }
  
  //: Compress newlabs and re-label segmentation.
  
  UIntT SegmentationBodyC::CompressAndRelabel(SArray1dC<UIntT> newLabs) {
    // ------ Compress labels -----
    // First make sure they form a directed tree
    // ending in the lowest valued label. 
    UIntT n = 0;
    for(SArray1dIterC<UIntT> it(newLabs);it;it++,n++) {
      if(*it > n) {
	// Minimize label.
	UIntT nat,at = *it;
	UIntT min = n;
	for(;at > n;at = nat) {
	  nat = newLabs[at];
	  if(nat < min)
	    min = nat;
	  else
	    newLabs[at] = min;	
	}
	*it = min;
      }
    }
    
    // Now we can minimize the labels.
    UIntT newLastLabel = RelabelTable(newLabs,labels-1);
    
    // And relable the image.
    for(Array2dIterC<UIntT> iti(segmap);iti;iti++)
      *iti = newLabs[*iti];
    
    labels = newLastLabel+1;
    return labels;
  }
  
  
  //: Remove small components from map, label them as 0.
  
  UIntT SegmentationBodyC::RemoveSmallComponents(IntT thrSize) {
    if(labels <= 1)
      return labels;
    
    SArray1dC<UIntT> area = Areas();
    
    // Assign new labels to the regions according their sizes and
    // another requirements.
    IntT newLabel = 1;
    SArray1dIterC<UIntT> it(area);
    *it = 0;
    it.Next();
    for(;it;it++) {
      if (*it < ((UIntT) thrSize)) 
	*it = 0;
      else 
	*it = newLabel++;
    }
    
    // Remove small components
    for(Array2dIterC<UIntT> iti(segmap);iti;iti++)
      *iti = area[*iti];
    
    labels = newLabel;
    return newLabel;    
  }

  //: Compute moments for each of the segmented regions.
  // if ignoreZero is true, region labeled 0 is ignored.
  
  SArray1dC<Moments2d2C> SegmentationBodyC::ComputeMoments(bool ignoreZero) {
    SArray1dC<Moments2d2C> ret(labels);
    
    if(ignoreZero) {
      // Ignore regions with label 0.
      for(Array2dIterC<UIntT> it(segmap);it;it++) {
	if(*it == 0)
	  continue;
	ret[*it].AddPixel(it.Index());
      }
    } else {
      for(Array2dIterC<UIntT> it(segmap);it;it++) 
	ret[*it].AddPixel(it.Index());
    }
    return ret;
  }


  ImageC<ByteT> SegmentationBodyC::ByteImage() const {
    ImageC<ByteT> byteimage(segmap.Rectangle());
    Array2dIter2C<UIntT, ByteT> seg_it(segmap, byteimage);
    for(seg_it.First(); seg_it.IsElm(); seg_it.Next())
      seg_it.Data2() = (unsigned char)seg_it.Data1();
    return byteimage;
  }
  
  ImageC<ByteRGBValueC> SegmentationBodyC::RandomImage() const {
    //generate Sobol sequence
    SobolSequenceC sobel_sequence(3);
    SArray1dC<ByteRGBValueC> colours(labels);    
    sobel_sequence.First();
    for (SArray1dIterC<ByteRGBValueC> it(colours);it;it++,sobel_sequence.Next())
      *it = ByteRGBValueC((ByteT) (sobel_sequence.Data()[0]*255), 
			  (ByteT) (sobel_sequence.Data()[1]*255),
			  (ByteT) (sobel_sequence.Data()[2]*255));
    
    //create RGBImage
    ImageC<ByteRGBValueC> rgbimage(segmap.Frame());
    for(Array2dIter2C<UIntT, ByteRGBValueC> seg_it(segmap, rgbimage); seg_it; seg_it++)
      seg_it.Data2() = colours[seg_it.Data1()];
    
    return rgbimage;
  }
  
  ImageC<ByteYUVValueC> SegmentationBodyC::RandomTaintImage(ByteT max) const {
    //generate Sobol sequence
    SobolSequenceC sobol_sequence(2);
    
    SArray1dC<ByteYUVValueC> colours(labels);    
    for (SArray1dIterC<ByteYUVValueC> it(colours);it;it++,sobol_sequence.Next())
      *it = ByteYUVValueC(127, (ByteT) (sobol_sequence.Data()[0]*max), (ByteT)( sobol_sequence.Data()[1]*max));
    
    //create RGBImage
    ImageC<ByteYUVValueC> yuvimage(segmap.Rectangle());
    for(Array2dIter2C<UIntT, ByteYUVValueC> seg_it(segmap, yuvimage); seg_it; seg_it++)
      seg_it.Data2() = colours[seg_it.Data1()];
    return yuvimage;
  }
  
}
