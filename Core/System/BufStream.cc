// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
//! rcsid="$Id: BufStream.cc 7546 2010-02-18 13:28:49Z craftit $"
//! lib=RavlCore
//! file="Ravl/Core/System/BufStream.cc"

#include "Ravl/BufStream.hh"
#include "Ravl/config.h"

#if RAVL_HAVE_ANSICPPHEADERS
#if RAVL_HAVE_STRINGSTREAM
#include <sstream>
#else
#include <strstream>
#endif
#else
#if !RAVL_COMPILER_VISUALCPP
#include <strstream.h>
#else
#include <strstrea.h>
#endif
#endif

namespace RavlN {

#if RAVL_HAVE_STRINGSTREAM

  class BufferStringBodyC 
    : public BufferBodyC<char>
  {
  public:
    BufferStringBodyC(string &nstr,UIntT size)
      : BufferBodyC<char>(size,(char *) nstr.data()),
	str(nstr)
    {}
    //: Constructor.
    
  protected:
    string str;
  };

  class BufferStringC 
    : public BufferC<char> 
  {
  public:
    BufferStringC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    BufferStringC(string &str,UIntT size)
      : BufferC<char>(*new BufferStringBodyC(str,size))
    {}
    //: Constructor.
  };
    
#endif
  ///////////////////
  //: Default constructor.
  
  BufOStreamC::BufOStreamC()
    : 
#if RAVL_HAVE_STRINGSTREAM
    OStreamC(*(oss = new ostringstream(ostringstream::binary)),true)
#else
    OStreamC(*(oss = new ostrstream(0,0,ios_base::app | ios_base::binary)),true)
#endif
  {}
  
  ///////////////////
  //: Get text written to stream so far.
  // NB. This does NOT clean the buffer.
  
  SArray1dC<char> &BufOStreamC::Data() {
#if RAVL_HAVE_STRINGSTREAM
    string astr = oss->str();
    SizeT size = astr.size();
    BufferStringC buf(astr,size);
    data = SArray1dC<char>(buf,size);
#else

    // Fix horrible bug in irix implementation. 
    // pcount gets incremtned when str() is called 
#if RAVL_COMPILER_MIPSPRO
    char * astr = oss->str() ;  
    int    size = oss->pcount() ;
    data = SArray1dC<char> ( astr, --size ) ;
#else
    data = SArray1dC<char>((char *) oss->str(),oss->pcount());
#endif // mips pro fix 
#endif
    return data;
  }
  
  ////////////////////////////////////////////////////
  
  //: Default constructor.
  
  BufIStreamC::BufIStreamC(const SArray1dC<char> &dat) 
    :
#if RAVL_COMPILER_VISUALCPP && !RAVL_HAVE_STRINGSTREAM
    IStreamC(*(iss = new istrstream(const_cast<char *>(dat.ReferenceElm()),dat.Size())),true),
#else
#if RAVL_HAVE_STRINGSTREAM
    IStreamC(*(iss = new istringstream(string(dat.ReferenceElm(),static_cast<size_t>(dat.Size())),istringstream::binary)),true),
#else
    IStreamC(*(iss = new istrstream(dat.ReferenceElm(),static_cast<size_t>(dat.Size()))),true),
#endif
#endif
      data(dat)
  {}
}
