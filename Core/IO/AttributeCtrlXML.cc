// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! date="26/8/2003"
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/AttributeCtrlXML.cc"

#include "Ravl/DP/AttributeCtrl.hh"
#include "Ravl/DP/AttributeType.hh"
#include "Ravl/XMLStream.hh"
#include "Ravl/DList.hh"

// Put these in a seperate file, so we don't have to link the XMLStream stuff all the time.

namespace RavlN {
  
  //: Save setup to XML stream.
  
  bool AttributeCtrlBodyC::SaveAttributes(XMLOStreamC &strm) const {
    DListC<AttributeTypeC> list;
    if(!GetAttrTypes(list))
      return false;
    strm << XMLStartTag("AttributeSet");
    for(DLIterC<AttributeTypeC> it(list);it;it++) {
      StringC value;
      if(!it->CanWrite() || !it->CanRead())
	continue; // No point in saving attributes you can't change, or that you can't read.
      if(!(const_cast<AttributeCtrlBodyC *>(this)->GetAttr(it->Name(),value)))
	continue; // Can't read attribute.
      strm << XMLStartTag("Attribute") 
	   << XMLAttribute("name",it->Name()) 
	   << XMLAttribute("value",value);
      strm << XMLEndTag;
    }
    strm << XMLEndTag;
    return false;
  }
  
  //: Load setup from XML stream.
  
  bool AttributeCtrlBodyC::LoadAttributes(XMLIStreamC &strm) {
    StringC name,value;
    if(strm.ReadTag(name) != XMLBeginTag)
      throw ExceptionInvalidStreamC("Unexpected XML tag type when loading attributes  ");
    if(name != "AttributeSet")
      throw ExceptionInvalidStreamC("Unexpected XML tag when loading attributes  ");
    for(;;) {      
      XMLTagOpsT tagType =strm.ReadTag(name);
      if(tagType == XMLEndTag)
	break;
      if(name != "Attribute") { // Unknown attribute.
	strm.SkipElement();
	continue; 
      }
      name = StringC();
      value = StringC();
      strm >> XMLAttribute("name",name) 
	   >> XMLAttribute("value",value);
      if(!SetAttr(name,value))
	cerr << "WARNING: Failed to set attribute '" << name << "' to value '" << value << "' \n";
      strm.SkipElement();
    }
    return false;
  }
  
}
