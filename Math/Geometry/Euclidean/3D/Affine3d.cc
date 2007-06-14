
#include "Ravl/Affine3d.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/LeastSquares.hh"

namespace RavlN {
  
  //: Fit an affine transformation
  
  Affine3dC FitAffine(const SArray1dC<Point3dC> &org,const SArray1dC<Point3dC> &newPos,RealT &residual) {
    RavlAssertMsg(org.Size() == newPos.Size(),"Affine3dC FitAffine(), Point arrays must have the same size.");
    
    UIntT samples = org.Size();
    if ( samples < 4 )
      throw ExceptionC("Sample size too small in FitAffine(). ");
    
    MatrixC A(samples,4);
    VectorC b(samples);
    VectorC c(samples);
    VectorC d(samples);
    UIntT i = 0;
    for(SArray1dIter2C<Point3dC,Point3dC> it(org,newPos);it;it++,i++) {
      RealT x1, y1, z1, x2, y2, z2;
      x1=it.Data1()[0]; y1=it.Data1()[1]; z1=it.Data1()[2];
      x2=it.Data2()[0]; y2=it.Data2()[1]; z2=it.Data2()[2];
      
      A[i][0] = x1;
      A[i][1] = y1;
      A[i][2] = z1;
      A[i][3] = 1;
      b[i] = x2;
      c[i] = y2;
      d[i] = z2;
    }
    
    MatrixC tA = A.Copy();
    MatrixC sA = A.Copy();
    if(A.Rows() == A.Cols()) {
      // solve for solution vector
      residual = 0;
      if(!SolveIP(tA,b))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine, 3d ");
      if(!SolveIP(sA,c))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine, 3d ");
      if(!SolveIP(A,d))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine, 3d ");
    } else {
      if(!LeastSquaresQR_IP(tA,b,residual))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine, 3d ");
      if(!LeastSquaresQR_IP(sA,c,residual))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine, 3d ");
      if(!LeastSquaresQR_IP(A,d,residual))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine, 3d ");
    }
    
    Matrix3dC sr(b[0],b[1],b[2],
		 c[0],c[1],c[2],
                 d[0],d[1],d[2]);
    Vector3dC tr(b[3],c[3],d[3]);
    
    return Affine3dC(sr,tr);    
  }

  //: Fit points on a 2d plane (this assumes the z position is always zero) to a 3d position.
  
  Affine3dC FitAffine(const SArray1dC<Point2dC> &org,const SArray1dC<Point3dC> &newPos,RealT &residual) {
    RavlAssertMsg(org.Size() == newPos.Size(),"Affine3dC FitAffine(), Point arrays must have the same size.");
    
    UIntT samples = org.Size();
    if ( samples < 3 )
      throw ExceptionC("Sample size too small in FitAffine(). ");
    
    MatrixC A(samples,3);
    VectorC b(samples);
    VectorC c(samples);
    VectorC d(samples);
    UIntT i = 0;
    for(SArray1dIter2C<Point2dC,Point3dC> it(org,newPos);it;it++,i++) {
      RealT x1, y1, x2, y2, z2;
      x1=it.Data1()[0]; y1=it.Data1()[1];
      x2=it.Data2()[0]; y2=it.Data2()[1]; z2=it.Data2()[2];
      
      A[i][0] = x1;
      A[i][1] = y1;
      A[i][2] = 1;
      b[i] = x2;
      c[i] = y2;
      d[i] = z2;
    }
    
    MatrixC tA = A.Copy();
    MatrixC sA = A.Copy();
    if(A.Rows() == A.Cols()) {
      // solve for solution vector
      residual = 0;
      if(!SolveIP(tA,b))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine, 3d ");
      if(!SolveIP(sA,c))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine, 3d ");
      if(!SolveIP(A,d))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine, 3d ");
    } else {
      if(!LeastSquaresQR_IP(tA,b,residual))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine, 3d ");
      if(!LeastSquaresQR_IP(sA,c,residual))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine, 3d ");
      if(!LeastSquaresQR_IP(A,d,residual))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine, 3d ");
    }
    
    Matrix3dC sr(b[0],b[1],0,
		 c[0],c[1],0,
                 d[0],d[1],0);
    
    // Fill in values as a rotation into the z axis.
    for(int i = 0;i < 3;i++) {
      RealT s = Sqr(sr[i][0]) + Sqr(sr[i][1]);
      if(s < 1.0) 
        sr[i][2] = Sqrt(1-s);
    }
    
    Vector3dC tr(b[2],c[2],d[2]);
    
    return Affine3dC(sr,tr);
  }

  
}
