#ifndef RAVLAUTOPORTGENERATOR_HEADER
#define RAVLAUTOPORTGENERATOR_HEADER 1
///////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/SourceTools/AutoPortSource.hh"
#include "Ravl/Text/TemplateComplex.hh"

namespace RavlN {

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
      return context.Top().fileName; 
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
	  fileName(li.Name()),
	  ctype(1)
	{}
      //: Constructor.

      ContextC(const ProgInfoC &pi)
	: progInfo(pi),
	  fileName(pi.Name()),
	  ctype(2)
	{}
      //: Constructor.
      
      ContextC(const StringC &s)
	: fileName(s),
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
      
      DListC<StringC> Headers() {
	switch(ctype) {
	case 1: return libInfo.Headers();
	  //case 2: return progInfo.Headers();
	}
	return DListC<StringC> ();
      }
      //: Access source list.
      
      LibInfoC libInfo;
      ProgInfoC progInfo;
      StringC fileName;
      int ctype; // 0-file 1-lib 2-Prog 
    };
    
    StackC<ContextC> context;
    StringC target; // Current target.
    StringC filePattern;
    StringC fileObject;
    StringC outputDir;
    AutoPortSourceC src; // Info about source.
  };
  
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
