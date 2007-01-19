// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FPNUMBER_HEADER
#define RAVL_FPNUMBER_HEADER 1
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlCore
//! docentry="Ravl.API.Core.Fixed Point Arithmetic"
//! file="Ravl/Core/Base/FPNumber.hh"
//! userlevel=Normal

#include "Ravl/Types.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Math.hh"

namespace RavlN {
  
  inline 
  int BitShift(int v,int n) {
    if(n > 0)
      return v << n;
    return v >> -n;
  }
  //: Left shift v by n bits where n can be negative.
  
  //:-
  
  //! userlevel=Normal
  //: Fixed Point Number.
  // A 32-bit real number with a fixed number N of fractional binary digits
  
  template<UIntT N>
  class FPNumberC {
  public:
    FPNumberC()
    {}
    //: Default constructor.
    
    FPNumberC(IntT raw,bool)
      : v(raw)
    {}
    //: Construct from a raw number
    
    FPNumberC(IntT num)
      : v(num << N)
    {}
    //: Convert from an integer.

    FPNumberC(RealT num)
      : v((IntT) Round(num * (RealT) (1 << N)))
    {}
    //: Convert from a real number.
    
    template<UIntT M>
    FPNumberC(FPNumberC<M> num)
      : v(BitShift(num.v,(int) N - (int) M))
    {}
    //: Convert from a another fixed point number.
    
    bool operator==(FPNumberC<N> n) const
    { return v == n.v; }
    //: Equal to another number ?
    
    template<UIntT M>
    bool operator==(FPNumberC<M> n) const
    { return v == BitShift(n.v,N-M) && BitShift(v,M-N) == n.v; }
    //: Equal to another number ?

    template<UIntT M>
    bool operator!=(FPNumberC<M> n) const
    { return !((*this) == n); }
    //: Not equal to another number ?
    
    bool operator==(IntT n) const
    { return (v == (n << N)) && ((v >> N) == n); }
    //: Equal to an integer ?
    
    bool operator!=(FPNumberC<N> n) const
    { return v != n.v; }
    
    bool operator!=(IntT n) const
    { return !((*this) == n); }
    
    bool operator<(FPNumberC<N> n) const
    { return v < n.v; }
    
    bool operator>(FPNumberC<N> n) const
    { return v > n.v; }
    
    bool operator<=(FPNumberC<N> n) const
    { return v <= n.v; }
    
    bool operator>=(FPNumberC<N> n) const
    { return v >= n.v; }
    
    FPNumberC<N> operator++()
    { return v += (1 << N); }
    //: pre increment.
    
    FPNumberC<N> operator--()
    { return v -= (1 << N); }
    //: pre decrement.
    
    FPNumberC<N> operator++(int) { 
      FPNumberC<N> t = (*this);
      v += (1 << N); 
      return t;
    }
    //: post increment.
    
    FPNumberC<N> operator--(int) {
      FPNumberC<N> t = (*this);
      v -= (1 << N); 
      return t;
    }
    //: post decrement.
    
    template<UIntT M>
    FPNumberC<N> &operator+=(FPNumberC<M> n) {
      v += (n.V() << (N - M));
      return (*this);
    }
    //: Add a value.

    template<UIntT M>
    FPNumberC<N> &operator-=(FPNumberC<M> n) {
      v -= (n.V() << (N - M));
      return (*this);
    }
    //: Subtract a value.
    
    template<UIntT M>
    FPNumberC<N> &operator*=(FPNumberC<M> n) {
      v *= n.v;
      v = v >> M;
      return (*this);
    }
    //: Multiply by a value.
    
    template<UIntT M>
    FPNumberC<N> &operator/=(FPNumberC<M> n) {
      v /= n.v;
      v = v << M;
      return (*this);
    }
    //: Divide by a value
    
    template<typename ValueT>
    FPNumberC<N> &operator+=(const ValueT &n) {
      v += n * (1 << N);
      return (*this);
    }
    //: Add a value.

    template<typename ValueT>
    FPNumberC<N> &operator-=(const ValueT &n) {
      v -= n * (1 << N);
      return (*this);
    }
    //: Subtract a value.
    
    template<typename ValueT>
    FPNumberC<N> &operator*=(const ValueT &n) {
      v *= n;
      return (*this);
    }
    //: Multiply by a value.
    
    template<typename ValueT>
    FPNumberC<N> &operator/=(const ValueT &n) {
      v /= n;
      return (*this);
    }
    //: Divide by a value
    
    operator int() const
    { return v >> N; }
    //: Convert to int.

    IntT Integer() const
    { return v >> N; }
    //: Return the nearest integer not greater.
    
    FPNumberC<N> Fraction() const
    { return FPNumberC<N>(v & ((1 << N)-1),true); }
    //: Return the fractional part of the number
    
    operator double() const
    { return (((RealT) v) / ((RealT) (1 << N))); }
    //: Convert to double.
    
    IntT RoundInt() const
    { return (v >> N) + ((v & (1<<(N-1))) != 0 ? 1 : 0);}
    //: Round to the nearest whole integer.
    
    IntT &V()
    { return v; }
    //: Access underlying integer value.
  
  protected:
    IntT v;
  };
  
  template<UIntT N>
  ostream &operator<<(ostream &s,FPNumberC<N> n) {
    s << (((RealT) n.V()) / ((RealT) (1 << N)));
    return s;
  }
  //: Output a number to a stream
  
  template<UIntT N>
  istream &operator<<(istream &s,FPNumberC<N> n) {
    RealT v;
    s >> v;
    n = v;
    return s;
  }
  //: Input a number from a stream
  
  template<typename ValueT,UIntT N>
  inline
  FPNumberC<N> operator+(const ValueT &vt,FPNumberC<N> n2)
  { return FPNumberC<N>((vt * (1 << N)) + n2.V(),true); }
  //: Add
  
  template<typename ValueT,UIntT N>
  inline
  FPNumberC<N> operator-(const ValueT &vt,FPNumberC<N> n2)
  { return FPNumberC<N>((vt * (1 << N)) - n2.V(),true); }
  //: Subtract
  
  template<typename ValueT,UIntT N>
  inline
  FPNumberC<N> operator*(const ValueT &vt,FPNumberC<N> n2)
  { return FPNumberC<N>(Round(vt * ((ValueT) n2.v)),true); }
  //: Multiply

  template<typename ValueT,UIntT N>
  inline
  FPNumberC<N> operator/(const ValueT &vt,FPNumberC<N> n2)
  { return FPNumberC<N>((vt * (1 << N)) / n2.V(),true); }
  //: Divide
  
  ///////////////////////////////////////////////////////////////

  template<typename ValueT,UIntT N>
  inline
  FPNumberC<N> operator+(FPNumberC<N> n1,const ValueT &vt)
  { return FPNumberC<N>(n1.V() + (vt * (1 << N)),true); }
  //: Add
  
  template<typename ValueT,UIntT N>
  inline
  FPNumberC<N> operator-(FPNumberC<N> n1,const ValueT &vt)
  { return FPNumberC<N>(n1 - (vt * (1 << N)).V(),true); }
  //: Subtract
  
  template<typename ValueT,UIntT N>
  inline
  FPNumberC<N> operator*(FPNumberC<N> n1,const ValueT &vt)
  { return FPNumberC<N>(Round(Round((ValueT) n1.V()) * vt),true); }
  //: Multiply
  
  template<typename ValueT,UIntT N>
  inline
  FPNumberC<N> operator/(FPNumberC<N> n1,const ValueT &vt)
  { return FPNumberC<N>(Round(n1.V() / vt),true); }
  //: Divide

  ///////////////////////////////////////////////////////////////
  
  template<UIntT N,UIntT M>
  inline
  FPNumberC<(N+M)/2> operator+(FPNumberC<N> n1,FPNumberC<M> n2) { 
    const UIntT RN = (N+M)/2;
    return FPNumberC<RN>(BitShift(n1.V(),(RN - N)) + BitShift(n2.V(), (RN - M)),true); 
  }
  //: Add
  
  template<UIntT N,UIntT M>
  inline
  FPNumberC<(N+M)/2> operator-(FPNumberC<N> n1,FPNumberC<M> n2) {
    const UIntT RN = (N+M)/2;
    return FPNumberC<RN>(BitShift(n1.V(), (RN - N)) - BitShift(n2.V(),(RN - M)),true); 
  }
  //: Subtract
  
  template<UIntT N,UIntT M>
  inline
  FPNumberC<(N+M)/2> operator*(FPNumberC<N> n1,FPNumberC<M> n2) { 
    const UIntT RN = (N+M)/2;
    return FPNumberC<RN>(BitShift(n1.V() * n2.V(),RN - (N+M)) ,true); 
  }
  //: Multiply
  
  template<UIntT N,UIntT M>
  inline
  FPNumberC<(N+M)/2> operator/(FPNumberC<N> n1,FPNumberC<M> n2) { 
    const UIntT RN = (N+M)/2;
    return FPNumberC<RN>(BitShift(n1.V(),RN - (N - M)) / n2.V(),true); 
  }
  //: Divide.

  template<UIntT N> 
  inline 
  void SetZero ( FPNumberC<N> & n1 ) {
    n1 = 0.0 ; }
  //: Set Zero
  
  template<UIntT N> 
  inline 
  FPNumberC<N> StdCopy (FPNumberC<N> num ) { return num ; }
  //: StdCopy 
  
}

#endif
