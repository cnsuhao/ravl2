// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Signals/2D/testFFT2d.cc"

#include "Ravl/FFT2d.hh"
#include "Ravl/SArray2dIter.hh"
#include "Ravl/SArray2dIter2.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/StrStream.hh"

using namespace RavlN;

int testFFT2d();
int testFFT2dPwr2();

int testRealFFT2d();
int testRealFFT2dPwr2();

int testFFTShift();
int testRealFFTShift();

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
  if((ln = testFFTShift()) != 0) {
    cerr << "Error line " << ln << "\n";
    return 1;
  }
  if((ln = testRealFFTShift()) != 0) {
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



int testFFTShift() {
  cerr << "testFFTShift(), Started \n";

  // Check even size using: evenSize = fftshift(fftshift(evenSize))
  SArray2dC<ComplexC> evenSize(2,4);
  int i=0;
  for( SArray2dIterC<ComplexC> it(evenSize); it; it++ )
    *it = ComplexC(i++, i++);

  SArray2dC<ComplexC>  sEvenSize = FFT2dC::FFTShift( evenSize);
  SArray2dC<ComplexC> ssEvenSize = FFT2dC::FFTShift(sEvenSize);

  for(SArray2dIter2C<ComplexC,ComplexC> rit(evenSize,ssEvenSize);rit;rit++) {
    if(Abs(rit.Data1().Re() - rit.Data2().Re()) > 0.000001)
      return __LINE__;
    if(Abs(rit.Data1().Im() - rit.Data2().Im()) > 0.000001)
      return __LINE__;
  }

  // Fixed test for odd size
  SArray2dC<ComplexC> oddSize(3,5);
  i=0;
  for( SArray2dIterC<ComplexC> it(oddSize); it; it++ )
    *it = ComplexC(i++, i++);

  SArray2dC<ComplexC> sOddSize = FFT2dC::FFTShift(oddSize);

  SArray2dC<ComplexC> correctSOddSize(3,5);
  StrIStreamC istr("3 5\n26 27 28 29 20 21 22 23 24 25\n6 7 8 9 0 1 2 3 4 5\n16 17 18 19 10 11 12 13 14 15");
  istr >> correctSOddSize;

  for(SArray2dIter2C<ComplexC,ComplexC> rit(sOddSize,correctSOddSize);rit;rit++) {
    if(Abs(rit.Data1().Re() - rit.Data2().Re()) > 0.000001)
      return __LINE__;
    if(Abs(rit.Data1().Im() - rit.Data2().Im()) > 0.000001)
      return __LINE__;
  }

  return 0;
}

int testRealFFTShift() {
  cerr << "testRealFFTShift(), Started \n";

  // Check even size using: evenSize = fftshift(fftshift(evenSize))
  SArray2dC<RealT> evenSize(128,200);
  int i=0;
  for( SArray2dIterC<RealT> it(evenSize); it; it++ )
    *it = i++;

  SArray2dC<RealT>  sEvenSize = FFT2dC::FFTShift( evenSize);
  SArray2dC<RealT> ssEvenSize = FFT2dC::FFTShift(sEvenSize);

  for(SArray2dIter2C<RealT,RealT> rit(evenSize,ssEvenSize);rit;rit++) {
    if(Abs(rit.Data1() - rit.Data2()) > 0.000001)
      return __LINE__;
  }

  // Fixed test for odd size
  SArray2dC<RealT> oddSize(3,5);
  i=0;
  for( SArray2dIterC<RealT> it(oddSize); it; it++ )
    *it = i++;

  SArray2dC<RealT> sOddSize = FFT2dC::FFTShift(oddSize);

  SArray2dC<RealT> correctSOddSize(3,5);
  StrIStreamC istr("3 5\n13 14 10 11 12\n3 4 0 1 2\n8 9 5 6 7");
  istr >> correctSOddSize;

  for(SArray2dIter2C<RealT,RealT> rit(sOddSize,correctSOddSize);rit;rit++) {
    if(Abs(rit.Data1() - rit.Data2()) > 0.000001)
      return __LINE__;
  }

  return 0;
}
