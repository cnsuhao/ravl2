#ifndef RAVLLIBINFO_HEADER
#define RAVLLIBINFO_HEADER 1
////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/RefCounter.hh"
#include "Ravl/String.hh"
#include "Ravl/DList.hh"

namespace RavlN {

  class DefsMkFileC;
  
  //: Information about library.
  
  class LibInfoBodyC
    : public RCBodyC
  {
  public:
    LibInfoBodyC(const StringC &ln)
      : libName(ln.Copy())
      {}
    //: Constructor.
    
    bool Add(DefsMkFileC &defs,const StringC &fromDir);
    //: Add information from defs file 'defs'.
    // True is returned if operation succeeded.
    
    const StringC &Name() const
      { return libName; }
    //: Get library name.
    
    DListC<StringC> &UsesLibs()
      { return useslibs; }
    //: Libraries required by this one.
    
    DListC<StringC> Sources()
      { return sources; }
    //: Source files in the library.
    
    DListC<StringC> Headers()
      { return headers; }
    //: Headers for the library.
    
  protected:
    StringC libName;
    DListC<StringC> useslibs;// Libraries required by this one.
    DListC<StringC> sources;  // Source files in the library.
    DListC<StringC> headers; // Headers for the library.
  };

  //: Information about library.
  
  class LibInfoC
    : public RCHandleC<LibInfoBodyC>
  {
  public:
    LibInfoC()
      {}
    //: Default constructor,
    // creates an invalid handle.
    
    LibInfoC(const StringC &ln)
      : RCHandleC<LibInfoBodyC>(*new LibInfoBodyC(ln))
      {}
    //: Constructor.
    
    bool Add(DefsMkFileC &defs,const StringC &fromDir)
      { return Body().Add(defs,fromDir); }
    //: Add information from defs file 'defs'.
    // True is returned if operation succeeded.
    
    const StringC &Name() const
      { return Body().Name(); }
    //: Get library name.
    
    DListC<StringC> &UsesLibs()
      { return Body().UsesLibs(); }
    //: Libraries required by this one.
    
    DListC<StringC> Sources()
      { return Body().Sources(); }
    //: Source files in the library.
    
    DListC<StringC> Headers()
      { return Body().Headers(); }
    //: Headers for the library.
    
  };
  
}

#endif
