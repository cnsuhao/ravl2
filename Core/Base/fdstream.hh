#ifndef RAVL_FDSTREAM_HEADER
#define RAVL_FDSTREAM_HEADER 1
/////////////////////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"

#include "Ravl/config.h"

#if RAVL_COMPILER_GCC3

#include "Ravl/fdstreambuf.hh"
#include "Ravl/Stream.hh"

namespace RavlN {
  
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
    
    basic_ifdstream()
      : basic_istream<char_type, traits_type>(0), 
	filebuf()
    { init(&filebuf); }
    //: Default constructor.
    
    explicit basic_ifdstream(int fd, ios_base::openmode mode = ios_base::in)
      : basic_istream<char_type, traits_type>(0), 
	filebuf()
    {
      init(&filebuf);
      open(fd,mode);
    }
    //: Construct from a file handle and an open mode.

    basic_fdbuf<char_type, traits_type>* rdbuf() const
    { return const_cast<basic_fdbuf<char_type, traits_type> *>(&filebuf); }
    //: Access fdbuffer.
    
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

  private:
    basic_fdbuf<char_type, traits_type>	filebuf;
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
    
    basic_ofdstream()
      : basic_ostream<char_type, traits_type>(0), 
	fdbuf()
    { init(&fdbuf); }
    //: Default constructor.
    
    explicit basic_ofdstream(int fd,ios_base::openmode mode = ios_base::out|ios_base::trunc)
      : basic_ostream<char_type, traits_type>(0), 
	fdbuf()
    {
      init(&fdbuf);
      open(fd, mode);
    }
    //: Construct from a file handle.
    
    basic_fdbuf<char_type, traits_type> * rdbuf() const
    { return const_cast<basic_fdbuf<char_type, traits_type> *>(&fdbuf); }
    //: Access fd buffer.
    
    bool is_open() 
    { return fdbuf.is_open(); }
    //: Is stream open ?
    
    void open(int fd,ios_base::openmode mode = ios_base::out | ios_base::trunc) {
      if (!fdbuf.open(fd, mode | ios_base::out))
	setstate(ios_base::failbit);
    }
    //: Open a stream with file handle 'fd'.
    
    void close() {
      if (!fdbuf.close())
	setstate(ios_base::failbit);
    }
    //: Close a file handle.
    
  private:
    basic_fdbuf<char_type, traits_type> fdbuf;
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
    
    basic_fdstream()
      : basic_iostream<CharT, TraitsT>(0),
	fdbuf()
    { init(&fdbuf); }
    //: Default constructor.
    
    explicit basic_fdstream(int fd,ios_base::openmode mode = ios_base::in | ios_base::out)
      : basic_iostream<char_type, traits_type>(NULL), 
	fdbuf()
    {
      init(&fdbuf);
      open(fd,mode);
    }
    //: Cosntructor.
    
    basic_fdbuf<char_type, traits_type> * rdbuf() const
    { return const_cast<basic_fdbuf<char_type, traits_type>*>(&fdbuf); }

    bool is_open() { return fdbuf.is_open(); }
    //: Is stream open ?
    
    void open(int fd,ios_base::openmode mode = ios_base::in | ios_base::out) {
      if (!fdbuf.open(fd, mode))
	setstate(ios_base::failbit);
    }
    //: Open a stream with the given file handle.
    
    void close() {
      if(!fdbuf.close())
	setstate(ios_base::failbit);
    }
    //: Close file handle.

  private:
    basic_fdbuf<char_type, traits_type>	fdbuf;

  };
  
  typedef basic_ifdstream<char> ifdstream;
  typedef basic_ofdstream<char> ofdstream;

}

#endif
#endif
