// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPOWERSPECTRUM1D_HEADER
#define RAVLPOWERSPECTRUM1D_HEADER
//////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! docentry="Ravl.Math.Signals.1D"
//! example=exPowerSpectrum.cc
//! lib=RavlMath

#include "Ravl/StdMath.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/FFT1d.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Power Spectrum 
  
  class PowerSpectrum1dC {
  public:
    PowerSpectrum1dC(IntT size);
    //: Constructor.
    
    SArray1dC<RealT> Apply(const SArray1dC<RealT> &data);
    //: Compute the power spectrum of data.
    // Compute the power spectrum using Bartlett window (simple triangle).
    
    SArray1dC<RealT> Apply(const SArray1dC<RealT> &d1,const SArray1dC<RealT> &d2);
    //: Compute the power spectrum of data in two arrays.
    // Compute the power spectrum using Bartlett window (simple triangle).
    // The arrays are expected to be of equal size, so the first
    // array will be multiplied by an increasing ramp, the second
    // by a decreasing one.
    
  protected:
    FFT1dC fft;  
  };
  
  SArray1dC<RealT> PowerSpectrumSimple(const SArray1dC<RealT> &data,int smooth = 0);
  //: Compute the power spectrum of data with no windowing..
}



#endif
