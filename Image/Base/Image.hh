// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_HEADER
#define RAVLIMAGE_HEADER 1
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/Image.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images"

#include "Ravl/Array2d.hh"
#include "Ravl/TFVector.hh"
#include "Ravl/Image/ImageRectangle.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Ya basic Image
  
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
    
    ImageC(UIntT rows,UIntT cols)
      : Array2dC<PixelT>(rows,cols)
      {}
    //: Construct an image with origin 0,0 and size rows cols.

    ImageC(UIntT rows,UIntT cols,const BufferC<PixelT> &buf)
      : Array2dC<PixelT>(IndexRange2dC(0,rows-1,0,cols-1),buf)
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
    
    inline PixelT BiLinear(const TFVectorC<RealT,2> &pnt)  const;
    //: Get a bi linearly interpolated pixel value.
  };
  
  
  template <class PixelT>
  PixelT ImageC<PixelT>::BiLinear(const TFVectorC<RealT,2> &pnt) const {
    RealT fx = Floor(pnt[0]); // Row
    RealT fy = Floor(pnt[1]); // Col
    RealT u = pnt[0] - fx;
    RealT t = pnt[1] - fy;
    IndexC ifx = fx;
    IndexC ify = fy;
    Index2dC y1(ifx+1,ify+1);
    Index2dC y2(ifx+1,ify);
    Index2dC y3(ifx,ify+1);
    Index2dC y4(ifx,ify);
    
    return (PixelT)(((1.0-t) * (1.0-u) * (*this)[y4]) + 
		    (t*(1.0-u)*(*this)[y3]) + 
		    ((1.0-t)*u*(*this)[y2]) +
		    (t*u*(*this)[y1]) 
		    );
  }
  
}

#endif
