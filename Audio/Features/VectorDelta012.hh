// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLAUDIO_VECTORDELTA012_HEADER
#define RAVLAUDIO_VECTORDELTA012_HEADER 1
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlAudioFeatures
//! docentry="Ravl.Audio.Feature Extraction"

#include "Ravl/FixedQueue.hh"
#include "Ravl/Types.hh"
#include "Ravl/Vector.hh"

namespace RavlAudioN {
  using namespace RavlN;
  
  //! userlevel=Normal
  //: Compute delta vectors.
  // This computes the first and second order derivatives and adds them to the
  // output feature vector. <br>
  // Note: This adds a 2 frame delay to the data.
  
  class VectorDelta012C {
  public:
    VectorDelta012C(UIntT fawFeatures,const VectorC &mean = VectorC());
    //: Constructor
    
    VectorC Apply(const VectorC &rawFeatures);
    //: Compute feature vector.
    
  protected:
    FixedQueueC<VectorC> samples;
    FixedQueueC<VectorC> delta1;
    UIntT features;
  };
}


#endif
