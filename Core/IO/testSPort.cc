// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/testSPort.cc"

#include "Ravl/DP/SPortAttach.hh"
#include "Ravl/DP/MethodIO.hh"

using namespace RavlN;

int TestSPort();

int main()
{
  // Do a quick check that things compile.
  
  int ln;
  if((ln = TestSPort()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  cerr << "Test completed ok.\n";
  return 0;
}

class TestC {
public:
  TestC()
    : i(0)
  {}
  
  int Seq()
  { return i++; }

  int i;
};

TestC tc;

int TestSPort() {  
  DPIPortC<int> ip = IMethod(tc,&TestC::Seq);
  DPISPortAttachC<int> sip(ip,true);
  DPISPortC<int> x(sip);
  if(!x.IsValid()) return __LINE__;
  DPIPortC<int> pip(sip);
  DPSeekCtrlC asc(x);
  if(!asc.IsValid()) return __LINE__;
  DPSeekCtrlC asc3(pip);
  if(!asc3.IsValid()) return __LINE__;
  DPSeekCtrlC asc2(ip);
  if(asc2.IsValid()) return __LINE__;
  return 0;
}
