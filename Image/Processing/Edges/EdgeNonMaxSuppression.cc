// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImage

#include "Ravl/Image/EdgeNonMaxSuppression.hh"
#include "Ravl/Array2dIter3.hh"
#include "Ravl/StdMath.hh"
#include "Ravl/SArray1d.hh"


#if RAVL_USE_PARALLEL
#include "Ravl/Threads/Launch.hh"
using namespace PThread;
static const IntT numberOfCPUs = 4;
#endif

namespace RavlImageN {
  using namespace RavlN;
  
  // Check for diagonal
  static inline
  bool IsDiag(RealT A,RealT xp,RealT yp,RealT xyp,RealT dr,RealT dc) {
    RealT adr = Abs(dr);
    RealT adc = Abs(dc);
    return A > xp + ((A+xp+yp+xyp)/4 - xp)*adc/(adr+adc);
  }

  bool EdgeNonMaxSuppressionBodyC::Apply(const ImageC<RealT> & inDrIm, 
					 const ImageC<RealT> & inDcIm,  
					 const ImageC<RealT> & inGrad,
					 ImageC<RealT> & res,
					 RealT &meanVal
					 ) {
    
    ImageRectangleC rect(inDrIm.Rectangle());
    rect.ClipBy(inDcIm.Rectangle());
    rect.ClipBy(inGrad.Rectangle());
    if(!res.IsEmpty())
      res = ImageC<RealT>(rect);
    else
      rect.ClipBy(res.Rectangle());
    rect.Erode();
    meanVal = 0;
#if RAVL_USE_PARALLEL
    IntT nrows = rect.Rnum();
    IntT ncols = rect.Cnum();
    IntT numChunks = numberOfCPUs;
    IntT chunkSize = nrows / numChunks;
    
    if(chunkSize < 20 || ncols < 50) {
#endif
      // Not worth doing anything clever.

      DoNonMaxSupp(res,meanVal,
		   inDrIm,inDcIm,inGrad,
		   rect.TRow().V(),rect.BRow().V());
#if RAVL_USE_PARALLEL
      return Tuple2C<ImageC<RealT>,RealT>(res,meanVal);
    }
    
    // Ok do it in parrallel.
    int endRow,startRow = rect.TRow().V();
    SArray1dC<LaunchEventC> events(numChunks);
    SArray1dC<RealT> meanValues(numChunks);
    EdgeNonMaxSuppressionC me(*this);
    
    ImageC<RealT> img1(imgs.Data1());
    ImageC<RealT> img2(imgs.Data2());
    
    for(int i = 0; i< numChunks;i++) {
      endRow = startRow + chunkSize;
      if(endRow > rect.BRow())
	endRow = rect.BRow().V();
      events[i] = ThreadLaunch(me,&EdgeNonMaxSuppressionC::DoNonMaxSupp,res,meanValues[i],imgs,startRow,endRow);
      startRow = endRow+1;
    }
    // Wait for everything to finish.
    meanVal = 0;
    for(int i = 0; i< numChunks;i++) {
      events[i].Done().Wait();
      meanVal += meanValues[i];
    }
    meanVal /= numChunks;
#endif
    return true;
  }


  // FIXME:- This could do with some work, if it used iterators it would be faster.
  
  void 
  EdgeNonMaxSuppressionBodyC::DoNonMaxSupp(ImageC<RealT> &res,
					   RealT &meanRes,
					   const ImageC<RealT> & drIm, 
					   const ImageC<RealT> & dcIm,  
					   const ImageC<RealT> & grad,
					   IntT startRow,IntT endRow
					   ) {
    
    RealT meanVal = 0;
    IntT points = 0;
    ImageC<RealT> & nonMax = res;
    
    ImageRectangleC rect(res.Rectangle());
    rect.Origin().Row() = startRow;
    rect.End().Row() = endRow;
    
    const IndexC minRow = rect.TRow();
    const IndexC maxRow = rect.BRow();
    const IndexC minCol = rect.LCol();
    const IndexC maxCol = rect.RCol();
  
    // Search of local maxima with linear interpolation
    // =================================================
    
    // The value of grad in the center is compared with the value 
    // in the direction determined by dx and dc which is estimated
    // using linear interpolation of values in the neighborhood of the
    // center value.
    
    //      * 5 * 4 *           o -- dc      top
    //      6       3           |
    //      *   *   *           dr           mid
    //      7       2
    //      * 8 * 1 *                        bot
    
    // It should be checked for 8 possibilities (octants), but 
    // the they are symmetrical.
    // The expression (yx-ya) * ty > (yb-ya)*tx   is used instead of
    // yx > ya + (yb-ya) * tx/ty.
    
    for (IndexC i = minRow; i <= maxRow; ++i) {
      const BufferAccessC<RealT> top = grad[i-1];
      const BufferAccessC<RealT> mid = grad[i];
      const BufferAccessC<RealT> bot = grad[i+1];
      
      for (IndexC j = minCol; j <= maxCol; ++j) {
	bool    isMaximum = false;
	RealT       dr        = drIm[i][j]; // direction of gradient
	RealT       dc        = dcIm[i][j];
	const RealT cen       = mid[j.V()];
	
	if (dc <0) { // work in octants 1,2,3,4 by making dc positive
	  dc = -dc;
	  dr = -dr;
	}
	
	if(dc != 0.0 || dr != 0.0 )
	  if(dr >= 0) { // octant 1 or 2 
	    if(dr > dc) // octant 1
	      isMaximum =   (bot[j+1]-bot[j])*dc <= (cen-bot[j])*dr
		&& (top[j-1]-top[j])*dc <  (cen-top[j])*dr; 
	    else  // octant 2
	      isMaximum =   (bot[j+1]-mid[j+1])*dr <  (cen-mid[j+1])*dc  
		&& (top[j-1]-mid[j-1])*dr <= (cen-mid[j-1])*dc; 
	  } else { // octant 3 or 4 
	    if(-dr < dc) // octant 3
	      isMaximum =   (mid[j-1]-bot[j-1])*dr <= (cen-mid[j-1])*dc 
		&& (mid[j+1]-top[j+1])*dr <  (cen-mid[j+1])*dc;
	    else // octant 4
	      // comparison reversed by negative dr
	      isMaximum =   (bot[j] - bot[j-1])*dc >= (cen-bot[j])*dr
		&& (top[j] - top[j+1])*dc >  (cen-top[j])*dr;
	  }
	
	if (isMaximum)  {
	  nonMax[i][j] = cen;
	  meanVal += cen;
	  points++;
	}
	else
	  nonMax[i][j] = 0.0;
        
      } // end of for j
    } // end of for i
    
    // converting from 4 to 8 way connectivity
    
    if (eightConnectivity) {
      for (IndexC i = minRow; i <= maxRow; ++i) {
	const BufferAccessC<RealT> top = grad[i-1];
	const BufferAccessC<RealT> mid = grad[i];
	const BufferAccessC<RealT> bot = grad[i+1];
	
	for (IndexC j = minCol; j <= maxCol; ++j)
	  if(nonMax[i][j] != 0) {
	    RealT i1 = nonMax[i-1][j];
	    RealT i2 = nonMax[i][j-1];
	    RealT i3 = nonMax[i+1][j];
	    RealT i4 = nonMax[i][j+1];
	    bool isConnected =  ((i1  > 0) && (i2  > 0))
	      ||((i2  > 0) && (i3  > 0))
	      ||((i3  > 0) && (i4  > 0))
	      ||((i4  > 0) && (i1  > 0));
	    if (isConnected) {
	      bool isMaximum = false;
	      RealT dr = drIm[i][j];
	      RealT dc = dcIm[i][j];
	      RealT cen = mid[j];
	      if (Abs(dr) >= Abs(dc) ){
		if (dr*dc > 0)
		  isMaximum =   IsDiag(cen,mid[j+1],bot[j],bot[j+1],dr,dc)
		    && IsDiag(cen,mid[j-1],top[j],top[j-1],dr,dc);
		else
		  isMaximum =   IsDiag(cen,mid[j+1],top[j],top[j+1],dr,dc)
		    && IsDiag(cen,mid[j-1],bot[j],bot[j-1],dr,dc);
	      } else {
		if (dr*dc > 0)
		  isMaximum =   IsDiag(cen,bot[j],bot[j],bot[j+1],dc,dr)
		    && IsDiag(cen,top[j],mid[j-1],top[j-1],dc,dr);
		else 
		  isMaximum =   IsDiag(cen,bot[j],mid[j-1],bot[j-1],dc,dr)
		    && IsDiag(cen,top[j],mid[j+1],top[j+1],dc,dr);
	      }
	      if (!isMaximum) { 
		nonMax[i][j] = 0;
		meanVal -= cen;
		points--;
	      }
	    } // end of connect  
	  } // end of nonMax > 0
      } 
    } // end of do four conn suppresion
    
    if(points != 0)
      meanRes = meanVal / points;
    else
      meanRes = 0;
  }
  
}
