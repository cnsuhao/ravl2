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

namespace RavlN {
  
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
    
    ImageRectangleC(const Index2dC &org,const Index2dC &end)
      : IndexRange2dC(org,end)
      {}
    //: Construct from corner points.

    ImageRectangleC(IndexC minRow, IndexC maxRow,
		    IndexC minCol, IndexC maxCol)
      : IndexRange2dC(minRow,maxRow,minCol,maxCol)
      {}
    //: Create rectangle from indvidual values.

  };
}




#endif
