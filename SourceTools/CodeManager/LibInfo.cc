///////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/SourceTools/LibInfo.hh"
#include "Ravl/SourceTools/DefsFile.hh"
#include "Ravl/StringList.hh"
#include "Ravl/OS/Filename.hh"

namespace RavlN {
  
  //: Add information from defs file 'defs'.
  // True is returned if operation succeeded.
  
  bool LibInfoBodyC::Add(DefsMkFileC &defs,const StringC &dir) {
    if(!defs.IsValid())
      return false;
    if(defs["PLIB"] != libName) {
      return false;
    }
    // We could check for duplications here, but there
    // really shouldn't be.
    {
      StringListC sl(defs["SOURCES"]);
      for(DLIterC<StringC> it(sl);it;it++) 
	sources += dir + filenameSeperator + *it;
    }
    {
      StringListC hl(defs["HEADERS"]);
      for(DLIterC<StringC> it(hl);it;it++) 
	headers += dir + filenameSeperator + *it;
    }
    // We need to check for repeated inclusions in USESLIBS.
    {
      StringListC ul(defs["USESLIBS"]);
      for(DLIterC<StringC> it(ul);it;it++) {
	if(*it == libName)
	  continue; // Don't make a circular dependancy.
	if(!useslibs.Contains(*it))
	  useslibs += *it;
      }
    }
    return true;
  }
 
}
