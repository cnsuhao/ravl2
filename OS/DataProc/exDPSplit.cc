// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlDPMT

#include "Ravl/Option.hh"
#include "Ravl/DP/RunningAve.hh"
#include "Ravl/DP/FileIO.hh"
#include "Ravl/DP/OffsetScale.hh"
#include "Ravl/DP/Compose.hh"
#include "Ravl/DP/SplitI.hh"
#include "Ravl/DP/TaskList.hh"

int main(int argc,char **argv) {  
  OptionC option(argc,argv,true);
  FilenameC infile = option.CharArr("i","in.dat","Input filename");
  FilenameC outfile = option.CharArr("o","out.dat","Output filename");
  option.Check();
  DPSplitIC<RealT> split;
  
  DPIFileC<RealT>(infile) >> split >> DPOffsetScale(2.0,2.0) >> DPRunningAverage(1.0,5) >>= DPOFileC<RealT>(outfile);
  split >> DPOffsetScale(2.0,2.0) >>= DPOFileC<RealT>(outfile+".xxx");

  //calc.Out1() >> xx >> xxx.Input2();
  
  DPTaskListC::GlobalTaskRun();

  return 1;
}
