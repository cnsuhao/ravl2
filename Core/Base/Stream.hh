// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_STREAM_HEADER
#define RAVL_STREAM_HEADER 1
/////////////////////////////////////////////////////////////
//! file="Ravl/Core/Base/Stream.hh"
//! lib=RavlCore
//! date="23/04/98"
//! author="Charles Galambos"
//! docentry="Ravl.Core.IO.Streams"
//! rcsid="$Id$"
//! userlevel=Default

#include "Ravl/String.hh"
#include "Ravl/Assert.hh"
#include "Ravl/HandleRefCounter.hh"
#include "Ravl/Exception.hh"
#if RAVL_HAVE_ANSICPPHEADERS
#include <iostream>
#else
#include <iostream.h>
#endif
#include <stdarg.h>

#if !RAVL_HAVE_STREAMSIZE
typedef unsigned int streamsize;
#endif

namespace RavlN {
  
  //! userlevel=Develop
  //: Reference counter IO stream base class.
  
  class StreamBaseC 
    : public HandleRefCounterC
  {
  public:
#if RAVL_HAVE_IOS_SEEKDIR
    // GCC...
    typedef ::ios::seekdir SeekDirT;
#else
    // IRIX...
    typedef ios::seek_dir SeekDirT;
#endif
    
    StreamBaseC()
      : s(0)
      {}
    //: Default constructor.
    
    StreamBaseC(const StreamBaseC &oth) 
      : HandleRefCounterC(oth),
        s(oth.s)
      {}
    //: Copy Constructor.
    
    virtual ~StreamBaseC() 
      {}
    //: Ensure correct destructor is used.
    
    inline const StringC &Name() const
      { return name; }
    //: Returns the name of the stream.
    
    inline bool IsOpen() const { 
      if(s == 0)
	return false;
      return (s->good() != 0);
    }
    //: Test if this stream is open.
    
    bool good() const { 
      if(s == 0)
	return false;
      return (s->good() != 0);
    }
    //: Is stream good ?
    
    bool bad() const {
      if(s == 0)
	return true;
      return (s->bad() != 0);
    }
    //: Is stream corrupted ?
    
    inline bool eof() const { return (s->eof() != 0); }
    //: End of file ?
    
    inline bool fail() const { return (s->fail() != 0); }
    //: Operation failed ?
    
    bool operator!() const { 
      if(s == 0)
	return true;
      return (s->fail()!=0); 
    }
    //: Not failed ?
    
    operator void*() const  { 
      if(s == 0)
	return 0;
      return s->fail() ? (void*)0 : (void*)(-1); 
    }
    //: Ok ?
    
    bool DiagnoseStream(ostream &out);
    //: Print diagnostic message about the streams state to out.
    
    bool Close();
    //: Close this stream.
    // After this is called no further IO should be attempted!
    
  protected:
    StreamBaseC(ostream *ns,StringC afilename,bool nDelOnClose = true);
    //: Body Constructor.
    
    StreamBaseC(istream *ns,StringC afilename,bool nDelOnClose = true);
    //: Body Constructor.
    
    bool Init(istream *ns,StringC afilename,bool nDelOnClose = true);
    //: Setup 
    // This should only be called on Stream's constructed with the
    // default constructor!
    
    bool Init(ostream *ns,StringC afilename,bool nDelOnClose = true);
    //: Setup 
    // This should only be called on Stream's constructed with the
    // default constructor!
    
    ios &buf() { 
      RavlAssert(s != 0);
      return *s; 
    }
    //: Access handle.
    
    const ios &buf() const  { 
      RavlAssert(s != 0);
      return *s; 
    }
    //: Access handle.
    
  protected:
    StringC name; // Name of stream.
    ios *s;
  };
  
  //! userlevel=Normal
  //: Standard output streams with reference counting.
  
  class OStreamC 
    : public StreamBaseC
  {
  public:
    OStreamC()
      {}
    //:Default constructor.
    
    OStreamC(const StringC &filename,bool binary = true,bool buffered=true,bool append = false);
    //: Open a file for output.
    // '-' is treated as cout.
    
    OStreamC(int fd,bool buffered = true);
    //: Send data to unix filehandle.
    
    inline OStreamC(ostream &strm,bool deletable = false)
      : StreamBaseC(&strm,"",deletable),
        out(&strm)
      {}
    //: Constructor.
    
    inline OStreamC(const OStreamC &oth)
      : StreamBaseC(oth),
      out(oth.out)
      {}
    //: Copy constructor.
    
    ostream& form(const char *format ...);
    //: Print to stream using good old 'C' sytle formating.
    // This isn't the saftest function, it uses a fixed
    // buffer of 4096 bytes.  <p>
    // This is a duplication of the function  GNU iostreams
    // for those platforms that don't have this function.
    
    operator ostream &() { return *out; }
    //: Converter.
    
    operator const ostream &() const { return *out; }
    //: Converter.  
    
    ostream &os() { return *out; }
    //: Access ostream.
    
    const ostream &os() const { return *out; }
    //: Access ostream.
    
    ostream &write(const char *d,StreamSizeT n) 
      { return os().write(d,n); }
    //: Write data.
    // ostream compatable.
    
    ostream &put(char ch) { return os().put(ch); }
    //: Put charactor.
    // ostream compatable.
    
    ostream &operator<<(const char *txt)
      { return os() << txt; }
    //: Output text.
    
    template<class DataT>
      ostream &operator<<(const DataT &dat)
      { return os() << dat; }
    
    streampos Tell() const { return out->tellp(); }
    //: Where are we in the stream.
    
    void Seek(streampos to) { os().seekp(to); }
    //: Goto a position in the stream.
    
    streampos tellp() const { return out->tellp(); }
    //: Where are we in the stream.
    // ostream compatable.
    
    ostream &seekg(streampos to) { return os().seekp(to); }
    //: Goto a position in the stream.
    // ostream compatable.
    
    ostream &seekg(streampos to,SeekDirT dir) { return os().seekp(to,dir); }
    //: Goto a position in the stream.
    // ostream compatable.

  protected:
    ostream *out;
  };
  
  
  //! userlevel=Normal
  //: Standard input streams with reference counting.
  
  class IStreamC 
    : public StreamBaseC
  {
  public:
    IStreamC()
      {}
    //:Default constructor.
    
    IStreamC(const StringC &filename,bool binary = true,bool buffered=true);
    //: Open a file.
    // '-' is treated as cin.
    
    IStreamC(int fd,bool buffered = true);
    //: Get data from unix filehandle.
    
    inline IStreamC(istream &strm,bool deletable = false)
      : StreamBaseC(&strm,StringC(""),deletable),
        in(&strm)
      {}
    //: Constructor.
    
    inline IStreamC(const IStreamC &oth)
      : StreamBaseC(oth),
        in(oth.in)
      {}
    //: Copy constructor.
    
    void Unget(StringC text);
    //: Put string pack. (Puts a '\n')
    
    void Unget(const char *dat,int len);
    //: Put string pack.
    
    IntT CopyTo(OStreamC &out,IntT maxChars = -1);
    //: Copy stream to output.
    
    operator istream &() { return dynamic_cast<istream &>(buf()); }
    //: Converter.
    
    operator const istream &() const { return *in; }
    //: Converter.
    
    istream &is() { 
      RavlAssert(s != 0);
      return *in; 
    }
    //: Access input stream.
    
    const istream &is() const { 
      RavlAssert(s != 0);
      return *in; 
    }
    //: Access input stream.
    
    istream &read(char *d,streamsize n) { return is().read(d,n); }
    //: read data.
    // istream compatable function.
    
    istream &get(char &ch) { return is().get(ch); }
    //: Get charactor.
    // istream compatable function.
    
    char get() { return is().get(); }
    //: Get charactor.
    // istream compatable function.
    
    istream &get(char *buff,int buffsize) { return is().get(buff,buffsize); }
    //: Read in a line.
    // istream compatable function.
    
    istream &getline(char *buff,int buffsize) { return is().getline(buff,buffsize); }
    //: Read in a line.
    // istream compatable function.
    
    streamsize gcount() { return is().gcount(); }
    //: Get number of charactor read in last operation.
    // istream compatable function.
    
    template<class DataT>
      istream &operator>>(DataT &dat)
      { return is() >> dat; }
    
    istream &operator>>(char *dat)
      { return is() >> dat; }
    
    streampos Tell() const { return in->tellg(); }
    //: Where are we in the stream.
    
    void Seek(streampos to) { is().seekg(to); }
    //: Goto a position in the stream.
    
    streampos tellg() const { return in->tellg(); }
    //: Where are we in the stream.
    // istream compatable function.
    
    istream &seekg(streampos to) { return is().seekg(to); }
    //: Goto a position in the stream.
    // istream compatable function.
    
    istream &seekg(streampos to,SeekDirT dir) { return is().seekg(to,dir); }
    //: Goto a position in the stream.
    // istream compatable.
    
    inline bool IsEndOfStream() {
      // Check there's more to read...
      if(!in->good())
	return true;
      char cbuff;
      read(&cbuff,1);
      if(!in->good())
	return true;
      Unget(&cbuff,1);
      return false;
    }
    //: Test if its the end of the stream is comming up...
    // Maybe there's a better way ?
    
    //:-------------------------------------------------
    //: Parsing Functions.
    // Some methods to help parse text streams.

    char GetChar();
    //: Get next charactor.
    // This will throw an ExceptionEndOfStreamC if the end
    // of the input stream is found.
    
    char SkipWhiteSpace();
    //: Skip white space charactors.
    // returns the first non-white space charactor found. <p>
    // This will throw an ExceptionEndOfStreamC if the end
    // of the input stream is found.
    
    bool SkipTo(const StringC &endStr);
    //: Skip through stream until endStr is found.
    // this leaves the stream positioned at the
    // first charactor after the string. <p>
    // returns false if the end of the stream is found first.
    
    bool SkipTo(char let);
    //: Skip through stream until 'let' is found.
    // returns false if the end of the stream is found first.
    
    StringC ClipTo(char let);
    //: Return all charactors before let.
    // the 'let' charactor is discarded. <p>
    // If the end of stream is found, all data found
    // upto that point is returned.
    
    StringC ClipTo(const StringC &endStr);
    //: Return all charactors before 'endStr'.
    // this leaves the stream positioned at the
    // first charactor after the string. <p>
    // If the end of stream is found, all data found
    // upto that point is returned.
    
  protected:
    istream *in;
  };
}

#endif
