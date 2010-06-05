// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_DRAWCIRCLE_HEADER
#define RAVLIMAGE_DRAWCIRCLE_HEADER 1
///////////////////////////////////////////////////////////////////
//! rcsid="$Id: DrawCircle.hh 5240 2005-12-06 17:16:50Z plugger $"
//! author="Charles Galambos"
//! date="8/8/2002"
//! docentry="Ravl.API.Images.Drawing"
//! lib=RavlImage
//! userlevel=Normal
//! file="Ravl/Image/Base/DrawCircle.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/CircleIter.hh"

namespace RavlImageN {
  
  template<class DataT>
  void DrawCircle(Array2dC<DataT> &dat,const DataT &value,const Index2dC &center,IntT radius ) {
    if(dat.Frame().Contains(center + Index2dC(radius,radius)) && dat.Frame().Contains(center - Index2dC(radius,radius))) {
      // If far diagonals are inside the image, all pixels in between are.
      for(CircleIterC it(radius,center);it;it++)
	dat[*it] = value;
      return ;
    }
    for(CircleIterC it(radius,center);it;it++) {
      if(!dat.Contains(*it)) 
	continue;
      dat[*it] = value;
    }
  }
  //: Draw a circle in an image.
  
}

#endif
