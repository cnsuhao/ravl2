// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Base/Exception.cc"

#include "Ravl/Exception.hh"

#if RAVL_HAVE_ANSICPPHEADERS
#include <iostream>
#include <typeinfo>
#else
#include <iostream.h>
#include <typeinfo.h>
#endif

namespace RavlN {
  
  //: Constructor
  
  ExceptionC::ExceptionC(const char *ntext,bool copy)
    : desc(ntext),
      ref(copy)
  {
    //cerr << "String: '" << ntext << "'\n";
    if(!copy)
      
      return;
    char *place = const_cast<char *>(ntext);
    // How long is the string ?
    int len = 1;
    for(;*place != 0;place++,len++) ;
    char *str = new char[len];
    // Copy it.
    desc = str;
    for(place = str;*ntext != 0;place++,ntext++) 
      *place = *ntext;
    *place = 0;
    //  cerr << "Stored: '" << desc << "'\n";
  }
  
  //: Virtualise destructor.
  
  ExceptionC::~ExceptionC()  {
    if(ref)
      delete [] desc;
  }
  
  //: Dump contents of exception to cerr;
  
  void ExceptionC::Dump(ostream &out) {
    out << "Ravl Exception:" << desc << endl;
  }


  //: Dump contents of exception to cerr;
  
  void ExceptionErrorCastC::Dump() {
    cerr << "RAVL Exception: Illegal cast. \n";
    cerr << " From:" << from.name() << endl;
    cerr << "   To:" << to.name() << endl;
    cerr << " Desc:" << desc << endl << endl;
  }
  
}
