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


namespace RavlImageN {
  
  //! userlevel=Normal
  
  template<class PixelT>
  ImageC<PixelT> SubSample(const ImageC<PixelT> & img,  const UIntT factor =2) {    
    ImageRectangleC oldRect  (img.Rectangle() ) ; 
    ImageRectangleC newRect = oldRect / factor ; 
    ImageC<PixelT>  subSampled (newRect) ;

    // iterate through rows 
    IndexC oldRow,oldCol, newRow, newCol ;
    for ( oldRow = oldRect.TRow() , newRow=newRect.TRow() ; oldRow <= oldRect.BRow() && newRow <= newRect.BRow() ; ++newRow , oldRow+=factor ) 
      {
	// lets get the whole rows
	RangeBufferAccessC<PixelT> oldRowBuffer = img[oldRow] ; 
	RangeBufferAccessC<PixelT>  newRowBuffer = subSampled[newRow] ; 
	
	// now go through columns and copy the pixels
	for ( oldCol = oldRect.LCol() , newCol = newRect.LCol() ;  oldCol <= oldRect.RCol() && newCol <= newRect.RCol() ; ++newCol, oldCol += factor ) 
	  newRowBuffer[newCol]  = oldRowBuffer[oldCol] ;   
      }
    return subSampled ; 
  }
  //: Subsamples the image by the given factor 
  // Pixel at origin is always sampled first. 

  template <class PixelT> 
  ImageC <PixelT> UpSample ( const ImageC<PixelT> & img, const UIntT factor=2 ) {
    ImageRectangleC oldRect (img.Rectangle() ) ; 
    ImageRectangleC newRect ( oldRect * factor ) ; 
    ImageC<PixelT> upSampled ( newRect ) ;  

    // iterate through rows of original image 
    IndexC oldRow, oldCol, newRow, newCol ; 
    UIntT counter ; 
    for ( oldRow = oldRect.TRow(), newRow = newRect.TRow()  ; oldRow <= oldRect.BRow() ; ++ oldRow  ) 
      {
	RangeBufferAccessC<PixelT> oldRowBuffer = img[oldRow] ; 
	// iterate through rows of upsampled image 
    for (  UIntT rowCounter = 1 ; (newRow <= newRect.BRow()) && (rowCounter <= factor)  ; ++newRow, ++rowCounter  ) 
      {
	RangeBufferAccessC<PixelT> newRowBuffer = upSampled[newRow] ; 
	// iterate through cols and do the copy 
	for ( oldCol = oldRect.LCol() , newCol = newRect.LCol()  ; oldCol <= oldRect.RCol()  ; ++ oldCol  ) // for each pixel in the old row
	    // iterate through cols of new images 
	  {
	  for (  counter = 1 ; newCol <= newRect.RCol() && counter <= factor ; ++ newCol, ++ counter ) // copy to desired number of pixels along new row 
	    { newRowBuffer[newCol] = oldRowBuffer[oldCol] ; }
	  } }}
    
    return upSampled ;     
  }
  //: Up-Samples an image by the given factor. 
   


}


#endif
