// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ENTRYPNT_HEADER
#define RAVL_ENTRYPNT_HEADER 1
//////////////////////////////////////////////////////////////////////////////
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.API.Core.Misc"
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Base/EntryPnt.hh"
//! date=""

// This head add makes sure all Ravl exceptions are caught and
// given to the user.  This avoids anonymous exits from the program.

namespace RavlN {  
  bool UsingRavlMain();
  //: Are we using RAVL_ENTRY_POINT.
  // Used to decide how to handle some internal errors.
  
  int RavlMain(int argc, char* argv[],int (*func)(int argc, char* argv[]));
  //: Call through function.
}

#define RAVL_ENTRY_POINT(Function)      \
  int main(int argc, char* argv[])     \
  { return RavlN::RavlMain(argc,argv,Function); }



#endif
