// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Base/testString.cc"

#include "Ravl/String.hh"

using namespace RavlN;

int testString();
int testSubString();

int main()
{
  int no;
  if((no = testString()) > 0) {
    cerr << "Basic test failed line :" << no << "\n";
    return 1;
  }
  if((no = testSubString()) > 0) {
    cerr << "Basic test failed line :" << no << "\n";
    return 1;
  }
  cerr << "Test passed ok .\n";
  return 0;
}

int testString() {  
  StringC hello("hello");
  if(hello.length() != 5) 
    return __LINE__;
  if(hello.index('h') != 0)
    return __LINE__;
  if(hello.index("ll") != 2)
    return __LINE__;
  if(hello != "hello")
    return __LINE__;
  if(StringC(" one  ").TopAndTail() != "one")
    return __LINE__;
  if(StringC("one").TopAndTail() != "one")
    return __LINE__;
  {
    StringC test(" * * * ");
    test.gsub("*","Hello");
    if(test.freq("Hello") != 3) return __LINE__;
  }
  return 0;
}

int testSubString() {
  StringC hello("hello");
  SubStringC ss = hello;
  if(ss.length() != 5) 
    return __LINE__;
  if(ss != hello)
    return __LINE__;
  if(!(ss == hello))
    return __LINE__;
  if(ss.index('l') != hello.index('l'))
    return __LINE__;
  if(hello.index("ll") != 2)
    return __LINE__;
  ss = hello.after(0);
  if(ss != "ello") {
    return __LINE__;
  }
  if(ss != hello.from(1))
    return __LINE__;
  if(ss.index("ll") != 1)
    return __LINE__;
  if(ss.length() != 4)
    return __LINE__;
  ss = ss.before(3);
  if(ss.length() != 3)
    return __LINE__;
  if(ss != "ell") 
    return __LINE__;
  if(ss.firstchar() != 'e')
    return __LINE__;
  if(ss.lastchar() != 'l')
    return __LINE__;
  if(ss.index('h') >= 0)
    return __LINE__;
  if(ss.index('o') >= 0)
    return __LINE__;
  if(ss.index("lo") >= 0)
    return __LINE__;
  if(ss.index("he") >= 0)
    return __LINE__;
  if(ss.index("ell") != 0)
    return __LINE__;
  if(ss.index(StringC("ll")) != 1)
    return __LINE__;
  if(ss.index(hello.after(2).before(1)) != 1)
    return __LINE__;

  StringC org = ss;
  if(org != ss)
    return __LINE__;
  if(ss == hello)
    return __LINE__;
  if(SubStringC(" one  ").TopAndTail() != "one")
    return __LINE__;
  if(SubStringC("one").TopAndTail() != "one")
    return __LINE__;
  return 0;
}
