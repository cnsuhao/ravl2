// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/FFT1d.hh"
#include "Ravl/Exception.hh"
#include "Ravl/SArr1Iter2.hh"
#include "ccmath/ccmath.h"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  //: Constructor.
  
  FFT1dBodyC::FFT1dBodyC(int nn,bool iinv) 
    : n(0),
      inv(iinv)
  { Init(nn,iinv); }
  
  //: Destructor
  
  FFT1dBodyC::~FFT1dBodyC()  {
  }
  
  //: Create a plan with the given setup.
  
  bool FFT1dBodyC::Init(int nn,bool iinv) {
    // Remeber settings in case we asked...
    inv = iinv;
    pwr2 = IsPow2(nn);
    n = nn;
    nf = pfac(n,primeFactors,'o');
    return true;
  }
  
  //: Apply transform to array.
  
  SArray1dC<ComplexC> FFT1dBodyC::Apply(const SArray1dC<ComplexC> &dat) {
    ONDEBUG(cerr << "FFT1dBodyC::Apply(SArray1dC<ComplexC>) n=" << n << " inv=" << inv << " \n");
    RavlAssert(dat.Size() == (UIntT) n);
    SArray1dC<ComplexC> ret = dat.Copy();
    SArray1dC<complex *> ptrArr(n);
    //cerr << dat <<  "\n";
    // FIXME :- Would it be quicker to copy the array and use fft2 if length is a power of two ?
    if(inv)
      fftgc((complex **) ((void *)&(ptrArr[0])),
	    (complex *) ((void *)&(ret[0])),
	    n,
	    primeFactors,
	    'i');
    else
      fftgc((complex **) ((void *)&(ptrArr[0])),
	    (complex *) ((void *)&(ret[0])),
	    n,
	    primeFactors,
	    'd');
    
    //cerr << "result:" << ret << "\n";;
    return ret;
  }
  
  //: Apply transform to array.
  
  SArray1dC<ComplexC> FFT1dBodyC::Apply(const SArray1dC<RealT> &dat) {
    ONDEBUG(cerr << "FFT1dBodyC::Apply(SArray1dC<RealT>) n=" << n << " inv=" << inv << " opt=" << opt << "\n");
    RavlAssert(dat.Size() == (UIntT) n)
    SArray1dC<ComplexC> ret(n); 
    if(inv)
      fftgr((double *) &(dat[0]),
	    (complex *) ((void *)&(ret[0])),
	    n,
	    primeFactors,
	    'i');
    else
      fftgr((double *) &(dat[0]),
	    (complex *) ((void *)&(ret[0])),
	    n,
	    primeFactors,
	    'd');
    return ret; 
  }

  
}
