// IAPS - Image analysis program system
//
// File name  : exUsefFn.cc
// Description: an example of usage of useful functions
// Last change: 26.04.1994
// Author     : Radek Marik
// Libraries  : iaps
// -----------------------------------------------------------------------
//
//
// Modifications:
//
//
//
//

#include <iostream.h>
#include "amma/StdIAPS.hh"
#include "amma/StdStrm.hh"
#include "amma/UsefulFn.hh"
#include "amma/StdConst.hh"
#include "amma/StdMath.hh"

double GetZero(); // Needed to avoid warning.

int 
main(void)
//========
{
  coutAMMA << "Useful functions\n"
           << "================\n";

  IntT i = 1;
  IntT j = 2;
  coutAMMA << " i = " << i << "; j = " << j << '\n';
  AMMA_Swap(i,j);
  coutAMMA << " i = " << i << "; j = " << j << '\n';
  
  if(!IsNan(0) && IsNan(StdConstC::nanReal))
    cerr << "IsNan() ok. \n" << flush;
  else {
    cerr << "IsNan() failed. \n" << flush;
    exit(-1);
  }
  if(IsInf(1/GetZero()) && !IsInf(1))
    cerr << "IsInf() ok. \n" << flush;
  else {
    cerr << "IsInf() failed. " << IsInf(1/GetZero()) << " " << IsInf(1) << "\n" << flush;
    exit(-1);
  }
  
  coutAMMA << "End of the example\n" << flush;
  return 0;
}

double GetZero() {
  return 0;
}

// IAPS - Image analysis program system.
// End of file exUsefFn.cc



