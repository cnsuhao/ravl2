// This file is part of VCPP, Visual C++ porting tool for QMake projects 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
#ifndef RAVL_AUTOPORTGENERATOR_HEADER
#define RAVL_AUTOPORTGENERATOR_HEADER 1
///////////////////////////////////////////////////////
//! docentry="Ravl.Source Tools.AutoPort"
//! rcsid="$Id$"
//! file="Ravl/SourceTools/VisualCPP/AutoPortGenerator.hh"

#include "Ravl/SourceTools/AutoPortSource.hh"
#include "Ravl/Text/TemplateComplex.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Auto port engine
  
  class AutoPortGeneratorBodyC 
    : public TemplateComplexBodyC
  {
  public:
    AutoPortGeneratorBodyC(AutoPortSourceC &src,StringC &templ,StringC &output);
    //: Constructor.
    
    bool BuildFiles();
    //: Build output files.
    
  protected:
    void Init();
    //: Setup template stuff.
    
    bool Forall(StringC &data);
    //: For all template function.
    
    bool dos(StringC &data);
    //: Generate a DOS filename.
    
    virtual bool Lookup(const StringC &varname,StringC &buff);
    //: Lookup variable.
    // if found put value into 'buff' and return true.
    // otherwise return false.
    
    StringC MakeFilename(const StringC &obj);
    //: Make a file name for an object using filePattern.
    
    StringC &CurFilename() { 
      RavlAssert(!context.IsEmpty());
      //cerr << "CurFilename() = " << context.Top().hdrInfo.SrcFile() << "\n";
      return context.Top().hdrInfo.SrcFile(); 
    }
    //: Access info about current filename.

    StringC &CurName() { 
      RavlAssert(!context.IsEmpty());
      //cerr << "CurFilename() = " << context.Top().hdrInfo.SrcFile() << "\n";
      return context.Top().hdrInfo.Name(); 
    }
    //: Access info about current filename.
    
    LibInfoC &CurLibInfo() {
      RavlAssert(!context.IsEmpty());
      return context.Top().libInfo;
    }
    //: Access info about current lib.
    
    class ContextC {
    public:
      ContextC(const LibInfoC &li)
	: libInfo(li),
	  hdrInfo(li.Name()),
	  ctype(1)
      {}
      //: Constructor.

      ContextC(const ProgInfoC &pi)
	: progInfo(pi),
	  hdrInfo(pi.Name(),StringC(),pi.MainSource()),
	  ctype(2)
      {}
      //: Constructor.
      
      ContextC(const StringC &s)
	: hdrInfo(s,StringC(),s),
	  ctype(0)
      {}
      //: Constructor.

      ContextC(const HeaderInfoC &hi)
	: hdrInfo(hi),
	  ctype(0)
      {}
      //: Constructor.
      
      DListC<StringC> Sources() {
	switch(ctype) {
	case 1: return libInfo.Sources();
	case 2: return progInfo.Sources();
	}
	return DListC<StringC> ();
      }
      //: Access source list.
      
      DListC<StringC> UsesLibs() {
	switch(ctype) {
	case 1: 
	  if(!libInfo.IsValid()) return DListC<StringC>();
	  return libInfo.UsesLibs();
	case 2: 
	  if(!progInfo.IsValid()) return DListC<StringC>();
	  return progInfo.UsesLibs();
	}
	return DListC<StringC>();
      }
      //: Access useslibs list.
      
      DListC<HeaderInfoC> Headers() {
	switch(ctype) {
	case 1: return libInfo.Headers();
	  //case 2: return progInfo.Headers();
	}
	return DListC<HeaderInfoC> ();
      }
      //: Access source list.
      
      HeaderInfoC &HeaderInfo() {
	return hdrInfo;
      }
      //: Access header info.
      
      LibInfoC libInfo;
      ProgInfoC progInfo;
      HeaderInfoC hdrInfo;
      int ctype; // 0-file 1-lib 2-Prog 
    };
    
    StackC<ContextC> context;
    StringC target; // Current target.
    StringC filePattern;
    StringC fileObject;
    StringC outputDir;
    AutoPortSourceC src; // Info about source.
  };
  
  //! userlevel=Normal
  //: Auto port engine
  
  class AutoPortGeneratorC 
    : public TemplateComplexC
  {
  public:
    AutoPortGeneratorC()
    {}
    //: Default constructor.
    // creates an invalid handle.

    AutoPortGeneratorC(AutoPortSourceC &src,StringC &templ,StringC &output)
      : TemplateComplexC(*new AutoPortGeneratorBodyC(src,templ,output))
    {}
    //: Constructor.
    
  protected:
    AutoPortGeneratorBodyC &Body()
    { return static_cast<AutoPortGeneratorBodyC &>(TemplateComplexC::Body()); }
    //: Access body.

    const AutoPortGeneratorBodyC &Body() const
    { return static_cast<const AutoPortGeneratorBodyC &>(TemplateComplexC::Body()); }
    //: Access body.
    
  public:

    bool BuildFiles()
    { return Body().BuildFiles(); }
    //: Build output files.
    
  };

}
#endif
