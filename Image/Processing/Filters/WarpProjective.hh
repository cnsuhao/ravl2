// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_WARPPROJECTIVE_HEADER
#define RAVLIMAGE_WARPPROJECTIVE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlImageProc
//! docentry="Ravl.Images.Warping"
//! author="Charles Galambos"
//! date="16/07/2002"

#include "Ravl/Image/PixelMixer.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/BilinearInterpolation.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Matrix3d.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/RealRange2d.hh"
#include "Ravl/LinePP2d.hh"
#include "Ravl/Projection2d.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Warp image with a projective transformation.
  
  template <class InT, class OutT = InT,class MixerT = PixelMixerAssignC<InT,OutT> >
  class WarpProjectiveC
  {
  public:
    WarpProjectiveC()
    {}
    //: Default constructor.
    
    WarpProjectiveC(const IndexRange2dC &orec,
		    const Matrix3dC &transform,
		    RealT niz = 1,
		    RealT noz = 1,
		    bool nFillBackground = true,
		    const MixerT &mix = MixerT())
      : trans(transform),
	iz(niz),
	oz(noz),
	rec(orec),
	fillBackground(nFillBackground),
	mixer(mix)
    { Init(); }
    //: Constructor.
    // Where orec is the size of the output rectangle.
    
    WarpProjectiveC(const Matrix3dC &transform,
		    RealT niz = 1,
		    RealT noz = 1,
		    bool nFillBackground = true,
		    const MixerT &mix = MixerT())
      : trans(transform),
	iz(niz),
	oz(noz),
	fillBackground(nFillBackground),
	mixer(mix)
    { Init(); }
    //: Constructor.

    WarpProjectiveC(const Projection2dC &transform,
		    bool nFillBackground = true,
		    const MixerT &mix = MixerT())
      : trans(transform.Matrix()),
	iz(transform.Oz()),
	oz(transform.Iz()),
	fillBackground(nFillBackground),
	mixer(mix)
    { Init(); }
    //: Constructor.
    
    void Apply(const ImageC<InT> &img,ImageC<OutT> &out);
    //: Warp image 'img' with the given transform and write it into 'out'
    
    ImageC<OutT> Apply(const ImageC<InT> &img) {
      ImageC<OutT> out(rec);
      Apply(img,out);
      return out;
    }
    //: Interpolate input image working rectangle into
    //: output image rectangle.
    // The output rectangle is specified in the constructor.
    
    void SetTransform(const Matrix3dC &transform) {
      trans = transform;
      Init();
    }
    //: Set projective transform.
    
    ImageRectangleC InputRectangle() const { 
      RealRange2dC orng(rec);
      ImageRectangleC ret(Project(orng.TopRight()),0);
      ret.Involve(Project(orng.TopLeft()));
      ret.Involve(Project(orng.BottomRight()));
      ret.Involve(Project(orng.BottomLeft()));
      return ret;
    }
    //: Get range of input rectangle that will be used.
    // Note: This may be larger than the actual input provided.
    
    Point2dC BackProject(const Point2dC &pnt) const;
    // Transform a point from the source to destination.

    Point2dC Project(const Point2dC &pnt) const;
    // Transform a point from the destination to source.
    
  protected:
    void Init();
    
    Matrix3dC trans;
    Matrix3dC inv;
    RealT iz, oz;
    IndexRange2dC rec;
    bool fillBackground;
    MixerT mixer;
  };

  template <class InT, class OutT,class MixerT>
  void WarpProjectiveC<InT,OutT,MixerT>::Init() {
    inv = trans.Inverse();
  }
  
  template <class InT, class OutT,class MixerT>
  Point2dC WarpProjectiveC<InT,OutT,MixerT>::BackProject(const Point2dC &pnt) const {
    Vector3dC vi = trans * Vector3dC(pnt[0],pnt[1],iz);
    return Point2dC(oz*vi[0]/vi[2],oz*vi[1]/vi[2]);
  }
  
  template <class InT, class OutT,class MixerT>
  Point2dC WarpProjectiveC<InT,OutT,MixerT>::Project(const Point2dC &pnt) const {
    Vector3dC vo = inv * Vector3dC(pnt[0],pnt[1],oz);
    return Point2dC(iz*vo[0]/vo[2],iz*vo[1]/vo[2]);          
  }
  
  template <class InT, class OutT,class MixerT>
  void WarpProjectiveC<InT,OutT,MixerT>::Apply(const ImageC<InT> &src,ImageC<OutT> &outImg) {
    
    RealRange2dC irng(src.Frame());
    if(rec.TRow()<=rec.BRow() && !outImg.Frame().Contains(rec))
      outImg = ImageC<OutT>(rec);
    //cerr << "Trans0=" << trans * orng.TopRight() << " from " << orng.TopRight() << "\n";
    
    // adjust source window for area where bilinear interpolation can be
    // computed safely. Using 0.51 instead of 0.5 ensures that points on the
    // boundary are not used, for safety.
    irng.TRow() += 0.51; irng.BRow() -= 0.51;
    irng.LCol() += 0.51; irng.RCol() -= 0.51;

    // If the output maps entirely within input, we don't have to do any checking.
    
    Vector3dC ldir(inv[0][1] * iz,inv[1][1] * iz,inv[2][1]);
    OutT tmp;
#if 0    
    RealRange2dC orng(outImg.Frame());
    if(irng.Contains(Project(orng.TopRight())) &&
       irng.Contains(Project(orng.TopLeft())) &&
       irng.Contains(Project(orng.BottomRight())) &&
       irng.Contains(Project(orng.BottomLeft()))) {
      Point2dC pat(outImg.Frame().Origin());
      pat[0] += 0.5;
      pat[1] += 0.5;

      Array2dIterC<OutT> it(outImg);  
      for(;it;pat[0]++) {
	Vector3dC at = inv * Vector3dC(pat[0],pat[1],oz);
	at[0] *= iz;
	at[1] *= iz;
	do {
	  mixer(*it,src.BiLinear(Point2dC((at[0]/at[2]) - 0.5,(at[1]/at[2])- 0.5)));
	  at += ldir;
	} while(it.Next()) ;
      }
      return;
    }
#endif
    
    ImageC<OutT> workingOutImg;
    if(!fillBackground) {
      // Find the projection of the input image in the output
      // to minimise the number of pixels we have to check.
      Point2dC pnt = BackProject(irng.TopRight());
      RealRange2dC trng(pnt,pnt);
      trng.Involve(BackProject(irng.TopLeft()));
      trng.Involve(BackProject(irng.BottomRight()));
      trng.Involve(BackProject(irng.BottomLeft()));
      IndexRange2dC oclip(Floor(trng.TRow()),Floor(trng.BRow())+1,
			  Floor(trng.LCol()),Floor(trng.RCol())+1);
      
      //cerr << "Clip=" << oclip << " Frame=" << outImg.Frame() << "\n";
      // Clip the output image appropriatly.
      oclip.ClipBy(outImg.Frame());
      workingOutImg = ImageC<OutT>(outImg,oclip);
    } else
      workingOutImg = outImg;
    
    // set pat as top-left pixel in output image
    Point2dC pat(workingOutImg.Frame().Origin());
    pat[0] += 0.5;
    pat[1] += 0.5;
    
    Array2dIterC<OutT> it(workingOutImg);  
    
    
#if 0
    // Do simple check for each pixel that its contained in the input image.
    // This could be sped up by projecting the line into the source image space,
    // clipping it and then projecting back into the output image and only iterate
    // along that bit of the line.
    Vector2dC endv(0,orng.Cols());
    cerr << "irng=" << irng << "\n";
    const int brow = workingOutImg.Frame().BRow().V();
    for(int r = workingOutImg.Frame().TRow().V();r < brow;r++,pat[0]++) {
      //cerr << "\nr=" << r << "\n";
      LinePP2dC rline(Project(pat),Project(pat + endv));
      //cerr << " P1=" << rline.P1() << " P2=" << rline.P2() << "\n";
      if(!rline.ClipBy(irng))
	continue;
      //cerr << " CP1=" << rline.P1() << " CP2=" << rline.P2() << "\n";
      // Map clipped line back into output image.
      Point2dC sp = BackProject(rline.P1());
      Point2dC ep = BackProject(rline.P2());
      //cerr << " sp=" << sp << " ep=" << ep << "\n";
      RavlAssert(Abs(sp[0] - ep[0]) < 0.01); // Sanity check.
      
      RealT rsp = ceil(sp[1]);
      IntT isp = (IntT) rsp;
      IntT iep = Floor(ep[1]);
      if(isp > iep)
	continue;
      
      Vector3dC at = inv * Vector3dC(pat[0],rsp,oz);
      at[0] *= iz;
      at[1] *= iz;
      //cerr << "Line from " << isp << " to " << iep << "\n";
      
      IndexRangeC colRange(isp,iep);
      RavlAssert(workingOutImg.Frame().Range2().Contains(colRange));
      for(BufferAccessIterC<OutT> rit(outImg[r],colRange);rit;rit++) {
	Point2dC ipat(at[0]/at[2],at[1]/at[2]);
	BilinearInterpolation(src,ipat - Point2dC(0.5,0.5),tmp);
	mixer(*rit,tmp);
	at += ldir;
      }
    }
  }
#else
    // Do simple check for each pixel that its contained in the input image.
    // This could be sped up by projecting the line into the source image space,
    // clipping it and then projecting back into the output image and only iterate
    // along that bit of the line.
    for(;it;) {
      Vector3dC at = inv * Vector3dC(pat[0],pat[1],oz);
      at[0] *= iz;
      at[1] *= iz;
      
      if(fillBackground) {
	do {
	  Point2dC ipat(at[0]/at[2],at[1]/at[2]);
	  if(irng.Contains(ipat)) {
	    BilinearInterpolation(src,ipat - Point2dC(0.5,0.5),tmp);
	    mixer(*it,tmp);
	  } else
	    SetZero(*it);
	  at += ldir;
	} while(it.Next()) ;
      } else {
	do {
	  Point2dC ipat(at[0]/at[2],at[1]/at[2]);
	  if(irng.Contains(ipat)) {
	    BilinearInterpolation(src,ipat - Point2dC(0.5,0.5),tmp);
	    mixer(*it,tmp);
	  }
	  at += ldir;
	} while(it.Next()) ;
      }
      pat[0]++;
    }
  }
#endif
}


#endif
