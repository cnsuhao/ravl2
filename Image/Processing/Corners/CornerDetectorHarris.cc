// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImageProc
//! author="Radek Marik, modified by Charles Galambos"
//! date="1/10/1991"

#include "Ravl/Image/CornerDetectorHarris.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/Array2dSqr31Iter2.hh"
#include "Ravl/Image/PeakDetector.hh"
#include "Ravl/Image/Gradient.hh"
#include "Ravl/MeanVariance.hh"
#include "Ravl/Image/ConvolveSeparable2d.hh"
#include "Ravl/GenerateSignal1d.hh"


#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {
  
  ///////////////////////////////////
  // Constructor.
  
  CornerDetectorHarrisBodyC::CornerDetectorHarrisBodyC(int nTheshold,int nW)
    : w(nW),
      threshold(nTheshold)
  {
    Array1dC<IntT> mask = GenerateBinomial((IntT) 1,w,false,true);
    filter = ConvolveSeparable2dC<IntT,TFVectorC<IntT,3>,TFVectorC<IntT,3>,TFVectorC<IntT,3> >(mask,mask);
    maskSum = (RealT) Sqr(mask.Sum());
    ONDEBUG(cerr << "Mask size=" << w << " Sum=" << maskSum << "\n");
    //ONDEBUG(cerr << "Mask=" << mask << "\n");
  }
  
  DListC<CornerC> CornerDetectorHarrisBodyC::Apply(const ImageC<ByteT> &img) {
    ImageC<IntT> var = CornerHarris(img);
    DListC<CornerC> lst;
    Peak(var,img,lst);
    return lst;
  }
  
  // Haris corner detector.
  
  ImageC<IntT> CornerDetectorHarrisBodyC::CornerHarris(const ImageC<ByteT> &img) {
    ImageRectangleC workRect(img.Rectangle().Shrink(1));
    if(!vals.Frame().Contains(workRect)) {
      vals = ImageC<TFVectorC<IntT,3> >(workRect);
      fvals = ImageC<TFVectorC<IntT,3> >(workRect);
      var = ImageC<IntT>(workRect);               /* cornerness image */
    }
    
    ImagGrad(img,vals);
    ImageRectangleC subWR(workRect.Shrink(w+1));
    filter(vals,fvals);
    
    for(Array2dIter2C<IntT,TFVectorC<IntT,3> > it(var,fvals,subWR);it;it++) {
      RealT ixixs = (RealT) it.Data2()[0] / maskSum;
      RealT iyiys = (RealT) it.Data2()[1] / maskSum; 
      RealT ixiys = (RealT) it.Data2()[2] / maskSum;
      /* Evaluating the cornerness measure */
      int val;
      if((ixixs+iyiys) != 0)
	val = (int) ((double)((ixixs*iyiys-ixiys*ixiys)/(ixixs+iyiys)));
      else
	val = 0;
      //cerr << "Val=" << val << "\n";
      it.Data1() = val;
    }
    return var;
  }
  
  void CornerDetectorHarrisBodyC::ImagGrad(const ImageC<ByteT> &img,ImageC<TFVectorC<IntT,3> > &val) {
    for(Array2dSqr31Iter2C<ByteT,TFVectorC<IntT,3> > it(img,val);it;it++) {
      /* Calculation of the gradients in x and y direction */
      const int ix = (it.DataBL1() + it.DataML1()*2 + it.DataTL1() - it.DataBR1() - it.DataMR1()*2 - it.DataTR1()) >> 1;
      const int iy = (it.DataTL1() + it.DataTM1()*2 + it.DataTR1() - it.DataBL1() - it.DataBM1()*2 - it.DataBR1()) >> 1;
      it.Data2()[0]=ix*ix;
      it.Data2()[1]=iy*iy;
      it.Data2()[2]=ix*iy;
    }
  }
  
  
  int CornerDetectorHarrisBodyC::Peak(ImageC<IntT> &result,const ImageC<ByteT> &in,DListC<CornerC> &cornLst) {
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
	  Point2dC pat = LocatePeakSubPixel(result,at,0.25);
	  cornLst.InsLast(CornerC(pat,SobelGradient3(in,at),in[at]));
	  n++;
	  peak = true;
	}
      }
      last = *it;
    }
    return n; 
  }
  
}
