// This file is part of CxxDoc, The RAVL C++ Documentation tool 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
#ifndef RAVLLIBINFO_HEADER
#define RAVLLIBINFO_HEADER 1
////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! lib=RavlSourceTools

#include "Ravl/RefCounter.hh"
#include "Ravl/String.hh"
#include "Ravl/DList.hh"

namespace RavlN {

  class DefsMkFileC;

  //: Header info. 
  // All you wanted to know about header files, but where
  // afraid to ask.
  
  class HeaderInfoC {
  public:
    HeaderInfoC(const StringC &nname,const StringC &pack = StringC(),const StringC &nsrc = StringC())
      : name(nname),
      package(pack),
      src(nsrc)
      {}
    //: Constructor.
    
    StringC &Name()
      { return name; }
    //: Name of headerfile (without path.)
    
    StringC &Package()
      { return package; }
    //: Where is should be installed.
    
    StringC &SrcFile()
      { return src; }
    //: Where it is in the source tree.
    
  protected:
    StringC name;    // Name of headerfile (without path.)
    StringC package; // Where is should be installed.
    StringC src;     // Where it is in the source tree.
  };
  
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
    
    DListC<HeaderInfoC> Headers()
      { return headers; }
    //: Headers for the library.
    
  protected:
    StringC libName;
    DListC<StringC> useslibs;// Libraries required by this one.
    DListC<StringC> sources;  // Source files in the library.
    DListC<HeaderInfoC > headers; // Headers for the library.
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
    
    DListC<HeaderInfoC> Headers()
      { return Body().Headers(); }
    //: Headers for the library.
    
  };
  
}

#endif
