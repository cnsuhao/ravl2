// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/FundamentalMatrix2d.hh"
#include "Ravl/Random.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/LineABC2d.hh"

using namespace RavlN;

int testBasic();

int main() {
  int ln;
  if((ln = testBasic()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

int testBasic() {
  int n = 8;
  SArray1dC<PPoint2dC> pnts1(n);
  SArray1dC<PPoint2dC> pnts2(n);
  
  FundamentalMatrix2dC fm1;
  
  for(int i = 0;i < 3;i++)
    for(int j = 0;j < 3;j++)
      fm1[i][j] = Random1();
  fm1.MakeRank2();
  fm1.NormaliseScale();
  
  cerr << "Fm1=" << fm1 << "\n";
  for(int i =0;i < n;i++) {
    PPoint2dC p1(Random1() * 10,Random1() * 10,1);
    pnts1[i] = p1;
    LineABC2dC l2 = fm1.EpipolarLine(p1);
    Point2dC xp2 = l2.Projection(Point2dC(Random1() * 10 ,Random1() * 10));
    PPoint2dC p2(xp2);
    pnts2[i] = p2;
    cerr << i << ": " << pnts1[i] << " <->  " << pnts2[i] << "    " << fm1.Error(p1,p2) << "\n";
  }
  cerr << "\n";
  SArray1dC<PPoint2dC> cps1 = pnts1.Copy();
  SArray1dC<PPoint2dC> cps2 = pnts2.Copy();
  
  FundamentalMatrix2dC fm2 = FundamentalMatrix2dC::FitLinear(cps1,cps2);
  cerr << "fm2=" << fm2 << "\n";
  for(int i = 0;i < n;i++) {
    RealT err1 = fm1.Error(pnts1[i],pnts2[i]);
    RealT err2 = fm2.Error(pnts1[i],pnts2[i]);
    
    cerr << i << ": Err1=" << err1 << " Err2=" << err2 << "\n";
    //RealT x = fm2(pnts1[i]).Distance(pnts2[i]);
    //cerr << "x=" << x <<" \n";
    if(err1 > 0.00001 || err2 > 0.000001) return __LINE__;
    
  }
  
  cerr << "\nFm2=" << fm2 << "\n";
  return 0;
}
