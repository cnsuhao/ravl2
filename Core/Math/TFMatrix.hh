// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLTFMATRIX_HEADER
#define RAVLTFMATRIX_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Math/TFMatrix.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Core.Math"

#include "Ravl/TFVector.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/SBfAcc.hh"

namespace RavlN {
  
  class BinIStreamC;
  class BinOStreamC;
  
  //! userlevel=Advanced
  //: Fixed size NxM matrix.
  // Provides basic matrix arithmetic operations for
  // an arbitrary sized matrix.
  
  template<class DataT,unsigned int N,unsigned int M>
  class TFMatrixC {
  public:
    TFMatrixC()
      {}
    //: Default constructor.

    TFMatrixC(const DataT *init);
    //: Constructor.
    // Initalise matrix with values from 'init'.
    
    SizeT Size1() const
      { return N; }
    //: Get size of matrix in the first dimention

    SizeT Size2() const
      { return M; }
    //: Get size of matrix in the second dimention

    bool Contains(const Index2dC &i) const
      { return ((UIntT) i.Row().V()) < Size1() && ((UIntT) i.Col().V()) < Size2(); }
    //: Test if array contains index i·
    
    DataT &operator[](const Index2dC &ind) { 
#if RAVL_CHECK
      if(!Contains(ind)) 
	IssueError(__FILE__,__LINE__,"Index %d,%d out of range, 0 - %u,0 - %u",ind[0].V(),ind[1].V(),N,M);
#endif
      return data[ind.Row().V()][ind.Col().V()]; 
    }
    //: Access item.

    const DataT &operator[](const Index2dC &ind) const { 
#if RAVL_CHECK
      if(!Contains(ind))
	IssueError(__FILE__,__LINE__,"Index %d,%d out of range, 0 - %u , 0 - %u",ind[0].V(),ind[1].V(),N,M);
#endif
      return data[ind.Row().V()][ind.Col().V()]; 
    }
    //: Access item.
    
    SizeBufferAccessC<DataT> operator[](UIntT ind) { 
#if RAVL_CHECK
      if(ind >= Size1())
	IssueError(__FILE__,__LINE__,"Index %d out of range, 0 - %u",ind,N);
#endif
      return SizeBufferAccessC<DataT>((DataT *)(data[ind]),M);
    }
    //: Access item.

    const SizeBufferAccessC<DataT> operator[](UIntT ind) const { 
#if RAVL_CHECK
      if(ind >= Size1())
	IssueError(__FILE__,__LINE__,"Index %d out of range, 0 - %u ",ind,N);
#endif
      return SizeBufferAccessC<DataT>((DataT *)(data[ind]),M);
    }
    //: Access item.

    inline void Fill(const DataT &dat);
    //: Fill array with value 'dat'.
    
    bool operator==(const TFMatrixC<DataT,N,M> &oth) const;
    //: Is exactly equal ?

    bool operator!=(const TFMatrixC<DataT,N,M> &oth) const;
    //: Is not exactly equal ?
    
    TFMatrixC<DataT,N,M> operator+(const TFMatrixC<DataT,N,M> & mat) const;
    //: Sum 2 matrixes.

    TFMatrixC<DataT,N,M> operator-(const TFMatrixC<DataT,N,M> & mat) const;
    //: Subtract 2 matrixes.

    TFMatrixC<DataT,N,M> operator*(const DataT &val) const;
    //: Multiply all elements of the matrix by a scaler 'val'.
    // put results in a new matrix

    TFMatrixC<DataT,N,M> operator/(const DataT &val) const;
    //: Divide all elements of the matrix by a scaler 'val'.
    // put results in a new matrix

    const TFMatrixC<DataT,N,M> &operator+=(const TFMatrixC<DataT,N,M> & mat);
    //: Add another matrix to this one.

    const TFMatrixC<DataT,N,M> &operator-=(const TFMatrixC<DataT,N,M> & mat);
    //: Subtract another matrix from this one.
    
    const TFMatrixC<DataT,N,M> &operator*=(const DataT &val);
    //: Multiply all elements of this matrix by a scaler 'val'.
    
    const TFMatrixC<DataT,N,M> &operator/=(const DataT &val);
    //: Divide all elements of this matrix by a scaler 'val'.
    
    TFVectorC<DataT,N> operator*(const TFVectorC<DataT,M> & mat) const;
    //: Multiply vector by the matrix.

    template<unsigned int MT>
      TFMatrixC<DataT,M,MT> operator*(const TFMatrixC<DataT,N,MT> & mat) const
    {
      TFMatrixC<DataT,N,MT> ret;
      for(UIntT i = 0;i < N;i++)
	for(UIntT j = 0;j < MT;j++)
	{
	  DataT &val = ret[i][j];
	  val = 0;
	  for(UIntT k = 0;k < M;k++)
	    val += data[i][k] * mat[k][j];
	}
      return ret;
    }
    //: Mutiply two matrixes.

    template<unsigned int MT>
      TFMatrixC<DataT,M,MT> TMul(const TFMatrixC<DataT,N,MT> & mat) const 
    {
      TFMatrixC<DataT,M,MT> ret;
      for(UIntT i = 0;i < M;i++)
	for(UIntT j = 0;j < MT;j++)
        {
	  DataT &val = ret[i][j];
	  val = 0;
	  for(UIntT k = 0;k < N;k++)
	    val += data[k][i] * mat[k][j];
	}
      return ret;
    }
    //: Transpose this matrix and Multiply by 'mat'
    
    template<unsigned int NT>
      TFMatrixC<DataT,N,NT> MulT(const TFMatrixC<DataT,NT, M> & mat) const {
      TFMatrixC<DataT,N,NT> ret;
      for(UIntT i = 0;i < N;i++)
	for(UIntT j = 0;j < NT;j++)
	{
	  DataT &val = ret[i][j];
	  val = 0;
	  for(UIntT k = 0; k < M;k++)
	    val += data[i][k] * mat[j][k];
	}
      return ret;
    }
    //: Mutiply this matrix by transpose of 'mat'
    
    TFVectorC<DataT,M> TMul(const TFVectorC<DataT,N>& vec) const 
    {
      TFVectorC<DataT,M> ret;
      for(UIntT i = 0; i < M; i++)
      {
	ret[i] = 0.0;
	for(UIntT j = 0; j < N;j++)
	  ret[i] += data[j][i] * vec[j];
      }
      return ret;
    }
    //: Transpose this matrix and multiply by 'vec'

    TFMatrixC<DataT,M,N> T() const;
    //: Matrix transpose.
    
    DataT SumOfAbs() const;
    //: Return the sum of the absolute values of the matrix.

    inline bool Limit(const DataT &min,const DataT &max);
    //: Limit all values in this matrix to between min and max.
    // Returns true if all values in the matrix are between the limits.
    
  protected:

    DataT data[N][M];

    //friend class TFMatrixC<DataT,M,N>; // Make the transpose a friend.
  };
  
  template<class DataT,unsigned int N,unsigned int M>
  ostream &operator<<(ostream &s,const TFMatrixC<DataT,N,M> &oth) {
    for(UIntT i = 0;i < N;i++) {
      for(UIntT j = 0;j < M;j++)
	s << oth[i][j] << ' ';
      s << '\n';
    }
    return s;
  }

  template<class DataT,unsigned int N,unsigned int M>
  istream &operator>>(istream &s,TFMatrixC<DataT,N,M> &oth) {
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	s >> oth[i][j];
    return s;
  }
  
  template<class DataT,unsigned int N,unsigned int M>
  BinIStreamC &operator>>(BinIStreamC &s,TFMatrixC<DataT,N,M> &oth) {
    for(UIntT i = 0;i < N;i++) {
      for(UIntT j = 0;j < M;j++)
	s >> oth[i][j];
    }
    return s;
  }
  
  template<class DataT,unsigned int N,unsigned int M>
  BinOStreamC &operator<<(BinOStreamC &s,const TFMatrixC<DataT,N,M> &oth) {    
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	s << oth[i][j];
    return s;
  }

  template<class DataT,unsigned int N,unsigned int M>
  TFMatrixC<DataT,N,M>::TFMatrixC(const DataT *init) {
    const DataT *place = init;
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	data[i][j] = *(place++);
  }
  
  template<class DataT,unsigned int N,unsigned int M>
  inline 
  void TFMatrixC<DataT,N,M>::Fill(const DataT &dat) {
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	data[i][j] = dat;
  }

  template<class DataT,unsigned int N,unsigned int M>
  bool TFMatrixC<DataT,N,M>::operator==(const TFMatrixC<DataT,N,M> &oth) const {
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	if(data[i][j] != oth.data[i][j])
	  return false;
    return true;
  }
  
  template<class DataT,unsigned int N,unsigned int M>
  bool TFMatrixC<DataT,N,M>::operator!=(const TFMatrixC<DataT,N,M> &oth) const {
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	if(data[i][j] != oth.data[i][j])
	  return true;
    return false;
  }

  template<class DataT,unsigned int N,unsigned int M>
  TFMatrixC<DataT,N,M> TFMatrixC<DataT,N,M>::operator+(const TFMatrixC<DataT,N,M> & mat) const {
    TFMatrixC<DataT,N,M> ret;
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	ret.data[i][j] = data[i][j] + mat.data[i][j];
    return ret;
  }

  template<class DataT,unsigned int N,unsigned int M>
  TFMatrixC<DataT,N,M> TFMatrixC<DataT,N,M>::operator-(const TFMatrixC<DataT,N,M> & mat) const {
    TFMatrixC<DataT,N,M> ret;
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	ret.data[i][j] = data[i][j] - mat.data[i][j];
    return ret;
  }

  template<class DataT,unsigned int N,unsigned int M>
  TFMatrixC<DataT,N,M> TFMatrixC<DataT,N,M>::operator*(const DataT & val) const {
    TFMatrixC<DataT,N,M> ret;
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	ret.data[i][j] = data[i][j] * val;
    return ret;
  }

  template<class DataT,unsigned int N,unsigned int M>
  TFMatrixC<DataT,N,M> TFMatrixC<DataT,N,M>::operator/(const DataT & val) const {
    TFMatrixC<DataT,N,M> ret;
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	ret.data[i][j] = data[i][j] / val;
    return ret;
  }
  
  template<class DataT,unsigned int N,unsigned int M>
  const TFMatrixC<DataT,N,M> &TFMatrixC<DataT,N,M>::operator+=(const TFMatrixC<DataT,N,M> & mat) {
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	data[i][j] += mat.data[i][j];
    return *this;
  }
  
  template<class DataT,unsigned int N,unsigned int M>
  const TFMatrixC<DataT,N,M> &TFMatrixC<DataT,N,M>::operator-=(const TFMatrixC<DataT,N,M> & mat) {
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	data[i][j] -= mat.data[i][j];
    return *this;
  }

  template<class DataT,unsigned int N,unsigned int M>
  const TFMatrixC<DataT,N,M> &TFMatrixC<DataT,N,M>::operator*=(const DataT & val) {
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	data[i][j] *= val;
    return *this;
  }

  template<class DataT,unsigned int N,unsigned int M>
  const TFMatrixC<DataT,N,M> &TFMatrixC<DataT,N,M>::operator/=(const DataT & val) {
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	data[i][j] /= val;
    return *this;
  }
  
  template<class DataT,unsigned int N,unsigned int M>
  TFVectorC<DataT,N> TFMatrixC<DataT,N,M>::operator*(const TFVectorC<DataT,M> & vec) const {
    TFVectorC<DataT,N> ret; // N=r M=c
    for(UIntT i = 0;i < N;i++) {
      ret[i] = 0;
      for(UIntT j = 0;j < M;j++)
	ret[i] += data[i][j] * vec[j];
    }
    return ret;
  }

  template<class DataT,unsigned int N,unsigned int M>
  TFMatrixC<DataT,M,N> TFMatrixC<DataT,N,M>::T() const {
    TFMatrixC<DataT,M,N> ret;
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	ret[j][i] = data[i][j];
    return ret;
  }

  //: Return the sum of the absolute values of the matrix.

  template<class DataT,unsigned int N,unsigned int M>
  DataT TFMatrixC<DataT,N,M>::SumOfAbs() const {
    DataT ret = 0;
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	ret += Abs(data[i][j]);
    return ret;
  }

  template<class DataT,unsigned int N,unsigned int M>
  inline bool TFMatrixC<DataT,N,M>::Limit(const DataT &min,const DataT &max) {
    bool ret = true;
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++) {
	if(data[i][j] > max) {
	  data[i][j] = max;
	  ret = false;
	  continue;
	}
	if(data[i][j] < min) {
	  data[i][j] = min;
	  ret = false;
	}
      }
    
    return ret;
  }

  template<class DataT,unsigned int N,unsigned int M>
  TFMatrixC<DataT,N,M> operator*(const DataT & val,const TFMatrixC<DataT,N,M> &mat) {
    TFMatrixC<DataT,N,M> ret;
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	ret[i][j] = val * mat[i][j];
    return ret;
  }
  
  template<class DataT,unsigned int N,unsigned int M>
  TFMatrixC<DataT,N,M> operator/(const DataT & val,const TFMatrixC<DataT,N,M> &mat) {
    TFMatrixC<DataT,N,M> ret;
    for(UIntT i = 0;i < N;i++)
      for(UIntT j = 0;j < M;j++)
	ret[i][j] = val / mat[i][j];
    return ret;
  }



}

#endif
