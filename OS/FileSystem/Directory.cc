// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////////////////
//! userlevel=Normal
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlOS
//! file="Ravl/OS/FileSystem/Directory.cc"

// This config stuff should be moved elseware.

#include "Ravl/config.h"

#if RAVL_OS_SOLARIS
#define _POSIX_PTHREAD_SEMANTICS 1
#endif

#include "Ravl/OS/Directory.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/Exception.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/HSet.hh"

#include <stdlib.h>

#ifdef WIN32
#include <windows.h>
#else
#if RAVL_HAVE_UNIXDIRFUNCS
#include <dirent.h>
#endif
#if RAVL_HAVE_UNISTD_H
#include <unistd.h>
#endif
#if !RAVL_HAVE_REENTRANT_UNIXDIRFUNCS
#include "Ravl/MTLocks.hh"
#endif
#endif

#define DPDEBUG 0

#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  static inline bool ReturnInList(const char *nm) {
    if(nm[0] != '.')
      return true;
    if(nm[1] == 0)
      return false; // skip "."
    if(nm[1] == '.')
      if(nm[2] == 0)
	return false;
    return true;
  }
  
  //////////////////////////////////////////////////////
  //: List contents of directory.
  
  DListC<StringC> DirectoryC::List() const  {
#ifdef WIN32
    DListC<StringC> ret;
    WIN32_FIND_DATA dataFind;
    memset(&dataFind, 0, sizeof(WIN32_FIND_DATA));
    StringC strSearch = StringC(chars()) + "/*";
    HANDLE hFindFile = FindFirstFile(strSearch, &dataFind);
    BOOL bFoundNext = hFindFile ? TRUE : FALSE;
    while (bFoundNext) {
      ret.InsLast(StringC(dataFind.cFileName));
      bFoundNext = FindNextFile(hFindFile, &dataFind);
    }
    return ret;
#else
#if RAVL_HAVE_UNIXDIRFUNCS
    DListC<StringC> ret;
    struct dirent *entry;
    DIR *dinf = opendir(chars());
    if(dinf == NULL)
      return ret; // Empty list, open failed.
#if RAVL_HAVE_REENTRANT_UNIXDIRFUNCS
    struct dirent *buff=(dirent *) malloc(sizeof(struct dirent) + pathconf(".",_PC_NAME_MAX)+1); 
    if(buff == 0) {
      closedir(dinf);
      throw ExceptionC("DirectoryC::List(), Failed to allocate buffer.");
    }
    // This seems to work everywhere.
    entry = 0;
    while(1) {
#if RAVL_READDIR_R_NOBUFF
      readdir_r(dinf,buff);
      entry = buff;
#else
      readdir_r(dinf,buff,&entry);
#endif
      if(entry!=buff)
	break;
      if(!ReturnInList(entry->d_name))
	continue;
      ret.InsLast(FilenameC(entry->d_name));
    }
    free(buff);
#else
    // This is non-reentrant, but portable.
    // so we have to do some locking.
    MTWriteLockC lock(2); // It involves modifying global buffers !
    while((entry = readdir(dinf)) != NULL) { 
      if(!ReturnInList(entry->d_name))
	continue;
      ret.InsLast(FilenameC(entry->d_name));
    }
    lock.Unlock(); // Unlock here, we're done.
#endif
    closedir(dinf);
    return ret;
#else
    throw ExceptionC("DirectoryC::List(), Not implemented. ");
#endif

#endif
  }
  
  //////////////////////////////////////////////////////
  //: List contents of directory, returning only files with the given
  //: prefix and postfix.
  // Either (or both) pre and post maybe empty strings..
  // Will return an empty list if anything goes wrong. 
  // This could be faster, we could filter as we build the list. Later.
  
  DListC<StringC> DirectoryC::List(const StringC &pre,const StringC &post) const { 
    DListC<StringC> ret = DirectoryC::List();
    for(DLIterC<StringC> it(ret);it.IsElm();it.Next()) {
      // Filter out files we're not interested in..
      ONDEBUG(cerr << "DirectoryC::List() Testing:" << it.Data() << "\n");
      if(!pre.IsEmpty()) {
	if(!it.Data().contains(pre,0)) {
	  it.Del();
	  continue;
	}
      }
      if(!post.IsEmpty()) {
	if(!it.Data().contains(post,it.Data().length() - post.length())) {
	  it.Del();
	  continue;
	}
      }
    }
    return ret;
  }
  
  //: List contents of directory, returning only files matching
  //: the given filter.
  
  DListC<StringC> DirectoryC::FiltList(const StringC &filter) const {
    DListC<StringC> ret = DirectoryC::List();
    for(DLIterC<StringC> it(ret);it.IsElm();it.Next()) {
      ONDEBUG(cerr << "DirectoryC::FiltList() Testing:" << it.Data() << "\n");
      if(!MatchFilt(filter.chars(),it.Data().chars()))
	it.Del();
    }
    return ret;
  }
  
  //: Simple test if 'x' matches filter.
  // Wild cards are '*','?' and '\' escapes. 
  
  bool DirectoryC::MatchFilt(const char *filt,const char *str) {
    char nextf;
    while(*str != 0) {
      switch(*filt)
	{
	case '*': // Match any sub-string.
	  filt++;
	  nextf = *filt;
	  // Find the next real character in filter.
	  // Could check for '*' or '?' here, but we're but
	  // this routine isn't intended to be that clever.
	  if(nextf == '\\')
	    nextf = *(++filt);
	  // Look for end of substring...
	  for(;*str != 0;str++) {
	    if(*str == nextf && MatchFilt(filt,str))
	      return true; // Found !
	  }
	  return *str == nextf; // Maybe end of filter and string.
	case 0: // End of string ?
	  return false; // If it was end of input we'd never have got here.
	default: // Require exact match.
	  if(*str != *filt)
	    return false;
	  // Fall through.
	case '?': // Match any character.
	  str++;
	  filt++;
	  break;
	}
    }
    return *filt == 0; // Must have found end of input, is filter there as well ?
  }
  
  //: Search a directory tree for files matching 'filter'
  // Returns a list of absolute paths to matching files. The filter
  // is the same as 'FiltList'
  
  DListC<StringC> DirectoryC::SearchTree(const StringC &filter) const {
    DListC<StringC> ret;
    DListC<StringC> list = DirectoryC::List();
    DirectoryC file;  
    for(DLIterC<StringC> it(list);it;it++) {
      ONDEBUG(cerr << "DirectoryC::SearchTree() Testing:" << it.Data() << "\n");
      if(it->lastchar() != '/')
	file = (*this) + '/' + *it;
      else
	file = (*this) + *it;
      if(file.IsDirectory()) {
	DListC<StringC> lst = file.SearchTree(filter);
	ret.MoveLast(lst);
      }
      else { // Don't match directories...
	if(MatchFilt(filter.chars(),it.Data().chars()))
	  ret.InsLast(file);
      }
    }
    return ret;
  }

  /////////////////////////////////////
  //: Copy all files in this directory into 'othDir'.
  // This will make 'othDir' if necissary. When 'rec' is true
  // it will do so recursively, if false sub directories will be
  // ignored.
  
  bool DirectoryC::Copy(const FilenameC &othDir,bool rec,bool lazy,bool sync,bool verb) {
    if(verb)
      cerr << "Copying directory '" << (*this) << "' to '" << othDir << "'\n";
    if(!othDir.Exists()) 
      othDir.MakeDir();
    if(!othDir.IsDirectory()) {
      cerr << "DirectoryC::Copy(), Failed to create '" << othDir << "' \n";
      return false; // Failed.
    }
    bool ret = true;
    HSetC<FilenameC> fileset;
    DListC<StringC> lst(List());
    for(DLIterC<StringC> it(lst);it.IsElm();it.Next()) {
      FilenameC lookat((*this) + '/' + it.Data());
      FilenameC target(othDir + '/' + it.Data());
      if(lookat.IsDirectory()) {
	if(!rec) // Recursive copy ?
	  continue; // Ignore sub-directories
	DirectoryC sub(lookat);
	if(!sub.Copy(othDir + '/' + it.Data(),rec,lazy,sync,verb))
	  ret = false;
	continue;
      }
      if(!lookat.IsRegular()) { // Is it a normal file ??
	cerr << "DirectoryC::Copy(), Ignoring special file : '" << lookat << "'\n";
	continue;
      }
      if(sync)
	fileset.Insert(it.Data());
      // Lazy copy, look at mod times before doing any work.
      if(lazy) {
	if(target.LastModTime() > lookat.LastModTime())
	  continue;
      }
      if(verb)
	cerr << "Copying file '" << lookat << "' to '" << target << "'\n";
      if(!lookat.CopyTo(target)) { // Copy the file.
	cerr << "DirectoryC::Copy(), Failed to copy '" << lookat << "' to '" << target << "' \n";
	return false; // Failed to copy file.
      }
    }
    if(!sync) // Remove old files ?
      return ret;
    // Check all files in target directory should actual be there....
    DirectoryC odir(othDir);
    DListC<StringC> tLst(List());
    for(DLIterC<StringC> it2(tLst);it2.IsElm();it2.Next()) {
      if(fileset.IsMember(it2.Data()))
	continue;
      FilenameC target(othDir + '/' + it2.Data());
      if(verb)
	cerr <<"Deleting old file '" << target << "' \n";
      if(!target.Remove())
	cerr << "DirectoryC::Copy(), Failed to delete '" << target << "' \n";
    }
    return true;
  }
  
}
