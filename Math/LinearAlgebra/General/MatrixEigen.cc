// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/StdConst.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"
#include "Ravl/CCMath.hh"

// matrix functions.

namespace RavlN {
  // n*m row*col
  
  VectorC MatrixC::EigenValues() const {
    MatrixC ret = Copy();
    return ret.EigenValuesIP();
  }
  
  VectorC MatrixC::EigenValuesIP() {
    RavlAlwaysAssert(IsContinuous()); // Should we cope with this silently ?
    RavlAlwaysAssertMsg(Rows() == Cols(),"MatrixC::EigenValuesIP() Matrix must be square. ");
    if(Rows() == 0)
      return VectorC(0);
    VectorC ret(Rows());
    eigval(&(*this)[0][0],&ret[0],Rows());
    return ret;
  }

  
  VectorC MatrixC::EigenVectors(MatrixC &ret) const {
    ret = Copy();
    return ret.EigenVectorsIP();
  }
  
  VectorC MatrixC::EigenVectorsIP() {
    RavlAlwaysAssert(IsContinuous()); // Should we cope with this silently ?
    RavlAlwaysAssertMsg(Rows() == Cols(),"MatrixC::EigenVectorsIP() Matrix must be square. ");
    VectorC ret(Rows());
    eigen(&(*this)[0][0],&ret[0],Rows());
    return ret;
  }
  
  //: Get the maximum eigen value and its vector.
  
  RealT MatrixC::MaxEigenValue(VectorC &maxv) const{
    RavlAlwaysAssert(IsContinuous()); // Should we cope with this silently ?
    RavlAlwaysAssertMsg(Rows() == Cols(),"MatrixC::MaxEigenValue() Matrix must be square. ");
    maxv = VectorC(Rows());
    RealT ret = evmax(const_cast<RealT *>(&(*this)[0][0]),&maxv[0],Rows());
#if 0
    if(ret == HUGE) {
      return RavlConstN::nanReal;
    }
#endif
    return ret;
  }
  

}
