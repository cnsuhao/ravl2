// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: DesignFuncLSQ.cc 3563 2003-10-17 12:33:18Z jonstarck $"
//! lib=RavlPatternRec
//! author="Charles Galambos"
//! file="Ravl/PatternRec/Modeling/Basic/DesignFuncLSQ.cc"

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
    int val;
    strm >> order >> val;
    orthogonal = (val != 0);
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignFuncLSQBodyC::Save (ostream &out) const {
    if(!DesignFunctionSupervisedBodyC::Save(out))
      return false;
    char ver = 1;
    out << ((int) ver) << ' ' << order << ' ' << ((int) orthogonal) << ' ';
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignFuncLSQBodyC::Save (BinOStreamC &out) const {
	if(!DesignFunctionSupervisedBodyC::Save(out))
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
  
  SArray1dC<IntT> DesignFuncLSQBodyC::FindCorrelatedParameters(const MatrixRUTC &mat,RealT thresh) {
    ONDEBUG(cerr << "DesignFuncLSQBodyC::FindCorelatedParameters(), Looking for corelations. \n");
    SArray1dC<IntT> ret(mat.Rows());
    ret.Fill(-1);
    for(IntT i = 0;i < (int) mat.Rows();i++) {
      if(ret[i] >= 0)
	continue; // Already found a correlation for this parameter.
      for(IntT j = i+1;j < (int) mat.Rows();j++) {
	RealT ii = mat[i][i];
	RealT ij = mat[j][i];
	RealT jj = mat[j][j];
	RealT aver = (ii + jj + 2 * ij)/4;
	RealT det = ii * jj - Sqr(ij);
	ONDEBUG(cerr << " " << i << " " << j << " Det=" << det << "\n");
	if(IsSmall(det,aver,thresh)) {
	  ret[j] = i;
	  break; // Parameters j and i are correlated.
	}
      }
    }
    return ret;
  }
  
  //: Create function from the given data.
  
  FunctionC DesignFuncLSQBodyC::Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out) {
    ONDEBUG(cerr << "DesignFuncLSQBodyC::Apply(), Computing coefficients.. \n");
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
    
#if 0 
    SampleVectorC coeffs(vin.Size());
    //: Build a sample set of coefficents.
    
    for(SampleIterC<VectorC> cit(in);cit;cit++)
      coeffs += func.MakeInput(*cit);
    
    //cerr << "Coeffs=" << coeffs << "\n";

    // Do a few sums.
    MatrixRUTC aaTu = coeffs.SumOuterProducts();
    aaTu.MakeSymmetric();
    MatrixRSC aaT(aaTu.Copy());
    MatrixC aTb = coeffs.TMul(vout);
#else
    // Do some sums without duplicating data.
    MatrixRUTC aaTu;
    MatrixC aTb;
    func.ComputeSums(in,out,aaTu,aTb);
    aaTu.MakeSymmetric();
    MatrixRSC aaT = aaTu.Copy();
#endif
    ONDEBUG(cerr << "DesignFuncLSQBodyC::Apply(), Solving equations.. \n");
#if 1
    if(!aaT.InverseIP()) {
      // Try and recover....
      cerr << "DesignFuncLSQBodyC::Apply(), WARNING: Covariance of input has singular values. \n";
      aaT = aaTu.PseudoInverse();
    }
    MatrixC A =  (aaT * aTb).T();
#else
    MatrixC At = Solve(aaTu,aTb);
    MatrixC A;
    if(!At.IsValid()) {
      // Try and recover....
      cerr << "DesignFuncLSQBodyC::Apply(), WARNING: Covariance of input has singular values. \n";
      aaT = aaTu.PseudoInverse();
      A = (aaT * aTb).T();
    } else
      A = At.T();
#endif
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
    
    MatrixC aTb = coeffs.TMul(vout,weight);
    
    MatrixRSC aaT(aaTu.Copy());
    
#if 1
    if(!aaT.InverseIP()) {
      // Try and recover....
      cerr << "DesignFuncLSQBodyC::Apply(), WARNING: Covariance of input has singular values. \n";
      aaT = aaTu.PseudoInverse();
    }
    // Ideally we'd use Solve here...
    
    MatrixC A =  (aaT * aTb).T();
#else
    MatrixC At = SolvePD(aaTu,aTb);
    MatrixC A;
    if(!At.IsValid()) {
      aaT = aaTu.PseudoInverse();
      A = (aaT * aTb).T();
    } else
      A = At.T();
#endif
    func.SetTransform(A);
    return func;
  }

  //: Create function from the given data.
  // Note: Construction from a sample stream may not be implemented by all designers.
  
  FunctionC DesignFuncLSQBodyC::Apply(SampleStream2C<VectorC,VectorC > &in) {
#if 1
    Tuple2C<VectorC,VectorC> tup;
    if(!in.Get(tup)) {
      cerr << "DesignFuncLSQBodyC::Apply(), WARNING: Dataset empty. ";
      return FunctionC();
    }
    
    UIntT inSize = tup.Data1().Size();
    UIntT outSize = tup.Data2().Size();
    in.First(); // Reset to the first element.
    
    FuncLinearCoeffC func = CreateFunc(inSize,outSize);
    if(!func.IsValid()) {
      cerr << "DesignFuncLSQBodyC::Apply(), ERROR: Failed to create new function. \n";
      return func;
    }
    
    // Do some sums without duplicating data.
    MatrixRUTC aaTu;
    MatrixC aTb;
    func.ComputeSums(in,aaTu,aTb);
    //func.ComputeSums(in,out,aaTu,aTb);
    aaTu.MakeSymmetric();
    MatrixRSC aaT = aaTu.Copy();
    
    ONDEBUG(cerr << "DesignFuncLSQBodyC::Apply(), Solving equations.. \n");
#if 1
    if(!aaT.InverseIP()) {
      // Try and recover....
      cerr << "DesignFuncLSQBodyC::Apply(), WARNING: Covariance of input has singular values. \n";
      aaT = aaTu.PseudoInverse();
    }
    MatrixC A =  (aaT * aTb).T();
#else
    MatrixC At = Solve(aaTu,aTb);
    MatrixC A;
    if(!At.IsValid()) {
      // Try and recover....
      cerr << "DesignFuncLSQBodyC::Apply(), WARNING: Covariance of input has singular values. \n";
      aaT = aaTu.PseudoInverse();
      A = (aaT * aTb).T();
    } else
      A = At.T();
#endif
    func.SetTransform(A);    
    return func;
#else
    return FunctionC();
#endif    
  }


  ////////////////////////////////////////////////////////////////////////
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(DesignFuncLSQBodyC,DesignFuncLSQC,DesignFunctionSupervisedC);
  
}
