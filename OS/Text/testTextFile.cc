// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlOS
//! file="Ravl/OS/Text/testTextFile.cc"
//! author="Charles Galambos"
//! docentry="Ravl.OS.Text Processing"
//! userlevel=Develop

#include "Ravl/Text/TextFile.hh"
#include "Ravl/Text/TextCursor.hh"
#include "Ravl/Text/TemplateFile.hh"
#include "Ravl/StrStream.hh"

using namespace RavlN;

int testTextFile();

int main() {
  int ln;
  if((ln = testTextFile()) != 0) {
    cerr << "Error line " << ln << "\n";
    return 1;
  }
  return 0;
}


int testTextFile() {
  StringC tmp("Greetings");
  StrOStreamC oss;  
  {
    TextFileC txtf(tmp,true,true);
    TemplateFileC tf(txtf ,oss);
    while(tf.IsElm()) {
      StringC &ip = tf.Next();
      if(ip.IsEmpty())
	break;
      cerr << "Got arg! " << ip << "\n";
      return __LINE__;
    }
    oss.os() << flush;
  }
  StringC to = oss.String();
  cerr << "Out='" << to << "'\n";
  if(to != tmp) return __LINE__;  
  return 0;
}
