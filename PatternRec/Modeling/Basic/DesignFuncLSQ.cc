// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos"

#include "Ravl/PatternRec/DesignFuncLSQ.hh"
#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/PatternRec/FuncLinear.hh"
#include "Ravl/PatternRec/FuncQuadratic.hh"
#include "Ravl/PatternRec/FuncOrthPolynomial.hh"
#include "Ravl/MatrixRUT.hh"
#include "Ravl/MatrixRS.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/VirtualConstructor.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Create least squares designer.
  
  DesignFuncLSQBodyC::DesignFuncLSQBodyC(UIntT norder,bool northogonal) 
    : order(norder),
      orthogonal(northogonal)
  {}
  
  //: Load from stream.
  
  DesignFuncLSQBodyC::DesignFuncLSQBodyC(istream &strm)
    : DesignFunctionSupervisedBodyC(strm)
  {
    int ver;
    strm >> ver;
    if(ver != 1)
      cerr << "DesignFuncLSQBodyC::DesignFuncLSQBodyC(), Unknown format version. \n";
    strm >> order >> orthogonal;
  }
  
  //: Load from binary stream.
  
  DesignFuncLSQBodyC::DesignFuncLSQBodyC(BinIStreamC &strm)
    : DesignFunctionSupervisedBodyC(strm)
  {
    char ver;
    strm >> ver;
    if(ver != 1)
      cerr << "DesignFuncLSQBodyC::DesignFuncLSQBodyC(), Unknown format version. \n";
    strm >> order >> orthogonal;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignFuncLSQBodyC::Save (ostream &out) const {
    if(!DesignFuncLSQBodyC::Save(out))
      return false;
    char ver = 1;
    out << ((int) ver) << ' ' << order << ' ' << orthogonal << ' ';
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignFuncLSQBodyC::Save (BinOStreamC &out) const {
    if(!DesignFuncLSQBodyC::Save(out))
      return false;
    char ver = 1;
    out << ver << order << orthogonal;
    return true;
  }
  
  //: Create new function.
  
  FuncLinearCoeffC DesignFuncLSQBodyC::CreateFunc(UIntT inSize,UIntT outSize) {
    switch(order) 
      {
      case 0: 
	cerr << "Warning: Order 0 model. \n";
	return FuncLinearCoeffC();
      case 1: // Linear.
	return FuncLinearC(inSize,outSize);
      case 2: // Quadratic
	if(!orthogonal)
	  return FuncQuadraticC(inSize,outSize);
      default:
	return FuncOrthPolynomialC(inSize,outSize,order);
      };
    return FuncLinearCoeffC();
  }

  //: Find correlated paramiters.
  
  SArray1dC<IntT> DesignFuncLSQBodyC::FindCorelatedParameters(const MatrixRUTC &mat,RealT thresh = 1e-6) {
    ONDEBUG(cerr << "DesignFuncLSQBodyC::FindCorelatedParamiters(), Looking for corelations. \n");
    SArray1dC<IntT> ret(mat.Rows());
    ret.Fill(-1);
    for(IntT i = 0;i < (int) mat.Rows();i++) {
      if(ret[i] >= 0)
	continue; // Already found a corelation for this paramiter.
      for(IntT j = i+1;j < (int) mat.Rows();j++) {
	RealT ii = mat[i][i];
	RealT ij = mat[j][i];
	RealT jj = mat[j][j];
	RealT aver = (ii + jj + 2 * ij)/4;
	RealT det = ii * jj - Sqr(ij);
	ONDEBUG(cerr << " " << i << " " << j << " Det=" << det << "\n");
	if(IsSmall(det,aver,thresh)) {
	  ret[j] = i;
	  break; // Paramiters j and i are corelated.
	}
      }
    }
    return ret;
  }
  
  //: Create function from the given data.
  
  FunctionC DesignFuncLSQBodyC::Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out) {
    SampleVectorC vin(in);
    SampleVectorC vout(out);
    
    if(in.IsEmpty() || out.IsEmpty()) {
      cerr << "DesignFuncLSQBodyC::Apply(), WARNING: Asked to design a function without any data. ";
      return FuncLinearCoeffC();
    }
    
    UIntT inSize = vin.VectorSize();
    UIntT outSize = vout.VectorSize();
    
    FuncLinearCoeffC func = CreateFunc(inSize,outSize);
    if(!func.IsValid()) {
      cerr << "DesignFuncLSQBodyC::Apply(), ERROR: Failed to create new function. \n";
      return func;
    }
    SampleVectorC coeffs(vin.Size());
    
    //: Build a sample set of coefficents.
    
    for(SampleIterC<VectorC> cit(in);cit;cit++)
      coeffs += func.MakeInput(*cit);
    
    //cerr << "Coeffs=" << coeffs << "\n";
    
    // Do a few sums.
    MatrixRUTC aaTu = coeffs.SumOuterProducts();
    aaTu.MakeSymmetric();
    MatrixRSC aaT(aaTu.Copy());
    if(!aaT.InverseIP()) {
      // Try and recover....
      cerr << "DesignFuncLSQBodyC::Apply(), WARNING: Covariance of input has singular values. \n";
      aaT = aaTu.PseudoInverse();
    }
    MatrixC aTb = coeffs.TMul(vout);
    MatrixC A =  (aaT * aTb).T();
    func.SetTransform(A);    
    return func;
  }
  
  //: Create function from the given data, and sample weights.
  
  FunctionC DesignFuncLSQBodyC::Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out,const SampleC<RealT> &weight) {
    SampleVectorC vin(in);
    SampleVectorC vout(out);
    
    if(in.IsEmpty() || out.IsEmpty()) {
      cerr << "DesignFuncLSQBodyC::Apply(), WARNING: Asked to design a function without any data. ";
      return FuncLinearCoeffC();
    }
    
    UIntT inSize = vin.VectorSize();
    UIntT outSize = vout.VectorSize();
    
    FuncLinearCoeffC func = CreateFunc(inSize,outSize);
    if(!func.IsValid()) {
      cerr << "DesignFuncLSQBodyC::Apply(), ERROR: Failed to create new function. \n";
      return func;
    }
    SampleVectorC coeffs(vin.Size());
    
    //: Build a sample set of coefficents.
    
    for(SampleIterC<VectorC> cit(in);cit;cit++)
      coeffs += func.MakeInput(*cit);
    
    //cerr << "Coeffs=" << coeffs << "\n";
    
    // Do a few sums.
    MatrixRUTC aaTu = coeffs.SumOuterProducts(weight);
    aaTu.MakeSymmetric();
    MatrixRSC aaT(aaTu.Copy());
    if(!aaT.InverseIP()) {
      // Try and recover....
      cerr << "DesignFuncLSQBodyC::Apply(), WARNING: Covariance of input has singular values. \n";
      aaT = aaTu.PseudoInverse();
    }
    MatrixC aTb = coeffs.TMul(vout,weight);
    MatrixC A =  (aaT * aTb).T();
    func.SetTransform(A);
    return func;
  }

  ////////////////////////////////////////////////////////////////////////
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(DesignFuncLSQBodyC,DesignFuncLSQC,DesignFunctionSupervisedC);
  
}
