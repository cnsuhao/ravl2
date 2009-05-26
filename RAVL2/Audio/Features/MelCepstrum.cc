// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAudioFeatures
//! file="Ravl/Audio/Features/MelCepstrum.cc"

#include "Ravl/Audio/MelCepstrum.hh"
#include "Ravl/StdConst.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SArray1dIter.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlAudioN {
  
  //: Default constructor.
  // This does not create any filters. Init(...) must be called
  // before any processing is done with Apply().
  
  MelCepstrumC::MelCepstrumC() 
  {}
  
  //: Constructor.
  // numCepstrum - Number of cepstrum co-efficients to generate.
  // specSize - Number of spectrum co-effience at input.
  
  MelCepstrumC::MelCepstrumC(IntT numCepstrum,IntT specSize) {
    Init(numCepstrum,specSize);
  }
  
  //: Initialise tables.
  // numCepstrum - Number of cepstrum co-efficients to generate.
  // specSize - Number of spectrum co-effience at input.
  
  void MelCepstrumC::Init(IntT numCepstrum,IntT specSize) {
    ONDEBUG(cerr << "MelCepstrumC::Init(), numCepstrum=" << numCepstrum << " Spec size=" << specSize << "\n");
    filters = SArray1dC<SArray1dC<RealT> >(numCepstrum);
    RealT period = ( 2 * (RealT) specSize);
    for(SArray1dIterC<SArray1dC<RealT> > it(filters);it;it++) {
      RealT freq = (2 * RavlConstN::pi * ((RealT) it.Index())) / period;
      SArray1dC<RealT> coeff(specSize);
      RealT i = 0.5;
      ONDEBUG(cerr << it.Index() << " Freq=" << freq << "\n");
      for(SArray1dIterC<RealT> fit(coeff);fit;fit++,i++) {
	*fit = Cos(freq * i);
	ONDEBUG(cerr << " " << *fit );
      }
      *it = coeff;
      ONDEBUG(cerr << "\n");
    }
  }
  
  //: Compute mel cepstrum from mel spectrum parmiters.
  
  SArray1dC<RealT> MelCepstrumC::Apply(const SArray1dC<RealT> &melSpectrum) {
    SArray1dC<RealT> ret(filters.Size());
    SArray1dC<RealT> logSpec(melSpectrum);
    for(SArray1dIter2C<RealT,RealT> sit(logSpec,melSpectrum);sit;sit++) {
      if(sit.Data2() > 0)
	sit.Data1() = Log(sit.Data2());
      else
	sit.Data1() = -1.0e+6;
    }
    
    for(SArray1dIter2C<RealT,SArray1dC<RealT> > it(ret,filters);it;it++) {
      RealT sum = 0;
      SArray1dIter2C<RealT,RealT> fit(logSpec,it.Data2());
#if 0
      sum += fit.Data1() * fit.Data2() * 0.5;
      fit++;
#endif
      for(;fit;fit++)
	sum += fit.Data1() * fit.Data2();
      it.Data1() = sum;
    }
    return ret;
  }
  
}



