
#include "Ravl/PatternRec/DesignFuncLSQ.hh"
#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/PatternRec/FuncLinear.hh"
#include "Ravl/MatrixRUT.hh"
#include "Ravl/MatrixRS.hh"

namespace RavlN {
  
  //: Create least squares designer.
  
  DesignFuncLSQBodyC::DesignFuncLSQBodyC(UIntT norder,bool northogonal) 
    : order(norder),
      orthogonal(northogonal)
  {
  }
  
  //: Create new function.
  
  FuncLinearCoeffC DesignFuncLSQBodyC::CreateFunc(UIntT inSize,UIntT outSize) {
    switch(order) 
      {
      case 0: 
	cerr << "Warning: Order 0 model. \n";
	return FuncLinearCoeffC();
      case 1: // Linear.
	return  FuncLinearC(inSize,outSize);
      case 2: // Quadratic
	break;
      };
    return FuncLinearCoeffC();
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
    MatrixC aaT(aaTu);
    if(!aaT.InverseIP()) {
      cerr << "DesignFuncLSQBodyC::Apply(), ERROR: Inverse failed, not enough data to complete design. \n";
      return FunctionC();
    }
    MatrixC aTb = coeffs.TMul(vout);
    MatrixC A =  (aaT * aTb).T();
    func.SetTransform(A);
    
#if 0
    MatrixC Y(outSize,vout.Size());
    MatrixC X(coeffs,vin.Size());
    IndexT index = 0;
    for (ConstDLIterC<NumVVDataC> elem (train); elem.IsElm (); elem.Next ()) {
      Y.SetCol (index, elem.Data().Output(), SizeY());
      X.SetCol (index++, MakeInput (elem.Data().Input()), Xdim);
    }
    SArray1dC<int> invalidX (Xdim);
    invalidX.Fill(1);
    MatrixC xxT = X.MulT(X);
    if (!IsMarginal (xxT,invalidX))
      _A = Y*X.TMul(xxT.I());
    else {
      invalidX.Fill (0);
      MatrixC Xcopy (X.RDim(),X.CDim());
      Xcopy.SetZero ();
      VectorC blank (train.Size());
      blank.SetZero ();
      FOR_SARRAY1 (_invalidX,index2) {
	_invalidX[index2] = 1;
	VectorC row = X.GetRow (index2);
	Xcopy.SetRow (index2,row,row.Dim());
	if (IsMarginal (Xcopy.MulT(Xcopy),_invalidX)) {
	  _invalidX[index2] = 0;
	  Xcopy.SetRow (index2,blank,blank.Dim());
	}	
      }
      cout << "Warning: Model only valid with parameters: ";
      FOR_SARRAY1 (_invalidX,index3)
      cout << _invalidX[index3];
      cout << "\n";
      _A = Y*Xcopy.TMul((Xcopy.MulT(Xcopy)).I());
    }
#endif
    return func;
  }
  
  //: Create function from the given data, and sample weights.
  
  FunctionC DesignFuncLSQBodyC::Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out,const SampleC<RealT> &weight) {
    RavlAssertMsg(0,"DesignFuncLSQBodyC::Apply(in,out,weight), Not implemented. \n"); 
    return FunctionC();
  }
  
  bool DesignFuncLSQBodyC::IsMarginal(const MatrixC &m, SArray1dC<int> invalid,bool verbose) {
    MatrixC temp = m.Inverse()*m;
    temp.SetSmallToBeZero (1e-9);
    for(SArray1dIterC<int> it(invalid);it;it++) {
      if(!*it) {
	IndexC i = it.Index(); 
	temp[i][i] = 1.0;
      }
    }
    double sum = temp.Sum();
    Slice1dC<RealT> slice = temp.Diagonal();
    double diagsum = slice.Sum();
    double diagprod = slice.Product();
    double offdiagsum = (sum - temp.Rows()) / (temp.Rows()*temp.Cols());
    
    if (Abs(diagsum-temp.Rows())>1e-6) {
      if(verbose)
	cout << "IsMarginal(), Diagonal Sum: " << Abs(diagsum-temp.Rows()) << "\n";
      return true;
    }
    if (Abs(diagprod-1.0)>1e-6) {
      if(verbose)      
	cout << "IsMarginal(), Diagonal Product: " << Abs(diagprod-1.0) << "\n";
      return true;
    }
    if (Abs(offdiagsum)>1e-6) {
      if(verbose)
	cout << "IsMarginal(), Off-diagonal sum: " << offdiagsum << "\n";
      return true;
    }
    return false;
  }
}
