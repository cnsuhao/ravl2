// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DimensionReduction/ReducePCA.cc"

#include "Ravl/PatternRec/ReducePCA.hh"
#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/Collection.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/MeanCovariance.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
#define FOR_MATRIX_COLS(matrix, index) \
  for (IndexC index = 0; index < (matrix).Cols(); index++)

#define FOR_MATRIX_ROWS(matrix, index) \
  for (IndexC index = 0; index < (matrix).Rows(); index++)

#define FOR_VECTOR(vec, index) \
  for (IndexC index = 0; index < (vec).Size(); index++)

  //: Design the transform.
  
  void ReducePCABodyC::DesignHighDim(SampleC<VectorC> &sample,RealT variation) {
    // FIXME :- This could be implemented more efficently.
    
    SampleVectorC sv(sample);
    UIntT N = sample.Size(); // number of training samples
    if(N == 0)
      return ;
    UIntT d = sample.First().Size(); // input dimension
    
    // Calculate difference vectors
    
    mean = sv.Mean();
    CollectionC<VectorC> collection(sample.Size());
    for(SampleIterC<VectorC> it(sample);it;it++) 
      collection.Insert(*it - mean);
    
    MatrixC A (d, N);
    FOR_MATRIX_COLS (A, index) {
      A.SetColumn (index, collection.Pick().SArray1d());
    }
    
    // Construct L=A^transpose A
    MatrixC AT = A.T();
    MatrixC L = AT.AAT();
    L /= N;

    // Calculate Eigenvectors.
    VectorMatrixC Leigenvecs  =  EigenVectors(L);
    //cout << "finished computing eigen vecs: " << endl << flush;
    
    ONDEBUG(cerr << "Values=" << Leigenvecs.Vector() << "\n");

    Leigenvecs.Sort();
    // Create output matrix Wpca
    MatrixC Wpca = A * Leigenvecs.Matrix();
    
    VectorC smallVec(d); 
    smallVec.Fill(0.0);
    
    FOR_MATRIX_COLS (Wpca,index2) {
      if (Leigenvecs.Vector()[index2] < 1e-10) 
	Wpca.SetColumn (index2,smallVec);
      else {
	Slice1dC<RealT> slice = Wpca.SliceColumn(index2);
	slice /= slice.Modulus();
      }
    }
    VectorC temp (Wpca.Cols());
    temp.Fill (0.0);
    
    // Do dot products on transposed matrices its faster.
    MatrixC WpcaT = Wpca.T();
    FOR_VECTOR (temp,index3) {
      VectorC sli(WpcaT.SliceRow(index3));
      for(UIntT index4 = 0;index4 < AT.Rows();index4++) {
	temp[index3] += Sqr(VectorC(AT.SliceRow(index4)).Dot(sli));
      }
    }
    
    temp /= N;
    RealT total = temp.Sum();
    RealT runningTotal = 0.0;
    UIntT numComponents = 0;
    //ONDEBUG(cerr << "Values=" << temp << "\n");
    if (variation < 1.0) {
      RealT limit = variation*total;
      while ((runningTotal += temp[numComponents++]) < limit);
    } else {
      numComponents = UIntT(variation < temp.Size()? variation: temp.Size());
      for (UIntT i = 0; i < numComponents; i++)
	runningTotal += temp[i];
    }
    InputSize(d);
    OutputSize(numComponents);
    pca = VectorMatrixC (temp.From(0,numComponents-1),
			 Wpca.SubMatrix(d,numComponents).T());
    
    proj = pca.Matrix();
    
    // ONDEBUG(cerr << "Mean=" << mean << "\n");
    // ONDEBUG(cerr << "Proj=" << proj << "\n");
  }


  //: Design the transform.
  
  void ReducePCABodyC::DesignLowDim(SampleC<VectorC> &sample,RealT variation) {
    IntT dim = sample.First().Size();
    //SetSizeX (dim);
    SampleVectorC sv(sample);
    MeanCovarianceC stats = sv.MeanCovariance();
    mean = stats.Mean();
    
    VectorMatrixC Leigenvecs =  EigenVectors(stats.Covariance());
    
    //: need to sort matrix into order
    Leigenvecs.Sort();

    ONDEBUG(cerr << "Values=" << Leigenvecs.Vector() << "\n");
    
    RealT total = Leigenvecs.Vector().Sum();
    RealT runningTotal = 0.0;
    UIntT numComponents = 0;
    
    if (variation < 1.0) 
      while ((runningTotal += Leigenvecs.Vector()[numComponents++]) < variation*total);
    else {
      numComponents = UIntT(variation < dim? variation: dim);
      for (UIntT i = 0; i < numComponents; i++)
	runningTotal += Leigenvecs.Vector()[i];
    }
    varPreserved = runningTotal / total;
    
    pca = VectorMatrixC (Leigenvecs.Vector().From(0,numComponents-1),
			 Leigenvecs.Matrix().SubMatrix(dim,numComponents).T());
    
    InputSize(mean.Size());
    OutputSize(numComponents);
    
    proj = pca.Matrix();
    
  }

}
