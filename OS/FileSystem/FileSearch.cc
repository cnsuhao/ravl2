// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlOS
//! file="Ravl/OS/FileSystem/FileSearch.cc"

#include "Ravl/OS/Filename.hh"
#include "Ravl/StringList.hh"
#include "Ravl/CDLIter.hh"

namespace RavlN {
  
  //: Search through a list of paths for this file.
  // Returns this filename if is not found on path.
  
  FilenameC FilenameC::Search(const DListC<StringC> &dirs) const  {
    for(DLIterC<StringC> it(dirs);it.IsElm();it.Next()) {
      FilenameC tmp(it.Data() + "/" + (*this));
      if(tmp.Exists())
	return tmp;
    }
    return (*this).Copy();  
  }
  
  //: Search through ':' seperated list pathList of deriectories
  //: for filename.
  // Returns full path to file, or empty string if none.
  
  FilenameC FilenameC::Search(StringC pathList) const {
    return Search(StringListC(pathList,":"));
  }
}
