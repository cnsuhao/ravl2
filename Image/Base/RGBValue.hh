// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLRGBVALUE_HEADER
#define RAVLRGBVALUE_HEADER
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/RGBValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/TFVector.hh"

namespace RavlN {
  
  //: RGB Pixel base class.
  
  template<class CompT>
  class RGBValueC 
    : public TFVectorC<CompT,3>
  {
  public:
    RGBValueC()
      {}
    //: Default constructor.
    // Creates an undefined value.

    RGBValueC(const CompT &r,const CompT &g,const CompT &b) {
      data[0] =r;
      data[1] =g;
      data[2] =b;
    }
    //: Construct from component values.
    
    template<class OCompT>
    RGBValueC(RGBValueC<OCompT> &oth) {
      data[0] = oth.Red();
      data[1] = oth.Green();
      data[2] = oth.Blue();
    }
    //: Construct from another component type.
    
    void Set(const CompT &r,const CompT &g,const CompT &b) {
      data[0] =r;
      data[1] =g;
      data[2] =b;
    }
    //: Set the values.
    
    inline const CompT & Red() const
      { return data[0]; }
    //: Returns the level of the red component.
    
    inline const CompT & Green() const
      { return data[1]; }
    //: Returns the level of the green component.
    
    inline const CompT & Blue() const
      { return data[2]; }
    //: Returns the level of the blue component.
    
    inline CompT & Red() 
      { return data[0]; }
    //: Returns the level of the red component.
    
    inline CompT & Green()
      { return data[1]; }
    //: Returns the level of the green component.
    
    inline CompT & Blue()
      { return data[2]; }
    //: Returns the level of the blue component.
    
    inline CompT Intensity()
      { return (CompT)((RealT) 0.299 * data[0] + 0.587 * data[1] + 0.114 * data[2]); }
    // Returns the intensity of this color according to
    // the NTSC RGB color system.

  };
  
  template<class CompT>
  inline
  istream &operator>>(istream &strm,RGBValueC<CompT> &val) 
    { return strm >> ((TFVectorC<CompT,3> &)(val)); }
  //: Stream input.
  
  template<class CompT>
  inline
  ostream &operator<<(ostream &strm,const RGBValueC<CompT> &val) 
    { return strm << ((const TFVectorC<CompT,3> &)(val)); }
  //: Stream output.
  
  template<class CompT>
  inline
  BinIStreamC &operator>>(BinIStreamC &strm,RGBValueC<CompT> &val) 
    { return strm >> ((TFVectorC<CompT,3> &)(val)); }
  //: Binary stream input.
  
  template<class CompT>
  inline
  BinOStreamC &operator<<(BinOStreamC &strm,const RGBValueC<CompT> &val) 
    { return strm << ((const TFVectorC<CompT,3> &)(val)); }
  //: Binary stream output
}

#endif
