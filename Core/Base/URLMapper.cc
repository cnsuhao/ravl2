
#include "Ravl/Stream.hh"
#include "Ravl/StreamType.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  extern URLMapperFuncT urlMapper;
  
  //: Map URL's to RAVL special filenames.
  // With the expection of 'file:' specifications this just changes URL's 
  // to a RAVL special file. This allows us to implement handlers in seperate
  // libraries which can link in as required.
  
  static StringC DefaultURLMapper(const StringC &fn) {
    ONDEBUG(cerr << "DefaultURLMapper(), Called on '" << fn << "'\n");
    if(fn.length() < 1)
      return StringC(fn);
    if(fn[0] == '@') // Is this a RAVL special filename ?
      return StringC(fn);
    int sep = fn.index(':');
    if(sep < 0)
      return StringC(fn); // No seperator, take as normal filename.
    SubStringC urltype = StringC(fn).before(sep);
    if(urltype == "file") { // Got a file descriptor.
      SubStringC theRest = StringC(fn).after(sep);
      if(theRest.length() < 2 || theRest[0] != '/')
	return StringC(theRest);
      if(theRest[1] != '/') // Hasn't got an internet qualification.   
	return theRest;
      // Fall through and use 'StreamTypeC' to handle..
    }
    if(StreamTypeC::Find(urltype.chars()) != 0)
      return StringC("@") + urltype + StringC(fn).from(sep); // Turn it into a RAVL stream type.
    cerr << "WARNING: Unsupported URL type '" << urltype << "'. \n";
    return StringC(fn);
  }
  
  //: Enable url mapping of filenames.
  
  bool EnableURLMapper() {
    urlMapper = &DefaultURLMapper;
    return true;
  }
  
  //: Dissable url mapping of filenames.
  
  bool DisableURLMapper() {
    urlMapper = 0;
    return true;
  }
  
}
