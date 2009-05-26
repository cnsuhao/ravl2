// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef IPSUBSAMPLE_HEADER
#define IPSUBSAMPLE_HEADER 1
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImage

#include "amma/Image.hh"
#include "amma/Image/SubSamp2Intl.hh"
#include "amma/DP/Process.hh"

template<class PixelT>
class IPSubSampleBodyC
  : public DPProcessBodyC<ImageC<PixelT>,ImageC<PixelT> >
{
 public:
  IPSubSampleBodyC()
    {}
  
  virtual ImageC<PixelT> Apply (const ImageC<PixelT> &procIn) {    
    ImageRectangleC prect(procIn.Rectangle());
    ImageRectangleC orect(((prect.Rnum() - 1)/2)+1,((prect.Cnum() - 1)/2)+1);
    ImageC<PixelT> ret(orect);
    
    IndexT atrow = procIn.TRow();
    IndexT brow  = procIn.BRow();
    
    IndexT off  = procIn.LCol();
    IndexT off2  = orect.LCol();
    IntT width   = orect.Cnum();;
    IndexT outRow = orect.TRow();
    
    for(;atrow < brow;outRow++) {
      const PixelT *pin1  = &(procIn[atrow++][off]);
      const PixelT *pin2  = &(procIn[atrow++][off]);
      PixelT *pout = &(ret[outRow][off2]);
      PixelT *pend = &pout[width];
      for(;pout != pend;pout++,pin1++,pin2++)
	*pout = StdMath::Average(*pin1,*(++pin1),*pin2,*(++pin2));
    }
    
    return ret;
  }
  
 protected:
};


template<class PixelT>
class IPSubSampleC
  : public DPProcessC<ImageC<PixelT>,ImageC<PixelT> >
{
 public:
  IPSubSampleC()
    : DPProcessC<ImageC<PixelT>,ImageC<PixelT> >(*new IPSubSampleBodyC<PixelT>())
    {}
  //: Default constructor.
  
};


#endif
