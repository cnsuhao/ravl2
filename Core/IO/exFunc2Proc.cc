////////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"

#include "amma/Option.hh"
#include "amma/DP/FileIO.hh"
#include "amma/DP/Compose.hh"
#include "amma/DP/Func2Proc.hh"
#include "amma/DP/Func2Proc2.hh"
#include "amma/DP/Func2Stream.hh"
#include "amma/DP/ProcMethod.hh"

IntT DoLog(RealT in)
{ return (IntT) (in * 2); }

int main(int argc,char **argv) 
{
  using namespace DPComposeST; // Using single threaded namespace.

  OptionC option(argc,argv,TRUE);
  FilenameC infile = option.String("i","in.dat","Input filename");
  FilenameC outfile = option.String("o","out.dat","Output filename");
  option.Check();
  
  DPIFileC<RealT>(infile) >> DoLog >> DPOFileC<IntT>(outfile);
  
  //DPIFileC<RealT>(infile) >> DPFunc2ProcC<RealT,RealT,DoLog>() >> DPOFileC<RealT>(outfile);
  
}
