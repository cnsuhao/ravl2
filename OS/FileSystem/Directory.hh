// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef FILEDIRECTORY_HEADER
#define FILEDIRECTORY_HEADER
///////////////////////////////////////////////////////////////////////
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.OS.File System"
//! lib=RavlOS
//! rcsid="$Id$"
//! file="amma/StdType/System/Generic/Directory.hh"
//! date="07/05/98"

#include "Ravl/OS/Filename.hh"
#include "Ravl/DList.hh"

namespace RavlN {

  //: Directory handling.
  // Used for querying and changing the contents of directories. <p>
  // The class is designed to be thread safe where different
  // instances of DirectoryC are used simulatiously and between
  // 'const' methods of this class.
  
  class DirectoryC : public FilenameC {
  public:    
    inline DirectoryC(const StringC &name = StringC("."));
    //: Construct from a string.
    
    inline DirectoryC(const DirectoryC &name);
    //: Copy constructor.
    
    inline bool Create(const FilePermissionC &Acc = FilePermissionC()) const
      { return FilenameC::MakeDir(Acc); }
    //: Create a directory by this name.
    
    inline bool IsValid() const
      { return FilenameC::IsDirectory(); }
    //: Is this really a directory ?
    
    DListC<FilenameC> List() const;
    //: List contents of directory.
    // Will return an empty list if anything goes wrong.
    // Gives names of contents relative to this directory
    // , without any leading or trailing "/"
    
    DListC<FilenameC> List(const StringC &pre,const StringC &post) const;
    //: List contents of directory, returning only files with the given
    //: prefix and postfix.
    // Either (or both) pre and post maybe empty strings..
    // Will return an empty list if anything goes wrong. 
    
    DListC<FilenameC> FiltList(const StringC &filter) const;
    //: List contents of directory, returning only files matching
    //: the given filter.
    
    
    bool Copy(const FilenameC &othDir,bool rec = true,bool lazy = false,bool sync = false,bool verb = false);
    //: Copy all files in this directory into 'othDir'.
    // This will make 'othDir' if necessary. When 'rec' is true
    // it will do so recursively, if false subdirectories will be
    // ignored.  If othDir is an empty string the currect directory 
    // is used. <p>
    // if lazy is true, files are only updated if they have a later 
    // date than the target. <p>
    // if sync is true, all files that are not in the source directory 
    // are removed. <p>
    
  protected:
    static bool MatchFilt(const char *filter,const char *str);
    //: Simple test if 'x' matches filter.
    // Wild cards are '*','?' and '\' escapes. 
  
  };
  
  ////////////////////////////////////////////////////////////
    
  inline 
  DirectoryC::DirectoryC(const StringC &name)
    : FilenameC(name)
  {}
  
  inline 
  DirectoryC::DirectoryC(const DirectoryC &name)
    : FilenameC(name)
  {}
}

#endif
