// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_WARPPROJECTIVE_HEADER
#define RAVLIMAGE_WARPPROJECTIVE_HEADER 1
///////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImageProc
//! docentry="Ravl.Images.Warping"
//! author="Charles Galambos"
//! date="16/07/2002"

#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Matrix3d.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/RealRange2d.hh"
#include "Ravl/Image/PixelMixer.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Warp image with a projective transformation.
  
  template <class InT, class OutT = InT,class MixerT = PixelMixerAssignC<InT,OutT> >
  class WarpProjectiveC
  {
  public:
    WarpProjectiveC(const Matrix3dC &transform,RealT nz = 1,bool nFillBackground = true,const MixerT &mix = MixerT())
      : trans(transform),
	z(nz),
	fillBackground(nFillBackground),
	mixer(mix)
    { Init(); }
    //: Constructor.
    // 'ir' is the output rectangle.
    
    void Apply(const ImageC<InT> &img,ImageC<OutT> &out);
    //: Warp image 'img' with the given transform and write it into 'out'
    
    Point2dC BackProject(const Point2dC &pnt) const;
    // Transform a point from the destination to source.

    Point2dC Project(const Point2dC &pnt) const;
    // Transform a point from the source to destination
    
  protected:
    void Init();
    
    Matrix3dC trans;
    Matrix3dC inv;
    RealT z;
    ImageRectangleC rec;
    bool fillBackground;
    MixerT mixer;
  };

  template <class InT, class OutT>
  void WarpProjectiveC<InT,OutT>::Init() {
    inv = trans.Inverse();
  }
  
  template <class InT, class OutT>
  Point2dC WarpProjectiveC<InT,OutT>::BackProject(const Point2dC &pnt) const {
    Vector3dC vo = trans * Vector3dC(pnt[0],pnt[1],z);
    return Point2dC(vo[0]/vo[2],vo[1]/vo[2]);
  }
  
  template <class InT, class OutT>
  Point2dC WarpProjectiveC<InT,OutT>::Project(const Point2dC &pnt) const {
    Vector3dC vo = inv * Vector3dC(pnt[0],pnt[1],z);
    return Point2dC(vo[0]/vo[2],vo[1]/vo[2]);          
  }
  
  template <class InT, class OutT>
  void WarpProjectiveC<InT,OutT>::Apply(const ImageC<InT> &src,ImageC<OutT> &outImg) {

    RealRange2dC orng(rec);
    RealRange2dC irng(src.Frame());
    if(outImg.Frame() != rec)
      outImg = ImageC<OutT>(rec);
    //cerr << "Trans0=" << trans * orng.TopRight() << " from " << orng.TopRight() << "\n";
    
    Point2dC pat(src.Frame().Origin());
    Array2dIterC<OutT> it(outImg);      
    
    if(irng.Contains(Project(orng.TopRight())) &&
       irng.Contains(Project(orng.TopLeft())) &&
       irng.Contains(Project(orng.BottomRight())) &&
       irng.Contains(Project(orng.BottomLeft()))) {
      // Output maps entirely within input, so we don't have to do any checking!
      //cerr << "No checking. \n";
      
      RealT beg = pat[1];
      for(;it;) {
	do {
	  mixer(*it,src.BiLinear(Project(pat)));
	  pat[1]++;
	} while(it.Next()) ;
	pat[1] = beg;
	pat[0]++;
      }
      return;
    }
    
    // Do simple check for each pixel that its contained in the input image.
    // This could be sped up by projecting the line into the source image space,
    // clipping it and then projecting back into the output image and only iterate
    // along that bit of the line.

    RealT beg = pat[1];
    for(;it;) {
      if(fillBackground) {
	do {
	  if(irng.Contains(pat))
	    mixer(*it,src.BiLinear(Project(pat)));
	  else
	    SetZero(*it);
	  pat[1]++;
	} while(it.Next()) ;
      } else {
	do {
	  if(irng.Contains(pat))
	    mixer(*it,src.BiLinear(Project(pat)));
	  pat[1]++;
	} while(it.Next()) ;
      }
      pat[1] = beg;
      pat[0]++;
    }
    
    return;
  }
  
}


#endif
