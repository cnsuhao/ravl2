// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_CONVOLVE2D_HEADER
#define RAVLIMAGE_CONVOLVE2D_HEADER 1
/////////////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! author="Charles Galambos"
//! lib=RavlImage
//! file="Ravl/Image/Processing/Filters/Convolve2d.hh"
//! docentry="Ravl.Images.Filtering"

#include "Ravl/Image/Correlate2d.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: 2D Convolution
  
  template<class KernelPixelT,class InPixelT = KernelPixelT,class OutPixelT = InPixelT,class SumTypeT = KernelPixelT>
  class Convolve2dC 
    : protected Correlate2dC<KernelPixelT,InPixelT,OutPixelT,SumTypeT>
  {
  public:
    Convolve2dC()
    {}
    //: Default constructor.
    // Use SetKernel() to setup a kernel before calling Apply().
    
    Convolve2dC(const ImageC<KernelPixelT> &nkernel)
    { SetKernel(nkernel); }
    //: Default constructor.
    
    void SetKernel(const ImageC<KernelPixelT> &nkernel) { 
      // The apply method actualy does correlation.
      Correlate2dC<KernelPixelT,InPixelT,OutPixelT,SumTypeT>::SetKernel(nkernel.Rotate180());
    }
    //: Set the convolution kernel.
    // Note: This method flips the kernel, so does take some time.
    
    void Apply(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const
    { Correlate2dC<KernelPixelT,InPixelT,OutPixelT,SumTypeT>::Apply(in,result); }
    //: Do convolution on image 'in', put the output in 'result' 
    
    void operator()(const ImageC<InPixelT> &in,ImageC<OutPixelT> &result) const
    { Apply(in,result); }    
  };
  
}

#endif
