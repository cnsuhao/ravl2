// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////
//! rcsid="$Id: TMatrixIO.cc 4777 2005-01-18 14:28:18Z ees1wc $"
//! lib=RavlMathIO
//! file="Ravl/Math/IO/TMatrixIO.cc"

#include "Ravl/DP/Converter.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"
#include "Ravl/VectorMatrix.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"

namespace RavlN {
  static TypeNameC type1(typeid(TMatrixC<FloatT>),"RavlN::TMatrixC<FloatT>");
  static TypeNameC type2(typeid(TVectorC<FloatT>),"RavlN::TVectorC<FloatT>");
  //  static TypeNameC type3(typeid(VectorTMatrixC<FloatT>),"RavlN::VectorTMatrixC<FloatT>");
  static TypeNameC type4(typeid(SArray1dC<TMatrixC<FloatT> >),"RavlN::SArray1dC<TMatrixC<FloatT>>");
  static TypeNameC type5(typeid(SArray1dC<TVectorC<FloatT> >),"RavlN::SArray1dC<TVectorC<FloatT>>");
  //static TypeNameC type6(typeid(SArray1dC<VectorTMatrixC<FloatT>>),"RavlN::SArray1dC<VectorTMatrixC<FloatT>>");
  
  void InitTMatrixIO()
  {}
  
  FileFormatStreamC<TMatrixC<FloatT> > FileFormatStream_TMatrix_Float;
  FileFormatStreamC<TVectorC<FloatT> > FileFormatStream_TVector_Float;
  //FileFormatStreamC<VectorTMatrixC<FloatT>> FileFormatStream_VectorMatrix;
  
  FileFormatBinStreamC<TMatrixC<FloatT> > FileFormatBinStream_TMatrix_Float;
  FileFormatBinStreamC<TVectorC<FloatT> > FileFormatBinStream_TVector_Float;
  //FileFormatBinStreamC<VectorTMatrixC<FloatT>> FileFormatBinStream_VectorMatrix;
  
  FileFormatStreamC<SArray1dC<TMatrixC<FloatT> > > FileFormatStream_SArray1dC_TMatrix_Float;
  FileFormatStreamC<SArray1dC<TVectorC<FloatT> > > FileFormatStream_SArray1dC_TVector_Float;
  //FileFormatStreamC<SArray1dC<VectorTMatrixC<FloatT>> > FileFormatStream_SArray1dC_VectorMatrix;
  
  FileFormatBinStreamC<SArray1dC<TMatrixC<FloatT> > > FileFormatBinStream_SArray1dC_TMatrix_Float;
  FileFormatBinStreamC<SArray1dC<TVectorC<FloatT> > > FileFormatBinStream_SArray1dC_TVector_Float;
  //FileFormatBinStreamC<SArray1dC<VectorTMatrixC<FloatT>> > FileFormatBinStream_SArray1dC_VectorMatrix;
  
  //-----------------------------------------------------------------------------------------
  // VectorC converters.
  
  TVectorC<FloatT> Vector2TVectorFloat(const VectorC &vec) {
    TVectorC<FloatT> ret(vec.Size());
    for(SArray1dIter2C<FloatT,RealT> it(ret,vec);it;it++)
      it.Data1() = static_cast<FloatT>(it.Data2());
    return ret;
  }
  
  VectorC TVectorFloat2Vector(const TVectorC<FloatT> &vec) {
    VectorC ret(vec.Size());
    for(SArray1dIter2C<RealT,FloatT> it(ret,vec);it;it++)
      it.Data1() = static_cast<RealT>(it.Data2());
    return ret;
  }
  
  
  DP_REGISTER_CONVERSION_NAMED(Vector2TVectorFloat,2,
			       "RavlN::TVectorC<FloatT> RavlN::Convert(const RavlN::VectorC &)");

  DP_REGISTER_CONVERSION_NAMED(TVectorFloat2Vector,1,
			       "RavlN::VectorC RavlN::Convert(const RavlN::TVectorC<FloatT> &)");


  //-----------------------------------------------------------------------------------------
  // MatrixC converters.
  
  TMatrixC<FloatT> Matrix2TMatrixFloat(const MatrixC &mat) {
    TMatrixC<FloatT> ret(mat.Rows(),mat.Cols());
    for(SArray2dIter2C<FloatT,RealT> it(ret,mat);it;it++)
      it.Data1() = static_cast<FloatT>(it.Data2());
    return ret;
  }
  
  MatrixC TMatrixFloat2Matrix(const TMatrixC<FloatT> &mat) {
    MatrixC ret(mat.Rows(),mat.Cols());
    for(SArray2dIter2C<RealT,FloatT> it(ret,mat);it;it++)
      it.Data1() = static_cast<RealT>(it.Data2());
    return ret;
  }
  
  
  DP_REGISTER_CONVERSION_NAMED(Matrix2TMatrixFloat,2,
			       "RavlN::TMatrixC<FloatT> RavlN::Convert(const RavlN::MatrixC &)");

  DP_REGISTER_CONVERSION_NAMED(TMatrixFloat2Matrix,1,
			       "RavlN::MatrixC RavlN::Convert(const RavlN::TMatrixC<FloatT> &)");
  
  
}
