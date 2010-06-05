// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLSIGNAL_REALCEPSTRAL
#define RAVLSIGNAL_REALCEPSTRAL 1
/////////////////////////////////////////////
//! rcsid="$Id: RealCepstral.hh 5240 2005-12-06 17:16:50Z plugger $"
//! userlevel=Normal
//! docentry="Ravl.API.Math.Signals.1D"
//! lib=RavlMath
//! file="Ravl/Math/Signals/1D/RealCepstral.hh"

#include "Ravl/Math.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Types.hh"
#include "Ravl/FFT1d.hh"

namespace RavlN {
  
  //: Compute the real cepstral 
  
  class RealCepstralC {
  public:
    RealCepstralC(SizeT size);
    //: Constructor.

    Array1dC<RealT> Apply(const Array1dC<RealT> &data);
    //: Compute the real cepstral of data.

  protected:
    FFT1dC fft;
    FFT1dC ifft;
  };


}  


#endif
