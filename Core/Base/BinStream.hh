// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLBINSTREAM_HEADER
#define RAVLBINSTREAM_HEADER 1
///////////////////////////////////////////////////////
//! file="Ravl/Core/Base/BinStream.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Charles Galambos"
//! date="09/02/99"
//! docentry="Ravl.Core.IO"
//! rcsid="$Id$"

#include "Ravl/config.h"
#include "Ravl/Stream.hh"
#include "Ravl/Index.hh"

namespace RavlN  {
#if RAVL_LITTLEENDIAN
#if RAVL_HAVE_BYTESWAP
#include <byteswap.h>
#else
  // If we don't have byte swap define these.
  
  //: Swap bytes of a 16 bit number.
  
  inline short bswap_16(const short &buf) {
    short ret;
    ((char *) &ret)[0] = ((const char *) &buf)[1];
    ((char *) &ret)[1] = ((const char *) &buf)[0];
    return ret;
  }
  
  //: Swap bytes of a 32 bit number.
  
  inline int bswap_32(const int &buf) {
    int ret;
    ((char *) &ret)[0] = ((const char *) &buf)[3];
    ((char *) &ret)[1] = ((const char *) &buf)[2];
    ((char *) &ret)[2] = ((const char *) &buf)[1];
    ((char *) &ret)[3] = ((const char *) &buf)[0];
    return ret;
  }
  
#endif
#endif
  
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
    //: Charactor buffer. NB. Length is NOT saved.
    
    inline BinIStreamC &operator >> (char &dat);
    inline BinIStreamC &operator >> (signed char &dat);
    inline BinIStreamC &operator >> (unsigned char &dat);  
    inline BinIStreamC &operator >> (Int16T &dat);
    inline BinIStreamC &operator >> (UInt16T &dat);
    inline BinIStreamC &operator >> (IntT &dat);
    inline BinIStreamC &operator >> (UIntT &dat);  
    
    inline BinIStreamC &operator >> (FloatT &dat);  
    inline BinIStreamC &operator >> (RealT &dat);  
    
    inline BinIStreamC &operator >> (bool &dat);
  
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
  //HashARC<IntT,void *> ptrMap;
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
    
    inline BinOStreamC &OBuff(const char *buff,IntT len); 
    //: Charactor buffer. NB. Length is NOT saved.
    
    inline BinOStreamC &operator << (char dat);
    inline BinOStreamC &operator << (signed char dat);
    inline BinOStreamC &operator << (unsigned char dat);  
    inline BinOStreamC &operator << (Int16T dat);
    inline BinOStreamC &operator << (UInt16T dat);
    inline BinOStreamC &operator << (IntT dat);
    inline BinOStreamC &operator << (UIntT dat);  
    //: Unsigned int.
    
    inline BinOStreamC &operator << (FloatT dat);  
    inline BinOStreamC &operator << (RealT dat);  
    
    inline BinOStreamC &operator << (bool dat);
    
    BinOStreamC &operator << (const char *text);
    
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
    //HashARC<void *,IntT> ptrMap;
  };

  
  /////////////////////////////////////////////////////
  
  inline 
  BinIStreamC &
  BinIStreamC::IBuff(char *buff,IntT len) {
    in.read(buff,len);
    return *this;
  }

  BinIStreamC &
  BinIStreamC::operator >> (char &dat)
  { in.read(&dat,sizeof(char));  return *this; }
  
  BinIStreamC &
  BinIStreamC::operator >> (signed char &dat)
  { in.read((char *) &dat,sizeof(signed char));  return *this; }

  BinIStreamC &
  BinIStreamC::operator >> (unsigned char &dat)
  { in.read((char *)&dat,sizeof(unsigned char));  return *this; }
  
  BinIStreamC &
  BinIStreamC::operator >> (Int16T &dat) {
#if RAVL_BIGENDIAN
    in.read((char *)&dat,2); 
#else
    short buf;
    in.read((char *)&buf,2);  
    dat = bswap_16(buf);
#endif
    return *this; 
  }
  
  BinIStreamC &
  BinIStreamC::operator >> (UInt16T &dat) {
#if RAVL_BIGENDIAN
    in.read((char *)&dat,2); 
#else
    short buf;
    in.read((char *) &buf,2);  
    dat = (UInt16T) bswap_16(buf);
#endif
    return *this; 
  }
  
  BinIStreamC &
  BinIStreamC::operator >> (IntT &dat) {
#if RAVL_BIGENDIAN
    in.read((char *)&dat,4);
#else
    int buf;
    in.read((char *) &buf,4);
    dat = (IntT) bswap_32(buf);
#endif
    return *this; 
  }
  
  BinIStreamC &
  BinIStreamC::operator >> (UIntT &dat) {
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
  BinIStreamC &
  BinIStreamC::operator >> (FloatT &dat) {
    RavlAssert(sizeof(FloatT) == sizeof(IntT));
    (*this) >> (*((IntT *) &dat));
    return *this;
  }
  
  inline 
  BinIStreamC &
  BinIStreamC::operator >> (RealT &dat) {
    RavlAssert(sizeof(RealT) == (sizeof(IntT) * 2));
    IntT *at = (IntT *) (&dat);
#if RAVL_BIGENDIAN
    (*this) >> at[0] >> at[1];
#else
    (*this) >> at[1] >> at[0];
#endif
    return *this;
  }
  
  inline 
  BinIStreamC &
  BinIStreamC::operator >> (bool &dat) {
    char flag;
    (*this) >> flag;
    dat = flag?true:false;
    return (*this);
  }
  
  /////////////////////////////////////////////////////
  
  inline 
  BinOStreamC &
  BinOStreamC::OBuff(const char *buff,IntT len) {
    out.write(buff,len);
    return *this;
  }
  
  BinOStreamC &
  BinOStreamC::operator << (char dat)
  { out.write(&dat,1);  return *this; }

  BinOStreamC &
  BinOStreamC::operator << (signed char dat)
  { out.write((char *) &dat,1);  return *this; }

  BinOStreamC &
  BinOStreamC::operator << (unsigned char dat)
  { out.write((char *)&dat,1);  return *this; }

  BinOStreamC &
  BinOStreamC::operator << (Int16T dat) {
#if RAVL_BIGENDIAN
    out.write((char *)&dat,2);  
#else
    short buf = bswap_16(dat);
    out.write((char *) &buf,2);  
#endif
    return *this; 
  }
  
  BinOStreamC &
  BinOStreamC::operator << (UInt16T dat) {
#if RAVL_BIGENDIAN
    out.write((char *)&dat,2);  
#else
    short buf = bswap_16(dat);
    out.write((char *) &buf,2);  
#endif
    return *this; 
  }
  
  BinOStreamC &
  BinOStreamC::operator << (IntT dat) {
#if RAVL_BIGENDIAN
    out.write((char *)&dat,4);
#else
    int buf = bswap_32(dat);
    out.write((char *) &buf,4);  
#endif
    return *this; 
  }
  
  BinOStreamC &
  BinOStreamC::operator << (UIntT dat) {
#if RAVL_BIGENDIAN
    out.write((char *)&dat,4);
#else
    int buf = bswap_32(dat);
    out.write((char *) &buf,4);
#endif
    return *this; 
  }
  
  inline 
  BinOStreamC &
  BinOStreamC::operator << (FloatT dat) {
    RavlAssert(sizeof(FloatT) == sizeof(IntT));
    (*this) << (*((IntT *) &dat));
    return *this;
  }
  
  inline 
  BinOStreamC &
  BinOStreamC::operator << (RealT dat) {
    RavlAssert(sizeof(RealT) == (sizeof(IntT) * 2));
    IntT *at = (IntT *) (&dat);
#if RAVL_BIGENDIAN
    (*this) << at[0] << at[1];
#else
    (*this) << at[1] << at[0];
#endif
    return *this;
  }
  
  inline BinOStreamC &
  BinOStreamC::operator << (bool dat) {
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

}

#endif
