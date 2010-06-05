// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLAUDIO_MELSPECTRUM_HEADER
#define RAVLAUDIO_MELSPECTRUM_HEADER 1
//! rcsid="$Id: MelSpectrum.hh 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlAudioFeatures
//! docentry="Ravl.API.Audio.Feature Extraction"
//! author="Charles Galambos"
//! file="Ravl/Audio/Features/MelSpectrum.hh"

#include "Ravl/RefCounter.hh"
#include "Ravl/RealRange1d.hh"
#include "Ravl/Math.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/SArray1d.hh"

namespace RavlAudioN {
  using namespace RavlN;
  
  //! userlevel=Normal
  //: Compute the mel spectrum from a power spectrum.
  
  class MelSpectrumC
  {
  public:
    MelSpectrumC();
    //: Default constructor.
    // This does not construct any filters. InitFilters must be called
    // before Apply.
    
    MelSpectrumC(RealT sampleRate,IntT frameSize,RealRangeC freqRange,IntT numFilters = 40);
    //: Constructor
    // Frequency's is in Hz.
    
    SArray1dC<RealT> Apply(const SArray1dC<RealT> &powerSpectrum);
    //: Compute mel spectrum from power spectrum
    
    bool InitFilters(RealT sampleRate,IntT frameSize,RealRangeC freqRange,IntT numFilters);
    //: Initiaise filters.
    // Frequency's is in Hz.
    
    RealT Lin2Mel(RealT f)
    { return 2595.0 * Log10(1 + (f / 700.0)); } 
    //: Map linear frequencys to mel frequencies.

    RealT Mel2Lin(RealT f)
    { return 700.0 * (Pow(10.0,f / 2595.0) - 1.0); } 
    //: Map mel frequencys to linear frequencies.
    
  protected:
    SArray1dC<Array1dC<RealT> > filters; // Filter bank.    
  };
  
}

#endif
