// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_WARPTHINPLATESPLINE_HEADER
#define RAVLIMAGE_WARPTHINPLATESPLINE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlImageProc
//! docentry="Ravl.Images.Warping"
//! author="Charles Galambos"
//! date="22/11/2002"

#include "Ravl/Image/Image.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/RealRange2d.hh"
#include "Ravl/Image/PixelMixer.hh"

namespace RavlImageN {
  using namespace RavlN;
  
  class WarpThinPlateSplineBaseC {
  public:
    WarpThinPlateSplineBaseC(RealT nSigma,bool nFillBackground = true)
      : sigma(nSigma),
	fillBackground(nFillBackground)
    {}
    //: Constructor.
    
    inline RealT U(RealT dist2) const { 
      dist2 = Sqrt(dist2);
      if(dist2 == 0)
	return 0; // Avoid Log(0).
      return Sqr(dist2/sigma) * Log(dist2/sigma); 
    }
    // Compute U(x).
    
    void ComputeWUd(const Array1dC<Point2dC> &orgPos,const Point2dC &pos,const MatrixC &w,Point2dC &at) const;
    //: Calculate WUd.
    
    MatrixC ComputeW(const Array1dC<Point2dC> &orgPos,const Array1dC<Point2dC> &newPos) const;
    //: Compute weight matrix.
    
  protected:
    RealT sigma;
    bool fillBackground;
  };
  
  
  template<class InT,class OutT = InT,class MixerT = PixelMixerAssignC<InT,OutT> >
  class WarpThinPlateSplineC 
    : public WarpThinPlateSplineBaseC
  {
  public:
    WarpThinPlateSplineC(RealT nSigma,bool nFillBackground = true,const MixerT &mix = MixerT())
      : WarpThinPlateSplineBaseC(nSigma,nFillBackground),
	mixer(mix)
    {}    
    //: Constructor.
    
    bool Apply(const ImageC<InT> &src,const Array1dC<Point2dC> &orgPos,const Array1dC<Point2dC> &newPos,ImageC<OutT> &ret) {
      if(ret.IsEmpty())
	ret = ImageC<ByteT>(src.Frame());
      RealRange2dC irng(src.Frame());
      irng = irng.Expand(-1.1); // There's an off by a bit error somewhere in here...
      MatrixC w = ComputeW(orgPos,newPos);
      if(w.IsEmpty())
	return false;
      Point2dC rstart(ret.Frame().Origin());
      rstart += Point2dC(0.5,0.5);
      Point2dC at,pat;
      for(Array2dIterC<OutT> it(ret);it;) {
	at = rstart;
	do {
	  ComputeWUd(orgPos,at,w,pat);
	  //cerr << " " << at << " => " << pat << "\n";
	  if(irng.Contains(pat))
	    mixer(*it,src.BiLinear(pat - Point2dC(0.5,0.5)));
	  else {
	    if(fillBackground)
	      SetZero(*it);
	  }
	  at[1]++;
	} while(it.Next()) ;
	rstart[0]++;
      }
      return true;
    }
    //: Warp image.
    
  protected:
    MixerT mixer;
  };
}

#endif
