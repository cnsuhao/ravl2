// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_DRAWLINE_HEADER
#define RAVLIMAGE_DRAWLINE_HEADER 1
///////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! date="22/04/2002"
//! docentry="Ravl.API.Images.Drawing"
//! lib=RavlImage
//! userlevel=Normal
//! file="Ravl/Image/Base/DrawLine.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Line2dIter.hh"

namespace RavlImageN {
  
  template<class DataT>
  void DrawLine(Array2dC<DataT> &dat,const DataT &value,const Index2dC &from,const Index2dC &to) {
    // FIXME: It would be much better to clip the line here, but for now just check pixels before writing them.
    if(dat.Frame().Contains(from) && dat.Frame().Contains(to)) {
      // If both start and end are inside the image, all pixels in between are.
      for(Line2dIterC it(from,to);it;it++)
	dat[*it] = value;
      return ;
    }
    for(Line2dIterC it(from,to);it;it++) {
      if(!dat.Contains(*it)) 
	continue;
      dat[*it] = value;
    }
  }
  //: Draw a line in an image.

  template<class DataT>
  void DrawLine(Array2dC<DataT> &dat,const DataT &valuefrom,const DataT &valueto,const Index2dC &from,const Index2dC &to) {
    RealT length = sqrt(static_cast<double>((to - from).SumOfSqr().V()));
    // FIXME: It would be much better to clip the line here, but for now just check pixels before writing them.
    if(dat.Frame().Contains(from) && dat.Frame().Contains(to)) {
      // If both start and end are inside the image, all pixels in between are.
      for(Line2dIterC it(from,to);it;it++) {
	RealT alpha = sqrt(static_cast<double>((it.Data() - from).SumOfSqr().V())) / length;
	dat[*it] = DataT((valuefrom*(1-alpha)) + (valueto*alpha));
      }
      return ;
    }
    for(Line2dIterC it(from,to);it;it++) {
      if(!dat.Contains(*it)) 
	continue;
      RealT alpha = sqrt(static_cast<double>((it.Data() - from).SumOfSqr().V())) / length;
      dat[*it] = DataT((valuefrom*(1-alpha)) + (valueto*alpha));
    }
  }
  //: Draw a line in an image, shaded between two colours
  // This function requires that DataT has a working operator*(double) function

}

#endif
