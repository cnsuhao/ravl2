// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_SUBSAMPLE_HEADER
#define RAVLIMAGE_SUBSAMPLE_HEADER 1
////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Images.Warping"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Tools/SubSample.hh"
//! author="Charles Galambos"

#include "Ravl/Image/Image.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/Array2dIter.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  
  



  
  
  template<class PixelT>
  ImageC<PixelT> SubSample(const  ImageC<PixelT> & img,  const UIntT factor =2) {    
    ImageRectangleC oldRect  (img.Rectangle() ) ; 
    ImageRectangleC newRect = oldRect / factor ; 
    ImageC<PixelT>  subSampled (newRect) ;
    Array2dIterC<PixelT> newImage  ( subSampled ) ; 
    IndexC oldRow ;
    for ( oldRow = oldRect.TRow() , newImage.First() ; (oldRow <= oldRect.BRow()) && (newImage.IsElm()) ; oldRow+= factor  ) 
      {
	for ( BufferAccessIterC<PixelT> oldCol = img [oldRow] ; (oldCol.IsElm()) && (newImage.IsElm()) ; oldCol += factor, ++newImage  ) 
	  newImage.Data() = oldCol.Data() ;
      }
    return subSampled ; 
  }
  //: Subsamples the image by the given factor 
  // Pixel at top left-hand corner is always sampled first. 
  




  template <class PixelT> 
  ImageC <PixelT> UpSample ( const ImageC<PixelT> & img, const UIntT factor=2 ) {
    ImageRectangleC oldRect (img.Rectangle() ) ; 
    ImageRectangleC newRect ( oldRect * factor ) ; 
    ImageC<PixelT> upSampled ( newRect ) ;  
    
    // iterate thougth rows of origial image 
    IndexC oldRow , newRow ; 
    UIntT counter ; 
    for ( oldRow = oldRect.TRow() , newRow = newRect.TRow() ; oldRow <= oldRect.BRow() ; ++ oldRow ) 
      {
	// iterate through rows of upsampled image 
	for ( UIntT rowCounter = 1 ; (newRow <= newRect.BRow() ) && ( rowCounter <= factor) ; ++ newRow , ++ rowCounter )
	  {
	    BufferAccessIterC<PixelT> newCol ( upSampled [newRow] ) ; 
	    BufferAccessIterC<PixelT>  oldCol ( img[oldRow] ) ; 
	    // now iterate the cols and do the copy 
	    for (  ; oldCol.IsElm() ; oldCol++ ) // each pixel in the old row  
	      // iterate through cols of the new image 
	      for ( counter = 1 ; newCol && counter <= factor ; ++ counter,  newCol++  ) 
		newCol.Data() = oldCol.Data() ; 
	  }
      }
    return upSampled ;     
  }
  //: Up-Samples an image by the given factor. 
  

}


#endif
