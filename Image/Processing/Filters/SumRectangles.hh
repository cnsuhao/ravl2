// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_SUMRECTANGLES_HEADER
#define RAVLIMAGE_SUMRECTANGLES_HEADER 1
//! rcsid="$Id$"
//! lib=RavlImageProc
//! author="Charles Galambos"
//! date="7/1/2003"
//! docentry="Ravl.Images.Filtering"

#include "Ravl/Array2d.hh"
#include "Ravl/IndexRange2d.hh"
#include "Ravl/Array1dIter3.hh"
#include "Ravl/Array2dIter3.hh"

namespace RavlImageN {
  using namespace RavlN;
  
  template<class InT,class OutT> 
  void SumRectangles(const Array2dC<InT> &iimg,
		     const IndexRange2dC &mask,
		     Array2dC<OutT> &result) 
  {
    Array2dC<InT> img(iimg);
    IndexRange2dC resultFrame(img.Frame());
    resultFrame -= mask;
    
    if(result.IsEmpty())
      result = Array2dC<OutT>(resultFrame);
    else
      resultFrame.ClipBy(result.Frame());
    
    IndexRange2dC initialRect = mask;
    initialRect.SetOrigin(img.Frame().Origin());
    
    Array1dC<OutT> vsum(img.Range2());
    
    // Setup vertical sums.
    
    for(Array1dIterC<OutT> itf(vsum);itf;itf++) {
      Slice1dC<InT> pr = img.SliceColumn(itf.Index());
      SetZero(*itf);
      for(Slice1dIterC<InT> it(pr,initialRect.Range1());it;it++)
 	*itf += *it;
    }
    
    // Do first row.
    
    OutT sum;
    SetZero(sum);
    IndexRangeC initRange(img.Frame().LCol(),result.Frame().LCol());
    for(BufferAccessIterC<OutT> itbfr(vsum,initRange);itbfr;itbfr++)
      sum += *itbfr;
    
    for(Array1dIter3C<OutT,OutT,OutT> itfr(result.SliceRow(result.Frame().TRow()),result.Frame().Range2(),
					   vsum,result.Frame().Range2() + mask.LCol(),
					   vsum,result.Frame().Range2() + mask.RCol());itfr;itfr++) {
      sum += itfr.Data3();
      itfr.Data1() = sum;
      sum -= itfr.Data2();
    }
    
    // Sum rest of image.

    IndexRange2dC rngTR(resultFrame + mask.TopRight());
    IndexRange2dC rngBR(resultFrame + mask.BottomRight());
    
    resultFrame.TRow()++;
    IndexC trow = rngTR.TRow();
    IndexC brow = ++rngBR.TRow();
    IndexC restMin = result.Frame().LCol()+1;
    
    for(Array2dIter3C<OutT,InT,InT> it(result,resultFrame,img,rngTR,img,rngBR);it;) {
      // Do begining of row.
      SetZero(sum);
      for(BufferAccessIter3C<OutT,InT,InT> itbfr(vsum,initRange,
						 img[trow++],initRange,
						 img[brow++],initRange);itbfr;itbfr++) {
	itbfr.Data1() += itbfr.Data3();
	itbfr.Data1() -= itbfr.Data2();
	sum += itbfr.Data1();
      }
      
      // And the rest...
      OutT *sat = &(vsum[restMin]);
      OutT *satn = &(vsum[initRange.Min()]);
      do {
	*sat += it.Data3();
	*sat -= it.Data2();
	sum += *sat;
	it.Data1() =  sum;
	sum -= *satn;
	sat++;
	satn++;
      } while(it.Next()) ;
    }
  }
  //! userlevel=Normal
  //: Calculate the sum of a rectangular window sliding across an image.
  
}


#endif
