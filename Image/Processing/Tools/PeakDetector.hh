// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_PEAKDETECTOR_HEADER
#define RAVLIMAGE_PEAKDETECTOR_HEADER 1
//! rcsid="$Id$"
//! lib=RavlImageProc
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.Images.Misc"

#include "Ravl/Array2d.hh"
#include "Ravl/Index2d.hh"

namespace RavlImageN {
  using namespace RavlN;
  
  template<class DataT>
  inline 
  bool PeakDetect3(const Array2dC<DataT> &img,const Index2dC &pos) {
    const DataT *rt = &(img[pos]);
    const DataT &cent = rt[0];
    if(rt[-1] >= cent || rt[1] >= cent)
      return false;
    rt = &(img[pos[0]-1][pos[1]]);
    if(rt[-1] >= cent || rt[0] >= cent || rt[1] >= cent)
      return false;
    rt = &(img[pos[0]+1][pos[1]]);
    return (rt[-1] < cent && rt[0] < cent && rt[1] < cent);
  }
  //: Test if position 'pos' is the largest value in a 3 by 3 area.
  // Is is the users responsibility to ensure that all pixels around 'pos'
  // are in the image.

  template<class DataT>
  inline
  bool PeakDetect5(const Array2dC<DataT> &img,const Index2dC &pos) {
    const DataT *rt = &(img[pos]);
    const DataT &cent = rt[0];
    IntT cc = pos[1].V();
    IntT cr = pos[0].V();
    // Check the middle row first as we already have a pointer to it.
    if(rt[-2] >= cent || rt[-1] >= cent || rt[1] >= cent || rt[2] >= cent)
      return false;
    
    rt = &(img[cr-1][cc]);
    if(rt[-2] >= cent || rt[-1] >= cent || rt[0] >= cent || rt[1] >= cent || rt[2] >= cent)
      return false;

    rt = &(img[cr+1][cc]);
    if(rt[-2] >= cent || rt[-1] >= cent || rt[0] >= cent || rt[1] >= cent || rt[2] >= cent)
      return false;

    rt = &(img[cr-2][cc]);
    if(rt[-1] >= cent || rt[0] >= cent || rt[1] >= cent)
      return false;
        
    rt = &(img[cr+2][cc]);
    if(rt[-1] >= cent || rt[0] >= cent || rt[1] >= cent)
      return false;
    return true;
  }
  //: Test if position 'pos' is the largest value in a 5 by 5 area.
  // Is is the users responsibility to ensure that all pixels around 'pos'
  // are in the image.  The corners of the area are not mask to bring
  // the area checked closer to a circle.

  template<class DataT>
  inline
  bool PeakDetect7(const Array2dC<DataT> &img,const Index2dC &pos) {
    const DataT *rt = &(img[pos]);
    const DataT &cent = rt[0];
    IntT cc = pos[1].V();
    IntT cr = pos[0].V();
    // Check the middle row first as we already have a pointer to it.
    if(rt[-3] >= cent || rt[-2] >= cent || rt[-1] >= cent || rt[1] >= cent || rt[2] >= cent || rt[3] >= cent)
      return false;
    
    rt = &(img[cr-1][cc]);
    if(rt[-3] >= cent || rt[-2] >= cent || rt[-1] >= cent || rt[0] >= cent || rt[1] >= cent || rt[2] >= cent || rt[3] >= cent)
      return false;
    
    rt = &(img[cr+1][cc]);
    if(rt[-3] >= cent || rt[-2] >= cent || rt[-1] >= cent || rt[0] >= cent || rt[1] >= cent || rt[2] >= cent || rt[3] >= cent)
      return false;
    
    rt = &(img[cr-2][cc]);
    if(rt[-2] >= cent || rt[-1] >= cent || rt[0] >= cent || rt[1] >= cent || rt[2] >= cent)
      return false;
    
    rt = &(img[cr+2][cc]);
    if(rt[-2] >= cent || rt[-1] >= cent || rt[0] >= cent || rt[1] >= cent || rt[2] >= cent)
      return false;
    
    rt = &(img[cr-3][cc]);
    if(rt[-1] >= cent || rt[0] >= cent || rt[1] >= cent)
      return false;

    rt = &(img[cr+3][cc]);
    if(rt[-1] >= cent || rt[0] >= cent || rt[1] >= cent)
      return false;
    return true;
  }
  //: Test if position 'pos' is the largest value in a 7 by 7 area.
  // Is is the users responsibility to ensure that all pixels around 'pos'
  // are in the image.  The corners of the area are not mask to bring
  // the area checked closer to a circle.
  
}



#endif
