// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Base/Stream.cc"

#include "Ravl/Stream.hh"
#include "Ravl/StreamType.hh"
#include "Ravl/Calls.hh"

#if RAVL_HAVE_ANSICPPHEADERS
#include <fstream>
#else
#include <fstream.h>
#endif

#include <stdio.h>

// Note: The implementation of the stream parsing functions
//
//    char GetChar();
//    char SkipWhiteSpace();
//    bool SkipTo(const StringC &endStr);
//    bool SkipTo(char let);
//    StringC ClipTo(char let);
//    StringC ClipTo(const StringC &endStr);
//
// Can be found in ../System/StreamParse.cc, the have been
// put there because they rely on containers which are
// compiled after this directory.

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
#if RAVL_HAVE_STDNAMESPACE
  using namespace std;
#endif

#if RAVL_COMPILER_GCC3
  // Part of a horrible hack to allow us to open a stream from a file descriptor.
  
  template<typename _CharT, typename _Traits>
  class basic_fdfilebuf 
    : public std::basic_filebuf< _CharT, _Traits>
  {
  public:
    basic_filebuf<_CharT, _Traits>  *open(int fd, ios_base::openmode __mode) {
      basic_filebuf<_CharT, _Traits> *__ret = NULL;
      if (!this->is_open())
	{
	  // The true here will cause the file to be closed when stream is destroyed.
	  _M_file.sys_open(fd, __mode,true); 
	  if (this->is_open())
	    {
	      _M_allocate_internal_buffer();
	      _M_mode = __mode;
	      
	      // For time being, set both (in/out) sets  of pointers.
	      _M_set_indeterminate();
	      if ((__mode & ios_base::ate)
		  && this->seekoff(0, ios_base::end, __mode) < 0)
		this->close();
	      __ret = this;
	    }
	}
      return __ret;      
    }
    //: Open a file handle.
    
    void SetBuf(char *buf,int len)
    { setbuf(buf,len); }
    //: Set buffer to use.
  };
#endif
  
  // A hook to allow a method to map urls to be added by another module.
  
  URLMapperFuncT urlMapper = 0;
  
  //: Test if URL mapping enabled.
  // Returns true if it is.
  
  bool IsURLMappingEnabled()
  { return urlMapper != 0; }
  
  //: Print diagnostic message about the streams state.
  
  bool StreamBaseC::DiagnoseStream(ostream &out) {
    bool found = false;
    out << "StreamBaseC, '" << name << "' Diagnoses: ";
    if(s == 0) {
      out << "Invalid handle. \n";
      return true;
    }
    if(eof()) {
      out << "End Of File. \n";
      found = true;
    } 
    if(fail()) {
      out << "Operation failed. \n";
      found = true;
    }
    return found; // Nothing wrong !
  }
  
  //: Close this stream.
  // After this is called no further IO should be attempted!
  
  bool StreamBaseC::Close() {
    if(s == 0)
      return false;
#if !defined(VISUAL_CPP) && !RAVL_COMPILER_GCC3
    fstreambase *fsb = dynamic_cast<fstreambase *>(s);
#else
    fstream *fsb = dynamic_cast<fstream *>(s);
#endif
    if(fsb != 0) {
      fsb->close();
      return true;
    }
    return false;
  }
  
  static bool NukeIStream(istream *&is) {
    delete is;
    return true;
  }
  
  static bool NukeOStream(ostream *&os) {
    delete os;
    return true;
  }
  
  //: Body Constructor.
  StreamBaseC::StreamBaseC(ostream *ns,StringC afilename,bool nDelOnClose) 
    : name(afilename.Copy()),
      s(ns)
  {
    if(nDelOnClose)
      SetDestructionOp(CallFunc1C<ostream *,bool>(&NukeOStream,ns));
    else
      SetDestructionOp(TriggerC());
  }
  
  //: Body Constructor.
  StreamBaseC::StreamBaseC(istream *ns,StringC afilename,bool nDelOnClose) 
    : name(afilename.Copy()),
      s(ns)

  {
    if(nDelOnClose)
      SetDestructionOp(CallFunc1C<istream *,bool>(&NukeIStream,ns));
    else
      SetDestructionOp(TriggerC());
  }
  
  //: Setup 
  // This should only be called on Stream's constructed with the
  // default constructor!
  
  bool StreamBaseC::Init(istream *ns,StringC afilename,bool nDelOnClose) {
    name = afilename;
    s = ns;
    if(nDelOnClose)
      SetDestructionOp(CallFunc1C<istream *,bool>(&NukeIStream,ns));
    else
      SetDestructionOp(TriggerC());
    return true;
  }
  
  //: Setup 
  // This should only be called on Stream's constructed with the
  // default constructor!
  
  bool StreamBaseC::Init(ostream *ns,StringC afilename,bool nDelOnClose) {
    name = afilename;
    s = ns;
    if(nDelOnClose)
      SetDestructionOp(CallFunc1C<ostream *,bool>(&NukeOStream,ns));
    else
      SetDestructionOp(TriggerC());
    return true;
  }
  
  ////////////////////////////////////////////////////
  
  //: Open a file.
  // '-' is treated as cout.
  
  OStreamC::OStreamC(const StringC &sfilename,bool binaryMod,bool buffered,bool append)
    : out(0)
  {
    ONDEBUG(cerr << "OStreamC::OStreamC(" << sfilename << "," << ((int) binaryMod) << ","  << (int) buffered << "," << (int) append << ") Called \n");
    ofstream *ofstrm = 0;
    if(sfilename == "-") {
      Init(out = &cout,sfilename,false);
      if(!buffered) 
	cerr << "WARNING: OStreamC() Can't disable buffering on 'cout'. \n";
      return ;
    }
    // Check if we're mapping url's.
    
    StringC filename;
    if(urlMapper != 0)
      filename = urlMapper(sfilename);
    else filename = sfilename;
    
    // Open a 'special file' ?
    
    if(filename.length() > 0) {
      if(filename[0] == '@') {
	int cat = filename.index(':');
	StringC ncfn(filename);
	StringC stypename;
	if(cat < 0)
	  stypename = ncfn.after(0);
	else
	  stypename = ncfn.at(1, cat-1);
	ONDEBUG(cerr << "Looking for '" << stypename << "'\n");
	StreamTypeC *st = StreamTypeC::Find(stypename);
	if(st != 0) {
	  (*this) = st->OpenO(ncfn.after(cat),binaryMod,buffered);
	  return ;
	}
      }
    }
    
    // Normal open.
    
    int fmode = ios::out;
#if RAVL_HAVE_IOS_BINARY
    if(binaryMod) 
      fmode |= ios::binary;
#endif
    if(append)
      fmode |= ios::app;  
#if !RAVL_COMPILER_GCC3
    Init(ofstrm = new ofstream(filename.chars(),fmode),filename);
#else
    Init(ofstrm = new ofstream(filename.chars(),(std::_Ios_Openmode) fmode),filename);
#endif
      
    //Init(ofstrm = new ofstream(filename),filename);
    out = ofstrm;
#if !RAVL_COMPILER_GCC3
    if(!buffered) 
      ofstrm->setbuf(0,0);
#endif
  }
  
  //: Get data from unix filehandle.
  
  OStreamC::OStreamC(int fd,bool buffered) { 
#if !RAVL_COMPILER_GCC3
    if(buffered)
      Init(out = new ofstream(fd),StringC(fd)); 
    else
      Init(out = new ofstream(fd,0,0),StringC(fd)); 
#else
    ofstream *ofs = new ofstream(); 
    // A horrible hack to allow us to open a file handle....
    basic_fdfilebuf<ofstream::char_type,ofstream::traits_type>  *bfd = 
      (basic_fdfilebuf<ofstream::char_type,ofstream::traits_type>  *) ofs->rdbuf(); 
    if(!bfd->open(fd,ios_base::out | ios_base::binary))
      ofs->setstate(ios_base::failbit);
    if(!buffered)
      bfd->SetBuf(0,0);
    Init(out = ofs,StringC(fd)); 
#endif
  }
  
  //: Print to stream using good old 'C' sytle formating.
  // This isn't the saftest function, it uses a fixed
  // buffer of 4096 bytes. 
  
  ostream& OStreamC::form(const char *format ...) {
    const int formSize = 4096;
    va_list args;
    va_start(args,format);
    char buff[formSize];
    int x = vsprintf(buff,format,args);
    if(x > (formSize - 256)) 
      cerr << "OStreamC::form(...), WARNING: Ouput string is near or over buffer length. \n";
    os() << buff;
    va_end(args);
    return *this;
  }
  
  ////////////////////////////////////////////////////
  
  //: Open a file for input.
  // '-' is treated as cin.
  
  IStreamC::IStreamC(const StringC &sfilename,bool binary,bool buffered) {
    ifstream *ifstrm = 0;
    if(sfilename == "-") {
      Init(in = &cin,sfilename,false);
      if(!buffered) 
	cerr << "WARNING: IStreamC() Can't disable buffering on 'cin'. \n";
      return ;
    } 
    
    // Check if we're mapping url's.
    
    StringC filename;
    if(urlMapper != 0)
      filename = urlMapper(sfilename);
    else filename = sfilename;
    
    // Open a 'special file' ?
    
    if(filename.length() > 0) {
      if(filename[0] == '@') {
	int cat = filename.index(':');
	StringC ncfn(filename);
	StringC stypename;
	if(cat < 0)
	  stypename = ncfn.after(0);
	else
	  stypename = ncfn.at(1, cat-1);
	//ONDEBUG(cerr << "Looking for '" << stypename << "'\n");
	StreamTypeC *st = StreamTypeC::Find(stypename);
	if(st != 0) {
	  (*this) = st->OpenI(ncfn.after(cat),binary,buffered);
	  return ;
	}
	//cerr << "WARNING: Can't find specal file '" << stypename << "'\n";
      }
  }
    
    // Normal open.
    
#if RAVL_HAVE_IOS_BINARY
    if(binary)
      Init(ifstrm = new ifstream(filename,ios::binary | ios::in),filename);
    else 
#endif
      Init(ifstrm = new ifstream(filename),filename);
    in = ifstrm;
#if !RAVL_COMPILER_GCC3
    if(!buffered) {
      RavlAssert(ifstrm != 0);
      ifstrm->setbuf(0,0);
    }
#endif
  }
  
  //: Get data from unix filehandle.
  
  IStreamC::IStreamC(int fd,bool buffered) {   
#if !RAVL_COMPILER_GCC3
    if(buffered)
      Init(in = new ifstream(fd),StringC(fd));
    else
      Init(in = new ifstream(fd,0,0),StringC(fd));
#else
    ifstream *ifs = new ifstream(); 
    // A horrible hack to allow us to open a unix file descriptor.
    basic_fdfilebuf<ifstream::char_type,ifstream::traits_type>  *bfd = 
      (basic_fdfilebuf<ifstream::char_type,ifstream::traits_type>  *) ifs->rdbuf(); 
    cerr << "Opening file descriptor " << fd << "\n";
    if(bfd->open(fd,ios_base::in  | ios_base::binary) == 0) {
      ifs->setstate(ios_base::failbit);
      cerr << "ERROR: Open of file descriptor failed. \n";
    }
#if 0
    if(!buffered)
      bfd->SetBuf(0,0);
#endif
    Init(in = ifs,StringC(fd)); 
#endif
  }
  
  /////////////////////////
  //: Unget a string.
  
  void IStreamC::Unget(StringC text) { 
    is().putback('\n'); // And terminator.
    for(int i=(int)text.length()-1;i >= 0;i--)
      is().putback(text[i]);
  }
  
  /////////////////////////
  //: Unget a string from a stream.
  
  void IStreamC::Unget(const char *dat,int len) {
#if !RAVL_ISTREAM_UNGET_BUG
    const char *place = dat;
    len--;
    for(;len >= 0;len--)
      is().putback(place[len]);
#else
    // unget doesn't seem to work for all charactors under
    // Visual C++. this works around the problem though its
    // not clear it will work for all types of streams.
    // FIXME:- Be a little more clever and try and use unget when it will work.
    is().seekg(is().tellg() - len);
#endif
  }
  
  ////////////////////////////////
  //: Copy stream to output.
  
  IntT IStreamC::CopyTo(OStreamC &out,IntT maxChars) {
    const int buffsize = 4096;
    char buff[buffsize];
    IntT total = 0;
    do {
      IntT readSize = buffsize;
      if((total+buffsize) > maxChars && maxChars >= 0)
	readSize = maxChars - total;
      read(buff,readSize);
      int n = gcount();
      out.write(buff,n);
      total += n;
    } while((*this).good() && out.good() && (bool)(total < maxChars)) ;
    return total;
  }
  
}
