// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/StdMath.hh"
#include "Ravl/RealCepstral.hh"
#include "Ravl/SArr1Iter2.hh"
#include "Ravl/SArr1Iter.hh"

namespace RavlN {

  //: Constructor.
  
  RealCepstralC::RealCepstralC(SizeT size) 
    : fft(size),
      ifft(size,true)
  {}
  
  //: Compute the real cepstral of data.
  
  SArray1dC<RealT> RealCepstralC::Apply(const SArray1dC<RealT> &data) {
    SArray1dC<ComplexC> res = fft.Apply(data); // Compute FFT
    // Log of magintude.
    for(SArray1dIterC<ComplexC> it(res);it;it++) {
      it.Data().Re() = Log(it.Data().Mag() + 0.00000000001);
      it.Data().Im() = 0;
    }
    res = ifft.Apply(res); // Inverse FFT
    SArray1dC<RealT> ret(res.Size()/2);
    // Get magnitude of results.
    for(SArray1dIter2C<RealT,ComplexC> it(ret,res);it;it++) {
      it.Data1() = it.Data2().Re();
      //cerr << "Im:" << it.Data2().Re() << " " << place->Re() << "\n";
    }
    return ret;
  }
}
