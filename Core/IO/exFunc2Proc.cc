////////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id: exFunc2Proc.cc 125 2001-05-21 12:17:49Z craftit $"

#include "Ravl/Option.hh"
#include "Ravl/DP/FileIO.hh"
#include "Ravl/DP/Compose.hh"
#include "Ravl/DP/Func2Proc.hh"
#include "Ravl/DP/Func2Proc2.hh"
#include "Ravl/DP/Func2Stream.hh"
#include "Ravl/DP/ProcMethod.hh"

IntT DoLog(RealT in)
{ return (IntT) (in * 2); }

int main(int argc,char **argv) 
{
  using namespace DPComposeST; // Using single threaded namespace.
  
  OptionC option(argc,argv,true);
  StringC infile = option.String("i","in.dat","Input filename");
  StringC outfile = option.String("o","out.dat","Output filename");
  option.Check();
  
  DPIFileC<RealT>(infile) >> DoLog >> DPOFileC<IntT>(outfile);
  
  //DPIFileC<RealT>(infile) >> DPFunc2ProcC<RealT,RealT,DoLog>() >> DPOFileC<RealT>(outfile);
  
}
