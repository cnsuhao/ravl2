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

#include "Ravl/Image/Image.hh"
#include "Ravl/GenerateSignal1d.hh"
#include "Ravl/Image/ConvolveSeparable2d.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Low-pass-filters an image with a finite-width approximation to a Gaussian mask
  //
  // <p>The "standard deviation" of a filter with <i>n</i> terms is (<i>n</i>-1/4)^1/2</p>
  // <p>It is designed by using a normalised row from Pascal's triangle
  // (i.e. binomial coefficients).  The rational is this:
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
  // e.g. If you wish to convolve a ByteRGBValueC SumTypeT should be set to RealRGBValueC.
  
  template<class InPixelT,class OutPixelT = InPixelT,class SumTypeT = RealT,class FilterT = RealT>
  class GaussConvolveC {
  public:
    GaussConvolveC()
    {}
    //: Default constructor.
    
    GaussConvolveC(UIntT order) {
      binomial = GenerateBinomial((FilterT) 1.0, order, true,true);
      conv.SetKernel(binomial, binomial);
    }
    //: Construct Gaussian with the given size.
    
    ImageC<OutPixelT> Apply (const ImageC<InPixelT> &in) const {
      ImageC<OutPixelT> op;
      conv.Apply(in, op);
      return op;
    }
    //: Performs histogram equalisation on image 'in'.
    // Returns a new equalised image.
    
    Array1dC<FilterT> &Filter()
    { return binomial; }
    //: Access current filter.
    // Note the save/load routines of this class do NOT save
    // the filter coefficients, just its order. So modifying
    // them and saving this class is pointless.
    
    const Array1dC<FilterT> &Filter() const
    { return binomial; }
    //: Access current filter.
    
    UIntT Order() const
    { return binomial.Size(); }
    //: Get size of gausian.

#if RAVL_NEW_ANSI_CXX_DRAFT
    friend ostream &operator<< <>(ostream &s, const GaussConvolveC<InPixelT,OutPixelT,SumTypeT> &out);
    //: output stream operator
    
    friend istream &operator>> <>(istream &s, GaussConvolveC<InPixelT,OutPixelT,SumTypeT> &in);
    //: input stream operator
    
    friend BinOStreamC &operator<< <>(BinOStreamC &s, const GaussConvolveC<InPixelT,OutPixelT,SumTypeT> &out);
    //: output stream operator
    
    friend BinIStreamC &operator>> <>(BinIStreamC &s, GaussConvolveC<InPixelT,OutPixelT,SumTypeT> &in);
    //: input stream operator
#else
    friend ostream &operator<< (ostream &s, const GaussConvolveC<InPixelT,OutPixelT,SumTypeT> &out);
    //: output stream operator
    
    friend istream &operator>> (istream &s, GaussConvolveC<InPixelT,OutPixelT,SumTypeT> &in);
    //: input stream operator
    
    friend BinOStreamC &operator<< (BinOStreamC &s, const GaussConvolveC<InPixelT,OutPixelT,SumTypeT> &out);
    //: output stream operator
    
    friend BinIStreamC &operator>> (BinIStreamC &s, GaussConvolveC<InPixelT,OutPixelT,SumTypeT> &in);
    //: input stream operator
#endif
    
  protected:
    Array1dC<FilterT> binomial;
    ConvolveSeparable2dC<FilterT, InPixelT,OutPixelT,SumTypeT> conv;
  };
  
  template<class InPixelT,class OutPixelT,class SumTypeT>
  ostream &operator<<(ostream &s, const GaussConvolveC<InPixelT,OutPixelT,SumTypeT> &out) {
    s << out.binomial.Size() << endl;
    return s;
  }

  template<class InPixelT,class OutPixelT,class SumTypeT>
  istream &operator>>(istream &s, GaussConvolveC<InPixelT,OutPixelT,SumTypeT> &in) {
    UIntT sz;
    s >> sz;
    in = GaussConvolveC<InPixelT,OutPixelT,SumTypeT>(sz);
    return s;
  }
  
  template<class InPixelT,class OutPixelT,class SumTypeT>
  BinOStreamC &operator<<(BinOStreamC &s, const GaussConvolveC<InPixelT,OutPixelT,SumTypeT> &out) {
    s << ((UIntT) out.binomial.Size());
    return s;
  }
  
  template<class InPixelT,class OutPixelT,class SumTypeT>
  BinIStreamC &operator>>(BinIStreamC &s, GaussConvolveC<InPixelT,OutPixelT,SumTypeT> &in) {
    UIntT sz;
    s >> sz;
    in = GaussConvolveC<InPixelT,OutPixelT,SumTypeT>(sz);
    return s;
  }

}




#endif
