// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_WARPAFFINE_HEADER
#define RAVLIMAGE_WARPAFFINE_HEADER 1
///////////////////////////////////////////////////////////////
//! docentry="Ravl.Images.Warping"
//! lib=RavlImageProc
//! author="Charles Galambos"
//! rcsid="$Id$"
//! date="16/07/2002"

#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Affine2d.hh"
#include "Ravl/RealRange2d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/LinePP2d.hh"
#include "Ravl/Image/PixelMixer.hh"

namespace RavlImageN {
  using namespace RavlN;
  
  //! userlevel=Normal
  //: Scale an image using bi-Linear Interpolation.
  
  template <class InT, class OutT = InT,class MixerT = PixelMixerAssignC<InT,OutT> >
  class WarpAffineC
  {
  public:
    WarpAffineC(const ImageRectangleC &ir,const Affine2dC &ntrans,bool nFillBackground = true,const MixerT &mix = MixerT())
      : rec(ir),
	trans(ntrans),
	itrans(ntrans.I()),
	fillBackground(nFillBackground),
	mixer(mix)
    {}
    //: Constructor.
    // 'ir' is the output rectangle.
    // 'ntrans' is the transform to use.
    
    void Apply(const ImageC<InT> &img,ImageC<OutT> &outImg);
    //: Interpolate input image working rectangle into
    //: output image.
    
    ImageC<OutT> Apply(const ImageC<InT> &img) {
      ImageC<OutT> out(rec);
      Apply(img,out);
      return out;
    }
    //: Interpolate input image working rectangle into
    //: output image rectangle.
    // The output rectangle is specified in the constructor.
    
  protected:
    ImageRectangleC rec;   // Output rectangle.
    Affine2dC trans;       // Transform.
    Affine2dC itrans;      // Inverse transform
    bool fillBackground;   // Fill background with zero ?
    MixerT mixer;
  };
  
  template <class InT, class OutT,class MixerT>
  void WarpAffineC<InT,OutT,MixerT>::Apply(const ImageC<InT> &src,ImageC<OutT> &outImg) {
    RealRange2dC orng(rec);
    RealRange2dC irng(src.Frame());
    if(!outImg.IsValid())
      outImg = ImageC<OutT>(rec);
    
    //cerr << "Trans0=" << trans * orng.TopRight() << " from " << orng.TopRight() << "\n";
    Matrix2dC invsr = trans.SRMatrix();
    Point2dC at = Point2dC(outImg.Frame().Origin()) + invsr * trans.Translation();
    const Matrix2dC &srm = trans.SRMatrix();
    Vector2dC ldir(srm[0][1],srm[1][1]);
    Vector2dC sdir(srm[0][0],srm[1][0]);
    Point2dC lstart(at[0] * sdir + at[1] * ldir);
    lstart -= Vector2dC(0.5,0.5); //Co-ordinate system correction.
    Array2dIterC<OutT> it(outImg);
    
    if(irng.Contains(trans * orng.TopRight()) &&
       irng.Contains(trans * orng.TopLeft()) &&
       irng.Contains(trans * orng.BottomRight()) &&
       irng.Contains(trans * orng.BottomLeft())) {
      // Output maps entirely within input, so we don't have to do any checking!
      //cerr << "No checking. \n";
      for(;it;) {
	Point2dC pat = lstart;
	do {
	  mixer(*it,src.BiLinear(pat));
	  pat += ldir;
	} while(it.Next()) ;
	lstart += sdir;
      }
      return;
    }    
#if 0
    Vector2dC endv(0,((RealT) orng.Cols()));
    // This attempts to be clever project the line back into
    // the source space, clipping it and the projecting it back
    // again.
    for(;it;) {
      Point2dC pat = lstart;
      LinePP2dC rline(pat,endv);
      if(!rline.ClipBy(irng)) {
	it.NextRow();
	lstart += sdir;
	continue;
      }
      // Map clipped line back into output image.
      Point2dC sp = itrans * rline.P1();
      Point2dC ep = itrans * rline.P2();
      
      int c = (((int) sp[1]) - outImg.LCol()).V();
      if(fillBackground) {
	for(;c >= 0;c--,it++)
	  SetZero(*it);
      } else
	it.NextCol(c);
      int ce = (((int) ep[1]) - outImg.LCol()).V();
      const OutT *end = &(*it) + ce;
      for(;&(*it) < end;it.NextCol()) {
	*it = src.BiLinear(pat);
	pat += ldir;
      }
      if(fillBackground) {
	for(;it.IsColElm();it.NextCol())
	  SetZero(*it);
      } else
	it.NextRow();
      lstart += sdir;
    }
#else 
    // Do simple check for each pixel that its contained in the input image.
    for(;it;) {
      Point2dC pat = lstart;
      if(fillBackground) {
	do {
	  if(irng.Contains(pat))
	    mixer(*it,src.BiLinear(pat));
	  else
	    SetZero(*it);
	  pat += ldir;
	} while(it.Next()) ;
      } else {
	do {
	  if(irng.Contains(pat))
	    mixer(*it,src.BiLinear(pat));
	  pat += ldir;
	} while(it.Next()) ;
      }
      lstart += sdir;
    }
    
#endif    
  }
  
}
#endif
