// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FFT2D_HEADER
#define RAVL_FFT2D_HEADER 1
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Math.Signals.2D"
//! lib=RavlMath
//! file="Ravl/Math/Signals/2D/FFT2d.hh"

#include "Ravl/RefCounter.hh"
#include "Ravl/Complex.hh"
#include "Ravl/SArray2d.hh"
#include "Ravl/Array2d.hh"
#include "Ravl/FFT1d.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: 2d FFT
  
  class FFT2dBodyC
    : public RCBodyC
  {
  public:
    FFT2dBodyC(Index2dC size,bool iinv);
    //: Constructor.
    
    ~FFT2dBodyC();
    //: Destructor
    
    bool Init(Index2dC size,bool iinv);
    //: Create a plan with the given setup.
    
    SArray2dC<ComplexC> Apply(const SArray2dC<ComplexC> &dat);
    //: Apply transform to array.
    // Note, only the first 'n' byte of dat are proccessed.
    // if the array is shorter than the given length, an
    // exception 'ErrorOutOfRangeC' will be thrown.
    
    SArray2dC<ComplexC> Apply(const SArray2dC<RealT> &dat);
    //: Apply transform to real array 
    // Note, only the first 'n' byte of dat are proccessed.
    // if the array is shorter than the given length, an
    // exception 'ErrorOutOfRangeC' will be thrown.
    
    Index2dC Size() const
      { return size; }
    //: The size of the transform.
    
  protected:
    Index2dC size;  // Size of the transform.
    IntT n,m;
    bool inv;      // Is the transform backward ??
    bool base2;    // Are both dimentions a power of 2?    
    
    int primeFactors1[32];
    int nf1; // Number of factors. Sufficent for all 32-bit lengths.

    int primeFactors2[32];
    int nf2; // Number of factors. Sufficent for all 32-bit lengths.
    
    SArray2dC<ComplexC> tmp1;
    SArray2dC<ComplexC *> tmp1Ptr;
  };
  
  //! userlevel=Normal
  //: 2d FFT.
  
  class FFT2dC
    : public RCHandleC<FFT2dBodyC>
  {
  public:
    FFT2dC()
      {}
    //: Default constructor.
    
    FFT2dC(Index2dC size,bool iinv = false)
      : RCHandleC<FFT2dBodyC>(*new FFT2dBodyC(size,iinv))
      {}
    //: Create a fft class.
    // If iinv is true do an inverse transform

    FFT2dC(SizeT s1,SizeT s2,bool iinv = false)
      : RCHandleC<FFT2dBodyC>(*new FFT2dBodyC(Index2dC(s1,s2),iinv))
      {}
    //: Create a fft class.
    // If iinv is true do an inverse transform
    
    bool Init(Index2dC size,bool iinv = false)
    { return Body().Init(size,iinv); }
    //: Create a plan with the given setup.
    
    SArray2dC<ComplexC> Apply(const SArray2dC<ComplexC> &dat)
    { return Body().Apply(dat); }
    //: Apply transform to array.
    // Note, only the first 'n' byte of dat are proccessed.
    // if the array is shorter than the given length, an
    // exception 'ErrorOutOfRangeC' will be thrown.
    
    SArray2dC<ComplexC> Apply(const SArray2dC<RealT> &dat)
    { return Body().Apply(dat); }
    //: Apply transform to real array 
    // Note, only the first 'n' byte of dat are proccessed.
    // if the array is shorter than the given length, an
    // exception 'ErrorOutOfRangeC' will be thrown.
    
    Array2dC<ComplexC> Apply(const Array2dC<ComplexC> &dat)
    { return Array2dC<ComplexC>(Body().Apply(const_cast<Array2dC<ComplexC> &>(dat).SArray2d(true))); }
    //: Apply transform to array.
    // Note, only the first 'n' byte of dat are proccessed.
    // if the array is shorter than the given length, an
    // exception 'ErrorOutOfRangeC' will be thrown. <p>
    // Note: The output will always have an origin of 0,0.
    
    Array2dC<ComplexC> Apply(const Array2dC<RealT> &dat)
    { return Array2dC<ComplexC>(Body().Apply(const_cast<Array2dC<RealT> &>(dat).SArray2d(true))); }
    //: Apply transform to real array 
    // Note, only the first 'n' byte of dat are proccessed.
    // if the array is shorter than the given length, an
    // exception 'ErrorOutOfRangeC' will be thrown. <p>
    // Note: The output will always have an origin of 0,0.
    
    Index2dC Size() const
    { return Body().Size(); }
    //: The size of the transform.
    
  };

}

#endif
