// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_YUVVALUE_HEADER
#define RAVL_YUVVALUE_HEADER
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/YUVValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/TFVector.hh"

namespace RavlImageN {
  using namespace RavlN;
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using RavlN::BinIStreamC;
  using RavlN::BinOStreamC;
  using RavlN::TFVectorC;
#endif
  
  //! userlevel=Normal
  //: YUV Pixel base class.
  
  template<class CompT>
  class YUVValueC 
    : public TFVectorC<CompT,3>
  {
  public:
    YUVValueC()
      {}
    //: Default constructor.
    // Creates an undefined value.

    YUVValueC(const CompT &y,const CompT &u,const CompT &v) {
      data[0] =y;
      data[1] =u;
      data[2] =v;
    }
    //: Construct from component values.
    
    YUVValueC(const TFVectorC<CompT,3> &v)
      : TFVectorC<CompT,3>(v)
      {}
    //: Constructor from base class.
    
    template<class OCompT>
    YUVValueC(YUVValueC<OCompT> &oth) {
      data[0] = oth.Y();
      data[1] = oth.U();
      data[2] = oth.V();
    }
    //: Construct from another component type.

    void Set(const CompT &y,const CompT &u,const CompT &v) {
      data[0] =y;
      data[1] =u;
      data[2] =v;
    }
    //: Set the values.
    
    inline const CompT & Y() const
      { return data[0]; }
    // Returns the level of the Y component.
    
    inline const CompT & U() const
      { return data[1]; }
    // Returns the level of the U component.
    
    inline const CompT & V() const
      { return data[2]; }
    // Returns the level of the V component.
    
    inline CompT & Y() 
      { return data[0]; }
    // Returns the level of the Y component.
    
    inline CompT & U()
      { return data[1]; }
    // Returns the level of the U component.
    
    inline CompT & V()
      { return data[2]; }
    // Returns the level of the V component.

  };

  template<class CompT>
  inline
  istream &operator>>(istream &strm,YUVValueC<CompT> &val) 
    { return strm >> ((TFVectorC<CompT,3> &)(val)); }
  //: Stream input.
  
  template<class CompT>
  inline
  ostream &operator<<(ostream &strm,const YUVValueC<CompT> &val) 
    { return strm << ((const TFVectorC<CompT,3> &)(val)); }
  //: Stream output.
  
  template<class CompT>
  inline
  BinIStreamC &operator>>(BinIStreamC &strm,YUVValueC<CompT> &val) 
    { return strm >> ((TFVectorC<CompT,3> &)(val)); }
  //: Binary stream input.
  
  template<class CompT>
  inline
  BinOStreamC &operator<<(BinOStreamC &strm,const YUVValueC<CompT> &val) 
    { return strm << ((const TFVectorC<CompT,3> &)(val)); }
  //: Binary stream output

}

#endif
