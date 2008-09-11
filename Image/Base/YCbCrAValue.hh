// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_YCBCRAVALUE_HEADER
#define RAVL_YCBCRAVALUE_HEADER 1
////////////////////////////////////////////////////////////////////
//! file="Ravl/Image/Base/YCbCrAValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="11/09/2008"
//! docentry="Ravl.API.Images.Pixel Types"

#include "Ravl/TFVector.hh"
#include "Ravl/Traits.hh"

namespace RavlImageN {
  using namespace RavlN;
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using RavlN::BinIStreamC;
  using RavlN::BinOStreamC;
  using RavlN::TFVectorC;
#endif
  
  //! userlevel=Normal
  //: YCbCrA Pixel base class.
  
  template<class CompT>
  class YCbCrAValueC 
    : public TFVectorC<CompT,4>
  {
  public:
    YCbCrAValueC()
    {}
    //: Default constructor.
    // Creates an undefined value.

    YCbCrAValueC(const CompT &y,
                 const CompT &b,
                 const CompT &r,
                 const CompT &a) 
    {
      this->data[0] =y;
      this->data[1] =b;
      this->data[2] =r;
      this->data[3] =a;
    }
    //: Construct from component values.
    
    YCbCrAValueC(const TFVectorC<CompT,4> &v)
      : TFVectorC<CompT,4>(v)
    {}
    //: Constructor from base class.
    
    template<class OCompT>
    YCbCrAValueC(YCbCrAValueC<OCompT> &oth) {
      this->data[0] = oth.Y();
      this->data[1] = oth.Cb();
      this->data[2] = oth.Cr();
      this->data[3] = oth.A();
    }
    //: Construct from another component type.
    
    inline const CompT & Y() const
    { return this->data[0]; }
    // Returns the level of the Y component.
    
    inline const CompT & Cb() const
    { return this->data[1]; }
    // Returns the level of the U component.
    
    inline const CompT & Cr() const
    { return this->data[2]; }
    // Returns the level of the V component.
    
    inline const CompT & A() const
    { return this->data[3]; }
    // Returns the level of the V component.
    
    inline CompT & Y() 
    { return this->data[0]; }
    // Returns the level of the Y component.
    
    inline CompT & Cb()
    { return this->data[1]; }
    // Returns the level of the U component.
    
    inline CompT & Cr()
    { return this->data[2]; }
    // Returns the level of the V component.

    inline CompT & A()
    { return this->data[3]; }
    // Returns the level of the V component.

  };

  template<class CompT>
  inline
  istream &operator>>(istream &strm,YCbCrAValueC<CompT> &val) 
  { return strm >> ((TFVectorC<CompT,4> &)(val)); }
  //: Stream input.
  
  template<class CompT>
  inline
  ostream &operator<<(ostream &strm,const YCbCrAValueC<CompT> &val) 
  { return strm << ((const TFVectorC<CompT,4> &)(val)); }
  //: Stream output.
  
  template<class CompT>
  inline
  BinIStreamC &operator>>(BinIStreamC &strm,YCbCrAValueC<CompT> &val) 
  { return strm >> ((TFVectorC<CompT,4> &)(val)); }
  //: Binary stream input.
  
  template<class CompT>
  inline
  BinOStreamC &operator<<(BinOStreamC &strm,const YCbCrAValueC<CompT> &val) 
  { return strm << ((const TFVectorC<CompT,4> &)(val)); }
  //: Binary stream output
  
}

namespace RavlN {
  
  //! userlevel=Advanced
  //: Traits for type
  
  template<typename PixelT>
  struct NumericalTraitsC<RavlImageN::YCbCrAValueC<PixelT> > {
    typedef RavlImageN::YCbCrAValueC<typename RavlN::NumericalTraitsC<PixelT>::AccumT > AccumT;    //: Type to use for accumulator, guarantee's at least 2x no bits for interger types.
    typedef RavlImageN::YCbCrAValueC<typename RavlN::NumericalTraitsC<PixelT>::RealAccumT > RealAccumT; //: Type to use for a floating point accumulator.
    typedef RavlImageN::YCbCrAValueC<typename RavlN::NumericalTraitsC<PixelT>::LongAccumT > LongAccumT; //: Type to use for accumulators that can take large sums.(10000's of elements at least.)
  };
}

#endif
