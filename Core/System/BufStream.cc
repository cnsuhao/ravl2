// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/System/BufStream.cc"

#ifndef VISUAL_CPP
#ifndef __sgi__
#include <strstream>
#else
#include <strstream.h>
#endif
#else
#include <strstrea.h>
#endif

#include "Ravl/BufStream.hh"

namespace RavlN {
  ///////////////////
  //: Default constructor.
  
  BufOStreamC::BufOStreamC()
    : OStreamC(*(oss = new ostrstream()),true)
  {}
  
  ///////////////////
  //: Get text written to stream so far.
  // NB. This does NOT clean the buffer.
  
  SArray1dC<char> &BufOStreamC::Data() {
    data = SArray1dC<char>(oss->str(),oss->pcount());
    return data;
  }
  
  ////////////////////////////////////////////////////
  
  //: Default constructor.
  
  BufIStreamC::BufIStreamC(const SArray1dC<char> &dat)
#ifdef VISUAL_CPP
    : IStreamC(*(iss = new istrstream(const_cast<char *>(dat.ReferenceElm()),dat.Size())),true),
#else
      : IStreamC(*(iss = new istrstream(dat.ReferenceElm(),dat.Size())),true),
#endif
      data(dat)
  {}
}
