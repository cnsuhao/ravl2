// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/DesignFuncLDA.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Default constructor.
  
  DesignFuncLDABodyC::DesignFuncLDABodyC(RealT variationPreserved)
    : DesignFuncReduceBodyC(variationPreserved),
      forceHimDim(false)
  {}
  
  //: Load from stream.
  
  DesignFuncLDABodyC::DesignFuncLDABodyC(istream &strm) 
    : DesignFuncReduceBodyC(strm)
  {
   strm >> forceHimDim;
  }
  
  //: Load from binary stream.
  
  DesignFuncLDABodyC::DesignFuncLDABodyC(BinIStreamC &strm)
    : DesignFuncReduceBodyC(strm)
  {
    strm >> forceHimDim;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignFuncLDABodyC::Save(ostream &out) const {
    if(!DesignFuncReduceBodyC::Save(out))
      return false;
    out << ' ' << forceHimDim;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignFuncLDABodyC::Save(BinOStreamC &out) const {
    if(!DesignFuncReduceBodyC::Save(out))
      return false;
    out << forceHimDim;
    return true;
  }

  //: Create function from the given data.
  
  FunctionC DesignFuncLDABodyC::Apply(const DataSetVectorLabelC &in) {

    DesignFuncPCAC pca(varPreserved);
    SampleC<VectorC> inVecs = in.Sample1();
    FunctionC pcaFunc = pca.Apply(inVecs);
    mean = pca.Mean();
    SampleC<VectorC> outPca = pcaFunc.Apply(inVecs);

    DataSetVectorLabelC inLda(outPca, in.Sample2());
    MatrixC Sb = inLda.BetweenClassScatter ();
    MatrixC Sw = inLda.WithinClassScatter ();
    lda = DesignMatrixTransformation(Sw, Sb);

    return FuncMeanProjectionC(mean, lda);
  }

  //: Design the transform.
  
  MatrixC DesignFuncLDABodyC::DesignMatrixTransformation(const MatrixC &sw,const MatrixC &sb) {

    RealT smallValue = 1.0e-10;
    VectorMatrixC eigensSw = EigenVectors (sw);
    ONDEBUG(cerr << "Values=" << eigensSw.Vector() << "\n");
    eigensSw.Sort ();
    VectorC eigenValsSw = eigensSw.Vector();
    MatrixC eigenVecsSw = eigensSw.Matrix();
    
    VectorC vec(eigenValsSw.Size());
    vec.Fill (0.0);
    for (IndexC ind = 0; ind < vec.Size(); ind++) {
      if (eigenValsSw[ind] != 0.0) vec[ind] = 1.0 / sqrt(eigenValsSw[ind]);
    }  

    MatrixC identity = MatrixC::Identity(vec.Size());
    MatrixC diag = diag.SetDiagonal(vec);

    MatrixC B = eigenVecsSw * diag;
    MatrixC BT = B.T();
    
    MatrixC S_hat = (BT * sb) * B;
    
    VectorMatrixC eigenVecsS_hat = EigenVectors (S_hat);
    eigenVecsS_hat.Sort ();
    VectorC temp = eigenVecsS_hat.Vector();
    UIntT firstZeroIndex = temp.Size()-1;
    for (UIntT ind = temp.Size()-1; ind >= 0; ind--) if(temp[ind] < smallValue) firstZeroIndex = ind;
    MatrixC V_hat = eigenVecsS_hat.Matrix().SubMatrix(eigenVecsS_hat.Matrix().Rows(), firstZeroIndex);
    MatrixC matLda = B * V_hat;

    for (IndexC index2 = 0; index2 < matLda.Cols(); index2++) {
      Slice1dC<RealT> slice = matLda.SliceColumn(index2);
      slice /= slice.Modulus();
    }

    return matLda;
  }

}
