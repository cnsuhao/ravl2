// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/Matrix.hh"
#include "Ravl/Random.hh"
#include "Ravl/Option.hh"
#include "Ravl/SArr2Iter.hh"

using namespace RavlN;

int main(int argc,char **argv) {
  OptionC  option(argc,argv,true);  
  //bool verbose  = option.Boolean("v",FALSE,"Verbose mode.");
  IntT n = option.Int("m",30,"Size of matrix to use. ");
  IntT r = option.Int("r",10,"Do r experiments. ");
  option.Check();
  
  for(IntT i = 0;i < r;i++) {
    MatrixC x(n,n);
    for(SArray2dIterC<RealT> it(x);it;it++)
      *it = Random1();
    MatrixC y = x.Inverse();
    MatrixC z = (y * x) - MatrixC::Identity(n);
    RealT ret = (z.SumOfAbs() * 100)/(n*n);
    cout <<" Remainder:" << ret << endl;
    if(ret > 1.0e-10) {
      cerr << "ERROR: Test Failed. \n";
      return 1;
    }
  }
  return 0;
}
