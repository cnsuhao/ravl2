// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/General/testMatInv.cc"

#include "Ravl/Matrix.hh"
#include "Ravl/MatrixRS.hh"
#include "Ravl/Random.hh"
#include "Ravl/Option.hh"
#include "Ravl/SArr2Iter.hh"

using namespace RavlN;

int testInverse(int n,int r,bool useNearSingular);

int main(int argc,char **argv) {
  OptionC  option(argc,argv,true);  
  //bool verbose  = option.Boolean("v",FALSE,"Verbose mode.");
  IntT n = option.Int("m",30,"Size of matrix to use. ");
  IntT r = option.Int("r",10,"Do r experiments. ");
  bool tns = option.Boolean("tns",false,"Test near singular only. ");
  bool tn = option.Boolean("tn",false,"Test normal inverse only. ");
  
  option.Check();
  if(tns) 
    return testInverse(n,r,true);
  if(tn) 
    return testInverse(n,r,false);
  if(testInverse(n,r,false) != 0)
    return 1;
  if(testInverse(n,r,true) != 0)
    return 1;
  cerr << "Tested passed ok. \n";
  return 0;
}


int testInverse(int n,int r,bool useNearSingular) {
  if(useNearSingular)
    cerr << "Testing near singular inverse.\n";
  else
    cerr << "Testing normal inverse.\n";
  
  for(IntT i = 0;i < r;i++) {
    MatrixC x;
    if(useNearSingular)
      x = RandomSymmetricMatrix(n);
    else
      x = RandomMatrix(n,n);
    MatrixC y;
    RealT det;
    if(!useNearSingular)
      y = x.Inverse();
    else
      y = MatrixRSC(x).NearSingularInverse(det);
    MatrixC z = (y * x) - MatrixC::Identity(n);
    RealT ret = (z.SumOfAbs() * 100)/(n*n);
    cout <<" Remainder:" << ret << endl;
    if(ret > 1.0e-5) {
      cerr << "ERROR: Test Failed. \n";
      return 1;
    }
  }
  return 0;
}
