// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImage

#include "Ravl/Image/CornerDetectorHarris.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dSqr3111Iter4.hh"
#include "Ravl/Image/PeakDetector.hh"
#include "Ravl/Image/Gradient.hh"
#include "Ravl/MeanVariance.hh"
namespace RavlImageN {
  
  ///////////////////////////////////
  // Constructor.
  
  CornerDetectorHarrisC::CornerDetectorHarrisC(int nTheshold,int nW,RealT Sigma)
    : w(nW),
      threshold(nTheshold),
      mask(Gauss2D(Sigma,nW))
  {}
  
  ImageC<RealT> CornerDetectorHarrisC::Gauss2D(RealT sigma,int w) {
    ImageC<RealT> ret(IndexRangeC(-w,w),IndexRangeC(-w,w));
    int x,y;
    MeanVarianceC mv(1,0,sigma);
    for (x=-w; x<=w; x++) {
      for (y=-w; y<=w; y++)
	ret[y][x] = mv.Gauss((RealT)  x) * mv.Gauss((RealT) y);
    }
    return ret;
  }
  
  DListC<CornerC> CornerDetectorHarrisC::Apply(ImageC<ByteT> &img) {
    ImageC<IntT> var = CornerHarris(img);
    DListC<CornerC> lst;
    Peak(var,img,lst);
    return lst;
  }


  // Haris corner detector.
  
  ImageC<IntT> CornerDetectorHarrisC::CornerHarris(ImageC<ByteT> &img) {
    ImageRectangleC workRect(img.Rectangle().Shrink(1));
    ImageC<IntT> ixix(workRect);
    ImageC<IntT> iyiy(workRect);
    ImageC<IntT> ixiy(workRect);
    ImageC<IntT> var(workRect);               /* cornerness image */
  
    int       x,y;
    RealT    ixixs,iyiys,ixiys;
    
    ImagGrad(img,ixix,iyiy,ixiy);
    ImageRectangleC subWR(workRect.Shrink(w));
    
    for(Array2dIterC<IntT> it(var,subWR);it;it++) {
      Index2dC at = it.Index();
      ixixs = 0.0; 
      iyiys = 0.0; 
      ixiys = 0.0;
      const int i = at[0].V();
      const int j = at[1].V();
      // FIXME:- This convolution could be much faster...
      for (x=-w; x<w; x++) {
	for (y=-w; y<w; y++) {
	  RealT mval = mask[y][x];
	  ixixs += ixix[i+y][j+x]*mval;
	  iyiys += iyiy[i+y][j+x]*mval; 
	  ixiys += ixiy[i+y][j+x]*mval; 
	}
      }
      /* Evaluating the cornerness measure */
      int val;
      if((ixixs+iyiys) != 0)
	val = (int) ((double)((ixixs*iyiys-ixiys*ixiys)/(ixixs+iyiys)));
      else
	val = 0;
      //cerr << "Val=" << val << "\n";
      *it = val;
    }
    return var;
  }
  
  void CornerDetectorHarrisC::ImagGrad(ImageC<ByteT> &img,ImageC<IntT> &ixix,ImageC<IntT> &iyiy,ImageC<IntT> &ixiy) {
    for(Array2dSqr3111Iter4C<ByteT,IntT,IntT,IntT> it(img,ixix,iyiy,ixiy);it;it++) {
      /* Calculation of the gradients in x and y direction */
      const int ix = it.DataBL1() + it.DataML1()*2 + it.DataTL1() - it.DataBR1() - it.DataMR1()*2 - it.DataTR1();        
      const int iy = it.DataTL1() + it.DataTM1()*2 + it.DataTR1() - it.DataBL1() - it.DataBM1()*2 - it.DataBR1();
      it.Data2()=ix*ix;
      it.Data3()=iy*iy;
      it.Data4()=ix*iy;
    }
  }

  
  int CornerDetectorHarrisC::Peak(ImageC<IntT> &result,ImageC<ByteT> &in,DListC<CornerC> &cornLst) {
    IndexRange2dC rect(result.Frame().Shrink(3));
    IntT last = 0;
    Index2dC at;
    bool peak = false;
    int n = 0;
    for(Array2dIterC<IntT> it(result,rect);it;it++) {
      if(*it < threshold) {
	last = 0;
	peak = false;
	continue;
      }
      if(*it >= last) {
 	last = *it;
	at = it.Index();
	peak = false;
	continue;
      }
      if(last >= threshold && !peak) {
	if(PeakDetect7(result,at)) {
	  cornLst.InsLast(CornerC(at,SobelGradient3(in,at),in[at]));
	  n++;
	  peak = true;
	}
      }
      last = *it;
    }
    return n; 
  }
  
}
