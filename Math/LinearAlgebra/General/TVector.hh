// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TVECTOR_HEADER
#define RAVL_TVECTOR_HEADER 1
///////////////////////////////////////////////////
//! userlevel=Normal
//! docentry="Ravl.Math.Linear Algebra"
//! rcsid="$Id$"
//! file="Ravl/Math/LinearAlgebra/General/TVector.hh"
//! author="Charles Galambos"
//! date="10/09/1998"
//! lib=RavlMath

#include "Ravl/SArray1d.hh"
#include "Ravl/Slice1d.hh"
#include "Ravl/TFVector.hh"

namespace RavlN {
  template<class DataT> class TMatrixC;
  
  //! userlevel=Advanced
  //: Templated vectors.
  
  template<class DataT>
  class TVectorC 
    : public SArray1dC<DataT>
  {
  public:
    inline TVectorC()
    {}
    //: Default constructor.
    
    inline TVectorC(const SArray1dC<DataT> &oth)
      : SArray1dC<DataT>(oth)
    {}
    //: Constructor for array of DataT's.

    inline TVectorC(const Slice1dC<DataT> &oth,bool alwaysCopy = true)
      : SArray1dC<DataT>(oth,alwaysCopy)
    {}
    //: Construct from a slice.
    
    explicit inline TVectorC(SizeT n);
    //: Constructor.

#if !RAVL_COMPILER_VISUALCPP
    template<unsigned int N>
    inline TVectorC(const TFVectorC<DataT,N> &dat)
      : SArray1dC<DataT>(N)
    {
      const DataT *at = &(dat[0]);
      for(BufferAccessIterC<DataT> it(*this);it;it++,at++)
	*it = *at;
    }
    //: Create from a fixed size vector.
    
    template<unsigned int N>
    operator TFVectorC<RealT,N> () {
      RavlAssertMsg(N == Size(),"Size mismatch converting to fixed size array. ");
      TFVectorC<RealT,N> ret;
      DataT *at = &(ret[0]);
      for(BufferAccessIterC<DataT> it(*this);it;it++,at++)
	*at = *it;
      return ret;
    }
    //: Convert to a fixed size vector.
#endif
    
    DataT Sum() const;      
    //: Returns the sum all elements of the vector.
    
    DataT Product() const;      
    //: Returns the product of all elements of the vector.
    
    DataT SumOfSqr() const;
    //: Returns the sum of the squares of all the elements of the vector.
    
    DataT SumOfAbs() const;
    //: Returns the sum of the absolute values of all the elements of the vector.
    
    DataT MaxValue() const;
    //: Largest value in the array.
    
    DataT MaxMagintude() const;
    //: Value of the largest magnitude in the vector.
    
    DataT MinValue() const;
    //: Smalleset value in the array.
    
    const TVectorC<DataT> & Reciprocal();
    //: All elements of the vector are changed to their reciprocal values. 
    //: It is assumed that all elements of the vector differs from zero.
    
    DataT Modulus() const
    { return Sqrt(SumOfSqr()); } 
    //: Returns the modulus of the vector.
    // The Sqrt(SumOfSqr()).
    
    DataT TMul(const TVectorC<DataT> & b) const;
    //: multiplication 'DataT' = (*this).T() * b
    
    DataT Dot(const TVectorC<DataT> & v) const;         
    //: scalar product of vectors    
    
    const TVectorC<DataT> &SetSmallToBeZero(const DataT &min);
    //: Set values smaller than 'min' to zero in vector.
    
    TMatrixC<DataT> OuterProduct(const TVectorC<DataT> &a) const;
    //: Calculate the outer product of this vector and a.
    // To use the function you must also include 'Ravl/Matrix.hh'.
    
    TMatrixC<DataT> OuterProduct(const TVectorC<DataT> &a,RealT b) const;
    //: Calculate the outer product of this vector and a multiplied by b.
    // To use the function you must also include 'Ravl/Matrix.hh'.
    
    TMatrixC<DataT> OuterProduct() const;
    //: Calculate the outer product of this vector with itself.
    // To use the function you must also include 'Ravl/Matrix.hh'.

    TVectorC<DataT> Unit() const
    { return (*this) / Modulus(); }
    //: Return a unit vector
   
    const TVectorC<DataT> &MakeUnit()
    { (*this) = Unit(); return *this; }
    //: Make this a unit vector.
    
    IndexC MaxIndex() const;
    //: Find the index with the most positive valued index.
    
    IndexC MaxAbsIndex() const;
    //: Find the index with the absolute maximum valued index.
  };
  
  ////////////////////////////////////////

  template<class DataC>
  ostream &operator<<(ostream & s, const TVectorC<DataC> & arr) {
    // This uses spaces instread of '\n' which makes vectors more readable.
    // otherwise its no different from the SArray1dC version.
    s << arr.Size() << ' '; 
    for(BufferAccessIterC<DataC> it(arr);it;it++)
      s << ((const DataC &) *it) << ' ';
    return s;
  }
  
  template<class DataT>
  inline 
  TVectorC<DataT>::TVectorC(SizeT n)
    : SArray1dC <DataT>(n)
  {}
  
  template<class DataT>
  DataT 
  TVectorC<DataT>::Sum() const  {
    BufferAccessIterC<DataT> it(*this);
    if(!it.IsElm())
      return 0;
    DataT sum = it.Data();
    it.Next();
    for(;it.IsElm();it.Next())
      sum += it.Data();
    return sum;
  }
  
  template<class DataT>
  DataT TVectorC<DataT>::Product() const  {
    BufferAccessIterC<DataT> it(*this);
    if(!it.IsElm())
      return 1; // Or throw an exception ?
    DataT prod = it.Data();
    it.Next();
    for(;it.IsElm();it.Next())
      prod *= it.Data();
    return prod;
  }
  
  template<class DataT>
  const TVectorC<DataT> & 
  TVectorC<DataT>::Reciprocal() {
    for(BufferAccessIterC<DataT> it(*this);it.IsElm();it.Next())
      it.Data() = 1/it.Data();
    return *this;
  }

  template<class DataT>
  DataT TVectorC<DataT>::SumOfSqr() const {
    DataT ret;
    SetToZero(ret);
    for(BufferAccessIterC<DataT> it(*this);it;it++)
      ret += Sqr(*it);
    return ret;
  }

  template<class DataT>
  DataT TVectorC<DataT>::SumOfAbs() const {
    DataT ret;
    SetToZero(ret);
    for(BufferAccessIterC<DataT> it(*this);it;it++)
      ret += Abs(*it);
    return ret;
  }
  
  template<class DataT>
  DataT 
  TVectorC<DataT>::TMul(const TVectorC<DataT> & b) const {
    DataT sum = 0;
    for(BufferAccessIter2C<DataT,DataT> it(*this,b);it.IsElm();it.Next())
      sum += it.Data1() * it.Data2();
    return sum;
  }
  
  template<class DataT>
  DataT 
  TVectorC<DataT>::Dot(const TVectorC<DataT> & v) const {
    DataT sum = 0;
    for(BufferAccessIter2C<DataT,DataT> it(*this,v);it.IsElm();it.Next())
      sum += it.Data1() * it.Data2();
    return sum;  
  }
  
  template<class DataT>
  const TVectorC<DataT> &TVectorC<DataT>::SetSmallToBeZero(const DataT &min) {
    for(BufferAccessIterC<DataT> it(*this);it;it++)
      if(Abs(*it) < min)
	SetToZero(*it);
    return *this;
  }


  template<class DataT>
  DataT TVectorC<DataT>::MaxValue() const {
    BufferAccessIterC<DataT> it(*this);
    if(!it.IsElm()) {
      DataT ret;
      SetToZero(ret);
      return ret;
    }
    DataT max = *it;
    for(;it;it++) 
      if(*it > max)
	max = *it;
    return max;
  }

  template<class DataT>
  DataT TVectorC<DataT>::MaxMagintude() const {
    BufferAccessIterC<DataT> it(*this);
    if(!it.IsElm()) {
      DataT ret;
      SetToZero(ret);
      return ret;
    }
    DataT max = Abs(*it);
    for(;it;it++) {
      DataT mag = Abs(*it);
      if(mag > max)
	max = mag;
    }
    return max;    
  }
  
  template<class DataT>
  DataT TVectorC<DataT>::MinValue() const {
    BufferAccessIterC<DataT> it(*this);
    if(!it.IsElm()) {
      DataT ret;
      SetToZero(ret);
      return ret;
    }
    DataT min = *it;
    for(;it;it++) 
      if(*it < min)
	min = *it;
    return min;
  }
  
  template<class DataT>
  IndexC TVectorC<DataT>::MaxIndex() const {
    IndexC ind = 0;
    BufferAccessIterC<DataT> it(*this);
    DataT maxVal = *it;
    for(it++;it;it++) {
      if(*it > maxVal) {
	maxVal = *it;
	ind = (IntT) (&(*it) - &(*this)[0]);
      }
    }
    return ind;
  }
  
  template<class DataT>
  IndexC TVectorC<DataT>::MaxAbsIndex() const {
    IndexC ind = 0;
    BufferAccessIterC<DataT> it(*this);
    DataT maxVal = *it;
    for(it++;it;it++) {
      DataT aM = Abs(*it);
      if(aM > maxVal) {
	maxVal = aM;
	ind = (IntT) (&(*it) - &(*this)[0]);
      }
    }
    return ind;
  }
  
}
#endif
