// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGERECTANGLE_HEADER
#define RAVLIMAGERECTANGLE_HEADER 1
////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/ImageRectangle.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images"

#include "Ravl/IndexRange2d.hh"

namespace RavlImageN {
  using namespace RavlN;
  
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using RavlN::IndexRange2dC;
  using RavlN::IntT;
  using RavlN::Index2dC;
  using RavlN::SizeT;
  using RavlN::IndexC;
#endif
  
  //! userlevel=Normal
  //: Image Rectangle.
  
  class ImageRectangleC 
    : public IndexRange2dC
  {
  public:
    ImageRectangleC()
      {}
    //: Default constructor.
    // creates an undefined rectangle.
    
    ImageRectangleC(const IndexRange2dC &oth)
      : IndexRange2dC(oth)
      {}
    //: Base constructor.

    ImageRectangleC(IntT rows,IntT cols)
      : IndexRange2dC(0,rows-1,0,cols-1)
      {}
    //: Construct a rectangle of the given size with an origin of 0,0
    
    ImageRectangleC(const Index2dC &org,const Index2dC &end)
      : IndexRange2dC(org,end)
      {}
    //: Construct from corner points.

    ImageRectangleC(const Index2dC &center,SizeT size)
      : IndexRange2dC(center,size)
    {}
    //: Construct a square from center and size.
    
    ImageRectangleC(const Index2dC &center,SizeT rows,SizeT cols)
      : IndexRange2dC(center,rows,cols)
    {}
    //: Create an 2d range from a center point and a size for rows and cols.
    // Size is the distance from the center to the edge, so
    // a size of 0 gives a single pixel, and a size of 1 generates
    // a 3 long rectangle in that dimention.

    ImageRectangleC(IndexC minRow, IndexC maxRow,
		    IndexC minCol, IndexC maxCol)
      : IndexRange2dC(minRow,maxRow,minCol,maxCol)
      {}
    //: Create rectangle from indvidual values.

    ImageRectangleC & ReflectUp() {
      RowRange() -= RowRange().Size();
      return *this;
    }
    //: Mirrors the image rectangle along its top edge.
    // Returns a refrence to this rectangle.
    
    ImageRectangleC & ReflectDown() {
      RowRange() += RowRange().Size();
      return *this;      
    }
    //: Mirrors the image rectangle along its bottom edge.
    // Returns a refrence to this rectangle.
    
    ImageRectangleC & ReflectLeft() {
      ColRange() -= ColRange().Size();
      return *this;
    }
    //: Mirrors the image rectangle along its left edge.
    // Returns a refrence to this rectangle.
    
    ImageRectangleC & ReflectRight() {
      ColRange() += ColRange().Size();
      return *this;
    }
    //: Mirrors the image rectangle along its right edge.
    // Returns a refrence to this rectangle.
    
  };
  
}




#endif
