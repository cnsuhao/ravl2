// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id: exFailOver.cc 558 2001-11-02 17:15:03Z craftit $"
//! lib=RavlDPMT

#include "Ravl/Option.hh"
#include "Ravl/DP/RunningAve.hh"
#include "Ravl/DP/FileIO.hh"
#include "Ravl/DP/Compose.hh"
#include "Ravl/DP/IFailOver.hh"
#include "Ravl/DP/TaskList.hh"
#include "Ravl/DP/IOConnect.hh"

int main(int argc,char **argv) {  
  using namespace DPComposeST; // Using single threaded namespace.
  
  OptionC option(argc,argv,true);
  FilenameC infile = option.CharArr("i","in.dat","Input filename");
  FilenameC outfile = option.CharArr("o","out.dat","Output filename");
  option.Check();
  DPIFailOverC<RealT> failOver;
  
  DPIFileC<RealT>(infile) >> failOver >> DPRunningAverage(1.0,5) >>= DPOFileC<RealT>(outfile);
  
  DPIFileC<RealT>(infile) >> failOver; // Second input.
  
  //calc.Out1() >> xx >> xxx.Input2();
  
  cout << "Running.\n";
  DPTaskListC::GlobalTaskRun();
  cout << "Done.\n";
  return 1;
}
