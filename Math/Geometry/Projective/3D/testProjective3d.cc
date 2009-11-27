
// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Projective/2D/testFundamentalMatrix2d.cc"

#include "Ravl/PProjection3d.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/Random.hh"
#include "Ravl/Vector4d.hh"

using namespace RavlN;

int testBasic();
int testPProjection();

int main() {
  int ln;
  if((ln = testPProjection()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}


int testPProjection() {
  cerr << "Testing projective fitting. \n";
  SArray1dC<PPoint3dC> from(6);
  SArray1dC<PPoint3dC> to(6);

  // Do a simple test.
  
  Matrix4dC testTransform(1,0,0,0,
                          0,2,0,0,
                          0,0,3,0,
                          0,0,0,1);

  from[0] = PPoint3dC(1,1,1,1); 
  from[1] = PPoint3dC(1,2,1,1); 
  from[2] = PPoint3dC(2,1,3,1); 
  from[3] = PPoint3dC(2,2,3,1); 
  from[4] = PPoint3dC(3,3,3,1); 
  from[5] = PPoint3dC(3,2,3,1); 
  
  for(int i = 0;i < from.Size();i++)
    to[i] = testTransform * from[i];
  
  PProjection3dC pp;
  if(!FitPProjection(from,to,pp)) 
    return __LINE__;
  
  for(SArray1dIter2C<PPoint3dC,PPoint3dC> it(from,to);it;it++) {
    PPoint3dC x = pp * it.Data1();
    //cerr << "D=" << it.Data1() << "  x=" << x <<"  x3=" << x.Point3d() << " Expected=" << it.Data2().Point3d() <<"\n";
    if((x.Point3d() - it.Data2().Point3d()).SumOfAbs() > 0.000001)
      return __LINE__;
  }
  //cerr << "Pp=" << pp << "\n";
  
  // Try a more complex transform.
  
  for(SArray1dIter2C<PPoint3dC,PPoint3dC> it(from,to);it;it++) {
    it.Data1() = PPoint3dC(Random1(),Random1(),Random1(),1);
    it.Data2() = PPoint3dC(Random1(),Random1(),Random1(),1);
  }
  from[4] = from[3]; to[4] = to[3]; // Duplicate last entry to ensure unique transform
  
  if(!FitPProjection(from,to,pp)) 
    return __LINE__;
  
  for(SArray1dIter2C<PPoint3dC,PPoint3dC> it(from,to);it;it++) {
    PPoint3dC x = pp * it.Data1();
    //cerr << "x=" << x <<"  " << x.Point3d() << "\n";
    if((x.Point3d() - it.Data2().Point3d()).SumOfAbs() > 0.000001)
      return __LINE__;
  }


  return 0;
}
