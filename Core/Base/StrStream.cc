// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore

#ifndef VISUAL_CPP
#ifndef __sgi__
#include <strstream>
#else
#include <strstream.h>
#endif
#else
#include <strstrea.h>
#endif

#include "Ravl/StrStream.hh"

namespace RavlN {
  ///////////////////
  //: Default constructor.
  
  OStrStreamC::OStrStreamC()
    : OStreamC(*(oss = new ostrstream()),true)
{}
  
  ///////////////////
  //: Get text written to stream so far.
  // NB. This does NOT clean the buffer.
  
  StringC OStrStreamC::String() {
    return StringC(oss->str(),oss->pcount(),oss->pcount()+1);
}
  
  ////////////////////////////////////////////////////
  
  //: Default constructor.
  
  IStrStreamC::IStrStreamC(StringC dat)
#ifdef VISUAL_CPP
    : IStreamC(*(iss = new istrstream(const_cast<char *>(dat.chars()),dat.length())),true),
#else
      : IStreamC(*(iss = new istrstream(dat.chars(),dat.length())),true),
#endif
      buff(dat)
  {}
}

