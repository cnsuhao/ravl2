// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLBUFSTREAM_HEADER
#define RAVLBUFSTREAM_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/System/BufStream.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="25/02/99"
//! docentry="Ravl.Core.IO"

#include "Ravl/Stream.hh"
#include "Ravl/SArray1d.hh"

class ostrstream;
class istrstream;

namespace RavlN {
  
  ////////////////////////////
  //! userlevel=Advanced
  //: Output stream to memory.
  // Wraps the standard library ostrstream class.
  
  class OBufStreamC 
    : public OStreamC
  {
  public:
    OBufStreamC();
    //: Default constructor.
    
    SArray1dC<char> &Data();
    //: Get data written to stream. 
    // Note, this will reset the buffer.
    
  protected:
    SArray1dC<char> data;
    ostrstream *oss; // Output string stream.
  };
  
  ////////////////////////////
  //! userlevel=Advanced
  //: Input stream from memory.
  // Wraps the standard library istrstream class.
  
  class IBufStreamC 
    : public IStreamC
  {
  public:
    IBufStreamC()
      : iss(0)
      {}
    //: Default constructor
    
    IBufStreamC(const SArray1dC<char> &dat);
    //: Constructor.
    
    inline SArray1dC<char> &Data() { return data; }
    //: Get string used as buffer.
    
  protected:
    SArray1dC<char> data;
    istrstream *iss; // Output string stream.
  };
  

}

#endif
