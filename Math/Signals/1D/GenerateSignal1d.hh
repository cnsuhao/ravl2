// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_GENERATESIGNAL1D_HEADER
#define RAVL_GENERATESIGNAL1D_HEADER 1
///////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! docentry="Ravl.Math.Signal.1D"
#include "Ravl/Array1d.hh"

namespace RavlN {
  
  
  Array1dC<RealT> GenerateRandomGuass1d(SizeT size,RealT stdDeviation,RealT mean);
  //: Generate an array containing guassian noise with specified properties.
  
  Array1dC<RealT> GenerateGuass1d(RealT sigma,RealT mean = 0,RealT scale = 1,RealT size = 2);
  //: Generate a 1-d guassian curve.
    
  template<class DataT>
  Array1dC<DataT> GenerateBinomial(DataT seed,SizeT size, bool doNorm = false,bool center = false) {
    Array1dC<DataT> fnc;
    if(!center)
      fnc = Array1dC<DataT>(size);
    else {
      fnc = Array1dC<DataT>(-(size/2),(size/2));
      RavlAssertMsg(size == fnc.Size(),"GenerateBinomial(), size must be odd to center. ");
    }
    BufferAccessIterC<DataT> it(fnc);
    DataT i = 1;
    DataT last,rsize = size;
    *it = seed;
    last = *it;
    it++;
    if(doNorm) {
      IntT norm = 1;
      for (;it;it++,i++) {
	*it = last * (rsize-i) / i;
	last = *it;
	norm *= 2;
      }
      for (it.First(fnc);it;it++)  
	*it /= norm;
    } else {
      for (;it;it++,i++) {
	*it = last * (rsize-i) / i;
	last = *it;
      }
    }
    return fnc;
  }
  //! author="Bill Chrismas"
  //: Creates an array of binomial coefficients 
  //(i.e. row "size" from Pascal's
  // triangle).<br> E.g. Binomial(5) would create the array: 1,4,6,4,1.<br> Can
  // be used as a finite approximation of a Gaussian.  The "variance" of this
  // Gaussian is (size-1)/4.<br>  The 'seed' should be set to a unit value of the
  // same type as the array element required.
  // If Norm = true, the array is normalised so that the sum of the terms = 1.
  
}

#endif
