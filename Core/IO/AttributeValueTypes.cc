// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/AttributeValueTypes.cc"


#include "Ravl/DP/AttributeValueTypes.hh"

namespace RavlN {
  
  //: Constructor
  
  AttributeTypeBoolBodyC::AttributeTypeBoolBodyC(const StringC &name,const StringC &desc,bool nCanRead,bool nCanWrite,bool ndefault)
    : AttributeTypeBodyC(name,desc,nCanRead,nCanWrite),
      defaultValue(ndefault)
  {}
  
  //: Get hint about type of value attribute has.
  
  AttributeValueTypeT AttributeTypeBoolBodyC::ValueType()
  { return AVT_Bool; }
  
  //: Set control to default value.
  
  bool AttributeTypeBoolBodyC::SetToDefault(AttributeCtrlC &ctrl) const
  { return ctrl.SetAttr(name,defaultValue); }
  
  //:----------------------------------------------------------------------------------------------------
  
  //: Constructor
  
  AttributeTypeStringBodyC::AttributeTypeStringBodyC(const StringC &name,const StringC &desc,bool nCanRead,bool nCanWrite,const StringC &ndefault,IntT nMaxLen)
    : AttributeTypeBodyC(name,desc,nCanRead,nCanWrite),
      defaultValue(ndefault),
      maxLength(nMaxLen)
  {}
  
  //: Get hint about type of value attribute has.
  
  AttributeValueTypeT AttributeTypeStringBodyC::ValueType()
  { return AVT_String; }

  //: Set control to default value.
  
  bool AttributeTypeStringBodyC::SetToDefault(AttributeCtrlC &ctrl) const
  { return ctrl.SetAttr(name,defaultValue); }
  
  //:----------------------------------------------------------------------------------------------------
  
  //: Constructor
  
  AttributeTypeEnumBodyC::AttributeTypeEnumBodyC(const StringC &name,const StringC &desc,bool nCanRead,bool nCanWrite,
						 const DListC<StringC> &nvalues,const StringC &ndefaultValue)
    : AttributeTypeBodyC(name,desc,nCanRead,nCanWrite),
      defaultValue(ndefaultValue),
      values(nvalues)
  {}
  
  //: Get hint about type of value attribute has.
  
  AttributeValueTypeT AttributeTypeEnumBodyC::ValueType()
  { return AVT_Enum; }
  
  bool AttributeTypeEnumBodyC::SetToDefault(AttributeCtrlC &ctrl) const
  { return ctrl.SetAttr(name,defaultValue); }
  
}
