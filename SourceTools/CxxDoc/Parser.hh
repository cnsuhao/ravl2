// This file is part of CxxDoc, The RAVL C++ Documentation tool 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
#ifndef RAVLCXXPARSER_HEADER
#define RAVLCXXPARSER_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/SourceTools/CxxDoc/Parser.hh"
//! userlevel=Normal
//! docentry="Ravl.Source Tools.CxxDoc"
//! lib=RavlCxxDoc
//! author="Charles Galambos"
//! date="06/12/99"

#include "Ravl/String.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/CxxDoc/Object.hh"
#include "Ravl/CxxDoc/CxxScope.hh"

class FlexLexer;

namespace RavlCxxDocN
{
  using namespace RavlN;

#if RAVL_VISUALCPP_NAMESPACE_BUG  
  using RavlN::RCBodyC;
  using RavlN::FilenameC;
  using RavlN::RCHandleC;
#endif
  
  //! userlevel=Develop
  //: C++ File Parser
  
  class ParserBodyC
    : public RCBodyC
  {
  public:
    ParserBodyC();
    //: Constructor.
    
    bool Parse(const FilenameC &fn);
    //: Parse a file.

    bool ParseTree(const FilenameC &fn);
    //: Parse a directory.
    
    int NextToken();
    //: Get the next token;

    int LineNo();
    //: Get current lineno
    
    const FilenameC &CurrentFilename() const { return curFilename; }
    //: Get current filename.
    
    void Dump(ostream &out);
    //: Dump database to 'out'
    
    ObjectListC &Data()
      { return data; }
    //: Access parsed data.

    bool Resolve();
    //: Resolve refrences in input data.
    
  protected:
    bool ParseOuter();
    //: Do top level parse.
    
    FlexLexer *lex; // Ptr because its really an external class.
    
    FilenameC curFilename;
    FilenameC rootFilename; // Directory where the search started.
    ScopeC data;
  };
  
  //! userlevel=Normal
  //: C++ File Parser
  
  class ParserC
    : public RCHandleC<ParserBodyC>
  {
  public:
    ParserC(bool)
      : RCHandleC<ParserBodyC>(*new ParserBodyC())
      {}
    //: Constructor.  
    
    bool Parse(const FilenameC &fn)
      { return Body().Parse(fn); }
    //: Parse a file.
    
    bool ParseTree(const FilenameC &fn)
      { return Body().ParseTree(fn); }
    //: Parse a directory.

    void Dump(ostream &out)
      { Body().Dump(out); }
    //: Dump database to 'out'
    
    ObjectListC &Data()
      { return Body().Data(); }
    //: Access parsed data.
    
    bool Resolve()
      {  return Body().Resolve(); }
    //: Resolve refrences in input data.
    
  };
  
}


#endif


