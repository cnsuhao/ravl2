// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Base/StrStream.cc"

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
#include "Ravl/Calls.hh"

namespace RavlN {
  
  ///////////////////
  //: Default constructor.

  StrOStreamC::StrOStreamC()
    : OStreamC(*(oss = new ostrstream()),true)
  {}
  
  ///////////////////
  //: Get text written to stream so far.
  // NB. This does NOT clean the buffer.
  
  StringC StrOStreamC::String() {
    char *data = oss->str(); 
    // This is a bit ugly, we have to copy the 
    // string into another buffer.
    StringC ret(data,oss->pcount(),oss->pcount()+1);
    delete data; // Free buffer.
    return ret;
  }
  
  ////////////////////////////////////////////////////
  
  //: Default constructor.
  
  StrIStreamC::StrIStreamC(const StringC &dat)
#ifdef VISUAL_CPP
    : IStreamC(*(iss = new istrstream(const_cast<char *>(dat.chars()),dat.length())),true),
#else
    : IStreamC(*(iss = new istrstream(dat.chars(),dat.length())),true),
#endif
      buff(dat)
  {}
}

