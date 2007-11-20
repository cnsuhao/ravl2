// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2007, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_STL_HEADER
#define RAVL_STL_HEADER 1
//////////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/System/STL.hh"
//! author="Charles Galambos" 
//! lib=RavlCore
//! date="12/11/2007"
//! docentry="Ravl.API.Core.STL"
//! userlevel=Normal
//! rcsid="$Id$"

// STL Compatibily methods.

#include "Ravl/StdHash.hh"
#include "Ravl/SArray1d.hh"
#include <vector>
#include <string>
#include <typeinfo>

namespace RavlN {
  class BinOStreamC;
  class BinIStreamC;
  
  BinOStreamC &operator<<(BinOStreamC &strm,const std::string &str);
  //: Write an STL string to binary stream.
  
  BinIStreamC &operator>>(BinIStreamC &strm,std::string &str);
  //: Read an STL string from binary stream.
  
  template<typename DataT>
  BinOStreamC &operator<<(BinOStreamC &strm,const std::vector<DataT> &vec) {
    SizeT size = vec.size();
    strm << size;
    for(SizeT i = 0;i <size;i++)
      strm << vec[i];
    return strm;
  }
  //: Write an STL vector to binary stream.
    
  template<typename DataT>
  BinIStreamC &operator>>(BinIStreamC &strm,std::vector<DataT> &vec) {
    SizeT size = 0;
    strm >> size;
    vec = std::vector<DataT>(size);
    for(SizeT i = 0;i <size;i++)
      strm >> vec[i];
    return strm;
  }
  //: Read an STL vector from binary stream.
  
  inline UIntT StdHash(const std::type_info &ti)
  { return StdHash(ti.name()); }
  //: Hash value for type info

  inline UIntT StdHash(const std::string &ti)
  { return StdHash(ti.data()); }
  //: Hash value for STL string

  template<typename DataT>
  inline UIntT StdHash(const std::vector<DataT> &vec)
  { 
    UIntT hv = vec.size();
    for(IntT i = 0;i < vec.size();i++) {
      UIntT lv = StdHash(vec[i]);
      hv += lv ^ (lv << (i % 20));
    }
    return hv;
  }
  //: Hash value for STL vector.

  template<typename DataT>
  SArray1dC<DataT> SArrayOf(const std::vector<DataT> &data) {
    if(data.size() < 1) return SArray1dC<DataT>();
    return SArray1dC<DataT>(&(data[0]),data.size());
  }
  //: Turn an STL vector into an SArray1dC.
}


#endif
