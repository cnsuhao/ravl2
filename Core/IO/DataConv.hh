// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDPDATACONV_HEADER
#define RAVLDPDATACONV_HEADER 1
/////////////////////////////////////////////////////////
//! docentry="Ravl.Core.IO.Type Converter"
//! lib=RavlIO
//! rcsid="$Id$"
//! file="Ravl/Core/IO/DataConv.hh"
//! userlevel=Default
//! author="Charles Galambos"
//! date="17/08/98"

#include "Ravl/RCWrap.hh"
#include "Ravl/RCAbstract.hh"

namespace RavlN {
  extern bool DPCanConvert(const type_info &from,const type_info &to);
  //: Test if conversion is possible.
  
  extern RCAbstractC DPDoConvertion(const RCAbstractC &dat,const type_info &from,const type_info &to);
  //: Do conversion through abstract handles.
  
  template<class InT,class OutT>
  bool DPTypeConvert(const InT &inraw,OutT &outraw) {
    RCAbstractC result = DPDoConvertion(RCWrapC<InT>(inraw).Abstract(),typeid(InT),
					typeid(OutT));
    RCWrapC<OutT> out(result);
    if(!out.IsValid())
      return false; // Did conversion succeed ?
    outraw = out.Data();
    return true;
  }
  
  template<class OutT>
  bool DPTypeConvert(const RCWrapAbstractC &in,OutT &outraw) {
    RCAbstractC result = DPDoConvertion(const_cast<RCWrapAbstractC &>(in).Abstract(),in.DataType(),
					typeid(OutT));
    RCWrapC<OutT> out(result);
    if(!out.IsValid())
      return false; // Did conversion succeed ?
    outraw = out.Data();
    return true;
  }
}



#endif
