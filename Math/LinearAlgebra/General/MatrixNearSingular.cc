// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/General/MatrixNearSingular.cc"

#include "Ravl/Matrix.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Vector.hh"
#include "Ravl/CCMath.hh"

namespace RavlN {
  
  //: Inverts this matrix and returns determinant of original matrix.
  // This routine is particularly useful when you matrices are near singular
  // as it uses PCA to first rotate co-ordinate axis, so no nasty divisions.
  // See Fukunaga -Introduction to Statistical Pat Rec, page 40.
  
  MatrixC MatrixC::NearSingularInverse(RealT &det) const {
    if( Cols() != Rows() ) {
      cerr << "MatrixC::NearSingularInverseIP(), Matrix to invert must be square" << endl;
      return MatrixC();
    }
    // Take care of special cases.
    switch(Cols()) 
      {
      case 2: {
	det = (*this)[0][0]*(*this)[1][1]-(*this)[0][1]*(*this)[1][0];
	MatrixC inv(2, 2);
	inv[0][0]=(*this)[1][1];
	inv[0][1]=-1.0 * (*this)[0][1];
	inv[1][0]=-1.0 * (*this)[1][0];
	inv[1][1]=(*this)[0][0];
	inv *= (1.0/det);
	return inv;
      }
      case 3: {
	det = (*this)[0][0] * (*this)[1][1]*(*this)[2][2] - (*this)[0][0] * (*this)[2][1] * (*this)[1][2] + (*this)[1][0] * (*this)[2][1] * (*this)[0][2] - (*this)[1][0] *(*this)[0][1] * (*this)[2][2] + (*this)[2][0]*(*this)[0][1]*(*this)[1][2] - (*this)[2][0] * (*this)[1][1] * (*this)[0][2];
	
	MatrixC inv(3, 3);
	inv[0][0]=(*this)[1][1]*(*this)[2][2] - (*this)[1][2]*(*this)[2][1];
	inv[0][1]=(*this)[0][2]*(*this)[2][1] - (*this)[0][1]*(*this)[2][2];
	inv[0][2]=(*this)[0][1]*(*this)[1][2] - (*this)[0][2]*(*this)[1][1];
	
	inv[1][0]=(*this)[1][2]*(*this)[2][0] - (*this)[1][0]*(*this)[2][2];
	inv[1][1]=(*this)[0][0]*(*this)[2][2] - (*this)[0][2]*(*this)[2][0];
	inv[1][2]=(*this)[0][2]*(*this)[1][0] - (*this)[0][0]*(*this)[1][2];
	
	inv[2][0]=(*this)[1][0]*(*this)[2][1] - (*this)[1][1]*(*this)[2][0];
	inv[2][1]=(*this)[0][1]*(*this)[2][0] - (*this)[0][0]*(*this)[2][1];
	inv[2][2]=(*this)[0][0]*(*this)[1][1] - (*this)[0][1]*(*this)[1][0];
	inv *= (1.0/det);
	return inv;
      }
      }
#if 0    
    VecMatC eigenvec;
    MatrixC cov=(*this).Copy();
    
    //: First need to compute PCA
    if(Cols()<10) 
      eigenvec = EigenSystemJacobi (cov);  // taken out cos bad for high dim
    else 
      eigenvec = EigenSystemHouseholderQL(cov);
  
    //: Now lets compute the determinant and inv
    RealT det=0.0;
    Fill(0.0);
    
    RealT sign(1.0);
    FOR_VECTOR(eigenvec.Vector(), ind) {
      if (eigenvec.Vector()[ind] == 0.0) sign=0.0;
      else if (eigenvec.Vector()[ind] < 0.0) { // check for -ve eigenvalues
	det += Log(-eigenvec.Vector()[ind]);
	sign = -sign;
      } else {
	det += Log(eigenvec.Vector()[ind]);
      }
      (*this) +=  eigenvec.Matrix().GetColumn(ind).OuterP() * (1.0/eigenvec.Vector()[ind]);
    }
    
    det = exp(det) * sign; 
    return det;
#else
    RavlAssert(0); // Need to sort this out.
    det = 0;
    return MatrixC();
#endif
  }
  

}
