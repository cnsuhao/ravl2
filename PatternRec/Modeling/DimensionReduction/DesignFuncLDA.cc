// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Modeling/DimensionReduction/DesignFuncLDA.cc"

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
    strm >> mean >> lda;
  }
  
  //: Load from binary stream.
  
  DesignFuncLDABodyC::DesignFuncLDABodyC(BinIStreamC &strm)
    : DesignFuncReduceBodyC(strm)
  {
    strm >> mean >> lda;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignFuncLDABodyC::Save(ostream &out) const {
    if(!DesignFuncReduceBodyC::Save(out))
      return false;
    out << " " << mean << " " << lda;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignFuncLDABodyC::Save(BinOStreamC &out) const {
    if(!DesignFuncReduceBodyC::Save(out))
      return false;
    out << " " << mean << " " << lda;
    return true;
  }

  //: Create the LDA  function from the given data.
  
  FunctionC DesignFuncLDABodyC::Apply(const DataSetVectorLabelC &in) {

     SampleC<VectorC>   inVecs(in.Sample1().Size());
    for(SampleIterC<VectorC> it(in.Sample1()); it ;it++)
      inVecs += *it;
  
    UIntT N  =  inVecs.Size();
    UIntT d =  inVecs.First().Size();
    UIntT maxN =  UIntT(0.2* (RealT)d);   //maximum nof data to use for the PCA step
    SampleC<VectorC> inVecsPca(Min(N,maxN));
    if(N <maxN)  inVecsPca= inVecs;
    else    for(UIntT i = 0; i<maxN;i++)  inVecsPca.Append(inVecs.Pick());
      
    DesignFuncPCAC pca(varPreserved);
    FunctionC pcaFunc = pca.Apply(inVecsPca);
    mean = pca.Mean();
    SampleC<VectorC> outPca = pcaFunc.Apply(in.Sample1());

    DataSetVectorLabelC inLda(outPca, in.Sample2());

    MatrixC Sb = inLda.BetweenClassScatter ();
    MatrixC Sw = inLda.WithinClassScatter ();
    MatrixC matLDA = DesignMatrixTransformation(Sw, Sb);
    
    lda = matLDA.SubMatrix(matLDA.Rows(),Min(matLDA.Cols(),in.Sample2().MaxValue())).T() * pca.Pca().Matrix();

    return FuncMeanProjectionC(mean, lda);
  }

  //: Design the transform using the matrix transformation method
  
  MatrixC DesignFuncLDABodyC::DesignMatrixTransformation(const MatrixC &sw,const MatrixC &sb) {

    RealT smallValue = 1.0e-10;
    VectorMatrixC eigensSw = EigenVectors (sw);
    eigensSw.Sort ();
    VectorC eigenValsSw = eigensSw.Vector();
    MatrixC eigenVecsSw = eigensSw.Matrix();

    //: check if there is any unvalid eigen values
    UIntT firstZeroIndex = eigenValsSw.Size()-1;
    while ((eigenValsSw[firstZeroIndex ]<smallValue) && (firstZeroIndex>0)) firstZeroIndex --;
    firstZeroIndex ++;
    VectorC eigenValsSw2 = eigenValsSw.From(0, firstZeroIndex);
    MatrixC eigenVecsSw2 = eigenVecsSw.SubMatrix(eigenVecsSw.Rows(), firstZeroIndex);

    VectorC vec(eigenValsSw2.Size());
    vec.Fill (0.0);
    for (IndexC ind = 0; ind < vec.Size(); ind++)  vec[ind] = 1.0 / sqrt(eigenValsSw2[ind]);

    MatrixC identity = MatrixC::Identity(vec.Size());
    MatrixC diag = diag.SetDiagonal(vec);

    MatrixC B = eigenVecsSw2 * diag;
    MatrixC BT = B.T();
    
    MatrixC S_hat = (BT * sb) * B;
    
    VectorMatrixC eigenVecsS_hat = EigenVectors (S_hat);
    eigenVecsS_hat.Sort ();
    VectorC temp = eigenVecsS_hat.Vector();
    firstZeroIndex = temp.Size()-1;
    while ((temp[firstZeroIndex ]<smallValue) && (firstZeroIndex>0)) firstZeroIndex --;
    firstZeroIndex ++;
    MatrixC V_hat = eigenVecsS_hat.Matrix().SubMatrix(eigenVecsS_hat.Matrix().Rows(), firstZeroIndex);
    MatrixC matLda = B * V_hat;

    for (IndexC index2 = 0; index2 < matLda.Cols(); index2++) {
      Slice1dC<RealT> slice = matLda.SliceColumn(index2);
      slice /= slice.Modulus();
    }

    return matLda;
  }

}
