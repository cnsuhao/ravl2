// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_IMAGE_HEADER
#define RAVLIMAGE_IMAGE_HEADER 1
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/Image.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images"
//! example=exImage.cc

#include "Ravl/Array2d.hh"
#include "Ravl/TFVector.hh"
#include "Ravl/Image/ImageRectangle.hh"

namespace RavlImageN {
  using namespace RavlN;
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using RavlN::Array2dC;
  using RavlN::UIntT;
  using RavlN::IndexRangeC;
  using RavlN::BufferC;
  using RavlN::TFVectorC;
  using RavlN::RealT;
  using RavlN::ByteT;
#endif
  
  //! userlevel=Normal
  //: Basic Image
  
  template <class PixelT>
  class ImageC
    : public Array2dC<PixelT>
  {
  public:
    ImageC()
    {}
    //: Default constructor.
    // creates an empty image.
    
    ImageC(const Array2dC<PixelT> &oth)
      : Array2dC<PixelT>(oth)
    {}
    //: Base constructor.
    
    ImageC(const IndexRange2dC &rng)
      : Array2dC<PixelT>(rng)
    {}
    //: Create an image of size 'rng'
    
    ImageC(const IndexRange2dC &rng,const PixelT &val)
      : Array2dC<PixelT>(rng)
    { Fill(val); }
    //: Create an image of size 'rng' filled with value 'val'
    
    ImageC(const Array2dC<PixelT> &oth,const IndexRange2dC &rect)
      : Array2dC<PixelT>(oth,rect)
    {}
    //: Construct an image as a sub rectangle 'rect' on oth.
    
    ImageC(UIntT rows,UIntT cols)
      : Array2dC<PixelT>(rows,cols)
    {}
    //: Construct an image with origin 0,0 and size rows cols.
    
    ImageC(IndexC rows,IndexC cols)
      : Array2dC<PixelT>(rows.V(),cols.V())
    {}
    //: Construct an image with origin 0,0 and size rows cols.
    
    ImageC(const IndexRangeC &rows,const IndexRangeC &cols)
      : Array2dC<PixelT>(rows,cols)
    {}
    //: Construct an image with the given range of indexes.
    
    ImageC(UIntT rows,UIntT cols,const BufferC<PixelT> &buf)
      : Array2dC<PixelT>(IndexRange2dC(0,rows-1,0,cols-1),buf)
    {}
    //: Construct an image with origin 0,0 and size rows cols with space in 'buf'
    
    ImageC(UIntT rows,UIntT cols,PixelT *data,bool deletable = true)
      : Array2dC<PixelT>(IndexRange2dC(0,rows-1,0,cols-1),BufferC<PixelT>(rows * cols,data,false,deletable))
    {}
    //: Construct an image with origin 0,0 and size rows cols with space in 'buf'
    
    UIntT Rows() const
    { return Range1().Size(); }
    //: Number of rows in image.
    
    UIntT Cols() const
    { return Range2().Size(); }
    //: Number of rows in image.
    
    inline IndexC TRow() const
    { return Range1().Min(); }
    // Returns the top row index.
    
    inline IndexC LCol() const
    { return Range2().Min(); }
    // Returns the left side column index.
    
    inline IndexC BRow() const
    { return Range1().Max(); }
    // Returns the bottom row index.
    
    inline IndexC RCol() const
    { return Range2().Max(); }
    // Returns the right side column index.
    
    PixelT *Row(IndexC row) 
    { return &(RangeBufferAccessC<BufferAccessC<PixelT> >::operator[](row)[rng2.Min()]); }
    //: Get a pointer to begining of row.
    
    ImageC<PixelT> Rotate180(Index2dC centre = Index2dC(0,0)) const;
    //: Create a copy of the image which is rotated 180 degree's.
    // The image is rotated around the center given.
  };
  
  template <class PixelT>
  ImageC<PixelT> ImageC<PixelT>::Rotate180(Index2dC centre) const {    
    ImageC<PixelT> flipped(Rectangle().Rotate180(centre));
    BufferAccess2dIterC<PixelT> it((*this),Range2());
    IntT frow = flipped.BRow().V();
    PixelT *place = &(flipped[frow][flipped.RCol()]);
    while(it.IsElm()) {
      *place = it.Data();
      if(it.Next()) {
        place--;
        continue;
      }
      // Next row ?
      if(!it.IsElm())
        break;
      frow--;
      place = &(flipped[frow][flipped.RCol()]);
    }
    return flipped;
  }
  
  ostream &operator<<(ostream &s,const ImageC<ByteT> &img);
  //: Save byte image to stream 
  // Override default IO to handle byte images correctly.
  
  istream &operator>>(istream &s,ImageC<ByteT> &img);
  //: Load byte image from stream 
  // Override default IO to handle byte images correctly.
  
}

#endif
