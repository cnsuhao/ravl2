#ifndef RAVLIMAGE_BILINEAR_HEADER
#define RAVLIMAGE_BILINEAR_HEADER
//! docentry="Ravl.Images"
//! author="Charles Galambos"
//! date="24/01/2001"

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
  
}

#endif
