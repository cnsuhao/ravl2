// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLTFVECTOR_HEADER
#define RAVLTFVECTOR_HEADER 1
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

namespace RavlN {
  
  class BinIStreamC;
  class BinOStreamC;

  template<class DataT,unsigned int N> class TFVectorC;
  
  template<class DataT,unsigned int N>
  istream &operator>>(istream &in,TFVectorC<DataT,N> &dat);
  
  template<class DataT,unsigned int N>
  ostream &operator<<(ostream &in,const TFVectorC<DataT,N> &dat);
  
  template<class DataT,unsigned int N>
  inline
  BinIStreamC &operator>>(BinIStreamC &in,TFVectorC<DataT,N> &dat);
  
  template<class DataT,unsigned int N>
  inline
  BinOStreamC &operator<<(BinOStreamC &in,const TFVectorC<DataT,N> &dat);
  
  //! userlevel=Advanced
  //: Fixed size vector.
  
  template<class DataT,unsigned int N>
  class TFVectorC {
  public:
    TFVectorC()
      {}
    //: Default constructor.
    // Note: The default constructor of 'DataT' is used to contruct
    // the elements of the vector, for builtin types this means
    // their values will be undefined.
    
    TFVectorC(const DataT *init);
    //: Value constructor.
    // Copy values from 'init'. It is the user's responsibility
    // to ensure that data has at least 'N' elements. 
    
    UIntT Size() const
      { return N; }
    //: Get size of array
    
    bool Contains(UIntT i) const
      { return i < N; }
    //: Test if array contains index i·
    
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

    inline DataT Dot(const TFVectorC<DataT,N> &oth) {
      DataT ret = data[0] * oth.data[0];
      for(UIntT i = 1;i <N;i++)
	ret += data[i] * oth.data[i];
      return ret;
    }
    //: Calculate the dot product of this and 'oth' vector.
    
    inline bool Limit(const DataT &min,const DataT &max);
    //: Limit all values in this vector to between min and max.
    // Returns true if all values in the vector are between the limits.
    
    // Distance calculations
    // ---------------------
    
    inline DataT MaxValueDistance(const TFVectorC<DataT,N> & i) const;
    //: Returns the distance of two indexes in maximum value metric.
    
    inline DataT CityBlockDistance(const TFVectorC<DataT,N> & i) const;
    //: Returns the distance of two indexes in absolute value metric.
    
    inline DataT SqrEuclidDistance(const TFVectorC<DataT,N> & i) const;
    //: Returns the distance of two indexes in square Euclid metric.
    
    DataT SumSqr() const;
    //: Calculate the sum of the squares of all the vector elements.

#if RAVL_NEW_ANSI_CXX_DRAFT
    friend istream &operator>> <>(istream &in,TFVectorC<DataT,N> &dat);  
    friend ostream &operator<< <>(ostream &in,const TFVectorC<DataT,N> &dat);  
    friend BinIStreamC &operator>> <>(BinIStreamC &in,TFVectorC<DataT,N> &dat);
    friend BinOStreamC &operator<< <>(BinOStreamC &in,const TFVectorC<DataT,N> &dat);
#else
    friend istream &operator>> (istream &in,TFVectorC<DataT,N> &dat);  
    friend ostream &operator<< (ostream &in,const TFVectorC<DataT,N> &dat);  
    friend BinIStreamC &operator>> (BinIStreamC &in,TFVectorC<DataT,N> &dat);
    friend BinOStreamC &operator<< (BinOStreamC &in,const TFVectorC<DataT,N> &dat);
#endif    
  protected:
    DataT data[N];
  };
  

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
      ret[i] = Abs(data[i]);
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

  //: Calculate the sum of the squares of all the vector elements.
  
  template<class DataT,unsigned int N>
  inline
  DataT TFVectorC<DataT,N>::SumSqr() const {
    DataT ret = RavlN::Sqr(data[0]);
    for(UIntT i = 1;i<N;i++)
      ret += RavlN::Sqr(data[i]);
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

}

#endif
