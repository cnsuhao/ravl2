// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLFFT1D_HEADER
#define RAVLFFT1D_HEADER 1
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Math.Signals.1D"
//! example=exFFT1d.cc
//! lib=RavlMath

#include "Ravl/RefCounter.hh"
#include "Ravl/Complex.hh"
#include "Ravl/SArray1d.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Interface class for 1d FFTW
  
  class FFT1dBodyC
    : public RCBodyC
  {
  public:
    FFT1dBodyC(int n,bool iinv);
    //: Constructor.
    
    ~FFT1dBodyC();
    //: Destructor
    
    bool Init(int n,bool iinv);
    //: Create a plan with the given setup.
    
    SArray1dC<ComplexC> Apply(const SArray1dC<ComplexC> &dat);
    //: Apply transform to array.
    // Note, only the first 'n' byte of dat are proccessed.
    // if the array is shorter than the given length, an
    // exception 'ErrorOutOfRangeC' will be thrown.
    
    SArray1dC<ComplexC> Apply(const SArray1dC<RealT> &dat);
    //: Apply transform to real array 
    // Note, only the first 'n' byte of dat are proccessed.
    // if the array is shorter than the given length, an
    // exception 'ErrorOutOfRangeC' will be thrown.
    
    IntT N() const
      { return n; }
    //: The size of the transform.
    
  protected:
    IntT n;  // Size of the transform.
    bool inv; // Is the transform backward ??
    
    int primeFactors[32];
    int nf; // Number of factors. Sufficent for all 32-bit lengths.
  };
  
  //! userlevel=Normal
  //: Handle to 1d FFT.
  
  class FFT1dC
    : public RCHandleC<FFT1dBodyC>
  {
  public:
    FFT1dC()
      {}
    //: Default constructor.
    
    FFT1dC(int n,bool iinv = false)
      : RCHandleC<FFT1dBodyC>(*new FFT1dBodyC(n,iinv))
      {}
    //: Create a fft class.
    // If iinv is true do an inverse transform
    
    bool Init(int n,bool iinv = false)
    { return Body().Init(n,iinv); }
    //: Create a plan with the given setup.
    
    SArray1dC<ComplexC> Apply(const SArray1dC<ComplexC> &dat)
      { return Body().Apply(dat); }
    //: Apply transform to array.
    // Note, only the first 'n' byte of dat are proccessed.
    // if the array is shorter than the given length, an
    // exception 'ErrorOutOfRangeC' will be thrown.
    
    SArray1dC<ComplexC> Apply(const SArray1dC<RealT> &dat)
      { return Body().Apply(dat); }
    //: Apply transform to real array 
    // Note, only the first 'n' byte of dat are proccessed.
    // if the array is shorter than the given length, an
    // exception 'ErrorOutOfRangeC' will be thrown.
    
    IntT N() const
      { return Body().N(); }
    //: The size of the transform.
    
  };

}

#endif
