// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FUNCSTREAM_HEADER
#define RAVL_FUNCSTREAM_HEADER 1
//! file="Ravl/Core/Base/FuncStream.hh"
//! lib=RavlCore
//! date="29/05/2008"
//! author="Charles Galambos"
//! docentry="Ravl.API.Core.IO.Streams"
//! userlevel=Normal

#include "Ravl/Stream.hh"
#include "Ravl/Calls.hh"

namespace RavlN {
  
  //: Write stream to a method.
  
  class FuncOStreamC 
    : public std::streambuf
  {
  public:
    typedef traits_type::int_type 		int_type;
    const static SizeT m_bufferSize = 8192; 
    
    //: Destructor.
    ~FuncOStreamC()  { 
      // Flush buffer.
      sync(); 
    }

    FuncOStreamC(const CallFunc2C<const char *,SizeT> &writeCall) 
      : m_write(writeCall)
    { setp(m_buffer,&m_buffer[m_bufferSize-1]); }
    
    //: Buffer overflow
    virtual int_type overflow(int_type c);
    
    //: Sync stream.
    virtual int sync();
  protected:    
    void Flush();
    
    char m_buffer[m_bufferSize];    
    CallFunc2C<const char *,SizeT> m_write; // Method to call to write data.
  };
  
  
  //: Read stream from a method.
  
  class FuncIStreamC 
    : public std::streambuf
  {
  public:
    typedef traits_type::int_type int_type;
    const static SizeT m_bufferSize = 8192;
    
    //: Constructor.
    FuncIStreamC(const CallFunc2C<char *,SizeT,SizeT> &readCall);
    
    //: Underflow.
    virtual int_type underflow();
    
  protected:
    char m_buffer[m_bufferSize];
    CallFunc2C<char *,SizeT,SizeT> m_read;
  };
  
  
}

#endif
