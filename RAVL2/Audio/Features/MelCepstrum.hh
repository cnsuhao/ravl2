// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLAUDIO_MELCEPSTRUM_HEADER
#define RAVLAUDIO_MELCEPSTRUM_HEADER 1
//! rcsid="$Id$"
//! lib=RavlAudioFeatures
//! docentry="Ravl.API.Audio.Feature Extraction"
//! author="Charles Galambos"
//! file="Ravl/Audio/Features/MelCepstrum.hh"

#include "Ravl/SArray1d.hh"

namespace RavlAudioN {
  using namespace RavlN;
  
  //! userlevel=Normal
  //: Compute mel cepstrum from the mel spectrum.
  
  class MelCepstrumC {
  public:
    MelCepstrumC();
    //: Default constructor.
    // This does not create any filters. Init(...) must be called
    // before any processing is done with Apply().
    
    MelCepstrumC(IntT numCepstrum,IntT specSize);
    //: Constructor.
    // numCepstrum - Number of cepstrum co-efficients to generate.
    // specSize - Number of spectrum co-effience at input.
    
    void Init(IntT numCepstrum,IntT specSize);
    //: Initialise tables.
    // numCepstrum - Number of cepstrum co-efficients to generate.
    // specSize - Number of spectrum co-effience at input.
    
    SArray1dC<RealT> Apply(const SArray1dC<RealT> &melSpectrum);
    //: Compute mel cepstrum from mel spectrum parmiters.
    
  protected:
    SArray1dC<SArray1dC<RealT> > filters;
  };
}

#endif
