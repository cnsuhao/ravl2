// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FDSTREAMBUF_HEADER
#define RAVL_FDSTREAMBUF_HEADER 1
////////////////////////////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/config.h"

#if RAVL_COMPILER_GCC3

#include <fstream>
#include <streambuf>
#include <unistd.h>

namespace RavlN {
  using namespace std;
  
  template<typename CharT, typename TraitsT>
  class basic_fdbuf 
    : public basic_streambuf<CharT, TraitsT>
  {
  public:
    typedef CharT                     	        char_type;
    typedef TraitsT                    	        traits_type;
    typedef typename traits_type::int_type 	int_type;
    typedef typename traits_type::pos_type 	pos_type;
    typedef typename traits_type::off_type 	off_type;
    
    basic_fdbuf()
      : fd(-1)
    {}
    //: Constructor.
    
    basic_fdbuf(int fd,ios_base::openmode mode) 
      : fd(-1)
    {
      fdbuf_init(fd,mode);
    }
    //: Constructor.
    
    virtual ~basic_fdbuf() 
    { close(); }

    bool is_open() const { return fd >= 0; }
    //: Is file handle open ?
    
    basic_fdbuf<CharT,TraitsT> *open(int nfd, ios_base::openmode mode) {
      fdbuf_init(fd,mode);
      return this;
    }
    //: Open buffer.
    
    basic_fdbuf<CharT,TraitsT> *close() {
      ::close(fd);
      if(_M_buf) {
	setg(0, 0, 0);
	setp(0, 0);
	delete [] _M_buf;
	_M_buf = 0;
	_M_buf_size_opt = 0;
	_M_buf_size = 0; 
      }
      fd = -1;
      return this;
    }
    //: Close buffer.

  private:
    int fd;
    
  protected:
    void fdbuf_init(int fd,ios_base::openmode mode) {
      _M_buf_size = 1024;
      _M_buf_size_opt = 1024;
      _M_mode = mode;
      _M_buf = new char_type[_M_buf_size];
    }
    //: Setup buffer.
    
    virtual int sync() {
      cerr << "basic_fdbuf::sync() Called. \n";
      return 0;
    }
    //: Flush buffer to output.
    
    virtual int_type underflow() {
      cerr << "basic_fdbuf::underflow() Called. Ptrs:" << (void *) eback() << " " << (void *) gptr() << " " << (void *) egptr() << "\n";
      return traits_type::eof();
    }
    //: Underflow the buffer on read.
    
    virtual int_type uflow() {
      cerr << "basic_fdbuf::uflow() Called. Ptrs:" << (void *) eback() << " " << (void *) gptr() << " " << (void *) egptr() << " \n";
      CharT cd;
      if(read(fd,&cd,sizeof(cd)) == 0)
	return traits_type::eof();
      return traits_type::to_int_type(cd);
    }
    //: Underflow the buffer on read.
    
    virtual int_type pbackfail(int_type c = traits_type::eof()) {
      cerr << "basic_fdbuf::pbackfail() Called. \n";
      return c;
    }
    //: Putback failed.
    
    virtual int_type overflow(int_type c = traits_type::eof()) {
      cerr << "basic_fdbuf::overflow() Called. Ptrs:" << (void *) pbase() << " " << (void *) pptr() << " " << (void *) epptr() << "\n";
      return c;
    }
    //: Overflow buffer on write.
    
    virtual basic_streambuf<char_type, traits_type> *setbuf(char_type* s, streamsize n) {
      cerr << "basic_fdbuf::setbuf() Called. \n";
      return this;
    }
    //: Set the buffer to use.
    
    virtual pos_type seekoff(off_type off,ios_base::seekdir way,ios_base::openmode mode = ios_base::in | ios_base::out) {
      cerr << "basic_fdbuf::seekoff() Called. \n";
      return 0;
    }
    //: Seek relative.
    
    virtual pos_type seekpos(pos_type sp,ios_base::openmode mode = ios_base::in | ios_base::out) {
      cerr << "basic_fdbuf::seekpos() Called. \n";
      return 0;
    }
    //: Seek absolute position.
    
  };
  
}

#endif
#endif
