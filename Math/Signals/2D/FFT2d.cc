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
#include "Ravl/SArray2dIter2.hh"
#include "Ravl/SArray2dIter3.hh"
#include "Ravl/Slice1d.hh"

#include "ccmath/ccmath.h"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif


namespace RavlN {
  
#if RAVL_COMPILER_MIPSPRO
  static Slice1dC<ComplexC*> fixSGIBug1;
  static Slice1dIter2C<ComplexC*,ComplexC> fixSGIBug2;
#endif

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
      ONDEBUG(cerr << "FFT2dBodyC::Init(), Initalise power of 2 transform. \n");
      base2 = true;
      m = ILog2(size[0].V());
      n = ILog2(size[1].V());
    } else {
      ONDEBUG(cerr << "FFT2dBodyC::Init(), Initalise arbitary size transform. \n");
      base2 = false;
      nf1 = pfac(size[0].V(),primeFactors1,'o');
      nf2 = pfac(size[1].V(),primeFactors2,'o');
      tmp1 = SArray2dC<ComplexC>(size[0].V(),size[1].V());
      tmp1Ptr = SArray2dC<ComplexC *>(size[0].V(),size[1].V());
    }
    return true;
  }
  
  //: Apply transform to array.
  
  SArray2dC<ComplexC> FFT2dBodyC::Apply(const SArray2dC<ComplexC> &dat) {
    ONDEBUG(cerr << "FFT2dBodyC::Apply(SArray2dC<ComplexC>) n=" << n << " inv=" << inv << " Size=" << size << "\n");
    RavlAssert(dat.Size1() == (UIntT) size[0].V());
    RavlAssert(dat.Size2() == (UIntT) size[1].V());
    SArray2dC<ComplexC> ret;
    if(base2) {
      ret = dat.Copy();
      //cerr << dat <<  "\n";
      if(inv)
	fft2_d((complex *) ((void *) ret[0].DataStart()),m,n,'i');
      else
	fft2_d((complex *) ((void *) ret[0].DataStart()),m,n,'d');
      //cerr << "result:" << ret << "\n";;
      return ret;
    }
    ret = SArray2dC<ComplexC>(size[0].V(),size[1].V());
    int i,j;
    SArray1dC<ComplexC> idat(size[0].V());
    SArray1dC<ComplexC *> ptrArr(size[0].V());
    for(SArray2dIter3C<ComplexC *,ComplexC,ComplexC> it(tmp1Ptr,tmp1,dat);it;it++) {
      it.Data2() = it.Data3();
      it.Data1() = &it.Data2();
    }
    
    if(inv) {
      // fft of rows.
      for(i = 0;i < (int) dat.Size1();i++)
	fftgc((Cpx **)((void *) (tmp1Ptr[i].DataStart())),
	      (complex *)((void *) (tmp1[i].DataStart())),
	      size[1].V(),primeFactors2,'i');
      
      // fft of cols.
      for(j = 0;j < (int) dat.Size2();j++) {
	Slice1dC<ComplexC> slice(tmp1.Buffer().Data(),tmp1Ptr[0][j],tmp1.Size1(),tmp1.Stride());
	idat.CopyFrom(slice);
	for(BufferAccessIter2C<ComplexC *,ComplexC> it(ptrArr,idat);it;it++)
	  it.Data1() = &it.Data2();
	//cerr << idat << "\n";
	fftgc((complex **) ((void *)&(ptrArr[0])),
	      (complex *) ((void *) idat.DataStart()),
	      idat.Size(),primeFactors1,'i');
	
	for(Slice1dIter2C<ComplexC *,ComplexC> itb(ptrArr.Slice1d(),ret.SliceColumn(j));itb;itb++)
	  itb.Data2() = *itb.Data1();
      }
    } else {
      // fft of rows.
      for(i = 0;i < (int) dat.Size1();i++)
	fftgc((Cpx **)((void *) (tmp1Ptr[i].DataStart())),
	      (complex *)((void *) (tmp1[i].DataStart())),
	      size[1].V(),primeFactors2,'d');
      // fft of cols.
      for(j = 0;j < (int) dat.Size2();j++) {
	Slice1dC<ComplexC> slice(tmp1.Buffer().Data(),tmp1Ptr[0][j],dat.Size1(),dat.Stride());
	idat.CopyFrom(slice);
	//cerr << const_cast<SArray2dC<ComplexC> &>(dat).SliceColumn(j) << "\n";
	for(BufferAccessIter2C<ComplexC *,ComplexC> it(ptrArr,idat);it;it++)
	  it.Data1() = &it.Data2();
	
	fftgc((complex **) ((void *) ptrArr.DataStart()),
	      (complex *) ((void *) idat.DataStart()),
	      idat.Size(),primeFactors1,'d');
	
	for(Slice1dIter2C<ComplexC *,ComplexC> itb(ptrArr.Slice1d(),ret.SliceColumn(j));itb;itb++)
	  itb.Data2() = *itb.Data1();      
      }
    }
    return ret;
  }
  
  //: Apply transform to array.
  
  SArray2dC<ComplexC> FFT2dBodyC::Apply(const SArray2dC<RealT> &dat) {
    ONDEBUG(cerr << "FFT2dBodyC::Apply(SArray2dC<ComplexC>) n=" << n << " inv=" << inv << " \n");
    RavlAssert(dat.Size1() == (UIntT) size[0].V());
    RavlAssert(dat.Size2() == (UIntT) size[1].V());
    SArray2dC<ComplexC> ret(dat.Size1(),dat.Size2());
    if(base2) {
      for(SArray2dIter2C<RealT,ComplexC> it(dat,ret);it;it++)
	it.Data2() = ComplexC(it.Data1(),0);
      //cerr << dat <<  "\n";
      if(inv)
	fft2_d((complex *) ((void *) ret[0].DataStart()),m,n,'i');
      else
	fft2_d((complex *) ((void *) ret[0].DataStart()),m,n,'d');
      //cerr << "result:" << ret << "\n";;
      return ret;
    }
    int i,j;
    SArray1dC<ComplexC> idat(size[0].V());
    SArray1dC<ComplexC *> ptrArr(size[0].V());
    
    if(inv) {
      // fft of rows.
      for(i = 0;i < (int) dat.Size1();i++)
	fftgr(dat[i].DataStart(),
	      (complex *)((void *) tmp1[i].DataStart()),
	      size[1].V(),primeFactors2,'i');
      // fft of cols.
      for(j = 0;j < (int) dat.Size2();j++) {
	idat.CopyFrom(tmp1.SliceColumn(j));
	for(BufferAccessIter2C<ComplexC *,ComplexC> it(ptrArr,idat);it;it++) 
	  it.Data1() = &it.Data2();
	
	fftgc((complex **) ((void *)&(ptrArr[0])),
	      (complex *) ((void *) idat.DataStart()),
	      idat.Size(),primeFactors1,'i');
	
	for(Slice1dIter2C<ComplexC *,ComplexC> itb(ptrArr.Slice1d(),ret.SliceColumn(j));itb;itb++)
	  itb.Data2() = *itb.Data1();
      }
    } else {
      // fft of rows.
      for(i = 0;i < (int) dat.Size1();i++)
	fftgr(dat[i].DataStart(),
	      (complex *)((void *) tmp1[i].DataStart()),
	      size[1].V(),primeFactors2,'d');
      // fft of cols.
      for(j = 0;j < (int) dat.Size2();j++) {
	idat.CopyFrom(tmp1.SliceColumn(j));
	for(BufferAccessIter2C<ComplexC *,ComplexC> it(ptrArr,idat);it;it++) 
	  it.Data1() = &it.Data2();
	
	fftgc((complex **) ((void *)&(ptrArr[0])),
	      (complex *) ((void *) idat.DataStart()),
	      idat.Size(),primeFactors1,'d');
	
	for(Slice1dIter2C<ComplexC *,ComplexC> itb(ptrArr.Slice1d(),ret.SliceColumn(j));itb;itb++)
	  itb.Data2() = *itb.Data1();
      }
    }
    return ret;
  }

  
}
