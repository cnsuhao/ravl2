// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/FFT2d.hh"
#include "Ravl/SArr2Iter.hh"
#include "Ravl/SArr2Iter2.hh"

using namespace RavlN;

int testFFT2d();
int testFFT2dPwr2();

int testRealFFT2d();
int testRealFFT2dPwr2();

int main()
{
  int ln;
  if((ln = testFFT2d()) != 0) {
    cerr << "Error line " << ln << "\n";
    return 1;
  }
  if((ln = testFFT2dPwr2()) != 0) {
    cerr << "Error line " << ln << "\n";
    return 1;
  }
  if((ln = testRealFFT2d()) != 0) {
    cerr << "Error line " << ln << "\n";
    return 1;
  }
  if((ln = testRealFFT2dPwr2()) != 0) {
    cerr << "Error line " << ln << "\n";
    return 1;
  }
  cout << "Test passed. \n";
  return 0;
}

int testFFT2d() {
  cerr << "testFFT2d(), Started. \n";
  SArray2dC<ComplexC> indat(30,20);
  int i = 0;
  for(SArray2dIterC<ComplexC> it(indat);it;it++)
    *it = ComplexC(i++,0);
  
  FFT2dC fftf(30,20,false); // create forward transform.
  SArray2dC<ComplexC> fres = fftf.Apply(indat);
  
  //cerr << fres << "\n";
  
  FFT2dC ffti(30,20,true);// create reverse transform.
  SArray2dC<ComplexC> ires = ffti.Apply(fres);
  
  //cerr << ires << "\n";
  
  for(SArray2dIter2C<ComplexC,ComplexC> rit(indat,ires);rit;rit++) {
    if(Abs(rit.Data1().Re() - rit.Data2().Re()) > 0.000001)
      return __LINE__;
    if(Abs(rit.Data1().Im() - rit.Data2().Im()) > 0.000001)
      return __LINE__;
  }
  return 0;
}

int testFFT2dPwr2() {
  cerr << "testFFT2dPwr2(), Started. \n";
  SArray2dC<ComplexC> indat(64,32);
  int i = 0;
  for(SArray2dIterC<ComplexC> it(indat);it;it++)
    *it = ComplexC(i++,0);
  
  FFT2dC fftf(64,32,false); // create forward transform.
  SArray2dC<ComplexC> fres = fftf.Apply(indat);
  
  //cerr << fres << "\n";
  
  FFT2dC ffti(64,32,true);// create reverse transform.
  SArray2dC<ComplexC> ires = ffti.Apply(fres);
  
  //cerr << ires << "\n";
  
  // Check results.
  
  for(SArray2dIter2C<ComplexC,ComplexC> rit(indat,ires);rit;rit++) {
    if(Abs(rit.Data1().Re() - rit.Data2().Re()) > 0.000001)
      return __LINE__;
    if(Abs(rit.Data1().Im() - rit.Data2().Im()) > 0.000001)
      return __LINE__;
  }
  return 0;
}



int testRealFFT2d() {
  cerr << "testRealFFT2d(), Started. \n";
  SArray2dC<RealT> indat(30,20);
  int i = 0;
  for(SArray2dIterC<RealT> it(indat);it;it++)
    *it = (RealT) i++;
  
  FFT2dC fftf(30,20,false); // create forward transform.
  SArray2dC<ComplexC> fres = fftf.Apply(indat);
  
  //cerr << fres << "\n";
  
  FFT2dC ffti(30,20,true);// create reverse transform.
  SArray2dC<ComplexC> ires = ffti.Apply(fres);
  
  //cerr << ires << "\n";
  
  for(SArray2dIter2C<RealT,ComplexC> rit(indat,ires);rit;rit++) {
    if(Abs(rit.Data1() - rit.Data2().Re()) > 0.000001)
      return __LINE__;
    if(Abs(rit.Data2().Im()) > 0.000001)
      return __LINE__;
  }
  return 0;
}

int testRealFFT2dPwr2() {
  cerr << "testRealFFT2dPwr2(), Started \n";
  SArray2dC<RealT> indat(64,32);
  int i = 0;
  for(SArray2dIterC<RealT> it(indat);it;it++)
    *it = i++;
  
  FFT2dC fftf(64,32,false); // create forward transform.
  SArray2dC<ComplexC> fres = fftf.Apply(indat);
  
  //cerr << fres << "\n";
  
  FFT2dC ffti(64,32,true);// create reverse transform.
  SArray2dC<ComplexC> ires = ffti.Apply(fres);
  
  //cerr << ires << "\n";
  
  // Check results.
  
  for(SArray2dIter2C<RealT,ComplexC> rit(indat,ires);rit;rit++) {
    if(Abs(rit.Data1() - rit.Data2().Re()) > 0.000001)
      return __LINE__;
    if(Abs(rit.Data2().Im()) > 0.000001)
      return __LINE__;
  }
  return 0;
}
