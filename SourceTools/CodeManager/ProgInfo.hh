// This file is part of CxxDoc, The RAVL C++ Documentation tool 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
#ifndef RAVLPROGINFO_HEADER
#define RAVLPROGINFO_HEADER 1
////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Source Tools"
//! lib=RavlSourceTools
//! userlevel=Normal
//! file="Ravl/SourceTools/CodeManager/ProgInfo.hh"

#include "Ravl/RefCounter.hh"
#include "Ravl/String.hh"
#include "Ravl/DList.hh"

namespace RavlN {

  class DefsMkFileC;
  
  //! userlevel=Develop
  //: Information about library.
  
  class ProgInfoBodyC
    : public RCBodyC
  {
  public:
    ProgInfoBodyC(const StringC &ln,DefsMkFileC &defs,const StringC &fromDir);
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
    StringC progName; // Unqualitified program name, (Has code extention though.)
    DListC<StringC> useslibs;// Libraries required by this one.
    DListC<StringC> sources;  // Source files in the program (fully qualified names).
  };

  //! userlevel=Normal
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
