// IAPS - Image analysis program system
//
// File name  : UsefulFn.cc
// Description: useful functions
// Last change: 26.12.1993
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

#include "amma/UsefulFn.hh"

IntT
ILog2(IntT i)
//==========
{
   IntT mex = 0;
   while((i/=2) != 0) mex++;
   return(mex);
}


// End of the file UsefulFn.cc


