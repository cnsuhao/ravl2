// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_GAUSSCONVOLVE_HEADER
#define RAVLIMAGE_GAUSSCONVOLVE_HEADER 1
//! userlevel=Normal
//! author="Kieron J Messer"
//! docentry="Ravl.Images.Filtering"
//! example=exGaussConvolve.cc
//! lib=RavlImageProc
//! rcsid="$Id$"
//! file="Ravl/Image/Processing/Filters/GaussConvolve.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/GenerateSignal1d.hh"
#include "Ravl/Image/ConvolveSeparable2d.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Low-pass-filters an image with a finite-width approximation to a Gaussian mask
  //
  //<p> The filter design is bsed on a normalised row from Pascal's triangle
  // (i.e. binomial coefficients).  The "standard deviation" of such a filter, with <i>n</i> coefficients, is thus (<i>n</i>-1/4)^1/2</p>
  //
  // <p> The rational is this:
  // <ul>
  // <li> The simplest possible non-trivial Gaussian filter is a 2nd-order one,
  // which from symmetry considerations will have two equal coefficients.
  // <li> Higher-order filters can be viewed as convolved 2nd-order filters,
  // i.e. an <i>n</i>th order filter is a convolution of <i>n</i>+1 2nd-order filters.
  // By the Central Limit Theorem these will approximate a Gaussian profile
  // more and more closely as the order increases.
  // <li> At the same time because they are of finite width they avoid the
  // problem of truncating the Gaussian tails.
  // </ul>
  // E.g. a 5th order filter has mask of:
  //
  // <pre> (1 4 6 4 1) / 16 </pre></p>
  // <p>This class is just wraps ConvolveSeparable2d and
  // GenerateBinomial() calls in a convenient form.</p>
  // The default form of this function is setup to handle single channel images. (e.g. byte, real, int)
  // if you want to convolve multi channel images you should change the 'SumTypeT' template argument to
  // a type that can handle sums and multiplications without overflowing 
  // e.g. If you wish to convolve a ByteRGBValueC SumTypeT should be set to RealRGBValueC. <p>
  // <b>Template args:</b> <br>
  // InPixelT = Type of pixel in input image. <br>
  // OutPixelT = Type of pixel in output image. (Default = InPixelT) <br>
  // KernelPixelT = Type of pixel in convolution kernel. (Default = RealT; integer types currently will not work, as the normalisation is done in the kernel generation)  <br>
  // SumTypeT = A type appropriate for summing the product of KernelPixelT and InPixelT. (Default = KernelPixelT <br>
  // There are two main issues when choosing these types.<br>
  // 1. Underflow and overflow of the sums and product operations. <br>
  // 2. Handing multi-channel images. (Such as RGB.) <br>
  // The exact requirements of these types depends on the gain and type of the filter being used.
  // In multi-channel filters SumPixelT should be a multi-channel value as well. e.g.
  // to filter an ImageC<ByteRGBValueC> you may use:
  // InPixelT=ByteRGBValueC, OutPixelT=ByteRGBValueC,KernelPixelT=RealT,SumType=RealRGBValueC

  template<class InPixelT,class OutPixelT = InPixelT,class KernelPixelT = RealT,class SumTypeT = OutPixelT>
  class GaussConvolveC {
  public:
    GaussConvolveC()
    {}
    //: Default constructor.
    
    GaussConvolveC(UIntT order) {
      binomial = GenerateBinomial((KernelPixelT) 1.0, order, true,true);
      conv.SetKernel(binomial, binomial);
    }
    //: Construct Gaussian with the given size.
    
    ImageC<OutPixelT> Apply (const ImageC<InPixelT> &in) const {
      ImageC<OutPixelT> op;
      conv.Apply(in, op);
      return op;
    }
    //: Performs Gaussian filter on image 'in'.
    // Returns a new filtered image.
    
    Array1dC<KernelPixelT> &Filter()
    { return binomial; }
    //: Access current filter.
    // Note the save/load routines of this class do NOT save
    // the filter coefficients, just its order. So modifying
    // them and saving this class is pointless.
    
    const Array1dC<KernelPixelT> &Filter() const
    { return binomial; }
    //: Access current filter.
    
    UIntT Order() const
    { return binomial.Size(); }
    //: Get size of gausian.

#if RAVL_NEW_ANSI_CXX_DRAFT
    friend ostream &operator<< <>(ostream &s, const GaussConvolveC<InPixelT,OutPixelT,KernelPixelT,SumTypeT> &out);
    //: output stream operator
    
    friend istream &operator>> <>(istream &s, GaussConvolveC<InPixelT,OutPixelT,KernelPixelT,SumTypeT> &in);
    //: input stream operator
    
    friend BinOStreamC &operator<< <>(BinOStreamC &s, const GaussConvolveC<InPixelT,OutPixelT,KernelPixelT,SumTypeT> &out);
    //: output stream operator
    
    friend BinIStreamC &operator>> <>(BinIStreamC &s, GaussConvolveC<InPixelT,OutPixelT,KernelPixelT,SumTypeT> &in);
    //: input stream operator
#else
    friend ostream &operator<< (ostream &s, const GaussConvolveC<InPixelT,OutPixelT,KernelPixelT,SumTypeT> &out);
    //: output stream operator
    
    friend istream &operator>> (istream &s, GaussConvolveC<InPixelT,OutPixelT,KernelPixelT,SumTypeT> &in);
    //: input stream operator
    
    friend BinOStreamC &operator<< (BinOStreamC &s, const GaussConvolveC<InPixelT,OutPixelT,KernelPixelT,SumTypeT> &out);
    //: output stream operator
    
    friend BinIStreamC &operator>> (BinIStreamC &s, GaussConvolveC<InPixelT,OutPixelT,KernelPixelT,SumTypeT> &in);
    //: input stream operator
#endif
    
  protected:
    Array1dC<KernelPixelT> binomial;
    ConvolveSeparable2dC<InPixelT,OutPixelT,KernelPixelT,SumTypeT> conv;
  };
  
  template<class InPixelT,class OutPixelT,class KernelPixelT,class SumTypeT>
  ostream &operator<<(ostream &s, const GaussConvolveC<InPixelT,OutPixelT,KernelPixelT,SumTypeT> &out) {
    s << out.binomial.Size() << endl;
    return s;
  }

  template<class InPixelT,class OutPixelT,class KernelPixelT,class SumTypeT>
  istream &operator>>(istream &s, GaussConvolveC<InPixelT,OutPixelT,KernelPixelT,SumTypeT> &in) {
    UIntT sz;
    s >> sz;
    in = GaussConvolveC<InPixelT,OutPixelT,SumTypeT>(sz);
    return s;
  }
  
  template<class InPixelT,class OutPixelT,class KernelPixelT,class SumTypeT>
  BinOStreamC &operator<<(BinOStreamC &s, const GaussConvolveC<InPixelT,OutPixelT,KernelPixelT,SumTypeT> &out) {
    s << ((UIntT) out.binomial.Size());
    return s;
  }
  
  template<class InPixelT,class OutPixelT,class KernelPixelT,class SumTypeT>
  BinIStreamC &operator>>(BinIStreamC &s, GaussConvolveC<InPixelT,OutPixelT,KernelPixelT,SumTypeT> &in) {
    UIntT sz;
    s >> sz;
    in = GaussConvolveC<InPixelT,OutPixelT,SumTypeT>(sz);
    return s;
  }

}




#endif
