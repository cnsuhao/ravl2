// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! docentry="Ravl.OS.File System"
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlOS

#include "Ravl/OS/FileStream.hh"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

namespace RavlN {
  
  //: Default constructor.
  
  FileStreamC::FileStreamC()
    : fd(-1)
  {}
  
  //: Construct from a file descriptor.
  
  FileStreamC::FileStreamC(int nfd)
    : fd(nfd)
  {}
  
  //: Construct from a file descriptor.
  
  FileStreamC::FileStreamC(const StringC &filename,bool forRead,bool forWrite)
    : fd(-1)
  {
    int flags = 0;
    if(forRead) {
      if(forWrite)
	flags =  O_RDWR;
      else
	flags =  O_RDONLY;
    } else
      flags = O_WRONLY | O_CREAT | O_TRUNC;
    flags |= O_LARGEFILE;
    fd = open(filename.chars(),flags,0666);
  }

  //: Destructor
  
  FileStreamC::~FileStreamC() {
    if(fd >= 0)
      close(fd);
  }
  
  //: Seek to offset in a file.
  
  bool FileStreamC::Seek(StreamOffsetT offset)
  { return lseek64(fd,offset,SEEK_SET) >= 0; }
  
  //: Write data to file descriptor.
  // Returns the number of charactors read, or -1 on error.
  
  IntT FileStreamC::Write(const void *data,IntT length) 
  { return write(fd,data,length); }
  
  //: Read data from file descriptor.
  
  IntT FileStreamC::Read(void *data,IntT length) 
  { return read(fd,data,length); }

  
  //: Write all data to file descriptor.
  // This routine works as Write(), but will handle temporary errors.
  
  IntT FileStreamC::WriteAll(const void *tdata,IntT length) {
    const char *data = (const char *) tdata;
    IntT done = 0;
    do {
      int n = Write(&(data[done]),length - done);
      if(n < 0) {
	if(errno == EAGAIN || errno == EINTR) // Recoverable error?
	  continue;
	return -1;
      }
      done += n;
    } while(done < length);
    return done;
  }
  
  //: Read all data from file descriptor.
  // This routine works as Write(), but will handle temporary errors.
  
  IntT FileStreamC::ReadAll(void *tdata,IntT length) {
    char *data = (char *) tdata;
    IntT done = 0;
    do {
      int n = Read(&(data[done]),length - done);
      if(n == 0) {
	// Indicates end of file on linux, what about other platforms ?
	return 0;
      }
      if(n < 0) {
	if(errno == EAGAIN || errno == EINTR) // Recoverable error?
	  continue;
	cerr << "Read error =" << errno << "\n";
	return -1;
      }
      done += n;
    } while(done < length);
    return done;
  }

  //: Find the size of the file.
  
  StreamSizeT FileStreamC::Size() const {
    if(!Good())
      return 0;
#if RAVL_USE_LARGEFILESUPPORT
    struct stat64 buff;
    if(fstat64(fd,&buff) < 0)
      return 0;
#else
    struct stat buff;
    if(fstat(fd,&buff) < 0)
      return 0;
#endif
    return (StreamSizeT) buff.st_size;
  }
  
}
