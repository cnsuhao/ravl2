// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_BILINEAR_HEADER
#define RAVLIMAGE_BILINEAR_HEADER
//! docentry="Ravl.Images"
//! author="Charles Galambos"
//! date="24/01/2001"
//! rcsid="$Id$"
//! lib=RavlImage
//! file="Ravl/Image/Base/BilinearInterpolation.hh"

#include "Ravl/Image/Image.hh"

namespace RavlImageN {
  
  template <class PixelT,class OutT>
  inline
  void BilinearInterpolation(const ImageC<PixelT> &img,const TFVectorC<RealT,2> &ipnt,OutT &pixVal) {
    TFVectorC<RealT,2> pnt = ipnt;
    IntT fx = Floor(pnt[0]); // Row
    IntT fy = Floor(pnt[1]); // Col
    RealT u = pnt[0] - fx;
    RealT t = pnt[1] - fy;
    const PixelT* pixel1 = &(img)[fx][fy];
    const PixelT* pixel2 = &(img)[fx+1][fy];
    const RealT onemt = (1.0-t);
    const RealT onemu = (1.0-u);
    pixVal = (OutT)((pixel1[0] * (onemt*onemu)) + 
		    (pixel1[1] * (t*onemu)) + 
		    (pixel2[0] * (onemt*u)) +
		    (pixel2[1] * (t*u)));
  }
  //: Do bilinear interpolation with different output pixel type.
  // Note: For efficency reasons this method assumes the CENTER
  // of the pixel is at 0,0.  This means that a 0.5 offset may
  // me needed if your co-oridnate systems is at the top left
  // of the pixel.
  

  inline
  void BilinearInterpolation(const ImageC<ByteT> &img,const TFVectorC<RealT,2> &ipnt,ByteT &pixVal) {
    TFVectorC<RealT,2> pnt = ipnt;
    IntT fx = Floor(pnt[0]); // Row
    IntT fy = Floor(pnt[1]); // Col
    RealT u = pnt[0] - fx;
    RealT t = pnt[1] - fy;
    const ByteT* pixel1 = &(img)[fx][fy];
    const ByteT* pixel2 = &(img)[fx+1][fy];
    const RealT onemt = (1.0-t);
    const RealT onemu = (1.0-u);
    pixVal = (ByteT)(((RealT)pixel1[0] * (onemt*onemu)) + 
		    ((RealT)pixel1[1] * (t*onemu)) + 
		    ((RealT)pixel2[0] * (onemt*u)) +
		    ((RealT)pixel2[1] * (t*u)));
  }
  //: Do bilinear interpolation with different output pixel type.
  // Note: For efficency reasons this method assumes the CENTER
  // of the pixel is at 0,0.  This means that a 0.5 offset may
  // me needed if your co-oridnate systems is at the top left
  // of the pixel.

  //:-
  
  //! userlevel=Normal
  //: Bilinear sampler
  
  template<class InT,class OutT>
  class SampleBilinearC
  {
  public:
    SampleBilinearC()
    {}
    
    void operator()(const ImageC<InT> &img,const TFVectorC<RealT,2> &ipnt,OutT &pixVal)
    { BilinearInterpolation(img,ipnt,pixVal); }
    //: Do bilinear interpolation
    
  };
  
  //! userlevel=Normal
  //: Nearest pixel sampler.
  
  template<class InT,class OutT>
  class SampleNearestC
  {
  public:    
    void operator()(const ImageC<InT> &img,const TFVectorC<RealT,2> &ipnt,OutT &pixVal)
    { pixVal = img[Round(ipnt[0])][Round(ipnt[1])]; }
    //: Do bilinear interpolation
    
  };

}

#endif
