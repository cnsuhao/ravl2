// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TFVECTOR_HEADER
#define RAVL_TFVECTOR_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Tuples"
//! file="Ravl/Core/Base/TFVector.hh"
//! lib=RavlCore
//! userlevel=Advanced
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/Assert.hh"
#include "Ravl/Math.hh"
#include "Ravl/Types.hh"
#include "Ravl/Stream.hh"

namespace RavlN {
  class BinIStreamC;
  class BinOStreamC;
  
  template<class DataT,unsigned int N> class TFVectorC;
  template<class DataT,unsigned int N,unsigned int M> class TFMatrixC;
  
  template<class DataT,unsigned int N>
  istream &operator>>(istream &in,TFVectorC<DataT,N> &dat);
  
  template<class DataT,unsigned int N>
  ostream &operator<<(ostream &in,const TFVectorC<DataT,N> &dat);
  
  template<class DataT,unsigned int N>
  inline BinIStreamC &operator>>(BinIStreamC &in,TFVectorC<DataT,N> &dat);
  
  template<class DataT,unsigned int N>
  inline BinOStreamC &operator<<(BinOStreamC &in,const TFVectorC<DataT,N> &dat);
  
  template<unsigned int N>
  inline ostream &operator<<(ostream &out,const TFVectorC<ByteT,N> &dat);
  
  template<unsigned int N>
  inline istream &operator>>(istream &in,TFVectorC<ByteT,N> &dat);
  
  template<unsigned int N>
  inline ostream &operator<<(ostream &out,const TFVectorC<SByteT,N> &dat);
  
  template<unsigned int N>
  inline istream &operator>>(istream &in,TFVectorC<SByteT,N> &dat);
  
  //! userlevel=Advanced
  //: Fixed size vector.
  
  template<class DataT,unsigned int N>
  class TFVectorC {
  public:
#if RAVL_COMPILER_VISUALCPP
    enum { SizeV = N }; 
#else
    static const int SizeV = N;
#endif
    
    TFVectorC()
    {}
    //: Default constructor.
    // Note: The default constructor of 'DataT' is used to contruct
    // the elements of the vector, for builtin types this means
    // their values will be undefined.
    
    explicit TFVectorC(const DataT *init);
    //: Value constructor.
    // Copy values from 'init'. It is the user's responsibility
    // to ensure that data has at least 'N' elements. 
    
    explicit TFVectorC(UIntT size)
    { RavlAssert(size == N); }
    //: This constructor is for compatibility with arbitrarily sized vectors.
    // Used by some templates.
  
    TFVectorC<DataT,N> Copy(void) const
      { return *this ; }
    //: return a copy of this vector 

  
    UIntT Size() const
    { return N; }
    //: Get size of array
    // Used by some templates.
    
    bool Contains(UIntT i) const
    { return i < N; }
    //: Test if array contains index i�
    
    DataT &operator[](UIntT ind) { 
#if RAVL_CHECK
      if(!Contains(ind)) 
	IssueError(__FILE__,__LINE__,"Index %u out of range, 0 - %u",ind,N);
#endif
      return data[ind]; 
    }
    //: Access item.

    const DataT &operator[](UIntT ind) const { 
#if RAVL_CHECK
      if(!Contains(ind)) 
	IssueError(__FILE__,__LINE__,"Index %u out of range, 0 - %u",ind,N);
#endif
      return data[ind]; 
    }
    //: Access item.

    inline bool operator==(const TFVectorC<DataT,N> & ind) const;
    //: is equal

    inline bool operator!=(const TFVectorC<DataT,N> & ind) const;
    //: is not equal
    
    inline void Fill(const DataT &dat);
    //: Fill array with value 'dat'.
    
    inline TFVectorC<DataT,N> Abs() const;
    //: Get an vector with Abs(x) run on all it values.
    
    inline const TFVectorC<DataT,N> & operator+=(const TFVectorC<DataT,N> & ind);
    //: Add an array to this one, inplace.
    
    inline const TFVectorC<DataT,N> & operator-=(const TFVectorC<DataT,N> & ind);
    //: Returns this index multiplied by index 'ind' item by item.

    inline const TFVectorC<DataT,N> & operator*=(const TFVectorC<DataT,N> & ind);
    //: Multiplies this index by index 'ind' item by item.

    inline const TFVectorC<DataT,N> & operator/=(const TFVectorC<DataT,N> & ind);
    //: Divides this index by index 'ind' item by item.
    
    inline TFVectorC<DataT,N> operator+(const TFVectorC<DataT,N> & ind) const;
    //: Adds this index and 'ind'.
  
    inline TFVectorC<DataT,N> operator-(const TFVectorC<DataT,N> & ind) const;
    //: Subtracts index 'ind' from this index.

    inline TFVectorC<DataT,N> operator*(const TFVectorC<DataT,N> & ind) const;
    //: Returns this object multiplied by index 'ind' item by item.

    inline TFVectorC<DataT,N> operator/(const TFVectorC<DataT,N> & ind) const;
    //: Returns this object devided by index 'ind' item by item.
    
    inline  TFVectorC<DataT,N> operator-() const;
    //: Returns opposite elements (unary minus operator).
    
    inline const TFVectorC<DataT,N> & operator*=(const DataT &alpha);
    //: Multiplies this index by number 'alpha'.

    inline const TFVectorC<DataT,N> & operator/=(const DataT &alpha);
    //: Divides this index by number 'alpha'.
    
    inline TFVectorC<DataT,N> operator*(const DataT &alpha) const;
    //: Returns this object mutliplied by alpha.
    
    inline TFVectorC<DataT,N> operator/(const DataT &alpha) const;
    //: Returns this object devided by alpha.

    inline DataT Dot(const TFVectorC<DataT,N> &oth) const {
      DataT ret = data[0] * oth.data[0];
      for(UIntT i = 1;i <N;i++)
	ret += data[i] * oth.data[i];
      return ret;
    }
    //: Calculate the dot product of this and 'oth' vector.
    
    TFMatrixC<DataT,N,N> &OuterProduct(const TFVectorC<DataT,N> &av, TFMatrixC<DataT,N,N> &result) const;
    //: Calculate the outer product of this vector with av.
    // The output is assigned to 'result'. A reference to 'result' is
    // returned. <p>
    // The implementation is in "Ravl/FMatrix.hh", it must be
    // included to use this function.
    
    TFMatrixC<DataT,N,N> &OuterProduct(TFMatrixC<DataT,N,N> &result) const;
    //: Calculate the outer product of this vector with itsself.
    // The output is assigned to 'result'. A reference to 'result' is
    // returned. <p>
    // The implementation is in "Ravl/FMatrix.hh", it must be
    // included to use this function.

    inline bool Limit(const DataT &min,const DataT &max);
    //: Limit all values in this vector to between min and max.
    // Returns true if all values in the vector are between the limits.
    
    //:---------------------
    //: Distance calculations
    
    inline DataT MaxValueDistance(const TFVectorC<DataT,N> & i) const;
    //: Returns the distance of two indexes in maximum value metric.
    
    inline DataT CityBlockDistance(const TFVectorC<DataT,N> & i) const;
    //: Returns the distance of two indexes in absolute value metric.
    
    inline DataT SqrEuclidDistance(const TFVectorC<DataT,N> & i) const;
    //: Returns the distance of two indexes in square Euclid metric.
    
    DataT Sum() const;
    //: Calculate the sum of all the vector elements.
    
    DataT SumOfSqr() const;
    //: Calculate the sum of the squares of all the vector elements.
    
    DataT SumOfAbs() const;
    //: Calculate the sum of the absolute values of all the vector elements.
    
    inline const TFMatrixC<DataT,1,N> &T() const;
    //: Transpose vector.
    // The implementation for this can be found in "Ravl/TFMatrix.hh"
    
#if RAVL_NEW_ANSI_CXX_DRAFT
    friend istream &operator>> <>(istream &in,TFVectorC<DataT,N> &dat);  
    friend ostream &operator<< <>(ostream &in,const TFVectorC<DataT,N> &dat);  
    friend BinIStreamC &operator>> <>(BinIStreamC &in,TFVectorC<DataT,N> &dat);
    friend BinOStreamC &operator<< <>(BinOStreamC &in,const TFVectorC<DataT,N> &dat);
#if RAVL_COMPILER_GCC3_4
    friend ostream &operator<< <>(ostream &out,const TFVectorC<ByteT,N> &dat);
    friend istream &operator>> <>(istream &in,TFVectorC<ByteT,N> &dat);
    friend ostream &operator<< <>(ostream &out,const TFVectorC<SByteT,N> &dat);
    friend istream &operator>> <>(istream &in,TFVectorC<SByteT,N> &dat);
#endif
#else
    friend istream &operator>> (istream &in,TFVectorC<DataT,N> &dat);  
    friend ostream &operator<< (ostream &in,const TFVectorC<DataT,N> &dat);  
    friend BinIStreamC &operator>> (BinIStreamC &in,TFVectorC<DataT,N> &dat);
    friend BinOStreamC &operator<< (BinOStreamC &in,const TFVectorC<DataT,N> &dat);
#endif    
  protected:
    DataT data[N];
  };
  
  template<class DataT>
  inline TFVectorC<DataT,2> TFVector2(const DataT &v1,const DataT &v2) {
    TFVectorC<DataT,2> ret;
    ret[0] = v1;
    ret[1] = v2;
    return ret;
  } 
  //: Create a 2d vector.
  // Helper function to make creation of fixed size vectors easier.
  
  template<class DataT>
  inline TFVectorC<DataT,3> TFVector3(const DataT &v1,const DataT &v2,const DataT &v3) {
    TFVectorC<DataT,3> ret;
    ret[0] = v1;
    ret[1] = v2;
    ret[2] = v3;
    return ret;
  } 
  //: Create a 3d vector.
  // Helper function to make creation of fixed size vectors easier.

  template<class DataT>
  inline TFVectorC<DataT,4> TFVector4(const DataT &v1,const DataT &v2,const DataT &v3,const DataT &v4) {
    TFVectorC<DataT,4> ret;
    ret[0] = v1;
    ret[1] = v2;
    ret[2] = v3;
    ret[3] = v4;
    return ret;
  } 
  //: Create a 3d vector.
  // Helper function to make creation of fixed size vectors easier.
  
  template<class DataT,unsigned int N>
  inline void SetZero(TFVectorC<DataT,N> &x) { 
    DataT xv;
    SetZero(xv);
    x.Fill(xv);
  }
  //: Set vector to zero.
  
  
  template<class DataT,unsigned int N>
  TFVectorC<DataT,N>::TFVectorC(const DataT *init) {
    for(UIntT i = 0;i < N;i++)
      data[i] = init[i];
  }
    
  template<class DataT,unsigned int N>
  inline 
  bool TFVectorC<DataT,N>::operator==(const TFVectorC<DataT,N> & ind) const {
    for(UIntT i = 0;i < N;i++)
      if(data[i] != ind[i])
	return false;
    return true;
  }
  
  template<class DataT,unsigned int N>
  inline 
  bool TFVectorC<DataT,N>::operator!=(const TFVectorC<DataT,N> & ind) const {
    for(UIntT i = 0;i < N;i++)
      if(data[i] != ind[i])
	return true;
    return false;
  }
  
  template<class DataT,unsigned int N>
  inline 
  void TFVectorC<DataT,N>::Fill(const DataT &dat) {
    for(UIntT i = 0;i < N;i++)
      data[i] = dat;
  }
  
  template<class DataT,unsigned int N>
  inline 
  const TFVectorC<DataT,N> & TFVectorC<DataT,N>::operator+=(const TFVectorC<DataT,N> & o) {
    for(UIntT i = 0;i < N;i++)
      data[i] += o[i];
    return *this;
  }
  
  template<class DataT,unsigned int N>
  inline 
  const TFVectorC<DataT,N> & TFVectorC<DataT,N>::operator-=(const TFVectorC<DataT,N> & o) {
    for(UIntT i = 0;i < N;i++)
      data[i] -= o[i];
    return *this;
  }
  
  template<class DataT,unsigned int N>
  inline 
  const TFVectorC<DataT,N> & TFVectorC<DataT,N>::operator*=(const TFVectorC<DataT,N> & o) {
    for(UIntT i = 0;i < N;i++)
      data[i] *= o[i];
    return *this;
  }
  
  template<class DataT,unsigned int N>
  inline 
  const TFVectorC<DataT,N> & TFVectorC<DataT,N>::operator/=(const TFVectorC<DataT,N> & o) {
    for(UIntT i = 0;i < N;i++)
      data[i] /= o[i];
    return *this;
  }
  
  template<class DataT,unsigned int N>
  inline 
  const TFVectorC<DataT,N> & TFVectorC<DataT,N>::operator*=(const DataT &alpha) {
    for(UIntT i = 0;i < N;i++)
      data[i] *= alpha;
    return *this;
  }
  
  template<class DataT,unsigned int N>
  inline 
  const TFVectorC<DataT,N> & TFVectorC<DataT,N>::operator/=(const DataT &alpha) {
    for(UIntT i = 0;i < N;i++)
      data[i] /= alpha;
    return *this;
  }
  
  template<class DataT,unsigned int N>
  inline
  TFVectorC<DataT,N> TFVectorC<DataT,N>::operator-() const {
    TFVectorC<DataT,N> ret;
    for(UIntT i = 0;i < N;i++)
      ret[i] = -data[i];
    return ret;
  }
  
  template<class DataT,unsigned int N>
  inline 
  TFVectorC<DataT,N> TFVectorC<DataT,N>::operator+(const TFVectorC<DataT,N> & o) const {
    TFVectorC<DataT,N> ret;
    for(UIntT i = 0;i < N;i++)
      ret[i] = data[i] + o[i];
    return ret;
  }
  
  template<class DataT,unsigned int N>
  inline 
  TFVectorC<DataT,N> TFVectorC<DataT,N>::operator-(const TFVectorC<DataT,N> & o) const {
    TFVectorC<DataT,N> ret;
    for(UIntT i = 0;i < N;i++)
      ret[i] = data[i] - o[i];
    return ret;
  }
  
  template<class DataT,unsigned int N>
  inline 
  TFVectorC<DataT,N> TFVectorC<DataT,N>::operator*(const TFVectorC<DataT,N> & o) const {
    TFVectorC<DataT,N> ret;
    for(UIntT i = 0;i < N;i++)
      ret[i] = data[i] * o[i];
    return ret;
  }
  
  template<class DataT,unsigned int N>
  inline 
  TFVectorC<DataT,N> TFVectorC<DataT,N>::operator/(const TFVectorC<DataT,N> & o) const {
    TFVectorC<DataT,N> ret;
    for(UIntT i = 0;i < N;i++)
      ret[i] = data[i] / o[i];
    return ret;
  }
  
  template<class DataT,unsigned int N>
  inline 
  TFVectorC<DataT,N> TFVectorC<DataT,N>::operator*(const DataT &alpha) const {
    TFVectorC<DataT,N> ret;
    for(UIntT i = 0;i < N;i++)
      ret[i] = data[i] * alpha;
    return ret;    
  }
  
  template<class DataT,unsigned int N>
  inline TFVectorC<DataT,N> operator*(const DataT &alpha,const TFVectorC<DataT,N> & data) {
    TFVectorC<DataT,N> ret;
    for(UIntT i = 0;i < N;i++)
      ret[i] = alpha * data[i];
    return ret;    
  }
  
  template<class DataT,unsigned int N>
  inline 
  TFVectorC<DataT,N> TFVectorC<DataT,N>::operator/(const DataT &alpha) const {
    TFVectorC<DataT,N> ret;
    for(UIntT i = 0;i < N;i++)
      ret[i] = data[i] / alpha;
    return ret;
  }

  template<class DataT,unsigned int N>
  inline 
  bool TFVectorC<DataT,N>::Limit(const DataT &min,const DataT &max) {
    bool ret = true;
    for(UIntT i =0;i <N;i++) {
      if(data[i] > max) {
	data[i] = max;
	ret = false;
	continue;
      }
      if(data[i] < min) {
	data[i] = min;
	ret = false;
      }
    }
    return ret;
  }
  
  template<class DataT,unsigned int N>
  inline
  TFVectorC<DataT,N> TFVectorC<DataT,N>::Abs() const {
    TFVectorC<DataT,N> ret;
    for(UIntT i =0;i <N;i++)
      ret[i] = RavlN::Abs(data[i]);
    return ret;
  }
  
  template<class DataT,unsigned int N>
  inline 
  DataT TFVectorC<DataT,N>::MaxValueDistance(const TFVectorC<DataT,N> & o) const {
    DataT ret = RavlN::Abs(data[0] - o[0]);
    for(UIntT i =1;i <N;i++) {
      DataT d = RavlN::Abs(data[i] - o[0]);
      if(ret > d)
	ret = d;
    }
    return ret;
  }
  
  template<class DataT,unsigned int N>
  inline 
  DataT TFVectorC<DataT,N>::CityBlockDistance(const TFVectorC<DataT,N> & o) const{
    DataT ret = RavlN::Abs(data[0] - o[0]);
    for(UIntT i =1;i <N;i++) 
      ret += RavlN::Abs(data[i] - o[i]);
    return ret;
  }
  
  template<class DataT,unsigned int N>
  inline 
  DataT TFVectorC<DataT,N>::SqrEuclidDistance(const TFVectorC<DataT,N> & o) const {
    DataT ret = RavlN::Sqr(data[0] - o[0]);
    for(UIntT i =1;i <N;i++) 
      ret += RavlN::Sqr(data[i] - o[i]);
    return ret;
  }
  
  template<class DataT,unsigned int N>
  inline
  DataT TFVectorC<DataT,N>::Sum() const {
    DataT ret = StdCopy(data[0]);
    for(UIntT i = 1;i<N;i++)
      ret += data[i];
    return ret;
  }
  
  template<class DataT,unsigned int N>
  inline
  DataT TFVectorC<DataT,N>::SumOfSqr() const {
    DataT ret = RavlN::Sqr(data[0]);
    for(UIntT i = 1;i<N;i++)
      ret += RavlN::Sqr(data[i]);
    return ret;
  }

  template<class DataT,unsigned int N>
  inline
  DataT TFVectorC<DataT,N>::SumOfAbs() const {
    DataT ret = RavlN::Abs(data[0]);
    for(UIntT i = 1;i<N;i++)
      ret += RavlN::Abs(data[i]);
    return ret;
  }
  
  template<class DataT,unsigned int N>
  inline
  ostream &operator<<(ostream &out,const TFVectorC<DataT,N> &dat) {
    for(UIntT i = 0;i < N;i++)
      out << dat.data[i] << ' ';
    return out;
  }
  
  template<class DataT,unsigned int N>
  inline
  istream &operator>>(istream &in,TFVectorC<DataT,N> &dat) {
    for(UIntT i = 0;i < N;i++)
      in >> dat.data[i];
    return in;
  }
  
#if !RAVL_COMPILER_VISUALCPP
  template<unsigned int N>
  inline ostream &operator<<(ostream &out,const TFVectorC<ByteT,N> &dat) {
    for(UIntT i = 0;i < N;i++)
      out << ((int) dat.data[i]) << ' ';
    return out;
  }
  //: Specialise byte vectors so they're treated as numerical values.
  
  template<unsigned int N>
  inline istream &operator>>(istream &in,TFVectorC<ByteT,N> &dat) {
    int x;
    for(UIntT i = 0;i < N;i++) {
      in >> x;
      dat.data[i] = (ByteT) x;
    }
    return in;
  }
  //: Specialise byte vectors so they're treated as numerical values.

  template<unsigned int N>
  inline ostream &operator<<(ostream &out,const TFVectorC<SByteT,N> &dat) {
    for(UIntT i = 0;i < N;i++)
      out << ((int) dat.data[i]) << ' ';
    return out;
  }
  //: Specialise byte vectors so they're treated as numerical values.
  
  template<unsigned int N>
  inline istream &operator>>(istream &in,TFVectorC<SByteT,N> &dat) {
    int x;
    for(UIntT i = 0;i < N;i++) {
      in >> x;
      dat.data[i] = (ByteT) x;
    }
    return in;
  }
  //: Specialise byte vectors so they're treated as numerical values.
#endif
}

#endif
