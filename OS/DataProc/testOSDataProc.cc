// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlDPMT
//! file="Ravl/OS/DataProc/testOSDataProc.cc"
//! docentry="Ravl.Core.Data Processing.Threads"
//! author="Charles Galambos"
//! userlevel=Develop

#include "Ravl/DP/ThreadPipe.hh"
#include "Ravl/DP/MTIOConnect.hh"
#include "Ravl/DP/Blackboard.hh"
#include "Ravl/BufStream.hh"
#include "Ravl/BinStream.hh"

using namespace RavlN;

template class DPThreadPipeC<IntT,IntT>;
template class DPMTIOConnectC<IntT>;

int testThreadPipe();
int testBlackboard();

int main() {
  int ln;
  if((ln = testThreadPipe()) != 0) {
    cerr << "Error on line " << ln << "\n";
    return 1;
  }
  if((ln = testBlackboard()) != 0) {
    cerr << "Error on line " << ln << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

int testThreadPipe() {
  cerr << "testThreadPipe() Called. \n";
  //...
  return 0;
}

int testBlackboard() {
  cerr << "testBlackboard() Called. \n";
  BlackboardC bb(true);
  IntT bval = 1;
  bb.Put("Hello",bval);
  IntT ival = 0;
  if(!bb.Get("Hello",ival)) return __LINE__;
  if(ival != (IntT) bval) return __LINE__;
  
  cerr << "Saving blackboard. \n";
  BufOStreamC bos;
  {
    BinOStreamC os(bos);
    os << bb;
  }
  cerr << "Loading blackboard. \n";
  BufIStreamC bis(bos.Data());
  BinIStreamC is(bis);
  BlackboardC bb2;
  is >> bb2;
  cerr << "Done.. \n";
  ival = 0;
  if(!bb2.Get("Hello",ival)) return __LINE__;
  if(ival != (IntT) bval) return __LINE__;
  
  return 0;
}
