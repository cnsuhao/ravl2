// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////
// $Id$
//! rcsid="$Id$"
//! lib=RavlIO

#include "Ravl/DP/Port.hh"
#include "Ravl/String.hh"

namespace RavlN {
  /////////////////////////////////////////////////////////
  
  //: Is this port connected to another ?
  // If not returns invalid handle.
  
  DPPortC DPPortBodyC::ConnectedTo() const { 
    return DPPortC(); 
  }
  
  //: Does port work asynchronously ?
  
  bool DPPortBodyC::IsAsync() const  { 
    return false; 
  }
  
  //: Get a stream attribute.
  // Returns false if the attribute name is unknown.
  
  bool DPPortBodyC::GetAttr(const StringC &attrName,StringC &attrValue) { 
    DPPortC parent = ConnectedTo();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.GetAttr(attrName,attrValue))
	return true;
#if RAVL_CHECK
    cerr << "DPPortBodyC::GetAttr(), Unknow attribute '" << attrName << "'\n";
#endif
    return false; 
  }
  
  //: Set a stream attribute.
  // Returns false if the attribute name is unknown.
  
  bool DPPortBodyC::SetAttr(const StringC &attrName,const StringC &attrValue) { 
    DPPortC parent = ConnectedTo();
    // Try pasing it back along the processing chain.
    if(parent.IsValid())
      if(parent.SetAttr(attrName,attrValue))
	return true;
#if RAVL_CHECK
    cerr << "DPPortBodyC::SetAttr(), Unknow attribute '" << attrName << "' Value:'" << attrValue << "'\n";
#endif
    return false; 
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

