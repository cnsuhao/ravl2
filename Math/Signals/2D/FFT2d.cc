// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/FFT2d.hh"
#include "Ravl/Exception.hh"
#include "Ravl/SArr2Iter2.hh"
#include "ccmath/ccmath.h"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  //: Constructor.
  
  FFT2dBodyC::FFT2dBodyC(Index2dC nn,bool iinv) 
    : n(0),
      m(0),
      inv(iinv)
  { Init(nn,iinv); }
  
  //: Destructor
  
  FFT2dBodyC::~FFT2dBodyC()  {
  }
  
  //: Create a plan with the given setup.
  
  bool FFT2dBodyC::Init(Index2dC nsize,bool iinv) {
    // Remeber settings in case we asked...
    inv = iinv;
    size = nsize;
    RavlAssert(IsPow2(size[0].V()) && IsPow2(size[1].V()));
    m = ILog2(size[0].V());
    n = ILog2(size[1].V());
    return true;
  }
  
  //: Apply transform to array.
  
  SArray2dC<ComplexC> FFT2dBodyC::Apply(const SArray2dC<ComplexC> &dat) {
    ONDEBUG(cerr << "FFT2dBodyC::Apply(SArray2dC<ComplexC>) n=" << n << " inv=" << inv << " \n");
    RavlAssert(dat.Size1() == (UIntT) size[0].V());
    RavlAssert(dat.Size2() == (UIntT) size[1].V());
    SArray2dC<ComplexC> ret = dat.Copy();
    //cerr << dat <<  "\n";
    if(inv)
      fft2_d((complex *) ((void *) &(ret[0][0])),m,n,'i');
    else
      fft2_d((complex *) ((void *) &(ret[0][0])),m,n,'d');
    //cerr << "result:" << ret << "\n";;
    return ret;
  }
  
  //: Apply transform to array.
  
  SArray2dC<ComplexC> FFT2dBodyC::Apply(const SArray2dC<RealT> &dat) {
    ONDEBUG(cerr << "FFT2dBodyC::Apply(SArray2dC<RealT>) n=" << n << " inv=" << inv << " opt=" << opt << "\n");
    RavlAssert(dat.Size1() == (UIntT) size[0].V());
    RavlAssert(dat.Size2() == (UIntT) size[1].V());
    SArray2dC<ComplexC> ret(dat.Size1(),dat.Size2());
    for(SArray2dIter2C<ComplexC,RealT> it(ret,dat);it;it++)
      it.Data1() = it.Data2();
    //cerr << dat <<  "\n";
    if(inv)
      fft2_d((complex *) ((void *)&(ret[0][0])),m,n,'i');
    else
      fft2_d((complex *) ((void *)&(ret[0][0])),m,n,'d');
    //cerr << "result:" << ret << "\n";;
    return ret;
  }

  
}
