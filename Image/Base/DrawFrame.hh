// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_DRAWFRAME_HEADER
#define RAVLIMAGE_DRAWFRAME_HEADER 1
///////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! date="22/04/2002"
//! docentry="Ravl.Images"
//! lib=RavlImage
//! userlevel=Normal

#include "Ravl/Image/Image.hh"

namespace RavlImageN {
  
  template<class DataT>
  void DrawFrame(Array2dC<DataT> &dat,const DataT &value,const IndexRange2dC &rect) {
    IndexRange2dC dr(rect);
    dr.ClipBy(dat.Frame());    
    DataT *it1,*it2,*eor;
    
    it1 = &(dat[rect.TRow()][rect.LCol().V()]);
    it2 = &(dat[rect.BRow()][rect.LCol().V()]);
    IntT ColN = rect.Cols();
    eor = &(it1[ColN]);
    for(;it1 != eor;) {
      *(it1++) = value;
      *(it2++) = value;
    }
    ColN--;
    for(IndexC r = rect.Origin().Row()+1; r < rect.End().Row(); r++) {
      it1 = &(dat[r][rect.LCol().V()]);
      it1[0] = value;
      it1[ColN] = value;
    }
  }
  //: Draw a rectangle in an image.
  
}

#endif
