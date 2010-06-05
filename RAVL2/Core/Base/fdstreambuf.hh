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
//! rcsid="$Id: fdstreambuf.hh 4900 2005-04-25 09:34:36Z craftit $"
//! lib=RavlCore
//! file="Ravl/Core/Base/fdstreambuf.hh"

#include "Ravl/config.h"
#include "Ravl/Assert.hh"

#if RAVL_COMPILER_GCC3 && !RAVL_COMPILER_GCC3_4 && !RAVL_COMPILER_GCC4

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
    
    basic_fdbuf(int nfd,ios_base::openmode mode) 
      : fd(-1)
    {
      fdbuf_init(nfd,mode);
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
    void fdbuf_init(int nfd,ios_base::openmode mode) {
      fd = nfd;
      _M_buf_size = 1024;
      _M_buf_size_opt = 1024;
      _M_mode = mode;
      _M_buf = new char_type[_M_buf_size];
      
      if (_M_mode & ios_base::in) {
	setg(0,0,0);
      }
      if (_M_mode & ios_base::out) {
	setp(_M_buf,_M_buf+_M_buf_size);
      }
      // Don't support input and output from the same buffer...
      RavlAssert(!((_M_mode & ios_base::out) && (_M_mode & ios_base::in )));
    }
    //: Setup buffer.
    
    virtual int sync() {
      //cerr << "basic_fdbuf::sync() Called. Ptrs:" << (void *) pbase() << " " << (void *) pptr() << " " << (void *) epptr() << "\n";
      char *at = (char *) pbase();
      while(at < pptr()) {
	int blen = ((char *)pptr()) - at;
	int n = write(fd,at,blen);
	if(n == 0)
	  cerr << "Write of zero bytes. \n";
	if(n < 0) {
	  cerr << "Write failed. \n";
	  //setstate(ios_base::badbit);
	  return -1;
	}
	at += n;
      }
      setp(_M_buf,_M_buf+_M_buf_size);
      return 0;
    }
    //: Flush buffer to output.

    virtual int_type overflow(int_type c = traits_type::eof()) {
      //cerr << "basic_fdbuf::overflow() Called. Ptrs:" << (void *) pbase() << " " << (void *) pptr() << " " << (void *) epptr() << "\n";
      sync();
      if(c != traits_type::eof())
	(*(_M_out_cur++)) = c;
      return c;
    }
    //: Overflow buffer on write.
    
    virtual int_type underflow() {
      //cerr << "basic_fdbuf::underflow() Called. Ptrs:" << (void *) eback() << " " << (void *) gptr() << " " << (void *) egptr() << "\n";
      int rsize = _M_buf_size;
      RavlAssert(gptr() == egptr()); // We're assuming the buffer's empty...
      int n = read(fd,_M_buf,rsize  * sizeof(CharT));
      //cerr << "basic_fdbuf::underflow() Read " << n << " bytes of " << _M_buf_size << ". " << (int) (*_M_buf) << "\n";
      setg(_M_buf,_M_buf,_M_buf + (n/sizeof(CharT)));
      if(n <= 0)
	return traits_type::eof();
      return traits_type::to_int_type(_M_buf[0]);
    }
    //: Underflow the buffer on read.
    
    virtual int_type uflow() {
      //cerr << "basic_fdbuf::uflow(), Called. Ptrs:" << (void *) eback() << " " << (void *) gptr() << " " << (void *) egptr() << " \n";
      RavlAssert(gptr() == egptr()); // Assume the buffer's empty.
      underflow();
      if(gptr() < egptr())
	return traits_type::to_int_type(*(_M_in_cur++));
      cerr << "basic_fdbuf::uflow(), Got end of file... \n";
      return traits_type::eof();
    }
    //: Underflow the buffer on read.
    
    
    virtual int_type pbackfail(int_type c = traits_type::eof()) {
      cerr << "basic_fdbuf::pbackfail() Called. \n";
      RavlAssert(0);
      return c;
    }
    //: Putback failed.
    
    virtual basic_streambuf<char_type, traits_type> *setbuf(char_type* s, streamsize n) {
      cerr << "basic_fdbuf::setbuf() Called. \n";
      RavlAssert(0);
      return this;
    }
    //: Set the buffer to use.
    
    virtual pos_type seekoff(off_type off,ios_base::seekdir way,ios_base::openmode mode = ios_base::in | ios_base::out) {
      cerr << "basic_fdbuf::seekoff() Called. \n";
      RavlAssert(0);
      return 0;
    }
    //: Seek relative.
    
    virtual pos_type seekpos(pos_type sp,ios_base::openmode mode = ios_base::in | ios_base::out) {
      cerr << "basic_fdbuf::seekpos() Called. \n";
      RavlAssert(0);
      return 0;
    }
    //: Seek absolute position.
  };
  
}

#endif
#endif
