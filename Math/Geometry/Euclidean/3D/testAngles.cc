
#include "Ravl/EulerAngle.hh"
#include "Ravl/AxisAngle.hh"
#include "Ravl/StdConst.hh"

using namespace RavlN;

int main()
{
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
	  return 1;
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
	return 1;
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
	  return 1;
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
	  return 1;
	}
      }

  cerr << "axis angles OK" << endl;
  
  return 0;
}






