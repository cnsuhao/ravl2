// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLCORRELATION1D_HEADER
#define RAVLCORRELATION1D_HEADER 1
//////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! docentry="Ravl.Math.Signals.1D"
//! lib=RavlMath

#include "Ravl/StdMath.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/FFT1d.hh"

namespace RavlN {

  class Correlation1dC {
  public:
    Correlation1dC(IntT size);
    //: Constructor.
    // Give the size of arrays to correlate.
    
    SArray1dC<RealT> Apply(const SArray1dC<RealT> &d1,const SArray1dC<RealT> &d2);
    //: Return the correlation of signals d1 and d2.
    // This uses FFT to caculate the correlation between d1 and d2.
    // both d1 and d2 must have the same length. <p>
    
    SArray1dC<RealT> AutoCorrelation(const SArray1dC<RealT> &d1);
    //: Return the auto correlation  signals d1.
    // This uses FFT to caculate the correlation d1 and itself. <p>
    
  protected:
    FFT1dC fft;  
    FFT1dC ifft;
  };
  
}



#endif
