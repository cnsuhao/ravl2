// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/Port.cc"

#include "Ravl/DP/Port.hh"
#include "Ravl/String.hh"
#include "Ravl/DList.hh"

#define DODEBUG 0
#if DODEBUG
#include "Ravl/TypeName.hh"
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  ////////////////////////////////////////////////////////
  //: Stream constructor.
  
  DPPortBodyC::DPPortBodyC(istream &in) 
    : DPEntityBodyC(in)
  { in >> portId; }
  
  
  //: Is this port connected to another ?
  // If not returns invalid handle.
  
  DPPortC DPPortBodyC::ConnectedTo() const { 
    return DPPortC(); 
  }
  
  //: Does port work asynchronously ?
  
  bool DPPortBodyC::IsAsync() const  { 
    return false; 
  }

  //: Save to ostream.
  
  bool DPPortBodyC::Save(ostream &out) const { 
    if(!DPEntityBodyC::Save(out))
      return false;
    out << portId << ' ';
    return true;
  }
  
  //: Get a stream attribute.
  // Returns false if the attribute name is unknown.
  
  bool DPPortBodyC::GetAttr(const StringC &attrName,StringC &attrValue) { 
    if(attrName == "id") {
      attrValue = portId;
      return true;
    }
    DPPortC parent = ConnectedTo();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.GetAttr(attrName,attrValue))
	return true;
#if RAVL_CHECK
    cerr << "DPPortBodyC::GetAttr(const StringC &,StringC &), Unknown attribute '" << attrName << "'\n";
#endif
    return false; 
  }

  //: Get a stream attribute.
  // Return the value of an attribute or an empty string if its unkown.
  // This is for handling stream attributes such as frame rate, and compression ratios.
  
  StringC DPPortC::GetAttr(const StringC &attrName) { 
    StringC ret;
    if(!Body().GetAttr(attrName,ret))
      return StringC(); 
    return ret;
  }
  
  //: Set a stream attribute.
  // Returns false if the attribute name is unknown.
  
  bool DPPortBodyC::SetAttr(const StringC &attrName,const StringC &attrValue) { 
    if(attrName == "id") {
      portId = attrValue;
      return true;
    }
    DPPortC parent = ConnectedTo();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.SetAttr(attrName,attrValue))
	return true;
#if RAVL_CHECK
    cerr << "DPPortBodyC::SetAttr(const StringC &,const StringC &), Unknown attribute '" << attrName << "' Value:'" << attrValue << "'\n";
#endif
    return false; 
  }
  
  //: Get a stream attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling stream attributes such as frame rate, and compression ratios.
  
  bool DPPortBodyC::GetAttr(const StringC &attrName,IntT &attrValue) {
    DPPortC parent = ConnectedTo();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.GetAttr(attrName,attrValue))
	return true;
#if RAVL_CHECK
    cerr << "DPPortBodyC::GetAttr(const StringC &,IntT &), Unknown attribute '" << attrName << "'\n";
#endif
    return false;
  }
  
  //: Set a stream attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling stream attributes such as frame rate, and compression ratios.
  
  bool DPPortBodyC::SetAttr(const StringC &attrName,const IntT &attrValue) {
    ONDEBUG(cerr << "DPPortBodyC::SetAttr(const StringC &,const IntT &) '" << attrName << "' = " <<attrValue << " \n");
    DPPortC parent = ConnectedTo();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.SetAttr(attrName,attrValue))
	return true;
#if RAVL_CHECK
    cerr << "DPPortBodyC::SetAttr(const StringC &,const IntT &), Unknown attribute '" << attrName << "' Value:'" << attrValue << "'\n";
#endif
    return false;
  }
  
  //: Get a stream attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling stream attributes such as frame rate, and compression ratios.
  
  bool DPPortBodyC::GetAttr(const StringC &attrName,RealT &attrValue) {
    DPPortC parent = ConnectedTo();
    ONDEBUG(cerr << "DPPortBodyC::GetAttr(const StringC &,const IntT &) '" << attrName << "'  Parent=" << parent.Hash() << "\n");
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.GetAttr(attrName,attrValue))
	return true;
#if RAVL_CHECK
    cerr << "DPPortBodyC::GetAttr(const StringC &,RealT &), Unknown attribute '" << attrName << "'\n";
#endif
    return false;
  }
  
  //: Set a stream attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling stream attributes such as frame rate, and compression ratios.

  bool DPPortBodyC::SetAttr(const StringC &attrName,const RealT &attrValue) {
    DPPortC parent = ConnectedTo();
    ONDEBUG(cerr << "DPPortBodyC::SetAttr(const StringC &,const IntT &) '" << attrName << "' = " <<attrValue << " Parent=" << parent.Hash() << " Obj=" << TypeName(typeid(*this)) << "\n");
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.SetAttr(attrName,attrValue))
	return true;
#if RAVL_CHECK
    cerr << "DPPortBodyC::SetAttr(const StringC &,const RealT &), Unknown attribute '" << attrName << "' Value:'" << attrValue << "'\n";
#endif
    return false;
  }

  //: Get list of attributes available.
  
  bool DPPortBodyC::GetAttrList(DListC<StringC> &list) const {
    DPPortC parent = ConnectedTo();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      parent.GetAttrList(list);
    return true;
  }
  
  /////////////////////////////////////////////////////////
  
  // Input type.
  
  const type_info &DPIPortBaseBodyC::InputType() const  {
    RavlAssert(0);
    return typeid(void);
  }
  
  //: Is some data ready ?
  // true = yes.
  
  bool DPIPortBaseBodyC::IsGetReady() const  { 
    return !IsGetEOS(); 
  }
  
  //: Is some data ready ?
  // true = yes.
  
  bool DPIPortBaseBodyC::IsGetEOS() const  { 
    return false; 
  }

  //: Discard the next input datum.
  
  bool DPIPortBaseBodyC::Discard()  { 
    return false; 
  }

  /////////////////////////////////////////////////////////
  
  //: Is port ready for data ?
  
  bool DPOPortBaseBodyC::IsPutReady() const  { 
    return true; 
  }

  //: Put End Of Stream marker.
  
  void DPOPortBaseBodyC::PutEOS()
  {}
  
  // Output type.
  
  const type_info &DPOPortBaseBodyC::OutputType() const {
    RavlAssert(0);
    return typeid(void);
  }
}

