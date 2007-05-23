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

#if RAVL_COMPILER_GCC
#include "Ravl/fdstream.hh"
#include "Ravl/stdio_fdstream.hh"
#include <ext/stdio_filebuf.h>
#endif

#if RAVL_HAVE_ANSICPPHEADERS
#include <fstream>
#else
#include <fstream.h>
#endif

#include <stdio.h>
#include <fcntl.h>

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
    ONDEBUG(cerr << "StreamBaseC::Close() Called. \n");
    if(s == 0)
      return false;
#if !RAVL_COMPILER_VISUALCPP && !RAVL_COMPILER_GCC
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
    ONDEBUG(cerr << "NukeIStream(), Called. \n");
    delete is;
    return true;
  }
  
  static bool NukeOStream(ostream *&os) {
    ONDEBUG(cerr << "NukeOStream(), Called. \n");
    delete os;
    return true;
  }
  
  //: Body Constructor.
  StreamBaseC::StreamBaseC(ostream *ns,StringC afilename,bool nDelOnClose) 
    : name(afilename.Copy()),
      s(ns)
  {
    if(nDelOnClose)
      SetDestructionOp(CallFunc1C<ostream *&,bool>(&NukeOStream,ns));
    else
      SetDestructionOp(TriggerC());
  }
  
  //: Body Constructor.
  StreamBaseC::StreamBaseC(istream *ns,StringC afilename,bool nDelOnClose) 
    : name(afilename.Copy()),
      s(ns)

  {
    if(nDelOnClose)
      SetDestructionOp(CallFunc1C<istream *&,bool>(&NukeIStream,ns));
    else
      SetDestructionOp(TriggerC());
  }
  
  //: Setup 
  // This should only be called on Stream's constructed with the
  // default constructor!
  
  bool StreamBaseC::Init(istream *ns,StringC afilename,bool nDelOnClose) {
    ONDEBUG(cerr << "StreamBaseC::Init((istream *)" << ((void *) ns) << "," << afilename << "," << nDelOnClose << ")\n");
    name = afilename;
    s = ns;
    if(nDelOnClose)
      SetDestructionOp(CallFunc1C<istream *&,bool>(&NukeIStream,ns));
    else
      SetDestructionOp(TriggerC());
    return true;
  }
  
  //: Setup 
  // This should only be called on Stream's constructed with the
  // default constructor!
  
  bool StreamBaseC::Init(ostream *ns,StringC afilename,bool nDelOnClose) {
    ONDEBUG(cerr << "StreamBaseC::Init((ostream *)" << ((void *) ns) << "," << afilename << "," << nDelOnClose << ")\n");
    name = afilename;
    s = ns;
    if(nDelOnClose)
      SetDestructionOp(CallFunc1C<ostream *&,bool>(&NukeOStream,ns));
    else
      SetDestructionOp(TriggerC());
    return true;
  }
  
  ////////////////////////////////////////////////////
  
  //: Open a file.
  // '-' is treated as cout.
  
  OStreamC::OStreamC(const StringC &sfilename,bool binaryMod,bool buffered,bool append)
    : StreamBaseC(sfilename),
      out(0)
  {
    ONDEBUG(cerr << "OStreamC::OStreamC(" << sfilename << "," << ((int) binaryMod) << ","  << (int) buffered << "," << (int) append << ") Called \n");
    ostream *ofstrm = 0;
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
    fmode |= ios::binary;
    
    if(append)
      fmode |= ios::app;  
#if RAVL_COMPILER_GCC
#if RAVL_HAVE_INTFILEDESCRIPTORS 
    // We can't use the native open, because we need to be able to handle large files.
    int mode = O_WRONLY | O_CREAT | O_LARGEFILE;
    if(append)
      mode |= O_APPEND;
    else
      mode |= O_TRUNC;
    
    static int defaultPermissions = 0644;
    IntT fd = open(filename.chars(),mode,defaultPermissions); 
    if(fd >= 0) {
      ofstrm = new stdofdstream(fd);
      Init(out = ofstrm,filename);     
    } else {
      // Open with a normal ofstream call. This helps ensure consistant behaviour
      // with ofstream for a file that failed to open.
      
      Init(ofstrm = new ofstream(filename.chars(),(std::_Ios_Openmode) fmode),filename);
      if(!buffered) {
        cerr << "WARNING: Unbuffered streams are not currently supported under gcc3.\n";
      }
    }
#else    
    Init(ofstrm = new ofstream(filename.chars(),(std::_Ios_Openmode) fmode),filename);
    if(!buffered) {
      cerr << "WARNING: Unbuffered streams are not currently supported under gcc3.\n";
    }
#endif
#else // RAVL_COMPILER_GCC
    Init(ofstrm = new ofstream(filename.chars(),fmode),filename);
#if RAVL_COMPILER_VISUALCPP
    if(!buffered) {
      cerr << "WARNING: Unbuffered streams are not currently supported under windows.\n";
    }
#else // RAVL_COMPILER_VISUALCPP
    if(!buffered) 
      ofstrm->setbuf(0,0);
#endif // RAVL_COMPILER_VISUALCPP
#endif // RAVL_COMPILER_GCC
    out = ofstrm;
  }
  
  //: Get data from unix filehandle.

#if RAVL_HAVE_INTFILEDESCRIPTORS
  OStreamC::OStreamC(int fd,bool binary,bool buffered) { 
    ONDEBUG(cerr << "OStreamC::OStreamC(" << fd << "," << ((int) binary) << ","  << (int) buffered << ") Called \n");
#if !RAVL_COMPILER_GCC
    if(buffered)
      Init(out = new ofstream(fd),StringC(fd)); 
    else
      Init(out = new ofstream(fd,0,0),StringC(fd)); 
#else
    ofdstream *ofs = new ofdstream(fd); 
    Init(out = ofs,StringC(fd)); 
#endif
  }
#endif

  //: Print to stream using good old 'C' sytle formating.
  // This isn't the saftest function, it uses a fixed
  // buffer of 4096 bytes. 
  
  ostream& OStreamC::form(const char *format ...) {
    
    va_list args;
    va_start(args,format);
    
	const int formSize = 4096;
	char buff[formSize];
#if RAVL_COMPILER_VISUALCPPNET_2005
	int x = vsprintf_s(buff,formSize,format,args);
#elif RAVL_COMPILER_VISUALCPP
    int x = _vsnprintf(buff,formSize,format,args);
#else
    int x = vsnprintf(buff,formSize,format,args);
#endif
    if(x < 0) 
      cerr << "OStreamC::form(...), WARNING: Output string is over buffer length. \n";
    else
      os() << buff;

    va_end(args);
    return *this;
  }
  
  ////////////////////////////////////////////////////
  
  //: Open a file for input.
  // '-' is treated as cin.
  
  IStreamC::IStreamC(const StringC &sfilename,bool binary,bool buffered) 
    : StreamBaseC(sfilename)
  {
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
    int fmode = ios::in;
#if RAVL_HAVE_IOS_BINARY
    if(binary)
      fmode |= ios::binary;
#endif
    
#if RAVL_HAVE_INTFILEDESCRIPTORS
    // We can't use the native open, because we need to be able to handle large files.
    //cerr << "USING NEW OPEN. \n";
    int mode = O_RDONLY | O_LARGEFILE;
    int fd = open(filename.chars(),mode);
    if(fd >= 0) {
      istream *ifs = new stdifdstream(fd,static_cast<std::ios_base::openmode>(fmode));
      Init(ifs ,filename);
      in = ifs;
    } else {
      // If we failed to open it as file descriptor try again with the normal istream interface.
      // This keeps behaviour consistant with the behavour of ifstream of files that failed to open.
      ifstream *ifstrm = 0;
      fmode |= ios::binary;
      Init(ifstrm = new ifstream(filename,static_cast<std::ios_base::openmode>(fmode)),filename);
      in = ifstrm;
    }
#else
    ifstream *ifstrm = 0;
    fmode |= ios::binary;
    Init(ifstrm = new ifstream(filename,static_cast<std::ios_base::openmode>(fmode)),filename);
    in = ifstrm;
#endif //  RAVL_HAVE_INTFILEDESCRIPTORS
    
#if RAVL_COMPILER_VISUALCPPNET || RAVL_COMPILER_GCC || RAVL_COMPILER_VISUALCPPNET_2005
    if(!buffered) {
      cerr << "WARNING: Unbuffered streams are not currently supported under windows or gcc3.\n";	
    }	
#else
    if(!buffered) {
      RavlAssert(ifstrm != 0);
      ifstrm->setbuf(0,0);
    }
#endif
  }
  
  //: Get data from unix filehandle.
  
#if RAVL_HAVE_INTFILEDESCRIPTORS
  IStreamC::IStreamC(int fd,bool binary,bool buffered) {   
    ONDEBUG(cerr << "IStreamC::IStreamC(" << fd << "," << ((int) binary) << ","  << (int) buffered << ") Called \n");
#if !RAVL_COMPILER_GCC
    if(buffered)
      Init(in = new ifstream(fd),StringC(fd));
    else
      Init(in = new ifstream(fd,0,0),StringC(fd));
#else
    ifdstream *ifs = new ifdstream(fd);
    Init(in = ifs,StringC(fd));    
#endif
  }
#endif

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
    // unget doesn't seem to work for all characters under
    // Visual C++. this works around the problem though its
    // not clear it will work for all types of streams.
    // FIXME:- Be a little more clever and try and use unget when it will work.
    is().seekg(is().tellg() - static_cast<streampos>(len));
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
    } while((*this).good() && out.good() && ((bool)(total < maxChars) || maxChars < 0)) ;
    return total;
  }
  
}
