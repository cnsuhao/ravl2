// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/AttributeCtrl.cc"

#include "Ravl/DP/AttributeCtrl.hh"
#include "Ravl/DP/AttributeType.hh"
#include "Ravl/DP/AttributeCtrlInternal.hh"
#include "Ravl/MTLocks.hh"
#include "Ravl/Hash.hh"
#include "Ravl/DList.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/Trigger.hh"

#define DODEBUG 0
#if DODEBUG
//#include "Ravl/TypeName.hh"
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Default constructor.
  
  AttributeCtrlInternalC::AttributeCtrlInternalC()
    : trigIdAlloc(1)
  {}
  
  //: Setup new schema.
  
  bool AttributeCtrlInternalC::SetSchema(const DListC<AttributeTypeC> &nattribTypeList) {
    attribTypeList = nattribTypeList;
    attribTypes.Empty();
    for(DLIterC<AttributeTypeC> it(nattribTypeList);it;it++)
      attribTypes[it->Name()] = *it;
    return true;
  }
  
  //:-----------------------------------------------------------------------
  
  
  //: Default constructor.
  
  AttributeCtrlBodyC::AttributeCtrlBodyC()
    : attrInfo(0)
  {}
  
  //: Stream constructor.
  
  AttributeCtrlBodyC::AttributeCtrlBodyC(istream &in) 
    : DPEntityBodyC(in),
      attrInfo(0)
  {}
  
  //: Copy constructor.
  
  AttributeCtrlBodyC::AttributeCtrlBodyC(const AttributeCtrlBodyC &bod)
    : attrInfo(0)
  {
    RavlAssertMsg(0,"Not implemented. ");
  }
  
  //: Destructor.
  
  AttributeCtrlBodyC::~AttributeCtrlBodyC() {
    if(attrInfo != 0)
      delete attrInfo;
  }
  
  //: Assignment operator.
  AttributeCtrlBodyC &AttributeCtrlBodyC::operator=(const AttributeCtrlBodyC &) {
    RavlAssertMsg(0,"Not implemented. ");
    return *this;
  }
  
  //: Get Parent attribute control.
  
  AttributeCtrlC AttributeCtrlBodyC::ParentCtrl() const
  { return AttributeCtrlC(); }
  

  //: Get named attribute.
  
  StringC AttributeCtrlBodyC::GetAttr(const StringC &attrName) {
    StringC val;
    if(!GetAttr(attrName,val))
      return StringC();
    return val;
  }
  
  //: Get a stream attribute.
  // Returns false if the attribute name is unknown.
  
  bool AttributeCtrlBodyC::GetAttr(const StringC &attrName,StringC &attrValue) { 
    AttributeCtrlC parent = ParentCtrl();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.GetAttr(attrName,attrValue))
	return true;

    // Maybe attribute is of a different type ?
    
    AttributeTypeC attrType = GetAttrType(attrName);
    if(attrType.IsValid()) { // Do we know of this attribute ?
      switch(attrType.ValueType()) {
      case AVT_Bool: {
	bool val;
	if(!GetAttr(attrName,val))
	  break;
	attrValue = StringC(val ? "1" : "0");
	return true;
      }
      case AVT_Int: {
	IntT val;
	if(!GetAttr(attrName,val))
	  break;
	attrValue = StringC(val);
	return true;
      }
      case AVT_Real: {
	RealT val;
	if(!GetAttr(attrName,val))
	  break;
	attrValue = StringC(val);
	return true;
      }
      case AVT_String:
      case AVT_Enum:
      case AVT_Abstract:
      case AVT_None:
      case AVT_Invalid:
	// Don't know how to handle these...
	break;
      }
    }
#if RAVL_CHECK
    cerr << "AttributeCtrlBodyC::GetAttr(const StringC &,StringC &), Unknown attribute '" << attrName << "'\n";
#endif
    return false; 
  }
  
  //: Set a stream attribute.
  // Returns false if the attribute name is unknown.
  
  bool AttributeCtrlBodyC::SetAttr(const StringC &attrName,const StringC &attrValue) { 
    AttributeCtrlC parent = ParentCtrl();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.SetAttr(attrName,attrValue))
	return true;
    
    // Maybe attribute is of a different type ?
    
    AttributeTypeC attrType = GetAttrType(attrName);
    if(attrType.IsValid()) { // Do we know of this attribute ?
      switch(attrType.ValueType()) {
      case AVT_Bool: {
	StringC tmp = attrValue;
	tmp.downcase();
	bool val = false;
	if(tmp == "0" || tmp == "f" || tmp == "false")
	  val = false;
	else {
	  if(tmp == "1" || tmp == "t" || tmp == "true") 
	    val = true;
	  else
	    cerr << "AttributeCtrlBodyC::SetAttr(const StringC &,const StringC &), Ambigous boolean value '" << tmp << "' for attribute " << attrName << "\n";
	}
	if(SetAttr(attrName,val))
	  return true;
      } break;
      case AVT_Int:
	if(SetAttr(attrName,attrValue.IntValue()))
	  return true;
	break;
      case AVT_Real: 
	if(SetAttr(attrName,attrValue.RealValue()))
	  return true;
	break;
      case AVT_String:
      case AVT_Enum:
      case AVT_Abstract:
      case AVT_None:
      case AVT_Invalid:
	// Don't know how to handle these...
	break;
      }
    }
      
#if RAVL_CHECK
    cerr << "AttributeCtrlBodyC::SetAttr(const StringC &,const StringC &), Unknown attribute '" << attrName << "' Value:'" << attrValue << "'\n";
#endif
    return false; 
  }
  
  //: Get a stream attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling stream attributes such as frame rate, and compression ratios.
  
  bool AttributeCtrlBodyC::GetAttr(const StringC &attrName,IntT &attrValue) {
    AttributeCtrlC parent = ParentCtrl();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.GetAttr(attrName,attrValue))
	return true;
    
    // Is attribute of another type ?
    
    AttributeTypeC attrType = GetAttrType(attrName);
    if(attrType.IsValid()) { // Do we know of this attribute ?
      switch(attrType.ValueType()) {
      case AVT_Bool: {
	bool val;
	if(GetAttr(attrName,val))
	  return true;
	attrValue = val ? 1 : 0;
      } break;
      default:
	break;
      }
    }

#if RAVL_CHECK
    cerr << "AttributeCtrlBodyC::GetAttr(const StringC &,IntT &), Unknown attribute '" << attrName << "'\n";
#endif
    return false;
  }
  
  //: Set a stream attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling stream attributes such as frame rate, and compression ratios.
  
  bool AttributeCtrlBodyC::SetAttr(const StringC &attrName,const IntT &attrValue) {
    ONDEBUG(cerr << "AttributeCtrlBodyC::SetAttr(const StringC &,const IntT &) '" << attrName << "' = " <<attrValue << " \n");
    AttributeCtrlC parent = ParentCtrl();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.SetAttr(attrName,attrValue))
	return true;
    
    // Is attribute of another type ?
    
    AttributeTypeC attrType = GetAttrType(attrName);
    if(attrType.IsValid()) { // Do we know of this attribute ?
      switch(attrType.ValueType()) {
      case AVT_Bool:
	if(SetAttr(attrName,(attrValue != 0)))
	  return true;
	break;
      default:
	break;
      }
    }
#if RAVL_CHECK
    cerr << "AttributeCtrlBodyC::SetAttr(const StringC &,const IntT &), Unknown attribute '" << attrName << "' Value:'" << attrValue << "'\n";
#endif
    return false;
  }
  
  //: Get a stream attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling stream attributes such as frame rate, and compression ratios.
  
  bool AttributeCtrlBodyC::GetAttr(const StringC &attrName,RealT &attrValue) {
    AttributeCtrlC parent = ParentCtrl();
    ONDEBUG(cerr << "AttributeCtrlBodyC::GetAttr(const StringC &,const RealT &) '" << attrName << "'  Parent=" << parent.Hash() << "\n");
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.GetAttr(attrName,attrValue))
	return true;
#if RAVL_CHECK
    cerr << "AttributeCtrlBodyC::GetAttr(const StringC &,RealT &), Unknown attribute '" << attrName << "'\n";
#endif
    return false;
  }
  
  //: Set a stream attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling stream attributes such as frame rate, and compression ratios.

  bool AttributeCtrlBodyC::SetAttr(const StringC &attrName,const RealT &attrValue) {
    AttributeCtrlC parent = ParentCtrl();
    ONDEBUG(cerr << "AttributeCtrlBodyC::SetAttr(const StringC &,const RealT &) '" << attrName << "' = " <<attrValue << " Parent=" << parent.Hash() << " Obj=" << TypeName(typeid(*this)) << "\n");
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.SetAttr(attrName,attrValue))
	return true;
#if RAVL_CHECK
    cerr << "AttributeCtrlBodyC::SetAttr(const StringC &,const RealT &), Unknown attribute '" << attrName << "' Value:'" << attrValue << "'\n";
#endif
    return false;
  }


  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool AttributeCtrlBodyC::GetAttr(const StringC &attrName,bool &attrValue) {
    AttributeCtrlC parent = ParentCtrl();
    ONDEBUG(cerr << "AttributeCtrlBodyC::GetAttr(const StringC &,const bool &) '" << attrName << "'  Parent=" << parent.Hash() << "\n");
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.GetAttr(attrName,attrValue))
	return true;
    
    // Is attribute of another type ?
    
    AttributeTypeC attrType = GetAttrType(attrName);
    if(attrType.IsValid()) { // Do we know of this attribute ?
      switch(attrType.ValueType()) {
      case AVT_Int: {
	int val;
	if(!GetAttr(attrName,val))
	  return false;
	attrValue = (val != 0);
	return true;
      }
      default:
	break;
      }
    }

#if RAVL_CHECK
    cerr << "AttributeCtrlBodyC::GetAttr(const StringC &,bool &), Unknown attribute '" << attrName << "'\n";
#endif
    return false;
  }
  
  //: Set a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool AttributeCtrlBodyC::SetAttr(const StringC &attrName,const bool &attrValue) {
    AttributeCtrlC parent = ParentCtrl();
    ONDEBUG(cerr << "AttributeCtrlBodyC::SetAttr(const StringC &,const bool &) '" << attrName << "' = " <<attrValue << " Parent=" << parent.Hash() << " Obj=" << TypeName(typeid(*this)) << "\n");
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.SetAttr(attrName,attrValue))
	return true;

    // Maybe attribute is of a different type ?
    
    AttributeTypeC attrType = GetAttrType(attrName);
    if(attrType.IsValid()) { // Do we know of this attribute ?
      switch(attrType.ValueType()) {
      case AVT_Int:
	if(SetAttr(attrName,(IntT) attrValue))
	  return true;
	break;
      default:
	break;
      }
    }

#if RAVL_CHECK
    cerr << "AttributeCtrlBodyC::SetAttr(const StringC &,const bool &), Unknown attribute '" << attrName << "' Value:'" << attrValue << "'\n";
#endif
    return false;
  }
  
  //: Get list of attributes available.
  
  bool AttributeCtrlBodyC::GetAttrList(DListC<StringC> &list) const {
    if(attrInfo != 0)
      attrInfo->GetAttrList(list);
    AttributeCtrlC parent = ParentCtrl();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      parent.GetAttrList(list);
    return true;
  }

  //: Get a list of available attribute types.
  
  bool AttributeCtrlBodyC::GetAttrTypes(DListC<AttributeTypeC> &list) const {
    if(attrInfo != 0)
      attrInfo->GetAttrTypes(list);
    AttributeCtrlC parent = ParentCtrl();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      parent.GetAttrTypes(list);
    return true;
  }
  
  //: Get type of a particular attribute. 
  // Returns an invalid handle if attribute is unknown.
  
  AttributeTypeC AttributeCtrlBodyC::GetAttrType(const StringC &attrName) const {
    if(attrInfo != 0) {
      AttributeTypeC attr;
      if((attr = attrInfo->GetAttrType(attrName)).IsValid())
	return attr;
    }
    AttributeCtrlC parent = ParentCtrl();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      return parent.GetAttrType(attrName);
    return AttributeTypeC();
  }

  //: Register a value changed signal.
  // Note: This method may not be implemented for all AttributeCtrl's.
  // Returns an id for the trigger, or -1 if operation fails.
  
  IntT AttributeCtrlBodyC::RegisterChangedSignal(const StringC &name,const TriggerC &trig) {
    MTWriteLockC lock(3);
    if(attrInfo == 0)
      attrInfo = new AttributeCtrlInternalC();
    return attrInfo->RegisterChangedSignal(name,trig);
  }
  
  //: Remove a changed signal.
  // Note: This method may not be implemented for all AttributeCtrl's.
  
  bool AttributeCtrlBodyC::RemoveChangedSignal(IntT id) {
    MTWriteLockC lock(3);
    if(attrInfo == 0) // Nothing registered.
      return false;
    return attrInfo->RemoveChangedSignal(id);
  }
  
  //: Signal that an attribute has changed.
  
  bool AttributeCtrlBodyC::SignalChange(const StringC &attrName) {
    MTReadLockC lock(3);
    if(attrInfo == 0) // Can't be anything to do.
      return true; 
    attrInfo->IssueChangedSignal(attrName);
    return true;
  }
  
  //: Register a new attribute type.
  
  bool AttributeCtrlBodyC::RegisterAttribute(const AttributeTypeC &attr) {
    MTWriteLockC lock(3);
    if(attrInfo == 0)
      attrInfo = new AttributeCtrlInternalC();
    return attrInfo->RegisterAttribute(attr);
  }
  
  //: Set all attributes to default values.
  
  bool AttributeCtrlBodyC::RestoreDefaults() {
    if(attrInfo == 0)
      return false;
    bool ret = true;
    AttributeCtrlC me(*this);
    for(DLIterC<AttributeTypeC> it(attrInfo->Attributes());it;it++)
      ret &= it->SetToDefault(me);
    return ret;
  }
  
  //--------------------------------------------------------------------------

  //: Get a stream attribute.
  // Return the value of an attribute or an empty string if its unkown.
  // This is for handling stream attributes such as frame rate, and compression ratios.
  
  StringC AttributeCtrlC::GetAttr(const StringC &attrName) { 
    StringC ret;
    if(!Body().GetAttr(attrName,ret))
      return StringC(); 
    return ret;
  }
  
  //: Get type of attribute.
  
  AttributeTypeC AttributeCtrlC::GetAttrType(const StringC &attrName) const
  { return Body().GetAttrType(attrName); }

}
