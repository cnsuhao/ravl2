// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! author="Charles Galambos"
//! docentry="Ravl.Core.Math.QInt"
//! file="Ravl/Core/Base/exQInt.cc"

#include "Ravl/QInt.hh"
#include "Ravl/Option.hh"

using namespace RavlN;


#define FLOAT_TO_INT(in,out)  \
                    __asm__ __volatile__ ("fistpl %0" : "=m" (out) : "t" (in) : "st") ;


inline IntT LFloor(RealT x) {
#if 0
  int y = static_cast<IntT>(x);
  if(y >=0) return y;
  return y + ((static_cast<double>(y) == x) ? 0 : -1);
#else
#if 0
  int r;
  FLOAT_TO_INT(x,r);
  return r;
#else
  return lrintf(x);
#endif
#endif
}
//: Returns the greatest integral  value  less  than  or equal  to  'x'.

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  bool useQInt = opt.Boolean("q",false,"Use QInt methods. ");
  bool testFloor = opt.Boolean("f",false,"Test Floor() ");
  bool test = opt.Boolean("t",false,"Test QFloor and QRound ");
  RealT count = opt.Real("c",100000,"Size of test. ");
  opt.Check();
  
  IntT sum = 0;
  if(!test) {
    if(!testFloor) {
      if(useQInt) {
	cerr << "Using QRound. \n";
	for(RealT v = -count;v < count;v += 0.013) {
	  sum += QRound(v);
	}
      } else {
	cerr << "Using Round. \n";
	for(RealT v = -count;v < count;v += 0.013) {
	  sum += Round(v);
	}
      }
    } else {
      if(useQInt) {
	cerr << "Using QFloor. \n";
	for(RealT v = -count;v < count;v += 0.013) {
	  sum += QFloor(v);
	}
      } else {
	cerr << "Using Floor. \n";
	for(RealT v = -count;v < count;v += 0.013) {
	  sum += LFloor(v);
	  //sum += floor(v);
	}
      }
    }
    cerr << "Sum=" << sum << "\n";
  } else {
    double values[] = { 0,0.1,-0.25,-3.6 , -3, 1.3,100000.01,1000,-1000,-0.00000000000001 };
    for(int i = 0;i < 10;i++) {
      cerr << "Round " << values[i] << " N=" << Round(values[i])  << " Q=" << QRound(values[i]) << " round=" << round(values[i]) << "\n";
      cerr << "Floor " << values[i] << " N=" << LFloor(values[i])  << " Q=" << QFloor(values[i]) << " floor=" << floor(values[i]) << "\n";
      if(round(values[i]) != QRound(values[i])) {
	cerr << "test failed. \n";
      }
      if(floor(values[i]) != QFloor(values[i])) {
	cerr << "test failed. \n";
      }
    }
    cerr << "test passed. \n";
  }
  
  return 0;
}
