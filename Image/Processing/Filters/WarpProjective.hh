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
#include "Ravl/Array2dIter.hh"
#include "Ravl/Matrix3d.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/RealRange2d.hh"

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
    
    Point2dC BackProject(const Point2dC &pnt) const;
    // Transform a point from the destination to source.

    Point2dC Project(const Point2dC &pnt) const;
    // Transform a point from the source to destination
    
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
    
    RealRange2dC orng(rec);
    RealRange2dC irng(src.Frame());
    if(!outImg.Frame().Contains(rec))
      outImg = ImageC<OutT>(rec);
    //cerr << "Trans0=" << trans * orng.TopRight() << " from " << orng.TopRight() << "\n";
    
    // adjust source window for area where bilinear interpolation can be
    // computed safely. Using 0.51 instead of 0.5 ensures that points on the
    // boundary are not used, for safety.
    irng.TRow() += 0.51; irng.BRow() -= 0.51;
    irng.LCol() += 0.51; irng.RCol() -= 0.51;
    
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
    
    // If the output maps entirely within input, we don't have to do any checking.
    
    if(irng.Contains(Project(orng.TopRight())) &&
       irng.Contains(Project(orng.TopLeft())) &&
       irng.Contains(Project(orng.BottomRight())) &&
       irng.Contains(Project(orng.BottomLeft()))) {
      Vector3dC ldir(trans[0][1] * iz,trans[1][1] * iz,trans[2][1]);
      for(;it;) {
	Vector3dC at = inv * Vector3dC(pat[0],pat[1],oz);
	at[0] *= iz;
	at[1] *= iz;
	do {
	  mixer(*it,src.BiLinear(Point2dC((at[0]/at[2]) - 0.5,(at[1]/at[2])- 0.5)));
	  at += ldir;
	} while(it.Next()) ;
	pat[0]++;
      }
      return;
    }
    
    // Do simple check for each pixel that its contained in the input image.
    // This could be sped up by projecting the line into the source image space,
    // clipping it and then projecting back into the output image and only iterate
    // along that bit of the line.
    
    Vector3dC ldir(trans[0][1] * iz,trans[1][1] * iz,trans[2][1]);
    for(;it;) {
      Vector3dC at = inv * Vector3dC(pat[0],pat[1],oz);
      at[0] *= iz;
      at[1] *= iz;
      
      if(fillBackground) {
	do {
	  Point2dC ipat(at[0]/at[2],at[1]/at[2]);
	  if(irng.Contains(ipat))
	    mixer(*it,src.BiLinear(ipat - Point2dC(0.5,0.5)));
	  else
	    SetZero(*it);
	  at += ldir;
	} while(it.Next()) ;
      } else {
	do {
	  Point2dC ipat(at[0]/at[2],at[1]/at[2]);
	  if(irng.Contains(ipat))
	    mixer(*it,src.BiLinear(ipat - Point2dC(0.5,0.5)));
	  at += ldir;
	} while(it.Next()) ;
      }
      pat[0]++;
    }
  }
  
}


#endif
