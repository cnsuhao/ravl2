// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/AttributeSet.cc"

#include "Ravl/DP/AttributeSet.hh"
#include "Ravl/DP/AttributeType.hh"
#include "Ravl/DP/AttributeCtrlInternal.hh"
#include "Ravl/DP/AttributeValueTypes.hh"
#include "Ravl/DList.hh"

#define RAVL_GETCREATESATTRIBUTE 1

namespace RavlN {
  
  
  //: Default constructor
  // Creates an empty attribute set.
  
  AttributeSetBodyC::AttributeSetBodyC(bool nEnforceSchema)
    : enforceSchema(nEnforceSchema)
  {
    if(attrInfo == 0)
      attrInfo = new AttributeCtrlInternalC();
  }
  
  
  //: Copy schema from 'attr' and optionally current settings.
  // If current settings aren't copied then the values will be 
  // set to their defaults.
  
  AttributeSetBodyC::AttributeSetBodyC(AttributeCtrlC &ctrl,bool copySettings,bool nEnforceSchema)
    : enforceSchema(nEnforceSchema)
  {
    if(attrInfo == 0)
      attrInfo = new AttributeCtrlInternalC();
    DListC<AttributeTypeC> list;
    if(ctrl.GetAttrTypes(list))
      SetSchema(list);
  }
  
  //: Set attribute schema to use.
  
  bool AttributeSetBodyC::SetSchema(const DListC<AttributeTypeC> &attrTypes) {
    return attrInfo->SetSchema(attrTypes);
  }

  
  //: Copy settings from 'ctrl'.
  
  bool AttributeSetBodyC::CopyFrom(AttributeCtrlC &ctrl) {
    DListC<AttributeTypeC> list;
    if(!ctrl.GetAttrTypes(list))
      return false;
    if(SetSchema(list))
      return false;
    bool ret = true;
    for(DLIterC<AttributeTypeC> it(list);it;it++) {
      StringC value;
      if(!ctrl.GetAttr(it->Name(),value)) {
	ret = false;
	continue; // Can't read attribute.
      }
      values[it->Name()] = value;
    }
    return ret;
  }
  
  //: Copy settings to 'ctrl'.
  
  bool AttributeSetBodyC::CopyTo(AttributeCtrlC &ctrl) const {
    DListC<AttributeTypeC> list;
    if(!GetAttrTypes(list))
      return false;
    bool ret = true;
    for(DLIterC<AttributeTypeC> it(list);it;it++) {
      StringC value;
      if(!values.Lookup(it->Name(),value))
	continue;
      if(!ctrl.SetAttr(it->Name(),value))
	ret = false;
    }
    return ret;
  }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool AttributeSetBodyC::GetAttr(const StringC &attrName,StringC &attrValue) {
    AttributeTypeC attrType = attrInfo->GetAttrType(attrName);
    if(!attrType.IsValid()) {
#if RAVL_GETCREATESATTRIBUTE 
      if(enforceSchema)
	return AttributeCtrlBodyC::GetAttr(attrName,attrValue);
      RegisterAttribute(AttributeTypeStringC(attrName,"")); // Register new attribute.
#else
      return AttributeCtrlBodyC::GetAttr(attrName,attrValue);
#endif
    }
    StringC value;
    if(!values.Lookup(attrName,value)) {
      AttributeTypeStringC attrTypeInt(attrType);
      attrValue = attrTypeInt.Default();
      return true;
    }
    attrValue = value;
    return true;
  }
  
  //: Set a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool AttributeSetBodyC::SetAttr(const StringC &attrName,const StringC &attrValue) {
    AttributeTypeC attrType = attrInfo->GetAttrType(attrName);
    if(!attrType.IsValid()) {
      if(enforceSchema)
	return AttributeCtrlBodyC::SetAttr(attrName,attrValue);
      RegisterAttribute(AttributeTypeStringC(attrName,attrValue)); // Register new attribute.
    }
    values[attrName] = attrValue;
    return true;
  }


  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool AttributeSetBodyC::GetAttr(const StringC &attrName,IntT &attrValue) {
    AttributeTypeC attrType = attrInfo->GetAttrType(attrName);
    if(!attrType.IsValid()) {
#if RAVL_GETCREATESATTRIBUTE 
      if(enforceSchema)
	return AttributeCtrlBodyC::GetAttr(attrName,attrValue);
      attrType = AttributeTypeNumC<IntT>(attrName,"",true,true,1,0,0,0);
      RegisterAttribute(attrType); // Register new attribute.
#else
      return AttributeCtrlBodyC::GetAttr(attrName,attrValue);
#endif
    }
    StringC value;
    if(!values.Lookup(attrName,value)) {
      AttributeTypeNumC<IntT> attrTypeInt(attrType);
      attrValue = attrTypeInt.Default();
      return true;
    }
    attrValue = value.IntValue();
    return true;
  }
  
  //: Set a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool AttributeSetBodyC::SetAttr(const StringC &attrName,const IntT &attrValue) {
    AttributeTypeC attrType = attrInfo->GetAttrType(attrName);
    if(!attrType.IsValid()) {
      if(enforceSchema)
	return AttributeCtrlBodyC::SetAttr(attrName,attrValue);
      attrType = AttributeTypeNumC<IntT>(attrName,"",true,true,1,0,0,attrValue);
      RegisterAttribute(attrType); // Register new attribute.
    }
    values[attrName] = StringC(attrValue);
    return true;
  }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool AttributeSetBodyC::GetAttr(const StringC &attrName,RealT &attrValue) {
    AttributeTypeC attrType = attrInfo->GetAttrType(attrName);
    if(!attrType.IsValid()) {
#if RAVL_GETCREATESATTRIBUTE 
      if(enforceSchema)
	return AttributeCtrlBodyC::SetAttr(attrName,attrValue);
      attrType = AttributeTypeNumC<IntT>(attrName,"",true,true,1,0,0,0);
      RegisterAttribute(attrType); // Register new attribute.
#else
      return AttributeCtrlBodyC::SetAttr(attrName,attrValue);
#endif
    }
    StringC value;
    if(!values.Lookup(attrName,value)) {
      AttributeTypeNumC<RealT> attrTypeInt(attrType);
      attrValue = attrTypeInt.Default();
      return true;
    }
    attrValue = value.IntValue();
    return true;
  }
  
  //: Set a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool AttributeSetBodyC::SetAttr(const StringC &attrName,const RealT &attrValue) {
    AttributeTypeC attrType = attrInfo->GetAttrType(attrName);
    if(!attrType.IsValid()) {
      if(enforceSchema)
	return AttributeCtrlBodyC::SetAttr(attrName,attrValue);
      attrType = AttributeTypeNumC<RealT>(attrName,"",true,true,1,0,0,attrValue);
      RegisterAttribute(attrType); // Register new attribute.
    }
    values[attrName] = StringC(attrValue);
    return true;
  }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool AttributeSetBodyC::GetAttr(const StringC &attrName,bool &attrValue) {
    AttributeTypeC attrType = attrInfo->GetAttrType(attrName);
    if(!attrType.IsValid()) {
#if RAVL_GETCREATESATTRIBUTE 
      if(enforceSchema)
	return AttributeCtrlBodyC::GetAttr(attrName,attrValue);
      attrType = AttributeTypeBoolC(attrName,"",true,true,attrValue);
      RegisterAttribute(attrType); // Register new attribute.
#else
      return AttributeCtrlBodyC::GetAttr(attrName,attrValue);
#endif
    }
    StringC value;
    if(!values.Lookup(attrName,value)) {
      AttributeTypeBoolC attrTypeInt(attrType);
      attrValue = attrTypeInt.Default();
      return true;
    }
    attrValue = (value.IntValue()!=0);
    return true;
  }
  
  //: Set a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool AttributeSetBodyC::SetAttr(const StringC &attrName,const bool &attrValue) {
    AttributeTypeC attrType = attrInfo->GetAttrType(attrName);
    if(!attrType.IsValid()) {
      if(enforceSchema)
	return AttributeCtrlBodyC::SetAttr(attrName,attrValue);
      attrType = AttributeTypeBoolC(attrName,"",true,true,attrValue);
      RegisterAttribute(attrType); // Register new attribute.
    }
    values[attrName] = StringC((IntT) attrValue);
    return true;    
  }

}
