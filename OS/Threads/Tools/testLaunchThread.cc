// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Tools/testLaunchThread.cc"

#include "Ravl/Threads/LaunchThread.hh"
#include <unistd.h>
#include <iostream.h>

using namespace RavlN;

int count1 = 0;
int count2 = 0;

class ExampleC
{
public:
  bool DoIt()
    {
      cerr << "Done it. \n";
      count1++;
      return true;
    }
  
  bool DoItArg(int &x)
    {
      cerr << "Done it:" << x << ". \n";
      count2 += x;
      return true;
    }
};

int main()
{
  ExampleC ae;
  LaunchThread(ae,&ExampleC::DoIt);
  LaunchThread(ae,&ExampleC::DoItArg,2);
  sleep(1);
  if(count1 != 1 || count2 != 2) {
    cerr << "Error launching threads. \n";
    return 1;
  }
  cerr << "Test passed ok. \n";
  return 0;
}
