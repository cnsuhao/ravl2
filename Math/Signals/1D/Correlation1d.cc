// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/StdMath.hh"
#include "Ravl/Correlation1d.hh"
#include "Ravl/SArr1Iter2.hh"
#include "Ravl/SArr1Iter.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  //: Constructor.
  
  Correlation1dC::Correlation1dC(IntT size)
#if 1
    : fft(size*2,false,true),
      ifft(size*2,true)
#else
    : fft(size,false),
      ifft(size,true)
#endif
  {}
  
  //: Return the correlation of signals d1 and d2.
  
  SArray1dC<RealT> Correlation1dC::Apply(const SArray1dC<RealT> &d1,const SArray1dC<RealT> &d2) {
    if(d1.Size() == 0)
      return SArray1dC<RealT>();
    // Do a forward fft.
    SArray1dC<ComplexC> fftd1 = fft.Apply(d1);
    SArray1dC<ComplexC> fftd2 = fft.Apply(d2);
    ONDEBUG(cerr << "CRes Size1:" << fftd1.Size() << " Size2:" << fftd2.Size() << "\n");
    // Multiply by the complex conjugate and put result back in fftd1.
    for(SArray1dIter2C<ComplexC,ComplexC> it(fftd1,fftd2);it;it++)
      it.Data1() = it.Data1() * it.Data2().Conj();
    // Do a reverse fft.
    SArray1dC<ComplexC> cres = ifft.Apply(fftd1);
    ONDEBUG(cerr << "CRes Size:" << cres.Size() << "\n");
    SArray1dC<RealT> ret(cres.Size());
    // Convert to real parts only.
    for(SArray1dIter2C<RealT,ComplexC> it(ret,cres);it;it++)
      it.Data1() = it.Data2().Re();
    return ret;
  }
  
  
  //: Return the auto correlation  signals d1.
  // This uses FFT to caculate the correlation d1 and itself.
  
  SArray1dC<RealT> Correlation1dC::AutoCorrelation(const SArray1dC<RealT> &d1) {
    if(d1.Size() == 0)
      return SArray1dC<RealT>();
    // Do a forward fft.
    SArray1dC<ComplexC> fftd1 = fft.Apply(d1);
    // Multiply by the complex conjugate and put result back in fftd1.
    for(SArray1dIterC<ComplexC> it(fftd1);it;it++)
      it.Data1() = it.Data1() * it.Data1().Conj();
    // Do a reverse fft.
    SArray1dC<ComplexC> cres = ifft.Apply(fftd1);
    SArray1dC<RealT> ret(cres.Size());
    for(SArray1dIter2C<RealT,ComplexC> it(ret,cres);it;it++)
      it.Data1() = it.Data2().Re();
    return ret;
  }

}
