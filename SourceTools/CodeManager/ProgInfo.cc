////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/SourceTools/ProgInfo.hh"
#include "Ravl/SourceTools/DefsFile.hh"
#include "Ravl/StringList.hh"
#include "Ravl/OS/Filename.hh"

namespace RavlN {
  
  //: Add information from defs file 'defs'.
  // True is returned if operation succeeded.
  
  bool ProgInfoBodyC::Add(DefsMkFileC &defs,const StringC &dir) {
    if(!defs.IsValid())
      return false;
    sources += dir + filenameSeperator + progName;
    // We could check for duplications here, but there
    // really shouldn't be.
    if(defs["PLIB"] == "") { // Are these just for the exe ?
      StringListC sl(defs["SOURCES"]);
      for(DLIterC<StringC> it(sl);it;it++) 
	sources += dir + filenameSeperator + *it;
    }
    // We need to check for repeated inclusions in USESLIBS.
    useslibs += defs["PLIB"];
    {
      StringListC pl(defs["PROGLIBS"]);
      for(DLIterC<StringC> it(pl);it;it++) {
	if(!useslibs.Contains(*it))
	  useslibs += *it;
      }
    }
    return true;
  }

}
