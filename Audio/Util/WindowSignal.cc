// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAudioUtil
//! author="Charles Galambos"
//! docentry="Ravl.Audio.Processing"
//! file="Ravl/Audio/Util/WindowSignal.cc"

#include "Ravl/Audio/WindowSignal.hh"
#include "Ravl/Math.hh"
#include "Ravl/StdConst.hh"

namespace RavlAudioN {
  
  //: Constructor.
  
  WindowSignalBaseC::WindowSignalBaseC(RAWindowSignalT nwinType,UIntT nsize)
    : winType(nwinType),
      winSize(nsize)
  {}
  
  //: Generate the filter.
  
  bool WindowSignalBaseC::Generate(SArray1dC<RealT> &filter) {
    switch(winType){
    case RAWNone:
      filter = SArray1dC<RealT>(winSize);
      filter.Fill(1);
      break;
    case RAWRamp:    return GenerateRamp(filter);
    case RAWHanning: return GenerateHanning(filter);
    case RAWHamming: return GenerateHamming(filter);
    case RAWBlackman: return GenerateBlackman(filter);
    default:
      RavlAssertMsg(0,"WindowSignalBaseC::Generate(), Unknown filter type.");
      break;
    }
    return true;
  }
  
  //: Generate a saw tooth ramp
  
  bool WindowSignalBaseC::GenerateRamp(SArray1dC<RealT> &filter) {
    filter = SArray1dC<RealT>(winSize);
    IntT halfSize = (winSize/2);
    RealT frac = ((winSize)/2);
    for(IntT i = 0;i < halfSize;i++) {
      RealT val = ((RealT)i+1) / frac;
      filter[i] =val ;
      filter[(winSize-1) -i] =val ;
    }
    return true;
  }
  
  bool WindowSignalBaseC::GenerateHanning(SArray1dC<RealT> &filter) {
    filter = SArray1dC<RealT>(winSize);    
    for(UIntT i = 0;i < winSize;i++)
      filter[i] = (1 - Cos(RavlConstN::pi * 2 * ((RealT) i / (winSize-1)))) / 2;
    return true;
  }
  
  bool WindowSignalBaseC::GenerateHamming(SArray1dC<RealT> &filter) {
    filter = SArray1dC<RealT>(winSize);    
    for(UIntT i = 0;i < winSize;i++)
      filter[i] = 0.54 - 0.46 * Cos(RavlConstN::pi * 2 * ((RealT) i / (winSize-1)));
    return true;
  }
  
  bool WindowSignalBaseC::GenerateBlackman(SArray1dC<RealT> &filter) {
    filter = SArray1dC<RealT>(winSize);    
    for(UIntT i = 0;i < winSize;i++) {
      RealT a = (RealT) i / (winSize-1);
      filter[i] = 0.42 - 0.5 * Cos(RavlConstN::pi * 2 * a) + 0.08 * Cos(RavlConstN::pi * 4 * a);
    }
    return true;
  }
  
}
