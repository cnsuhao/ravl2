// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_COMPLEX_HEADER
#define RAVL_COMPLEX_HEADER 1
/////////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Math/Complex.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Radek Marik"
//! date="26.01.1994"
//! example=exComplx.cc
//! docentry="Ravl.Core.Math"
//! rcsid="$Id$"

#include "Ravl/Types.hh"
#include "Ravl/StdMath.hh"

class ostream;
class istream;

namespace RavlN {
  
  //! userlevel=Normal
  //: Complex algebra
  
  class ComplexC {
  public:
    
    // Constructors.
    // -------------
    
    inline ComplexC();
    // Creates the complex number (0,0).
    
    inline ComplexC(RealT real);
    // Creates the complex number (real, 0).
    
    inline ComplexC(RealT real, RealT imaginary);
    // Create the complex number (real, imaginary).
    
    inline ComplexC(const ComplexC & x);
    // Copy constructor.
    
    // Access to the parts of a complex number.
    // ----------------------------------------
    
    inline RealT &  Re()
    { return re; }
    // Returns the real part.
    
    inline RealT    Re() const
    { return re; }
    // Returns the real part.
    
    inline RealT &  Im()
    { return im; }
    // Returns the imaginary part of the complex number.
    
    inline RealT    Im() const
    { return im; }
    // Returns the imaginary part of the complex number.
    
    inline RealT    Mag() const
    { return Sqrt(re*re + im*im); }
    //: The maginude
    
    inline ComplexC I() const 
    { return ComplexC(-im, re); }
    //: Inverse.
    
    inline ComplexC Conj() const
    { return ComplexC(re, -im); }
    //: Get the complex conjugate.
    
    
    inline const ComplexC & operator+=(RealT a);
    inline const ComplexC & operator+=(const ComplexC & x);
    inline const ComplexC & operator-=(RealT a);
    inline const ComplexC & operator-=(const ComplexC & x);
    inline const ComplexC & operator*=(RealT a);
    inline const ComplexC & operator*=(const ComplexC & x);
    inline const ComplexC & operator/=(RealT a);
    inline const ComplexC & operator/=(const ComplexC & x);
    
    friend inline ComplexC operator+(RealT a, const ComplexC & x);
    friend inline ComplexC operator+(const ComplexC & x,RealT a);
    friend inline ComplexC operator+(const ComplexC & a, const ComplexC & x);
    friend inline ComplexC operator-(RealT a, const ComplexC & x);
    friend inline ComplexC operator-(const ComplexC & x,RealT a);
    friend inline ComplexC operator-(const ComplexC & a, const ComplexC & x);
    friend inline ComplexC operator*(RealT a, const ComplexC & x);
    friend inline ComplexC operator*(const ComplexC & x,RealT a);
    friend inline ComplexC operator*(const ComplexC & a, const ComplexC & x);
    friend inline ComplexC operator/(const ComplexC & x, RealT a);
    friend inline ComplexC operator/(const ComplexC & a, const ComplexC & x);
    friend inline ComplexC operator/(RealT a, const ComplexC & x);
    friend inline ComplexC operator^(const ComplexC & x, RealT a);
    friend inline RealT    operator&&(const ComplexC & a,const ComplexC & x);
    
    friend inline ComplexC Exp(const ComplexC & x);
    friend inline ComplexC CExp(RealT a);
    friend inline ComplexC Log(const ComplexC & x);
    
  private:
    RealT  re;
    RealT  im;
  };
  
  ostream & operator<<(ostream & outS, const ComplexC & x);
  istream & operator>>(istream & inS, ComplexC & x);
  
  
  //======================================================================
  //=============== ComplexC =============================================
  //======================================================================
  
  inline 
  ComplexC::ComplexC()
    : re(0), im(0)
  {}
  
  inline 
  ComplexC::ComplexC(RealT real)
    : re(real), im(0)
  {}
  
  inline
  ComplexC::ComplexC(RealT real, RealT imaginary)
    : re(real), im(imaginary)
  {}
  
  inline
  ComplexC::ComplexC(const ComplexC & x)
    : re(x.re), im(x.im)
  {}
  
  inline
  const ComplexC &
  ComplexC::operator+=(RealT a) {
    re += a;
    return *this;
  }
  
  inline
  const ComplexC &
  ComplexC::operator+=(const ComplexC & x) {
    re += x.re;
    im += x.im;
    return *this;
  }
  
  inline
  const ComplexC &
  ComplexC::operator-=(RealT a) {
    re -= a;
    return *this;
  }
  
  inline
  const ComplexC &
  ComplexC::operator-=(const ComplexC & x) {
    re -= x.re;
    im -= x.im;
    return *this;
  }
  
  inline
  const ComplexC &
  ComplexC::operator*=(RealT a) {
    re *= a;
    im *= a;
    return *this;
  }
  
  inline
  const ComplexC &
  ComplexC::operator*=(const ComplexC & x) {
    RealT outRe = re*x.re - im*x.im;
    im = im*x.re + re*x.im;
    re = outRe;
    return *this;
  }
  
  inline
  const ComplexC &
  ComplexC::operator/=(RealT a) {
    re /= a;
    im /= a;
    return *this;
  }
  
  inline
  const ComplexC &
  ComplexC::operator/=(const ComplexC & x) {
    RealT mod = x.re*x.re + x.im*x.im;
    RealT outRe = (re*x.re + im*x.im) / mod;
    im = (im*x.re - re*x.im) / mod;
    re = outRe;
    return(*this);
  }
  
  
  inline
  ComplexC operator+(RealT a, const ComplexC & x)
  { return ComplexC(a + x.re, x.im); }

  inline
  ComplexC operator+(const ComplexC & x,RealT a)
  { return ComplexC(a + x.re, x.im); }

  inline
  ComplexC operator+(const ComplexC & a, const ComplexC & b)
  { return ComplexC(a.re + b.re, a.im + b.im); }

  inline
  ComplexC operator-(RealT a, const ComplexC & x)
  { return ComplexC(a - x.re, -x.im); }

  inline
  ComplexC operator-(const ComplexC & x, RealT a)
  { return ComplexC(x.re - a, x.im); }

  inline
  ComplexC operator-(const ComplexC & a, const ComplexC & x)
  { return ComplexC(a.re - x.re, a.im - x.im); }

  inline
  ComplexC operator*(RealT a, const ComplexC & x)
  { return ComplexC(a * x.re, a * x.im); }

  inline
  ComplexC operator*(const ComplexC & x, RealT a)
  { return ComplexC(a * x.re, a * x.im); }

  inline
  ComplexC operator*(const ComplexC & a, const ComplexC & x) {
    return ComplexC(a.re * x.re - a.im * x.im, 
		    a.re * x.im + a.im * x.re);
  }
  
  inline
  ComplexC operator/(const ComplexC & x, RealT a)
  { return ComplexC(x.re/a, x.im/a); }

  inline
  ComplexC
  operator/(const ComplexC & a, const ComplexC & x) {
    RealT magx = x.re * x.re + x.im * x.im;
    return ComplexC((a.re * x.re + a.im * x.im)/magx, 
		    (a.im * x.re - a.re * x.im)/magx);
  }
  
  inline
  ComplexC
  operator/(RealT a, const ComplexC & x) {
    RealT magx = x.re * x.re + x.im * x.im;
    return ComplexC(a*x.re/magx, -a*x.im/magx);
  }
  
  inline
  ComplexC
  operator^(const ComplexC & x, RealT a) {
    RealT magx = x.re * x.re + x.im * x.im;
    return ComplexC(Pow(magx,a/2.0)* Cos(a* ATan2(x.im,x.re)),
		    Pow(magx,a/2.0)* Sin(a* ATan2(x.im,x.re)));
  }
  
  inline
  RealT operator&&(const ComplexC & a, const ComplexC & x)
  { return a.re*x.re + a.im*x.im; }

  inline
  ComplexC Exp(const ComplexC & a)
  { return ComplexC(RavlN::Exp(a.re)* Cos(a.im), RavlN::Exp(a.re)* Sin(a.im)); }
  
  inline
  ComplexC CExp(RealT a)
    // Note: this is when it's exp(i*a), a real
  { return ComplexC(Cos(a), Sin(a)); }
  
  inline
  ComplexC
  Log(const ComplexC & a) {
    return ComplexC(Log(Sqrt(a.re*a.re + a.im*a.im)), 
		    ATan2(a.im,a.re));
  }  
}

#endif

// IAPS - Image analysis program system.
// End of include file Complex.hh 

