// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLFFT2D_HEADER
#define RAVLFFT2D_HEADER 1
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Math.Signals.2D"
//! lib=RavlMath

#include "Ravl/RefCounter.hh"
#include "Ravl/Complex.hh"
#include "Ravl/SArray2d.hh"

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
    bool inv; // Is the transform backward ??
    
    int primeFactors[32];
    int nf; // Number of factors. Sufficent for all 32-bit lengths.
  };
  
  //! userlevel=Normal
  //: 2d FFT.
  // The size of the dimentions of the array must be a power of 2 in the
  // current implementation.
  
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
    
    Index2dC Size() const
    { return Body().Size(); }
    //: The size of the transform.
    
  };

}

#endif
