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

#define DODEBUG 0
#if DODEBUG
//#include "Ravl/TypeName.hh"
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Stream constructor.
  
  AttributeCtrlBodyC::AttributeCtrlBodyC(istream &in) 
    : DPEntityBodyC(in)
  {}
  
  //: Destructor.
  
  AttributeCtrlBodyC::~AttributeCtrlBodyC()
  {}
  
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
#if RAVL_CHECK
    cerr << "AttributeCtrlBodyC::SetAttr(const StringC &,const bool &), Unknown attribute '" << attrName << "' Value:'" << attrValue << "'\n";
#endif
    return false;
  }
  
  //: Get list of attributes available.
  
  bool AttributeCtrlBodyC::GetAttrList(DListC<StringC> &list) const {
    AttributeCtrlC parent = ParentCtrl();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      parent.GetAttrList(list);
    return true;
  }

  //: Get a list of available attribute types.
  
  bool AttributeCtrlBodyC::GetAttrTypes(DListC<AttributeTypeC> &list) const {
    AttributeCtrlC parent = ParentCtrl();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      parent.GetAttrTypes(list);
    return true;
  }
  
  //: Get type of a particular attribute. 
  // Returns an invalid handle if attribute is unknown.
  
  AttributeTypeC AttributeCtrlBodyC::GetAttrType(const StringC &attrName) const {
    AttributeCtrlC parent = ParentCtrl();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      return parent.GetAttrType(attrName);
    return AttributeTypeC();
  }

  //: Register a value changed signal.
  // Note: This method may not be implemented for all AttributeCtrl's.
  // Returns an id for the trigger, or -1 if operation fails.
  
  IntT AttributeCtrlBodyC::RegisterChangedSignal(const TriggerC &trig) {
    return -1;
  }
  
  //: Remove a changed signal.
  // Note: This method may not be implemented for all AttributeCtrl's.
  
  bool AttributeCtrlBodyC::RemoveChangedSignal(IntT id) {
    return false;
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
