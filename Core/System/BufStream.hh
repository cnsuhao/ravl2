// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BUFSTREAM_HEADER
#define RAVL_BUFSTREAM_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/System/BufStream.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="25/02/99"
//! docentry="Ravl.Core.IO.Streams"

#include "Ravl/Stream.hh"
#include "Ravl/SArray1d.hh"

class ostrstream;
class istrstream;

namespace RavlN {
  
  ////////////////////////////
  //! userlevel=Normal
  //: Output stream to memory.
  // Wraps the standard library ostrstream class.
  
  class BufOStreamC 
    : public OStreamC
  {
  public:
    BufOStreamC();
    //: Default constructor.
    
    SArray1dC<char> &Data();
    //: Get data written to stream. 
    // Note, this will reset the buffer.
    
  protected:
    SArray1dC<char> data;
    ostrstream *oss; // Output string stream.
  };
  
  ////////////////////////////
  //! userlevel=Normal
  //: Input stream from memory.
  // Wraps the standard library istrstream class.
  
  class BufIStreamC 
    : public IStreamC
  {
  public:
    BufIStreamC()
      : iss(0)
      {}
    //: Default constructor
    
    BufIStreamC(const SArray1dC<char> &dat);
    //: Constructor.
    
    inline SArray1dC<char> &Data() { return data; }
    //: Get string used as buffer.
    
  protected:
    SArray1dC<char> data;
    istrstream *iss; // Output string stream.
  };
  

}

#endif
