// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLFILEPERM_HEADER
#define RAVLFILEPERM_HEADER 1
////////////////////////////////////////////////////////
//! file="Ravl/OS/FileSystem/FilePermission.hh"
//! lib=RavlOS
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.OS.File System"
//! date="20/10/1996"
//! rcsid="$Id$"

#include <sys/stat.h>
#include <sys/types.h>
#include "Ravl/Types.hh"

namespace RavlN {
#ifdef VISUAL_CPP
  typedef unsigned long ulong_t;
  typedef ulong_t mode_t;
  typedef long uid_t;
  typedef uid_t gid_t;
  
  //#define S_IFMT  0xF000          /* type of file */
  
  //#define S_IFDIR  0x4000         /* directory */
#define S_IFBLK  0x6000         /* block special */
  //#define S_IFREG  0x8000         /* regular */
#define S_IFLNK  0xA000         /* symbolic link */
#define S_IFSOCK 0xC000         /* socket */
#define S_IFDOOR 0xD000         /* door */

#define	S_IRWXU	00700		/* read, write, execute: owner */
#define	S_IRUSR	00400		/* read permission: owner */
#define	S_IWUSR	00200		/* write permission: owner */
#define	S_IXUSR	00100		/* execute permission: owner */
#define	S_IRWXG	00070		/* read, write, execute: group */
#define	S_IRGRP	00040		/* read permission: group */
#define	S_IWGRP	00020		/* write permission: group */
#define	S_IXGRP	00010		/* execute permission: group */
#define	S_IRWXO	00007		/* read, write, execute: other */
#define	S_IROTH	00004		/* read permission: other */
#define	S_IWOTH	00002		/* write permission: other */
#define	S_IXOTH	00001		/* execute permission: other */

#define S_ISDIR(mode)	(((mode)&0xF000) == 0x4000) /* Is a directory ?     */
#define S_ISREG(mode)	(((mode)&0xF000) == 0x8000) /* Is a regulary file ? */

#endif

  class UserInfoC;
  
  //: Unix style file permisions.
  
  class FilePermissionC {
  public:	
    inline FilePermissionC();
    //: Default access is RW all.
    
    inline FilePermissionC(mode_t Value,uid_t userid = 0,gid_t grpid = 0);
    //: Default access is RW all.
  
    inline void SetRWXAll();
    //: Set Read, Write, Excute all.
    
    inline void SetUserReadWrite();
    //: Add user read/write permission.
    
    inline const FilePermissionC &operator=(mode_t mode);
    //: Set mode.
    
    inline bool operator[](IntT ABit) const;
    //: Test a bit.
    
    inline void ZeroBit(IntT ABit);
    //: Set a single bit to zero. ABit should be 0-32
    
    inline void SetBit(IntT ABit);
    //: Set a single bit to one.  ABit should be 0-32
    
    inline void Zero(IntT ABit);
    //: Set bits to zero.
  
    inline void Set(IntT ABit);
    //: Set bits to one.
    
    inline void SetNone();
    //: Set file permisions to none at all.
    
    inline bool IsNone();
    //: Test if no-permisions. 
    
    inline mode_t Mode() const;
    //: Get current mode.
    
    inline uid_t Owner() const;
    //: Owner of file.
    
    UserInfoC OwnerInfo() const;
    //: Get information on owner.
    
    inline uid_t Group() const;
    //: Group of file.
    
    bool IsReadable() const;
    //: Do we have read permission for this process ?
    
    bool IsWritable() const;
    //: Do we have write  permission for this process ?
    
    bool IsOwnerWritable() const;
    //: Does owner have write access ?
  
    bool IsWorldWritable() const;
    //: Does world have write access ?
    
    inline bool IsDirectory() const;
    //: Is this object a directory ?
    
    inline bool IsRegular() const;
    //: Is this object a regular file ?
    
    inline bool IsSocket() const;
    //: Is this object a socket ?
    
    inline bool IsFifo() const;
    //: Is this object a socket ?
    
    FilePermissionC SetUMask() const;
    //: Set the process mask to this mode.
    // Returns the value of the mask before it was set.
  private:
    mode_t mode;
    uid_t owner; // Owner of file.
    gid_t group;
  };
  
  /////////////////////////////////////////////////////////
  
  inline 
  FilePermissionC::FilePermissionC()
    : mode(S_IRWXU | S_IRWXG | S_IRWXO)
  {}
  
  inline 
  FilePermissionC::FilePermissionC(mode_t Value,uid_t userid,gid_t grpid) 
    : mode(Value),
      owner(userid),
      group(grpid)
  {}
  
  inline 
  void FilePermissionC::SetRWXAll() 
  { mode |= S_IRWXU | S_IRWXG | S_IRWXO;  }
  
  inline 
  void FilePermissionC::SetUserReadWrite()
  { mode |= S_IWUSR | S_IRUSR; }
  
  inline 
  bool FilePermissionC::operator [](IntT ABit) const 
  { return (mode & (1 << ABit)) != 0; }
  
  inline 
  void FilePermissionC::ZeroBit(IntT ABit)
  { mode &= ~(1 << ABit); }

  inline 
  void FilePermissionC::SetBit(IntT ABit) 
  { mode |= (1 << ABit); }

  inline 
  void FilePermissionC::Zero(IntT ABit) 
  { mode &= ~ABit; }

  inline 
  void FilePermissionC::Set(IntT ABit) 
  { mode |= ABit; }

  inline 
  void FilePermissionC::SetNone()
  { mode = 0; }
  
  inline 
  mode_t FilePermissionC::Mode() const 
  { return mode; }
  
  inline 
  uid_t FilePermissionC::Owner() const
  { return owner; }

  inline 
  uid_t FilePermissionC::Group() const
  { return group; }
  
  
  inline
  bool FilePermissionC::IsDirectory() const 
  { return S_ISDIR(Mode()); }
  
  inline 
  bool FilePermissionC::IsRegular() const 
  { return S_ISREG(Mode()); }
  
  inline 
  bool FilePermissionC::IsSocket() const  { 
#if defined(S_ISSOCK)
    return S_ISSOCK(Mode()); 
#else
    return false;  
#endif
  }
  
  inline 
  bool FilePermissionC::IsFifo() const  { 
#if defined(S_ISSOCK)
    return S_ISFIFO(Mode()); 
#else
    return false;
#endif
  }
  
}
#endif
  
