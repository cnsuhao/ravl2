// Copyright A.Griffin NOT FOR INCLUSION IN AMMA,. 24Aug98
//
// The SVD of the real matrix A is
//  A = Q*D*P.T() where Q,P are orthogonal
//
// therefore A.T()*A = P*D.T()*Q.T()*Q*D*P.T()
//
// Q orthogonal, ie. Q.T()*Q = I, so A.T()*A = P*D.T()*D*P.T()
//
// .. cf. the diagonalisation of A.T()*A, A.T()*A = U.I()*V*U
//
// where V is the diagonal matrix of eigenvalues of A.T()*A, and U
// is formed from the corresponding eigenvectors.
//
// As a test of the SVD routine I firstly shall fix an arbitrary P,Q  
// and vary the value of the eigenvalues of D.T()*D by -> 0

#define ZERO 1e-15

#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"
#include "Ravl/StdMath.hh"
#include "Ravl/Slice1d.hh"

using namespace RavlN;

int main() {
  
  // I shall look at [3][3] matrices
  MatrixC A(3,3);
  MatrixC Q(3,3);
  VectorC D(3);
  MatrixC P(3,3);
  MatrixC C(3,3);
  
  C.Fill(0);
  
  // Q is orthogonal, 
  Q[0][0] =  1/Sqrt(2); Q[0][1] =  1/Sqrt(6); Q[0][2] = 1/Sqrt(3);
  Q[1][0] = -1/Sqrt(2); Q[1][1] =  1/Sqrt(6); Q[1][2] = 1/Sqrt(3);
  Q[2][0] =  0        ; Q[2][1] = -2/Sqrt(6); Q[2][2] = 1/Sqrt(3);
  
  // P is orthogonal,
  P[0][0] = -2.0/3; P[0][1] = 2.0/3; P[0][2] =  1.0/3;
  P[1][0] =  1.0/3; P[1][1] = 2.0/3; P[1][2] = -2.0/3;
  P[2][0] =  2.0/3; P[2][1] = 1.0/3; P[2][2] =  2.0/3;
  
  // D is diagonal,
  D[2] = 1; D[1] = 1; D[0] = 1;
  
  while (D[2] > ZERO || D[1] > ZERO || D[0] > ZERO) {
    
    D.SetSmallToBeZero(ZERO);
    
    A = Q*C.SetDiagonal(D)*P.T();
    
    cout << "\n";
    
    MatrixC origA = A.Copy();
    VectorC origD = D.Copy();
    
    MatrixC rmv;
    MatrixC rmu;
    
    D = A.SVD_IP(rmu,rmv);
    A = rmu*C.SetDiagonal(D)*rmv.T();
    
    //D.Sort();
    
    cout << "D:" << origD << "\n" << D << "\n";
    cout << "A:" << origA << "\n" << rmu << "\n";
    
    // P, Q are not unique, but D is. 
    // My check shall be that A_before=A_after and that D_before=D_after
    MatrixC diffM = MatrixC(A-origA).SetSmallToBeZero(ZERO);
    VectorC diffV = VectorC(D-origD).SetSmallToBeZero(ZERO);
    
    if (diffV.Modulus()>0 || 
	diffM.SliceColumn(0).Modulus()>0 || 
	diffM.SliceColumn(1).Modulus()>0 || 
	diffM.SliceColumn(2).Modulus()>0) {
      cout << diffV.Modulus() << "\n"; 
      cout << diffM.SliceColumn(0).Modulus() << "\n";
      cout << diffM.SliceColumn(1).Modulus() << "\n"; 
      cout << diffM.SliceColumn(2).Modulus() << "\n";
      cout << "FAIL\n";
      return 1;
    }
    
    cout << "***********************\n";
    
    D = origD;

    if (D[1]==0 && D[0]==0) 
      D[2] /= 10;
    else 
      if (D[0]==0) 
	D[1] /= 10;
      else D[0] /= 10;
    
  }
  
  return 0;
}
