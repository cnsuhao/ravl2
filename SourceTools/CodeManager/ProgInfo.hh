#ifndef RAVLPROGINFO_HEADER
#define RAVLPROGINFO_HEADER 1
////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/RefCounter.hh"
#include "Ravl/String.hh"
#include "Ravl/DList.hh"

namespace RavlN {

  class DefsMkFileC;
  //: Information about library.
  
  class ProgInfoBodyC
    : public RCBodyC
  {
  public:
    ProgInfoBodyC(const StringC &ln,DefsMkFileC &defs,const StringC &fromDir)
      : progName(ln.Copy())
      { Add(defs,fromDir); }
    //: Constructor.
    
    bool Add(DefsMkFileC &defs,const StringC &fromDir);
    //: Add information from defs file 'defs'.
    // True is returned if operation succeeded.
    
    const StringC &Name() const
      { return progName; }
    //: Get program name.
    
    DListC<StringC> &UsesLibs()
      { return useslibs; }
    //: Libraries required by this one.
    
    DListC<StringC> Sources()
      { return sources; }
    //: Source files in the program.
    
  protected:
    StringC progName;
    DListC<StringC> useslibs;// Libraries required by this one.
    DListC<StringC> sources;  // Source files in the program.
  };

  //: Information about program.
  
  class ProgInfoC
    : public RCHandleC<ProgInfoBodyC>
  {
  public:
    ProgInfoC()
      {}
    //: Default constructor,
    // creates an invalid handle.
    
    ProgInfoC(const StringC &ln,DefsMkFileC &defs,const StringC &fromDir)
      : RCHandleC<ProgInfoBodyC>(*new ProgInfoBodyC(ln,defs,fromDir))
      {}
    //: Constructor.
    
    bool Add(DefsMkFileC &defs,const StringC &fromDir)
      { return Body().Add(defs,fromDir); }
    //: Add information from defs file 'defs'.
    // True is returned if operation succeeded.
    
    const StringC &Name() const
      { return Body().Name(); }
    //: Get program name.
    
    DListC<StringC> &UsesLibs()
      { return Body().UsesLibs(); }
    //: Libraries required by this one.
    
    DListC<StringC> Sources()
      { return Body().Sources(); }
    //: Source files in the program.
    
  };

}

#endif
