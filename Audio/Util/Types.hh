// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLAUDIO_TYPES_HEADER
#define RAVLAUDIO_TYPES_HEADER 1
//! rcsid="$Id$"
//! lib=RavlAudioUtil

#include "Ravl/Types.hh"

namespace RavlAudioN {
  using namespace RavlN;
  
  //! userlevel=Normal
  //: Sample across input channels.
  
  template<unsigned int N,typename SampleT>
  struct SampleElemC {
    SampleT channel[N];
  };
  
}


#endif
