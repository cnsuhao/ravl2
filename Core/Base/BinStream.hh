// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BINSTREAM_HEADER
#define RAVL_BINSTREAM_HEADER 1
///////////////////////////////////////////////////////
//! file="Ravl/Core/Base/BinStream.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Charles Galambos"
//! date="09/02/1999"
//! docentry="Ravl.Core.IO.Streams"
//! rcsid="$Id$"

#include "Ravl/config.h"
#include "Ravl/Stream.hh"
#include "Ravl/Index.hh"
#include "Ravl/TFVector.hh"

namespace RavlN  {
#if RAVL_LITTLEENDIAN
#if RAVL_HAVE_BYTESWAP
#include <byteswap.h>
#else
  // If we don't have byte swap define these.
  
  inline short bswap_16(const short &buf) {
    short ret;
    ((char *) &ret)[0] = ((const char *) &buf)[1];
    ((char *) &ret)[1] = ((const char *) &buf)[0];
    return ret;
  }
  //! userlevel=Advanced
  //: Swap bytes of a 16 bit number.
  
  inline int bswap_32(const int &buf) {
    int ret;
    ((char *) &ret)[0] = ((const char *) &buf)[3];
    ((char *) &ret)[1] = ((const char *) &buf)[2];
    ((char *) &ret)[2] = ((const char *) &buf)[1];
    ((char *) &ret)[3] = ((const char *) &buf)[0];
    return ret;
  }
  //! userlevel=Advanced
  //: Swap bytes of a 32 bit number.
  
  
#endif
#endif
  //:-
  
  // Type     Bytes.
  // Int16T    2 
  // UInt16T   2 
  // IntT      4
  // UIntT     4
  
  //! userlevel=Normal
  //: Machine independant binary input stream.
  
  class BinIStreamC {
  public:
    BinIStreamC(const IStreamC &nIn)
      : in(nIn)
      {}
    //: Constructor.
  // From a IStreamC.
    
    BinIStreamC(int fd)
      : in(fd)
      {}
    //: Constructor.
    // From a file descriptor.
    
    BinIStreamC(const StringC &nIn,bool buffered = true)
      : in(nIn,true,buffered) // Open binary stream.
      {}
    //: Constructor.
    
    BinIStreamC()
      {}
    //: Default construtor.
    
    inline BinIStreamC &IBuff(char *buff,IntT len); 
    //: Character buffer. NB. Length is NOT saved.
    
    inline BinIStreamC &operator>>(char &dat);
    //: Read in a character.
    
    inline BinIStreamC &operator>>(signed char &dat);
    //: Read in a signed character.
    
    inline BinIStreamC &operator>>(unsigned char &dat);  
    //: Read in an unsigned character.
    
    inline BinIStreamC &operator>>(Int16T &dat);
    //: Read in a 16 bit integer.
    
    inline BinIStreamC &operator>>(UInt16T &dat);
    //: Read in an unsigned 16 bit integer.
    
    inline BinIStreamC &operator>>(IntT &dat);
    //: Read in an signed 32 bit integer.
    
    inline BinIStreamC &operator>>(UIntT &dat);  
    //: Read in an unsigned 32 bit integer.
    
    inline BinIStreamC &operator>>(FloatT &dat);  
    //: Read in a floating point number.
    
    inline BinIStreamC &operator>>(RealT &dat);  
    //: Read in a double precision floating point number.
    
    inline BinIStreamC &operator>>(bool &dat);
    //: Read in a boolean value.
    
    streampos Tell() const { return in.Tell(); }
    //: Where are we in the stream.
    
    void Seek(streampos to) { in.Seek(to); }
    //: Goto a position in the stream.
    
    inline const StringC &Name() const
      { return in.Name(); }
    //: Returns the name of the stream.
    
    IStreamC &Stream() { return in; }
    //: Access underlying stream.
    
    const IStreamC &Stream() const { return in; }
    //: Access underlying stream.
    
    inline bool IsEndOfStream() 
      { return in.IsEndOfStream(); }
    //: Test if at end of the stream.
  
  protected:
    void Dummy(void);
    //: Dummy func.
    
    IStreamC in;
    IntT idAlloc;
  //HashC<IntT,void *> ptrMap;
  };

  //! userlevel=Normal
  //: Machine independant binary output stream.
  
  class BinOStreamC {
  public:
    BinOStreamC(const OStreamC &nOut)
      : out(nOut)
    {}
    //: Constructor.
    
    BinOStreamC(int fd)
      : out(fd)
    {}
    //: Constructor.
    // From a file descriptor.
    
    BinOStreamC(const StringC &nOut,bool buffered = true)
      : out(nOut,true,buffered) // Open binary stream.
    {}
    //: Constructor.
    
    BinOStreamC()
    {}
    //: Default construtor.
    // Creates an invalid stream.
    
    inline BinOStreamC &OBuff(const char *buff,IntT len); 
    //: Character buffer. NB. Length is NOT saved.
    
    inline BinOStreamC &operator<<(char dat);
    //: Write a character.
    
    inline BinOStreamC &operator<<(signed char dat);
    //: Write a signed character.
    
    inline BinOStreamC &operator<<(unsigned char dat);  
    //: Write an unsigned character.
    
    inline BinOStreamC &operator<<(Int16T dat);
    //: Write a 16 bit integer.
    
    inline BinOStreamC &operator<<(UInt16T dat);
    //: Write an unsigned 16 bit integer.
    
    inline BinOStreamC &operator<<(IntT dat);    
    //: Write a 32 bit integer.
    
    inline BinOStreamC &operator<<(UIntT dat);  
    //: Write a 32 bit unsigned integer.
    
    inline BinOStreamC &operator<<(FloatT dat);  
    //: Write a floating point number.
    
    inline BinOStreamC &operator<<(RealT dat);  
    //: Write a double precision floating point number.
    
    inline BinOStreamC &operator<<(bool dat);
    //: Write a boolean value.
    
    BinOStreamC &operator<<(const char *text);
    //: Write a 'C' style string.
    
    streampos Tell() const { return out.Tell(); }
    //: Where are we in the stream.
    
    void Seek(streampos to) { out.Seek(to); }
    //: Goto a position in the stream.
    
    inline const StringC &Name() const
    { return out.Name(); }
    //: Returns the name of the stream.
    
    OStreamC &Stream() { return out; }
    //: Access underlying stream.
    
    const OStreamC &Stream() const { return out; }
    //: Access underlying stream.
    
  protected:
    void Dummy(void);
    //: Dummy func.
    
    OStreamC out;
    //IntT idAlloc;
    //HashC<void *,IntT> ptrMap;
  };

  
  /////////////////////////////////////////////////////
  
  inline 
  BinIStreamC & BinIStreamC::IBuff(char *buff,IntT len) {
    in.read(buff,len);
    return *this;
  }

  BinIStreamC &BinIStreamC::operator>>(char &dat)
  { in.read(&dat,sizeof(char));  return *this; }
  
  BinIStreamC &BinIStreamC::operator>>(signed char &dat)
  { in.read((char *) &dat,sizeof(signed char));  return *this; }

  BinIStreamC &BinIStreamC::operator>>(unsigned char &dat)
  { in.read((char *)&dat,sizeof(unsigned char));  return *this; }
  
  BinIStreamC &BinIStreamC::operator>>(Int16T &dat) {
#if RAVL_BIGENDIAN
    in.read((char *)&dat,2); 
#else
    short buf;
    in.read((char *)&buf,2);  
    dat = bswap_16(buf);
#endif
    return *this; 
  }
  
  BinIStreamC &BinIStreamC::operator>>(UInt16T &dat) {
#if RAVL_BIGENDIAN
    in.read((char *)&dat,2); 
#else
    short buf;
    in.read((char *) &buf,2);  
    dat = (UInt16T) bswap_16(buf);
#endif
    return *this; 
  }
  
  BinIStreamC &BinIStreamC::operator>>(IntT &dat) {
#if RAVL_BIGENDIAN
    in.read((char *)&dat,4);
#else
    int buf;
    in.read((char *) &buf,4);
    dat = (IntT) bswap_32(buf);
#endif
    return *this; 
  }
  
  BinIStreamC &BinIStreamC::operator>>(UIntT &dat) {
#if RAVL_BIGENDIAN
    in.read((char *)&dat,4);
#else
    int buf;
    in.read((char *) &buf,4);
    dat = (UIntT) bswap_32(buf);
#endif
    return *this; 
  }
  
  inline 
  BinIStreamC &BinIStreamC::operator>>(FloatT &dat) {
    RavlAssert(sizeof(FloatT) == sizeof(IntT));
    (*this) >> (*((IntT *) &dat));
    return *this;
  }
  
  inline 
  BinIStreamC &BinIStreamC::operator>>(RealT &dat) {
    RavlAssert(sizeof(RealT) == (sizeof(IntT) * 2));
    IntT *at = (IntT *) (&dat);
#if RAVL_BIGENDIANDOUBLES
    (*this) >> at[0] >> at[1];
#else
    (*this) >> at[1] >> at[0];
#endif
    return *this;
  }
  
  inline 
  BinIStreamC &BinIStreamC::operator>>(bool &dat) {
    char flag;
    (*this) >> flag;
    dat = flag?true:false;
    return (*this);
  }
  
  /////////////////////////////////////////////////////
  
  inline 
  BinOStreamC &BinOStreamC::OBuff(const char *buff,IntT len) {
    out.write(buff,len);
    return *this;
  }
  
  BinOStreamC &BinOStreamC::operator<<(char dat)
  { out.write(&dat,1);  return *this; }

  BinOStreamC &BinOStreamC::operator<<(signed char dat)
  { out.write((char *) &dat,1);  return *this; }

  BinOStreamC &BinOStreamC::operator<<(unsigned char dat)
  { out.write((char *)&dat,1);  return *this; }

  BinOStreamC &BinOStreamC::operator<<(Int16T dat) {
#if RAVL_BIGENDIAN
    out.write((char *)&dat,2);  
#else
    short buf = bswap_16(dat);
    out.write((char *) &buf,2);  
#endif
    return *this; 
  }
  
  BinOStreamC &BinOStreamC::operator<<(UInt16T dat) {
#if RAVL_BIGENDIAN
    out.write((char *)&dat,2);  
#else
    short buf = bswap_16(dat);
    out.write((char *) &buf,2);  
#endif
    return *this; 
  }
  
  BinOStreamC &BinOStreamC::operator<<(IntT dat) {
#if RAVL_BIGENDIAN
    out.write((char *)&dat,4);
#else
    int buf = bswap_32(dat);
    out.write((char *) &buf,4);  
#endif
    return *this; 
  }
  
  BinOStreamC &BinOStreamC::operator<<(UIntT dat) {
#if RAVL_BIGENDIAN
    out.write((char *)&dat,4);
#else
    int buf = bswap_32(dat);
    out.write((char *) &buf,4);
#endif
    return *this; 
  }
  
  inline 
  BinOStreamC &BinOStreamC::operator<<(FloatT dat) {
    RavlAssert(sizeof(FloatT) == sizeof(IntT));
    (*this) << (*((IntT *) &dat));
    return *this;
  }
  
  inline 
  BinOStreamC &BinOStreamC::operator<<(RealT dat) {
    RavlAssert(sizeof(RealT) == (sizeof(IntT) * 2));
    IntT *at = (IntT *) (&dat);
#if RAVL_BIGENDIANDOUBLES
    (*this) << at[0] << at[1];
#else
    (*this) << at[1] << at[0];
#endif
    return *this;
  }
  
  inline 
  BinOStreamC &BinOStreamC::operator<<(bool dat) {
    char out;
    out = dat?1:0;
    (*this) << out;
    return (*this);
  }

  ///// A few extra's to make life easier. /////////////////////////////////////////
  
  inline
  BinIStreamC &operator>>(BinIStreamC &s,IndexC &ind)  {
    s >> ind.V();
    return s;
  }
  
  inline
  BinOStreamC &operator<<(BinOStreamC &s,const IndexC &ind)  {
    s << ind.V();
    return s;
  }

  template<class DataT,unsigned int N>
  inline
  BinOStreamC &operator<<(BinOStreamC &out,const TFVectorC<DataT,N> &dat) {
    for(UIntT i = 0;i < N;i++)
      out << dat[i];
    return out;
  }
  
  template<class DataT,unsigned int N>
  inline
  BinIStreamC &operator>>(BinIStreamC &in,TFVectorC<DataT,N> &dat) {
    for(UIntT i = 0;i < N;i++)
      in >> dat[i];
    return in;
  }

}

#endif
