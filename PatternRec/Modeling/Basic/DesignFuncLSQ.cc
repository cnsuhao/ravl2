
#include "Ravl/PatternRec/DesignFuncLSQ.hh"
#include "Ravl/PatternRec/SampleVector.hh"

namespace RavlN {
  
  //: Create least squares designer.
  
  DesignFuncLSQBodyC::DesignFuncLSQBodyC(UIntT norder,bool northogonal) 
    : order(norder),
      orthogonal(northogonal)
  {
  }
  
  //: Create function from the given data.
  
  FunctionC DesignFuncLSQBodyC::Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out) {
    FuncLinearCoeffC func;
    SampleVectorC vin(in);
    SampleVectorC vout(out);
    
    if(in.IsEmpty() || out.IsEmpty()) {
      cerr << "DesignFuncLSQBodyC::Apply(), WARNING: Asked to design a function without any data. ";
      return func;
    }
    UIntT inSize = vin.VectorSize();
    UIntT outSize = vout.VectorSize();
    func.InputSize(inSize);
    func.OutputSize(outSize);
    UIntT coeffs = func.NumberCoeffs(inSize);
    
    MatrixC Y(outSize,vout.Size());
    MatrixC X(coeffs,vin.Size());
    
#if 0
    IndexT index = 0;
    for (ConstDLIterC<NumVVDataC> elem (train); elem.IsElm (); elem.Next ()) {
      Y.SetCol (index, elem.Data().Output(), SizeY());
      X.SetCol (index++, MakeInput (elem.Data().Input()), Xdim);
    }
    SArray1dC<int> _invalidX (Xdim);
    _invalidX.Fill (1);
    if (!IsMarginal (X.MulT(X),_invalidX))
      _A = Y*X.TMul((X.MulT(X)).I());
    else {
      _invalidX.Fill (0);
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
    return FunctionC();
  }
  
  //: Create function from the given data, and sample weights.
  
  FunctionC DesignFuncLSQBodyC::Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out,const SampleC<RealT> &weight) {
    RavlAssertMsg(0,"DesignFuncLSQBodyC::Apply(in,out,weight), Not implemented. \n"); 
    return FunctionC();
  }
  
  
#if 0
  bool IsMarginal (MatrixC m, SArray1dC<int> invalid) {
    MatrixC temp = m.I()*m;
    temp.SetSmallToBeZero (1e-9);
    FOR_SARRAY1 (invalid,i)
      if (!invalid[i])
	temp.P(i,i) = 1.0;
    double sum = 0.0;
    //  cout << temp <<"\n";
    FOR_MATRIX (temp,i1,i2)
      sum += temp.G(i1,i2);
    double diagsum = temp.GetDiag().Sum();
    double diagprod = temp.DiagonalProduct();
    double offdiagsum = (sum - temp.RDim()) / (temp.RDim()*temp.CDim());
    if (::Abs(diagsum-temp.RDim())>1e-6) {
      cout << "Diagonal Sum: " << ::Abs(diagsum-temp.RDim()) << "\n";
      return true;
    }
    if (::Abs(diagprod-1.0)>1e-6) {
      cout << "Diagonal Product: " << ::Abs(diagprod-1.0) << "\n";
      return true;
    }
    if (::Abs(offdiagsum)>1e-6) {
      cout << "Off-diagonal sum: " << offdiagsum << "\n";
      return true;
    }
    return false;
  }
#endif  
}
