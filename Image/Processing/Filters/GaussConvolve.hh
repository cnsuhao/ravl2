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
  //: Filter an image with a guassian.
  // This class is just wraps ConvolveSeparable2d and
  // GenerateBinomial() calls in a convient form.
  
  template<class DataT>
  class GaussConvolveC {
  public:
    GaussConvolveC()
    {}
    //: Default constructor.
    
    GaussConvolveC(UIntT order);
    //: Construct gausian with the given size.
    
    ImageC<DataT> Apply (const ImageC<DataT> &in) const;
    //: Performs histogram equalisation on image 'in'.
    // Returns a new equalised image.
    
    Array1dC<RealT> &Filter()
    { return binomial; }
    //: Access current filter.
    // Note the save/load routines of this class do NOT save
    // the filter co-efficients, just its order. So modifying
    // them and saving this class is pointless.
    
    const Array1dC<RealT> &Filter() const
    { return binomial; }
    //: Access current filter.
    
    UIntT Order() const
    { return binomial.Size(); }
    //: Get size of gausian.
    
    friend ostream &operator<< <>(ostream &s, const GaussConvolveC<DataT> &out);
    //: output stream operator
    
    friend istream &operator>> <>(istream &s, GaussConvolveC<DataT> &in);
    //: input stream operator
    
    friend BinOStreamC &operator<< <>(BinOStreamC &s, const GaussConvolveC<DataT> &out);
    //: output stream operator
    
    friend BinIStreamC &operator>> <>(BinIStreamC &s, GaussConvolveC<DataT> &in);
    //: input stream operator
    
  protected:
    Array1dC<RealT> binomial;
    ConvolveSeparable2dC<RealT, DataT> conv;
  };
  
  //: Performs histogram equalisation on image 'in'.
  // Returns a new equalised image.


  template<class DataT>
  GaussConvolveC<DataT>::GaussConvolveC(UIntT order) {
    binomial = GenerateBinomial(1.0, order, true,true);
    conv.SetKernel(binomial, binomial);
  }
  
  template<class DataT>
  ImageC<DataT> GaussConvolveC<DataT>::Apply (const ImageC<DataT> &in) const {
    ImageC<DataT> op;
    conv.Apply(in, op);
    return op;
  }

  template<class DataT>
  ostream &operator<<(ostream &s, const GaussConvolveC<DataT> &out) {
    s << out.binomial.Size() << endl;
    return s;
  }

  template<class DataT>
  istream &operator>>(istream &s, GaussConvolveC<DataT> &in) {
    UIntT sz;
    s >> sz;
    in = GaussConvolveC<DataT>(sz);
    return s;
  }
  
  template<class DataT>
  BinOStreamC &operator<<(BinOStreamC &s, const GaussConvolveC<DataT> &out) {
    s << ((UIntT) out.binomial.Size());
    return s;
  }
  
  template<class DataT>
  BinIStreamC &operator>>(BinIStreamC &s, GaussConvolveC<DataT> &in) {
    UIntT sz;
    s >> sz;
    in = GaussConvolveC<DataT>(sz);
    return s;
  }

}




#endif
