// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_HISTOGRAMEQUALISE_HEADER
#define RAVLIMAGE_HISTOGRAMEQUALISE_HEADER 1
//! userlevel=Normal
//! author="Kieron J Messer"
//! docentry="Ravl.Images.Filtering"
//! rcsid="$Id$"
//! lib=RavlImage

#include "Ravl/Image/Image.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/Array1dIter2.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Histogram Equalisation.
  
  template<class DataT>
  class HistogramEqualiseC {
  public:
    HistogramEqualiseC(DataT nminValue = 0,DataT nmaxValue = 255)
      : minValue(nminValue),
	maxValue(nmaxValue)
    {}
    //: Constructor.
    
    ImageC<DataT> Apply (const ImageC<DataT> &in);
    //: Performs histogram equalisation on image 'in'.
    // Returns a new equalised image.
    
  protected:
    DataT minValue;
    DataT maxValue;
  };
  
  //: Performs histogram equalisation on image 'in'.
  // Returns a new equalised image.
  
  template<class DataT>
  ImageC<DataT> HistogramEqualiseC<DataT>::Apply (const ImageC<DataT> &in) {
    // Build the histogram.
    
    Array1dC<RealT> pr(minValue,maxValue);
    pr.Fill(0.0);
    for(Array2dIterC<DataT> it(in);it;it++)
      pr[Floor(*it)]++;
    
    // Compute the cumalitve histogram, and use it to compute the
    // transform.
    
    RealT n = (RealT) in.Frame().Area();
    RealT sum = 0.0;
    DataT diff = maxValue - minValue;
    Array1dC<DataT> tr(minValue,maxValue);
    for(Array1dIter2C<DataT,RealT> it(tr,pr);it;it++) {
      RealT val = it.Data2();
      it.Data1() = (DataT) (sum * diff) + minValue;
      if(val > 0.0)
	sum += val / n;
    }
    
    // Transform the image.
    
    ImageC<DataT> op(in.Frame());
    for(Array2dIter2C<DataT,DataT> it(in,op);it;it++)
      it.Data2() = tr[Floor(it.Data1())];
    
    return op;
  }

}

#endif
