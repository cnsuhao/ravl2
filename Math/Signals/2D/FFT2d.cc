// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Signals/2D/FFT2d.cc"

#include "Ravl/FFT2d.hh"
#include "Ravl/Exception.hh"
#include "Ravl/SArr2Iter2.hh"
#include "Ravl/Slice1d.hh"

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
      inv(iinv),
      base2(false)
  { Init(nn,iinv); }
  
  //: Destructor
  
  FFT2dBodyC::~FFT2dBodyC()  {
  }
  
  //: Create a plan with the given setup.
  
  bool FFT2dBodyC::Init(Index2dC nsize,bool iinv) {
    // Remeber settings in case we asked...
    inv = iinv;
    size = nsize;
    if(IsPow2(size[0].V()) && IsPow2(size[1].V())) {
      m = ILog2(size[0].V());
      n = ILog2(size[1].V());
      base2 = true;
    } else {
      base2 = false;
      
      nf = pfac(size[1].V(),primeFactors,'o');
      
      tmp1 = SArray2dC<ComplexC>(size[0].V(),size[1].V());
      tmp1Ptr = SArray2dC<ComplexC *>(size[0].V(),size[1].V());
    }
    return true;
  }
  
  //: Apply transform to array.
  
  SArray2dC<ComplexC> FFT2dBodyC::Apply(const SArray2dC<ComplexC> &dat) {
    ONDEBUG(cerr << "FFT2dBodyC::Apply(SArray2dC<ComplexC>) n=" << n << " inv=" << inv << " \n");
    RavlAssert(dat.Size1() == (UIntT) size[0].V());
    RavlAssert(dat.Size2() == (UIntT) size[1].V());
    SArray2dC<ComplexC> ret = dat.Copy();
    if(base2) {
      //cerr << dat <<  "\n";
      if(inv)
	fft2_d((complex *) ((void *) &(ret[0][0])),m,n,'i');
      else
	fft2_d((complex *) ((void *) &(ret[0][0])),m,n,'d');
      //cerr << "result:" << ret << "\n";;
      return ret;
    }
    int nr = dat.Size2();
    int i,j;
    SArray1dC<ComplexC> cplx(size[1].V());
    SArray1dC<complex> idat(dat.Size());
    SArray1dC<complex *> ptrArr(size[1].V());
    for(BufferAccessIter2C<complex *,complex> it(ptrArr,idat);it;it++)
	it.Data1() = &it.Data2();  
    for(SArray2dIter2C<ComplexC *,ComplexC> it(tmp1Ptr,tmp1);it;it++)
      it.Data1() = &it.Data2();
    
    if(inv) {
      // fft of rows.
      for(i = 0;i < (int) dat.Size1();i++)
	fftgc((Cpx **)((void *) (tmp1Ptr[i].DataStart())),
	      (complex *)((void *) (tmp1[i].DataStart())),
	      nr,primeFactors,'i');
      // fft of cols.
      for(j = 0;j < (int) dat.Size2();j++) {
	idat.Copy(tmp1.SliceColumn(j));
	
	fftgc((complex **) ((void *)&(ptrArr[0])),
	      (complex *) ((void *) idat.DataStart()),
	      n,
	      primeFactors,
	      'i');
	
	for(Slice1dIter2C<complex *,ComplexC> itb(ptrArr,ret.SliceCol(j));itb;itb++)
	  itb.Data2() = *((ComplexC *)itb.Data1());
      }
    } else {
    }
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
