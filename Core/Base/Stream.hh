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
//! date="23/04/1998"
//! author="Charles Galambos"
//! docentry="Ravl.Core.IO.Streams"
//! rcsid="$Id$"
//! userlevel=Normal

#include "Ravl/config.h"
#include "Ravl/String.hh"
#include "Ravl/Assert.hh"
#include "Ravl/HandleRefCounter.hh"
#include "Ravl/Exception.hh"
#include <stdarg.h>

#if RAVL_HAVE_ANSICPPHEADERS
#include <iostream>
#else
#include <iostream.h>
#endif

#if !RAVL_HAVE_STREAMSIZE
typedef unsigned int streamsize;
#endif

namespace RavlN {
#if (RAVL_COMPILER_VISUALCPP && !RAVL_HAVE_STDNAMESPACE)
  inline istream& operator>>(istream& is, bool & b) {
    int val;
    is >> val;
    b = (val != 0);
    return is; 
  }
  //: Fix for Visual C++'s lack of a bool stream operator.
  
  inline ostream& operator<<(ostream& os, bool b) { 
    os << ((int)b);
    return os;
  }
  //: Fix for Visual C++'s lack of a bool stream operator.
#endif
  
  typedef StringC (*URLMapperFuncT)(const StringC &fn);
  //: Pointer to URL mapping function.
  
  //! userlevel=Normal
  
  bool EnableURLMapper();
  //: Enable url mapping of filenames.
  // With the expection of 'file:' specifications this enabled the  changing of URL's 
  // to a RAVL special files. i.e. 'http:' becomes '@http:'  This allows us to 
  // implement handlers in seperate libraries which can link in as required.
  // If the 'file:' if found not to have a domain specifier then the 'file:' is stripped
  // off and the file is treated normally. <p>
  // Note: At the moment the URL handling mechanism may not handle relative filenames
  // correctly as it uses the program current working directory as a start point. If this
  // becomes a problem some optional data maybe added to StreamC which holds a current directory.
  
  bool DisableURLMapper();
  //: Dissable url mapping of filenames.
  
  bool IsURLMappingEnabled();
  //: Test if URL mapping enabled.
  // Returns true if it is.
  
  //:-
  
  //! userlevel=Develop
  //: Reference counter IO stream base class.
  
  class StreamBaseC 
    : public HandleRefCounterC
  {
  public:
#if RAVL_HAVE_STDNAMESPACE
    typedef std::ios::seekdir SeekDirT;
#else
#if RAVL_HAVE_IOS_SEEKDIR
    // GCC...
    typedef ::ios::seekdir SeekDirT;
#else
    // IRIX...
    typedef ios::seek_dir SeekDirT;
#endif
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
    
    RCHandleC<RCBodyVC> &PointerManager()
    { return ptrManager; }
    //: Access the pointer manager.
    
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
    RCHandleC<RCBodyVC> ptrManager;
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
    
#if RAVL_HAVE_INTFILEDESCRIPTORS 
	OStreamC(int fd,bool binary = true,bool buffered = true);
    //: Send data to unix filehandle.
#endif
    
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

    ostream &os() { 
      RAVL_PARANOID(RavlAssertMsg(out != 0,"Attempt to use invalid OStreamC. "));
      return *out; 
    }
    //: Access ostream.
    // Enables access to the underlying ostream functionality
    
    const ostream &os() const { 
      RAVL_PARANOID(RavlAssertMsg(out != 0,"Attempt to use invalid OStreamC. "));
      return *out; 
    }
    //: Access ostream.
    // Enables access to the underlying ostream functionality
    
    operator ostream &() 
    { return os(); }
    //: Converter.
    
    operator const ostream &() const 
    { return os(); }
    //: Converter.  
    
    ostream &write(const char *d,StreamSizeT n) 
    { return os().write(d,n); }
    //: Write data.
    // ostream compatable.
    
    ostream &put(char ch) 
    { return os().put(ch); }
    //: Put character.
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
    
    ostream &seekp(streampos to) { return os().seekp(to); }
    //: Goto a position in the stream.
    // ostream compatable.
    
    ostream &seekp(streampos to,SeekDirT dir) { return os().seekp(to,dir); }
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

#if RAVL_HAVE_INTFILEDESCRIPTORS
    IStreamC(int fd,bool binary = true,bool buffered = true);
    //: Get data from unix filehandle.
#endif

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
        
    istream &is() { 
      RAVL_PARANOID(RavlAssertMsg(in != 0,"Attempt to use invalid IStreamC. "));
      return *in; 
    }
    //: Access istream.
    // Enables access to the underlying istream functionality
    
    const istream &is() const { 
      RAVL_PARANOID(RavlAssertMsg(in != 0,"Attempt to use invalid IStreamC. "));
      return *in; 
    }
    //: Access istream.
    // Enables access to the underlying istream functionality

    operator istream &() 
    { return is(); }
    //: Converter.
    
    operator const istream &() const 
    { return is(); }
    //: Converter.
    
    istream &read(char *d,streamsize n) 
    { return is().read(d,n); }
    //: read data.
    // istream compatable function.
    
    istream &get(char &ch) 
    { return is().get(ch); }
    //: Get character.
    // istream compatable function.
    
    char get() 
    { return is().get(); }
    //: Get character.
    // istream compatable function.
    
    istream &get(char *buff,int buffsize) 
    { return is().get(buff,buffsize); }
    //: Read in a line.
    // istream compatable function.
    
    istream &getline(char *buff,int buffsize) 
    { return is().getline(buff,buffsize); }
    //: Read in a line.
    // istream compatable function.
    
    streamsize gcount() 
    { return is().gcount(); }
    //: Get number of character read in last operation.
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
    //: Get next character.
    // This will throw an ExceptionEndOfStreamC if the end
    // of the input stream is found.
    
    char SkipWhiteSpace();
    //: Skip white space characters.
    // returns the first non-white space character found. This stream is left on 
    // the charactor after the one returned. <p>
    // This will throw an ExceptionEndOfStreamC if the end
    // of the input stream is found. <br>
    
    bool Skip(const char *delim = " \n\t\r");
    //: Skip all 'delim' characters.
    // Leaves stream at first character this is not one of those
    // listed in 'delim'. If end of stream is found before
    // returns false.
    
    bool SkipTo(const StringC &endStr);
    //: Skip through stream until endStr is found.
    // this leaves the stream positioned at the
    // first character after the string. <p>
    // returns false if the end of the stream is found first.
    
    bool SkipTo(char let);
    //: Skip through stream until 'let' is found.
    // returns false if the end of the stream is found first.
    
    StringC ClipTo(char let);
    //: Return all characters before let.
    // the 'let' character is discarded. <p>
    // If the end of stream is found, all data found
    // upto that point is returned.
    
    StringC ClipTo(const StringC &endStr);
    //: Return all characters before 'endStr'.
    // this leaves the stream positioned at the
    // first character after the string. <p>
    // If the end of stream is found, all data found
    // upto that point is returned.
    
    StringC ClipWord(const char *delim = " \n\t\r",bool initalSkipDelim = false);
    //: Clip word until one of 'delim' characters are found.
    // Stream is left at the terminating deliminator.
    
  protected:
    istream *in;
  };
}

#if RAVL_COMPILER_MIPSPRO 
istream & operator >> ( istream & str,  signed char & dat ) 
{ 
  char tmp ; 
  str >> tmp ; 
  dat = (signed char) tmp ; 
  return str ; 
} 
#endif 

#endif
