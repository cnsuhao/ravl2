// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/FuncStream.hh"

namespace RavlN {
  
  void FuncOStreamC::Flush() {
    //std::cerr << "Overflow called. \n";
    RavlAssert(pptr() >= pbase());
    SizeT len = pptr() - pbase();
    if(len > 0) {
      const char *buff = pbase();
      m_write.Call(buff,len);
      // Reset buffer.
      setp(m_buffer,&m_buffer[m_bufferSize]);
    }
  }
  

  FuncOStreamC::int_type FuncOStreamC::overflow(FuncOStreamC::int_type c) {
    if(c != EOF) {
      *pptr() = c;
      pbump(1);
    }
    Flush();
    return 0;
  }
  
  //: Sync stream.
  
  int FuncOStreamC::sync() {
    Flush();
    return 0;
  }


  // ---------------------------------------------
  
  //: Constructor.
  FuncIStreamC::FuncIStreamC(const CallFunc2C<char *,SizeT,SizeT> &readCall) 
    : m_read(readCall)
    { setg(m_buffer+4,m_buffer+4,m_buffer+4); }
    
  //: Underflow.
  FuncIStreamC::int_type FuncIStreamC::underflow() {
    if(gptr() < egptr())
      return traits_type::to_int_type(*gptr());
    int nPutback;
    nPutback = gptr() - eback();
    if(nPutback > 4)
      nPutback = 4;
    std::memmove(m_buffer+(4-nPutback),gptr() - nPutback,nPutback);
    char *buf = m_buffer+4;
    SizeT num = m_bufferSize-4;
    num = m_read.Call(buf,num);
    if(num == 0)
      return EOF;
    setg(m_buffer+(4-nPutback),m_buffer+4,m_buffer+4+num);
    return traits_type::to_int_type(*gptr());
  }
}
