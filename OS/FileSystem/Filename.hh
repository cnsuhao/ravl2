// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FILENAME_HEADER
#define RAVL_FILENAME_HEADER
/////////////////////////////////////////////////////////////
//! file="Ravl/OS/FileSystem/Filename.hh"
//! lib=RavlOS
//! userlevel=Basic
//! author="Charles Galambos"
//! date="10.6.97"
//! docentry="Ravl.API.OS.File System"
//! rcsid="$Id: Filename.hh 5240 2005-12-06 17:16:50Z plugger $"
//! example=exFilename.cc

#include "Ravl/String.hh"
#include "Ravl/OS/FilePermission.hh"
#include "Ravl/Exception.hh"

namespace RavlN {
  class DateC;
  class OStreamC;
  class ExceptionOperationFailedC;
  template<class DataT> class DListC;
  
#if RAVL_COMPILER_VISUALCPP
  const char filenameSeperator ='\\';
#else
  const char filenameSeperator ='/';
#endif
  
  //: StringC representing a filename.
  
  class FilenameC 
    : public StringC 
  {
  public: 
    inline FilenameC()
      {}
    //: Default constructor.
    
    inline FilenameC(const char *nname);
    //: Construct from a C string.
    
    inline FilenameC(const StringC &nname);
    //: Construct from a StringC.

    inline FilenameC(const SubStringC &nname);
    //: Construct from a SubStringC.
    
    inline FilenameC(const FilenameC &ano);
    //: Copy constructor.
    
    bool MakeDir(const FilePermissionC &Acc = FilePermissionC()) const;
    //: Make a directory with this name.
    // Return: true = Directory created ok.
    
    bool Exists() const;
    //: Test if the file/directory given in this path exists.
    // Return: true = File does exist.
    
    bool Rename(const StringC &newname) const;
    //: Rename file.
    // This does NOT change the value of this filename.
    // Ret true=Succeeded.
    
    inline bool IsReadable() const
      { return Permissions().IsReadable(); }
    //: Test if the file/directory is readable by this process.
    // Return: true = It can be read.
    
    inline bool IsWritable() const
      { return Permissions().IsWritable(); }
    //: Test if the file/directory is writable by this process.
    // Return: true = It can be written to.
    
    inline bool IsDirectory() const
      { return Permissions().IsDirectory(); }
    //: Test if the this is a directory.
    // Return: true = Yep.
    
    inline bool IsFifo() const
      { return Permissions().IsFifo(); }
    //: Test if the this is a pipe
    // Return: true = Yep.
    
    inline bool IsRegular() const
      { return Permissions().IsRegular(); }
    //: Test if the this is a regular file ?
    // Return: true = Yep.
    
    FilePermissionC Permissions() const;
    //: Get the access permisions for this file.
    // Returns no-permisions if file is not found.
    
    bool SetPermissions(const FilePermissionC &perm);
    //: Set the access permisions for this file.
    // Returns false if failed.
    
    FilenameC PathComponent() const;
    //: Return the path component of a Filename, ie. upto last / 
    
    FilenameC NameComponent() const;
    //: Return the name component of a Filename, ie. after last / 

    FilenameC BaseNameComponent() const;
    //: Return the base name component of a Filename, 
    // ie. after last / and before the extention. 
    // (the last '.' in the NameComponent()).
    
    FilenameC MkTemp(IntT Digits = 4,IntT maxretry=100) const RAVL_THROW2(ExceptionOperationFailedC,ExceptionOutOfRangeC);
    //: Make this filename unique by appending a unique string
    //: and checking if it doesn't exist already. 
    // If it does try another, if process failes more than 
    // maxretry times, then an ExceptionOperationFailedC is thrown. <br>
    // If maxretry  is negative infinite retries are alowed. <br>
    // Digits should be betwee 0 and 6. <br>
    // If the filename contains an extension the numbers will be added before it.
    
    DateC LastAccessTime() const;
    //: Get last file access.
    
    DateC LastModTime() const;
    //: Get last modification time.
    
    DateC LastStatusModTime() const;
    //: Get last status modification time.
    
    StreamSizeT FileSize() const;
    //: Get size of file.
    // Return 0 if file's not found.
    
    bool Remove() const;
    //: Remove this file.
    
    UserInfoC OwnerInfo() const;
    //: Get information on owner of file.
    
    bool CopyTo(const FilenameC &oth) const;
    //: Copy this file to somewhere else.
  
    bool BinCompare(const FilenameC &oth) const;
    //: Are two files identical. byte wise comparison.
    
    FilenameC Absolute(bool removeAMD = true) const;
    //: Make an absolute path.
    // If removeAMD is true, any automount prefix will also
    // be remove from the path.
    
    static void SetAMDPrefix(StringC prefix);
    //: Set the AMD prefix.
    
    bool HasExtension(StringC ext,bool caseSens = false) const;
    //: Test if filename has the given extention.
    // caseSens = false means case is ignored.
    
    StringC Extension() const;
    //: Get the extention on the file name.
    // That is the text after the last '.' in the name component.
    // Returns empty string if none found.
    
    FilenameC Search(StringC pathList) const;
    //: Search through ':' seperated list pathList of deriectories
    //: for this filename.
    // Returns this filename if is not found on path.
    
    FilenameC Search(const DListC<StringC> &pathList) const;
    //: Search through a list of paths for this file.
    // Returns this filename if is not found on path.
    // Usefull for searching through the 'PATH' enviroment variable.
    
    inline const FilenameC &operator=(const FilenameC &s);
    //: Assign from filename 
    
    inline const FilenameC &operator=(const StringC &s);
    //: Assign from string.
    
    inline const FilenameC &operator=(const SubStringC &s);
    //: Assign from sub string
    
    inline const FilenameC &operator=(const char *s);
    //: Assign from char string.
    
  protected:
    static StringC AMDPrefix; // Defaults to "/a/"
 };
  
  //////////////////////////////////////////////
  
  inline 
  FilenameC::FilenameC(const char *nname) 
    : StringC(nname)
  {}
  
  inline 
  FilenameC::FilenameC(const StringC &nname) 
    : StringC(nname)
  {}
  
  inline 
  FilenameC::FilenameC(const SubStringC &nname)
    : StringC(nname)
  {}
  
  inline 
  FilenameC::FilenameC(const FilenameC &ano)
    : StringC(ano)
  {}
  
  inline 
  const FilenameC &FilenameC::operator=(const FilenameC &s) {
    StringC::operator= (s);
    return *this;
  }
  
  inline 
  const FilenameC &FilenameC::operator=(const StringC &s) {
    StringC::operator= (s);
    return *this;
  }
  
  inline 
  const FilenameC &FilenameC::operator=(const SubStringC &s) {
    StringC::operator= (s);
    return *this;
  }
  
  inline 
  const FilenameC &FilenameC::operator=(const char *s) {
    StringC::operator= (s);
    return *this;
  }
  
}


#endif
