// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FDSTREAM_HEADER
#define RAVL_FDSTREAM_HEADER 1
/////////////////////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Base/fdstream.hh"

#include "Ravl/config.h"


#if RAVL_COMPILER_GCC3

#define RAVL_USE_FDSTREAMBUF 1

#include "Ravl/Stream.hh"

#if RAVL_USE_FDSTREAMBUF
#include "Ravl/fdstreambuf.hh"
#else
#include <ext/stdio_filebuf.h>
#endif

namespace RavlN {
  using namespace __gnu_cxx;
  
  //! userlevel=Normal
  //: Basic input from a fd stream.
  
  template<typename CharT, typename TraitsT = char_traits<CharT> >
  class basic_ifdstream 
    : public basic_istream<CharT, TraitsT>
  {
  public:
    typedef CharT 			    char_type;
    typedef TraitsT 			    traits_type;
    typedef typename traits_type::int_type  int_type;
    typedef typename traits_type::pos_type  pos_type;
    typedef typename traits_type::off_type  off_type;

#if RAVL_USE_FDSTREAMBUF
    typedef basic_fdbuf <char_type, traits_type>  buf_type;
#else
    typedef stdio_filebuf<char_type, traits_type> buf_type;
#endif
    
    explicit basic_ifdstream(int fd, ios_base::openmode mode = ios_base::in)
      : basic_istream<char_type, traits_type>(0),
#if RAVL_USE_FDSTREAMBUF
	filebuf(fd,mode)
#else
	filebuf(fd,mode,false,100)
#endif
    {
      init(&filebuf);
    }
    //: Construct from a file handle and an open mode.
    
    buf_type* rdbuf() const
    { return const_cast<buf_type *>(&filebuf); }
    //: Access fdbuffer.
    
#if RAVL_USE_FDSTREAMBUF
    basic_ifdstream()
      : basic_istream<char_type, traits_type>(0), 
	filebuf()
    { init(&filebuf); }
    //: Default constructor.
    
    bool is_open() { return filebuf.is_open(); }
    //: Check if its open.
    
    void open(int fd, ios_base::openmode mode = ios_base::in) {
      if (!filebuf.open(fd,mode | ios_base::in))
	setstate(ios_base::failbit);
    }
    //: open a file handle.
    
    void close() {
      if (!filebuf.close())
	setstate(ios_base::failbit);
    }
    //: Close a file.
#endif
    
  private:
    buf_type filebuf;
  };
  
  //! userlevel=Normal
  //: Derivation of general output streams, specific to unix file handles.
  
  template<typename CharT, typename TraitsT = char_traits<CharT> >
  class basic_ofdstream 
    : public basic_ostream<CharT,TraitsT>
  {
  public:
    typedef CharT 			    char_type;
    typedef TraitsT 			    traits_type;
    typedef typename traits_type::int_type  int_type;
    typedef typename traits_type::pos_type  pos_type;
    typedef typename traits_type::off_type  off_type;

#if RAVL_USE_FDSTREAMBUF
    typedef basic_fdbuf <char_type, traits_type>  buf_type;
#else
    typedef stdio_filebuf<char_type, traits_type> buf_type;
#endif
    
    explicit basic_ofdstream(int fd,ios_base::openmode mode = ios_base::out|ios_base::trunc)
      : basic_ostream<char_type, traits_type>(0),
#if RAVL_USE_FDSTREAMBUF
	filebuf(fd,mode)
#else
	filebuf(fd,mode,false,100)
#endif
    {
      init(&filebuf);
    }
    //: Construct from a file handle.
    
#if RAVL_USE_FDSTREAMBUF
    basic_ofdstream()
      : basic_ostream<char_type, traits_type>(0), 
	filebuf()
    { init(&filebuf); }
    //: Default constructor.
    
    buf_type* rdbuf() const
    { return const_cast<buf_type *>(&filebuf); }
    //: Access fd buffer.
    
    bool is_open() 
    { return filebuf.is_open(); }
    //: Is stream open ?

    void open(int fd,ios_base::openmode mode = ios_base::out | ios_base::trunc) {
      if (!filebuf.open(fd, mode | ios_base::out))
	setstate(ios_base::failbit);
    }
    //: Open a stream with file handle 'fd'.
    
    void close() {
      if (!filebuf.close())
	setstate(ios_base::failbit);
    }
    //: Close a file handle.
#endif
    
  private:
    buf_type filebuf;
  };
  
  
  //! userlevel=Normal
  //: Basic fdstream.
  
  template<typename CharT, typename TraitsT>
  class basic_fdstream 
    : public basic_iostream<CharT, TraitsT>
  {
  public:
    typedef CharT 		           char_type;
    typedef TraitsT 		           traits_type;
    typedef typename traits_type::int_type int_type;
    typedef typename traits_type::pos_type pos_type;
    typedef typename traits_type::off_type off_type;
    
#if RAVL_USE_FDSTREAMBUF
    typedef basic_fdbuf <char_type, traits_type>  buf_type;
#else
    typedef stdio_filebuf<char_type, traits_type> buf_type;
#endif
    
    explicit basic_fdstream(int fd,ios_base::openmode mode = ios_base::in | ios_base::out)
      : basic_iostream<char_type, traits_type>(NULL), 
#if RAVL_USE_FDSTREAMBUF
	filebuf(fd,mode)
#else
	filebuf(fd,mode,false,100)
#endif
    {
      init(&filebuf);
    }
    //: Cosntructor.
    
#if RAVL_USE_FDSTREAMBUF
    basic_fdstream()
      : basic_iostream<CharT, TraitsT>(0),
	filebuf()
    { init(&filebuf); }
    //: Default constructor.
    
    buf_type* rdbuf() const
    { return const_cast<buf_type *>(&filebuf); }
    
    bool is_open() { return fdbuf.is_open(); }
    //: Is stream open ?
    
    void open(int fd,ios_base::openmode mode = ios_base::in | ios_base::out) {
      if (!filebuf.open(fd, mode))
	setstate(ios_base::failbit);
    }
    //: Open a stream with the given file handle.
    
    void close() {
      if(!filebuf.close())
	setstate(ios_base::failbit);
    }
    //: Close file handle.
#endif

  private:
    buf_type  filebuf;
  };
  
  typedef basic_ifdstream<char> ifdstream;
  typedef basic_ofdstream<char> ofdstream;

}

#endif
#endif
