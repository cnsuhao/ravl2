// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLAUDIO_FEATUREEXTACTOR_HEADER
#define RAVLAUDIO_FEATUREEXTACTOR_HEADER 1
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! docentry="Ravl.Audio.Feature Extraction"
//! lib=RavlAudioFeatures
//! examples=exFeatureMFCC.cc

#include "Ravl/Audio/WindowSignal.hh"
#include "Ravl/Audio/MelSpectrum.hh"
#include "Ravl/Audio/MelCepstrum.hh"
#include "Ravl/DP/StreamOp.hh"
#include "Ravl/Vector.hh"

namespace RavlAudioN {
  using namespace RavlN;
  
  //! userlevel=Develop
  //: Mel-Frequency Cepstral Coefficients feature extractor.
  
  class FeatureMFCCBodyC
    : public DPIStreamOpBodyC<Int16T,VectorC>
  {
  public:
    FeatureMFCCBodyC();
    //: Constructor.
    
    FeatureMFCCBodyC(RealT sampleRate,    // Sample rate in Hz.
		     RealT frameRate,     // Frames a second.
		     IntT frameSize,      // Size of a frame.
		     RealRangeC freqRange,// Range of frequencies.
		     IntT numMelFilters,  // Number of mel spectrum filters.
		     IntT numCep);        // Number of ceptstrum co-efficents to compute.
    //: Constructor.
    
    VectorC Get();
    //: Get next sample
    
    bool Get(VectorC &buff);
    //: Get next sample
    
  protected:
    WindowSignalC<Int16T,RealT,RealT> window;
    MelSpectrumC melSpectrum;
    MelCepstrumC melCepstrum;
  };
  
  //! userlevel=Normal
  //: Mel-Frequency Cepstral Coefficients feature extractor.
  // Based on  Sphinx III front end signal processor.
  
  class FeatureMFCCC
    : public DPIStreamOpC<Int16T,VectorC>
  {
  public:
    FeatureMFCCC()
      : DPEntityC(true)
    {}
    //: Default constructor
    // creates an invalid handle.
    
    FeatureMFCCC(RealT sampleRate , // Sample rate in Hz.
		 RealT frameRate = 100,    // Frames a second.
		 IntT frameSize = 512,     // Size of a frame.
		 RealRangeC freqRange = RealRangeC(133.333334,6855.4976),// Range of frequencies.
		 IntT numMelFilters = 40,  // Number of mel spectrum filters.
		 IntT numCep = 13)         // Number of ceptstrum co-efficents to compute.
      : DPEntityC(*new FeatureMFCCBodyC(sampleRate,frameRate,frameSize,freqRange,numMelFilters,numCep) )
    {}
    //: Constructor.
    
  };
  
}


#endif
