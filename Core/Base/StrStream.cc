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

#include "Ravl/StrStream.hh"
#include "Ravl/Calls.hh"

#if RAVL_HAVE_ANSICPPHEADERS
#if USE_GCC30
#include <sstream>
#else
#include <strstream>
#endif
#else
#ifndef VISUAL_CPP
#include <strstream.h>
#else
#include <strstrea.h>
#endif
#endif

namespace RavlN {
  
  ///////////////////
  //: Default constructor.

  StrOStreamC::StrOStreamC()
    :
#if !USE_GCC3
    OStreamC(*(oss = new ostrstream()),true)
#else
    OStreamC(*(oss = new ostringstream()),true)
#endif
  {}

  //: Get the number of bytes written so far.
  
  UIntT StrOStreamC::Size() const {
#if !USE_GCC3
    return oss->pcount();
#else
    return oss->str().size();
#endif
  }
  
  ///////////////////
  //: Get text written to stream so far.
  // NB. This does NOT clean the buffer.
  
  StringC StrOStreamC::String() {
    UIntT count = Size();
#if USE_GCC3
    const char *data = oss->str().data();
#else
    const char *data = &(oss->str()[0]); 
#endif
    // This is a bit ugly, we have to copy the 
    // string into another buffer.
    StringC ret(data,count,count); // It would be nice to avoid this copy!!
    //delete [] data; // Free buffer.
    return ret;
  }
  
  ////////////////////////////////////////////////////
  
  //: Default constructor.
  
  StrIStreamC::StrIStreamC(const StringC &dat)
    :
#if !USE_GCC3
#ifdef VISUAL_CPP
    IStreamC(*(iss = new istrstream(const_cast<char *>(dat.chars()),dat.length())),true),
#else
    IStreamC(*(iss = new istrstream(dat.chars(),dat.length())),true),
#endif
#else
    IStreamC(*(iss = new istringstream(string(dat.chars(),dat.length()))),true),
#endif
    buff(dat)
  {}
}

