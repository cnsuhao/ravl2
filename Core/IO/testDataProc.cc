// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/testDataProc.cc"

#include "Ravl/DP/IFailOver.hh"
#include "Ravl/DP/IOTap.hh"
#include "Ravl/DP/Multiplex.hh"
#include "Ravl/DP/SplitO.hh"
#include "Ravl/DP/FileIO.hh"
#include "Ravl/DP/Compose.hh"
#include "Ravl/DP/ContainerIO.hh"
#include "Ravl/StrStream.hh"

using namespace RavlN;

int testSimple(); 
int testMultiplex();
int testContainerIO();

int main(int nargs,char **argv) {
  int ln;
  if((ln = testSimple()) != 0) {
    cerr << "Error in testSimple(), Line:" << ln << "\n";
    return 1;
  }
  if((ln = testMultiplex()) != 0) {
    cerr << "Error in testMultiplex(), Line:" << ln << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}


RealT MultiplyBy2(const RealT &val)
{ return val * 2; }

int testSimple() {  
  StrOStreamC ostr;
  StrIStreamC src("1 2 3 4");
  DPIFileC<RealT>(src) >>  Process(MultiplyBy2) >> DPOFileC<RealT>(ostr);
  StringC result = ostr.String();
  if(result != "2\n4\n6\n8\n") return __LINE__;
  return 0;
}


int testContainerIO() {
  DListC<IntT> lst1;
  DListC<IntT> lst2;
  lst1.InsLast(1);
  lst1.InsLast(2);
  lst1.InsLast(3);
  DPIContainer(lst1) >> DPOContainer(lst2);
  if(lst2.Size() != 3) return __LINE__;
  if(lst2.First() != lst1.First()) return __LINE__;
  if(lst2.Last() != lst1.Last()) return __LINE__;
  return 0;
}

int testMultiplex() {  
#if 0
  StrOStreamC ostr;
  StrIStreamC src("1 2 3 4");
  DPIFileC<RealT>(src) >>  DPMultiplex(1,Process(MultiplyBy2)) >> DPOFileC<RealT>(ostr);
  StringC result = ostr.String();
  if(result != "2\n4\n6\n8\n") return __LINE__;
#endif
  return 0;
}
