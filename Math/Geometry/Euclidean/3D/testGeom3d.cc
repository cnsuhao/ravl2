// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! author="Joel Mitchelson"
//! docentry="Ravl.API.Math.Geometry.3D"
//! userlevel=Develop
//! file="Ravl/Math/Geometry/Euclidean/3D/testGeom3d.cc"

#include "Ravl/EulerAngle.hh"
#include "Ravl/AxisAngle.hh"
#include "Ravl/StdConst.hh"
#include "Ravl/LinePP3d.hh"
#include "Ravl/LinePV3d.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/Affine3d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/SArray1d.hh"

using namespace RavlN;

int testAngles();
int testLine();
int testLineDist();
int testFitAffine();

int main(int nargs,char **argv) {
  int ln;
  if((ln = testLine()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testLineDist()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testFitAffine()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
#if 1
  if((ln = testAngles()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
#endif
  
  cerr << "Test passed ok. \n";
  return 0;
}

int testLine() {
  cerr << "Testing lines. \n";
  Point3dC p0(1,1,1);
  Point3dC p1(3,5,7);
  Point3dC p2(2,3,4);
  Point3dC p3(5,9,13);
  
  LinePP3dC line(p0,p1);
  
  if(line.Distance(p2) > 0.0000001) return __LINE__;
  RealT val;
  val = line.ParClosest(p0);
  if(Abs(val) > 0.0000001) return __LINE__;
  val = line.ParClosest(p1);  
  if(Abs(val-1) > 0.0000001) return __LINE__;
  val = line.ParClosest(p2);
  if(Abs(val-0.5) > 0.0000001) return __LINE__;
  val = line.ParClosest(p3);
  if(Abs(val-2) > 0.0000001) return __LINE__;
  return 0;
}

int testLineDist() {
  
  LinePV3dC line1(Point3dC(0,0,0),Vector3dC(1,0,0));
  LinePV3dC line2(Point3dC(0,1,0),Vector3dC(0,0,1));
  if(Abs(line1.Distance(line2) - 1) > 0.0000001) return __LINE__;
  if((line1.Intersection(line2) - Point3dC(0,0.5,0)).SumOfSqr() > 0.000001) return __LINE__;
  
  LinePV3dC line3(Point3dC(0.5,0.5,0.5),Vector3dC(0.5,0.5,0.5));
  if(Abs(line1.Distance(line3)) > 0.000001) return __LINE__;
  
  
  return 0;
}

int testFitAffine() {
  cerr << "testFitAffine Called. \n";

  // Try 3d -> 3d case.
  
  SArray1dC<Point3dC> ipnt(4);
  ipnt[0] = Point3dC(1,1,3);
  ipnt[1] = Point3dC(2,1,4);
  ipnt[2] = Point3dC(1,3,5);
  ipnt[3] = Point3dC(2,4,6);
  
  SArray1dC<Point3dC> opnt(4);
  opnt[0] = Point3dC(2,2,6);
  opnt[1] = Point3dC(3,2,5);
  opnt[2] = Point3dC(2,4,4);
  opnt[3] = Point3dC(3,3,3);
  
  Affine3dC aff = FitAffine(ipnt,opnt);
  int i;
  for(i=0;i < 4;i++) {
    //std::cerr << "i=" << i << " " << ipnt[i] << " -> " << opnt[i] << " " << (aff * ipnt[i]) << "\n";
    if(((aff * ipnt[i]) - opnt[i]).SumOfSqr() > 0.001)
      return __LINE__;
  }
  
  // Test 2d -> 3d stuff.
  
  SArray1dC<Point2dC> ipnt2(3);
  ipnt2[0] = Point2dC(1,1);
  ipnt2[1] = Point2dC(2,1);
  ipnt2[2] = Point2dC(1,3);
  
  SArray1dC<Point3dC> opnt2(3);
  opnt2[0] = Point3dC(2,2,6);
  opnt2[1] = Point3dC(3,2,5);
  opnt2[2] = Point3dC(2,4,4);
  
  aff = FitAffine(ipnt2,opnt2);
  for(i=0;i < 3;i++) {
    //std::cerr << "i=" << i << " " << ipnt[i] << " -> " << opnt[i] << " " << (aff * ipnt[i]) << "\n";
    if(((aff * Point3dC(ipnt2[i][0],ipnt2[i][1],0)) - opnt2[i]).SumOfSqr() > 0.001)
      return __LINE__;
  }
  
  
  return 0;
}

//! date="7/12/2002"
//! author="Joel Mitchelson"

int testAngles() {
  cerr << "Testing Euler angles...";
  
  for (int sequence = 0; sequence < EulerSequenceC::NumSequences; sequence++)
  {
    for (int a = -32; a <= 32; a++)
      for (int b = -32; b <= 32; b++)
	for (int c = -32; c <= 32; c++)
    {
      // make euler angle
      EulerAngleC e1(a*RavlConstN::pi/8.0, b*RavlConstN::pi/8.0, c*RavlConstN::pi/8.0, sequence);
      
      // extract rotation matrix
      Matrix3dC R1;
      e1.Matrix(R1);
      
      // check determinant
      if (fabs(R1.Det() - 1.0) > 1E-12)
	{
	  cerr << "ERROR: euler sequence " << sequence << " caused non-orthonormal matrix" << endl;
	  cerr << "Angles: " << Vector3dC(e1) << endl;
	  cerr << "Matrix: " << endl << R1 << endl;
	  return __LINE__;
	}
      
      // make new angle
      EulerAngleC e2(R1, sequence);
      
      // convert to new matrix
      Matrix3dC R2;
      e2.Matrix(R2);
      
      // check they coincide
      if ((R2-R1).SumOfAbs() > 1E-6)
      {
	cerr << "ERROR: euler sequence " << sequence << " conversion problem." << endl;
	cerr << "Angles: " << Vector3dC(e1) << endl;
	cerr << "Matrix: " << endl << R1 << endl;
	cerr << "Convertex to angles: " << Vector3dC(e2) << endl;
	cerr << "Converted to matrix: " << endl << R2 << endl;
	return __LINE__;
      }
    }
  }

  cerr << "Euler angles OK" << endl;


  cerr << "Testing axis-angles...";
  for (int a = -15; a <= 15; a++)
    for (int b = -15; b <= 15; b++)
      for (int c = -15; c <= 15; c++)
      {
	// make euler angle
	AxisAngleC e1(a*RavlConstN::pi/8.0, b*RavlConstN::pi/8.0, c*RavlConstN::pi/8.0);
      
	// extract rotation matrix
	Matrix3dC R1;
	e1.Matrix(R1);
      
	// check determinant
	if (fabs(R1.Det() - 1.0) > 1E-12)
	{
	  cerr << "ERROR: axis-angle sequence caused non-orthonormal matrix" << endl;
	  cerr << "Angles: " << Vector3dC(e1) << endl;
	  cerr << "Matrix: " << endl << R1 << endl;
	  return __LINE__;
	}
      
	// make new angle
	AxisAngleC e2(R1);
      
	// convert to new matrix
	Matrix3dC R2;
	e2.Matrix(R2);
      
	// check they coincide
	if ((R2-R1).SumOfAbs() > 1E-6)
	{
	  cerr << "ERROR: axis angle conversion problem." << endl;
	  cerr << "Angles: " << Vector3dC(e1) << endl;
	  cerr << "Matrix: " << endl << R1 << endl;
	  cerr << "Convertex to angles: " << Vector3dC(e2) << endl;
	  cerr << "Converted to matrix: " << endl << R2 << endl;
	  return __LINE__;
	}
      }

  cerr << "axis angles OK" << endl;
  
  return 0;

}
