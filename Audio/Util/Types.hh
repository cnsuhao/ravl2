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
//! author="Charles Galambos"
//! docentry="Ravl.Audio.IO"

#include "Ravl/Types.hh"

namespace RavlAudioN {
  using namespace RavlN;
  
  //! userlevel=Normal
  //: Sample across input channels.
  
  template<unsigned int N,typename SampleT>
  struct SampleElemC {
    SampleT channel[N];
  };

  template<unsigned int N,typename SampleT>
  inline
  ostream &operator<<(ostream &strm,const SampleElemC<N,SampleT> &sample) {
    for(unsigned int i = 0;i < N;i++)
      strm << sample.channel[i] << ' ';
    return strm;
  }
  
  template<unsigned int N,typename SampleT>
  inline
  istream &operator>>(istream &strm,SampleElemC<N,SampleT> &sample) {
    for(unsigned int i = 0;i < N;i++)
      strm >> sample.channel[i];
    return strm;
  }

  template<unsigned int N,typename SampleT>
  inline
  BinOStreamC &operator<<(BinOStreamC &strm,const SampleElemC<N,SampleT> &sample) {
    for(unsigned int i = 0;i < N;i++)
      strm << sample.channel[i];
    return strm;
  }
  
  template<unsigned int N,typename SampleT>
  inline
  BinIStreamC &operator>>(BinIStreamC &strm,SampleElemC<N,SampleT> &sample) {
    for(unsigned int i = 0;i < N;i++)
      strm >> sample.channel[i];
    return strm;
  }
  
  
}


#endif
