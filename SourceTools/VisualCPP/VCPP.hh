#ifndef RAVLVCPP_HEADER
#define RAVLVCPP_HEADER 1
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="amma/Util/VisualCPP/VCPP.hh"
//! lib=SysUtil
//! userlevel=Normal
//! author="Charles Galambos"
//! date="28/09/98"
//! docentry="Utilities.Misc"

#include "Ravl/Hash.hh"
#include "Ravl/DList.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/Stream.hh"
#include "Ravl/SourceTools/SourceCodeManager.hh"

namespace RavlN {
  class RCSFileC;
  
  // -----------------------------------------------------------------------------
  //: Convert defs.mk to Visual C++ make format.
  // ConvertVCPP is a utility designed to take a Ravl style src tree with 
  // defs.mk files and generate a tree suitable to compilation under 
  // Visual C++ with workspace and project files.
  //
  // There is also a 'putback' option which enables files in this tree
  // to be copied 'backwards' if changes need to be propagated back onto Unix.
  //
  // The necessary files are the workspace file, produced as Ravl.dsw in
  // the root directory and a series of project files which are complex
  // and contain a variety of switches and libraries. Project files
  // which can be created are "static library" and "console application" 
  //
  // To create new template files get them from Visual then
  //   - replace any $(CFG) by $$(CFG)
  //   - replace explicit paths by 
  //       $(PROJECT_NAME)
  //       $(TEMP_PATH)
  //       $(VCPP_SRC_ROOT)
  //       $(ALL_THE_SRC_FILES)
  //
  // TAKE EXTRA CARE WITH DOS STYLE \r\n - IT MATTERS!
  // 
  // Notes on meaning of VCPP compile switches:
  //          .....
  
  //
  // There are 3 major tasks to perform
  //
  // (1) LoadNested(..); (baseclass)
  // read the defs files and load info on all the unix src files
  //
  // (2) DoNested(...);  (baseclass)
  // goes thru all the files and calls DoOp as provided in ConvertVCPP
  // i.e. all the file copying forward or backwards
  //
  // (3) CreateProjectFiles();
  //     CreateWorkspaceFile();
  //
  
  
  // -----------------------------------------------------------------------------
  
  class ConvertVCPPC
  {
  public:
    
    ConvertVCPPC(StringC nDir,StringC nRoot,StringC nWork,
		StringC ndosdrive, StringC ndospath, StringC ndostemp,
		bool pback, bool doexecs, bool doone,
		bool Enabled = true);
    // Constructor
    // nDir      : is the directory in which a defs.mk file will be loaded, this
    //             defines the unix src tree
    // nRoot     : is the unix directory where the VCPP workspace will be written to (read from)
    // nWork     : is the unix directory where the VCPP src files will be written to (read from)
    // pback     : when true the operation is run in reverse
    // ndosdrive : dos drive letter, no colon
    // ndospath  : dos path, should start without and end without a /, unix / not dos \ OK
    // ndostemp  : dos path for temp, e.g. D:/temp
    // Enabled   : ??
    
    
    bool DoOp();
    //: The is called for each directory in the unix src tree.
    // It should return  true=Continue,  FALSE=Abort.
    // 
    // 1. makes sures all directories exist
    // 2. changes vcpp filenames to lower case
    
    bool Update(StringC vcpp,RCSFileC &mainLine);
    //: Given the VCPP filename (on a unix disk) and the Ravl filename this 
    // routine does the forward or reverse copy.
    // - the latest Ravl src is checked out
    // - on the way back to unix \LF characters are stripped
    
    void CreateProjectFiles(const StringC & StaticLibTemplate,
			    const StringC & ConsoleAppTemplate);
    //: Create the project files .dsp. 
    // Template files must be provided
    // A project is either a static library or a console application
    
    void CreateWorkspaceFile();
  //: Create the workspace file Ravl.dsw and Proj.lst
    
    void CreateRAVLported(const StringC & StaticLibTemplate, const StringC & RAVLported);
    //: This creates an RAVLported.dsw workspace file of all successfully RAVL ported libraries 
    // If you want to add a ported library to the list edit the RAVLported file in the source dir
    
  protected:
    
    StringC root;   // Root of output.
    StringC work;   // Current output directory.
    
    StringC dosdrive; // e.g. d
    StringC dospath;  // e.g. /user/me/Ravl/thisworkspace
    // so the total dos path will be d:/user/me/Ravl/thisworkspace
    // it is assumed the VCPP is always happy with unix / not dos slash
    StringC dostemp;  // e.g. d:/temp
    StringC arrow;    // Which way we are going ?
    
    bool putBack; // Put files back.
    bool execs;   // do the executables as well, one project per executable
    bool one;     // one library
  }; 

}
#endif

// -----------------------------------------------------------------------------
