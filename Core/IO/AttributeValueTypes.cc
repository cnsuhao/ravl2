// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/AttributeValueTypes.cc"

#include "Ravl/BinStream.hh"
#include "Ravl/DP/AttributeValueTypes.hh"
#include "Ravl/VirtualConstructor.hh"

namespace RavlN {
  
  //: Constructor
  
  AttributeTypeBoolBodyC::AttributeTypeBoolBodyC(const StringC &name,const StringC &desc,bool nCanRead,bool nCanWrite,bool ndefault)
    : AttributeTypeBodyC(name,desc,nCanRead,nCanWrite),
      defaultValue(ndefault)
  {}
  
  //: Binary stream constructor.
  
  AttributeTypeBoolBodyC::AttributeTypeBoolBodyC(BinIStreamC &is)
    : AttributeTypeBodyC(is)
  { is >> defaultValue; }
  
  //: stream constructor.
  
  AttributeTypeBoolBodyC::AttributeTypeBoolBodyC(istream &is)
    : AttributeTypeBodyC(is)
  { is >> defaultValue; }
  
  //: Save the attribute to a stream 
  
  bool AttributeTypeBoolBodyC::Save(ostream & strm) const {
    if(!AttributeTypeBodyC::Save(strm))
      return false;
    strm << ' ' << defaultValue;
    return true;
  }
  
  //: Save the attribute to a stream 
  
  bool AttributeTypeBoolBodyC::Save(BinOStreamC & strm) const {
    if(!AttributeTypeBodyC::Save(strm))
      return false;
    strm << defaultValue;
    return true;
  }
  
  //: Get hint about type of value attribute has.
  
  AttributeValueTypeT AttributeTypeBoolBodyC::ValueType() const
  { return AVT_Bool; }
  
  //: Set control to default value.
  
  bool AttributeTypeBoolBodyC::SetToDefault(AttributeCtrlC &ctrl) const
  { return ctrl.SetAttr(name,defaultValue); }
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(AttributeTypeBoolBodyC,AttributeTypeBoolC,AttributeTypeC);
  
  //:----------------------------------------------------------------------------------------------------
  
  //: Constructor
  
  AttributeTypeStringBodyC::AttributeTypeStringBodyC(const StringC &name,const StringC &desc,bool nCanRead,bool nCanWrite,const StringC &ndefault,IntT nMaxLen)
    : AttributeTypeBodyC(name,desc,nCanRead,nCanWrite),
      defaultValue(ndefault),
      maxLength(nMaxLen)
  {}
  
  //: Binary stream constructor.
  
  AttributeTypeStringBodyC::AttributeTypeStringBodyC(BinIStreamC &is)
    : AttributeTypeBodyC(is)
  { is >> defaultValue >> maxLength; }
  
  //: stream constructor.

  AttributeTypeStringBodyC::AttributeTypeStringBodyC(istream &is)
    : AttributeTypeBodyC(is)
  { is >> defaultValue >> maxLength; }
  
  //: Save the attribute to a stream 
  
  bool AttributeTypeStringBodyC::Save(ostream & strm) const {
    if(!AttributeTypeBodyC::Save(strm))
      return false;
    strm << ' ' << defaultValue << ' ' << maxLength;
    return true;
  }
  
  //: Save the attribute to a stream 
  
  bool AttributeTypeStringBodyC::Save(BinOStreamC & strm) const {
    if(!AttributeTypeBodyC::Save(strm))
      return false;
    strm << defaultValue << maxLength;
    return true;
  }
  
  //: Get hint about type of value attribute has.
  
  AttributeValueTypeT AttributeTypeStringBodyC::ValueType() const
  { return AVT_String; }

  //: Set control to default value.
  
  bool AttributeTypeStringBodyC::SetToDefault(AttributeCtrlC &ctrl) const
  { return ctrl.SetAttr(name,defaultValue); }

  RAVL_INITVIRTUALCONSTRUCTOR_FULL(AttributeTypeStringBodyC,AttributeTypeStringC,AttributeTypeC);
  
  //:----------------------------------------------------------------------------------------------------
  
  //: Constructor
  
  AttributeTypeEnumBodyC::AttributeTypeEnumBodyC(const StringC &name,const StringC &desc,bool nCanRead,bool nCanWrite,
						 const DListC<StringC> &nvalues,const StringC &ndefaultValue)
    : AttributeTypeBodyC(name,desc,nCanRead,nCanWrite),
      defaultValue(ndefaultValue),
      values(nvalues)
  {}
  
  //: Binary stream constructor.
  
  AttributeTypeEnumBodyC::AttributeTypeEnumBodyC(BinIStreamC &is)
    : AttributeTypeBodyC(is)
  { is >> defaultValue >> values; }
  
  //: stream constructor.
  
  AttributeTypeEnumBodyC::AttributeTypeEnumBodyC(istream &is)
    : AttributeTypeBodyC(is)
  { is >> defaultValue >> values; }
    
  //: Save the attribute to a stream 
  
  bool AttributeTypeEnumBodyC::Save(ostream & strm) const {
    if(!AttributeTypeBodyC::Save(strm))
      return false;
    strm << ' ' << defaultValue << ' ' << values;
    return true;
  }
  
  //: Save the attribute to a stream 
  
  bool AttributeTypeEnumBodyC::Save(BinOStreamC & strm) const {
    if(!AttributeTypeBodyC::Save(strm))
      return false;
    strm << defaultValue << values;
    return true;
  }
  
  //: Get hint about type of value attribute has.
  
  AttributeValueTypeT AttributeTypeEnumBodyC::ValueType() const
  { return AVT_Enum; }
  
  bool AttributeTypeEnumBodyC::SetToDefault(AttributeCtrlC &ctrl) const
  { return ctrl.SetAttr(name,defaultValue); }
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(AttributeTypeEnumBodyC,AttributeTypeEnumC,AttributeTypeC);
  
  //:----------------------------------------------------------------------------------------------------
  
  //: Constructor
  
  AttributeTypeMiscBodyC::AttributeTypeMiscBodyC(const StringC &name,const StringC &desc,const AttributeValueTypeT &nvalType,bool nCanRead,bool nCanWrite)
    : AttributeTypeBodyC(name,desc,nCanRead,nCanWrite),
      valType(nvalType)
  {}
  
  //: Get hint about type of value attribute has.
  
  AttributeValueTypeT AttributeTypeMiscBodyC::ValueType() const
  { return valType; }
  
  //: Set control to default value.
  
  bool AttributeTypeMiscBodyC::SetToDefault(AttributeCtrlC &ctrl) const
  { return true; }
  
  //:----------------------------------------------------------------------------------------------------
  
  static VirtualConstructorInstC<AttributeTypeNumBodyC<IntT> > vc_function_AttributeTypeNumBodyC_IntT("AttributeTypeNumBodyC<IntT>" );
  static VirtualConstructorInstC<AttributeTypeNumBodyC<RealT> > vc_function_AttributeTypeNumBodyC_RealT("AttributeTypeNumBodyC<RealT>" );
  
  
}
