// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////////////////////
//! userlevel=Normal
//! rcsid="$Id: EntryPnt.cc 7711 2010-05-03 11:05:58Z craftit $"
//! date="06/08/95"
//! lib=RavlCore
//! file="Ravl/Core/Base/EntryPnt.cc"

#include "Ravl/EntryPnt.hh"
#include "Ravl/config.h"
#include "Ravl/Exception.hh"
#include <stdlib.h>

#if RAVL_HAVE_ANSICPPHEADERS
#include <iostream>
#if RAVL_HAVE_EXCEPTIONS
#include <exception>
#endif
#else
#if RAVL_HAVE_EXCEPTION_H
#include <exception.h>
#endif
#include <iostream.h>
#endif

//: Main function.

namespace RavlN {
#if RAVL_HAVE_STDNAMESPACE
  using namespace std;
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using std::cerr;
#endif
#endif
  
  extern const char *(*TypeNameMap)(const type_info &type);

  bool usedRavlMain = false;
  
  bool UsingRavlMain()
  { return usedRavlMain; }

  //: Are we using RAVL_ENTRY_POINT.
  // Used to decide how to handle some internal errors.

  int RavlMainDefault(int argc, char* argv[],int (*func)(int argc, char* argv[]))
  {
    usedRavlMain=true;
    int ret;
#if 0
    try {
      ret = func(argc,argv);
    } catch(exception &e) {
      cerr << "C++ Exception :'" << e.what() << "'\n";
      cerr << "Exiting program. \n";
      exit(-1);
    }catch(ExceptionErrorCastC &e) {
      cerr << "Ravl Exception :'" << e.what() << "'\n";
      if(TypeNameMap == 0) {
        cerr << " Casting " << e.From().name() << " to " << e.To().name() << "\n";
      } else {
        cerr << " Casting "
             << TypeNameMap(e.From()) << " (" << e.From().name() << ") to "
             << TypeNameMap(e.To()) << " (" << e.To().name() << ")\n";
      }
      cerr << "Exiting program. \n";
      exit(-1);
    } catch(ExceptionC &e) {
      cerr << "Ravl Exception :'" << e.what() << "'\n";
      cerr << "Exiting program. \n";
      exit(-1);
    } catch(...) {
      cerr << "Unknown exception caught. \n";
      cerr << "Exiting program. \n";
      exit(-1);
    }
#else
    ret = func(argc,argv);    
#endif
    usedRavlMain=false; // As we're not longer inside the catch.
    return ret;
  }

  static FuncMainCallManagerT g_mainCallManager = &RavlMainDefault;

  //: Access current MainCallManager.

  FuncMainCallManagerT RetrieveMainCallManager()
  {
    return g_mainCallManager;
  }

  bool RegisterMainCallManager(FuncMainCallManagerT entryPoint) {
    g_mainCallManager = entryPoint;
    return true;
  }
  //: Register an alternate call to start the main program.
  // This is used on MacOSX where for many libraries expect the main
  // thread to be running in an event loop. It should be registered
  // in the constructor of a static variable to ensure its setup
  // before main() is entered.

  int RavlMain(int argc, char* argv[],int (*func)(int argc, char* argv[])) {
    usedRavlMain = true;
    return g_mainCallManager(argc,argv,func);
  }
}
