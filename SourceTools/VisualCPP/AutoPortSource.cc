// This file is part of VCPP, Visual C++ porting tool for QMake projects 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/SourceTools/VisualCPP/AutoPortSource.cc"

#include "Ravl/SourceTools/AutoPortSource.hh"
#include "Ravl/SourceTools/SourceCodeManager.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/CallMethods.hh"
#include <fstream.h>

namespace RavlN {
  
  //: Constructor.
  
  AutoPortSourceBodyC::AutoPortSourceBodyC(StringC &where)
    : verbose(false)
  {
  }
  
  //: Scan a tree for info.
  
  bool AutoPortSourceBodyC::ScanTree(StringC &where) {
    SourceCodeManagerC chkit(where);
    if(verbose)
      chkit.SetVerbose(true);
    chkit.ForAllDirs(CallMethod2C<AutoPortSourceC,StringC,DefsMkFileC,bool>(AutoPortSourceC(*this) ,
									    &AutoPortSourceC::ScanDirectory));
    return true;
  }

  //: Scan the contents of a directory.
  
  bool AutoPortSourceBodyC::ScanDirectory(StringC &where,DefsMkFileC &defs) {
    if(verbose)
      cerr << "Scanning '" << where << "'\n";
    // Check this directory supports VCPP.
    if(defs.Value("DONOT_SUPPORT").contains("VCPP")) 
      return true;
    StringC supportOnly = defs.Value("SUPPORT_ONLY");
    if(!supportOnly.IsEmpty()) {
      if(!supportOnly.contains("VCPP")) 
	return true;
    }
    
    StringC libName = defs["PLIB"];
    if(!libName.IsEmpty()) {
      LibInfoC &li = libs[libName];
      if(!li.IsValid()) // Need to create it?
	li = LibInfoC(libName);
      li.Add(defs,where);
    }
    {
      StringListC lmains(defs["MAINS"]);
      for(DLIterC<StringC> it(lmains);it;it++) 
	mains += ProgInfoC(*it,defs,where);
    }
    {
      StringListC lexam(defs["EXAMPLES"]);
      for(DLIterC<StringC> it(lexam);it;it++) 
	examples += ProgInfoC(*it,defs,where);
    }
    {
      StringListC ltests(defs["TESTEXES"]);
      for(DLIterC<StringC> it(ltests);it;it++) 
	tests += ProgInfoC(*it,defs,where);
    }
    return true;
  }

  //: Update a file.
  // vcpp, is the file in the Visual C++ tree.
  // src, is the unix version. <p>

  bool AutoPortSourceBodyC::Unix2Dos(const StringC &src,const StringC &vcpp) {
    // Install new files.
    FilenameC srcFn(src);
    if(!srcFn.Exists()) {
      cerr << "WARNING: Can't find src file : " << srcFn << "\n";
      return false;
    }
    FilenameC vcppFn(vcpp);
    
    if(vcppFn.Exists()) {
      if(vcppFn.LastModTime() > srcFn.LastModTime())
	return true; // File is upto date.
    }
    // Check the destination is writeable.
    
    if(vcppFn.Exists()) {
      if(!vcppFn.IsWritable()) {
	FilePermissionC perm = vcppFn.Permissions();
	perm.SetUserReadWrite(); // Make sure user has read/write.
	if(!vcppFn.SetPermissions(perm)) {
	  cerr << "ERROR: Failed to get write permission for file : " << vcpp << "\n";
	  return false;
	}
      }
    }
    // Do the copy.
    if(!srcFn.CopyTo(vcpp)) {
      cerr << "ERROR: Failed to update file : " << vcpp << "\n";
      return false;
    }
    return true;
  }
  
  //: Update a file.
  // vcpp, is the file in the Visual C++ tree.
  // src, is the unix version. <p>
  
  bool AutoPortSourceBodyC::Dos2Unix(const StringC &src,const StringC &vcpp) {    
    FilenameC vcppFn(vcpp);
    if(!vcppFn.Exists()) {
      cerr << "ERROR: Failed to checkout file " << src << " for update. \n";
      return false;
    }
    ifstream in1(vcpp);
    ofstream in2(src);
    if(!in1) {
      cerr << "ERROR: Failed to open file :" << vcpp << " for update." <<endl;
      return false;
    }
    if(!in2) {
      cerr << "ERROR: Failed to open file :" << src << " for update." << endl;
      return false;
    }
    
    // As we all know DOS has additional junk \CR\LF
    // this neatly removes them on the way back to Unix
    // (they are not inserted on the way there)
    
    const int buffsize = 4096;
    char buff[buffsize];
    do {
      in1.read(buff,buffsize);
      int at = 0;
      char *place = buff;
      char *start = buff;
      char *end = &buff[in1.gcount()];
      for(;place != end;place++) {
	if(*place == 0x0d) { // Cut out these chars.
	  if(at != 0) 
	    in2.write(start,at); // Write upto here.
	  start = place;
	  start++; // Skip this char.
	  at = 0;
	} else
	  at++;
      }
      in2.write(start,at); // Write out the rest.
    } while(in1) ;
    
    return true;
  }

  

}
