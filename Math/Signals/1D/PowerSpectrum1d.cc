// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/StdMath.hh"
#include "Ravl/PowerSpectrum1d.hh"
#include "Ravl/SArr1Iter2.hh"
#include "ccmath/ccmath.h"

namespace RavlN {

  //: Compute the power spectrum of data with no windowing.
  
  SArray1dC<RealT> PowerSpectrumSimple(const SArray1dC<RealT> &data,int smooth = 0) {
    SArray1dC<RealT> ret = data.Copy();
    int os = pwspec((double *) &(ret[0]),data.Size(),smooth);
    return SArray1dC<RealT>(ret,os);
  }
  
  //: Constructor
  
  PowerSpectrum1dC::PowerSpectrum1dC(IntT size)
    : fft(size)
  {}

  //: Compute the power spectrum of data.
  
  SArray1dC<RealT> PowerSpectrum1dC::Apply(const SArray1dC<RealT> &data) {
    UIntT size = data.Size();
    UIntT mid = size/2;
    UIntT rem = size - mid;
    //cerr << "Size=" << size <<" Mid=" << mid << " Rem=" << rem << "\n";
    SArray1dC<RealT> d1(data,mid);
    SArray1dC<RealT> d2(data,rem,mid);
    return Apply(d1,d2);
  }
  
  //: Compute the power spectrum of data in two arrays.
  // Compute the power spectrum using Bartlett window (simple triangle).
  // The arrays are expected to be of equal size, so the first
  // array will be multiplied by an increasing ramp, the second
  // by a decreasing one.
  
  SArray1dC<RealT> PowerSpectrum1dC::Apply(const SArray1dC<RealT> &d1,const SArray1dC<RealT> &d2) {
    UIntT size = d1.Size() + d2.Size();
    RavlAssert(Abs((int) d1.Size() - (int) d2.Size()) <= 1);    
    if(size == 0)
      return SArray1dC<RealT>();
    SArray1dC<RealT> work(size);
    SArray1dC<RealT> ret(size);
    
    RealT wss = 0; // This should be computed analytically.
    // Ramp up
    int mid = d1.Size();
    RealT frac = 0,inc = 1/((RealT)size);
    for(SArray1dIter2C<RealT,RealT> it(d1,work);it;it++) {
      frac += inc;
      it.Data2() = it.Data1() * frac;
      wss += Sqr(frac); 
    }
    
    // Ramp down
    int rem = d2.Size();
    inc = 1/(RealT) rem; // Make sure its accurate.
    SArray1dC<RealT> t2(work,rem,mid);
    for(SArray1dIter2C<RealT,RealT> it(t2,d2);it;it++) {
      frac -= inc;
      it.Data1() = it.Data2() * frac;
      wss += Sqr(frac);
    }
    
    // Do the fft.
    
    SArray1dC<ComplexC> fftres = fft.Apply(work);
    
    wss *= size/2; // Because we only sum half the spectrum.
    //cerr << "wss:" << wss << "\n";
    // Compute the magintude.
    SArray1dC<RealT> mag(fftres.Size() / 2);
    SArray1dIter2C<RealT,ComplexC> it(mag,fftres);
    it.Data1() = (Sqr(it.Data2().Re()) + Sqr(it.Data2().Im())) / (wss * 2);
    it++;
    for(;it;it++)
      it.Data1() = (Sqr(it.Data2().Re()) + Sqr(it.Data2().Im())) / wss;
    
    // Return the results.
    return mag;
  }

  
}
