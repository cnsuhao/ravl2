// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/AttributeType.cc"

#include "Ravl/DP/AttributeType.hh"

namespace RavlN {
  
  //: Constructor.
  
  AttributeTypeBodyC::AttributeTypeBodyC()
    : canRead(true),
      canWrite(true)
  {}
  
  //: Constructor.
  
  AttributeTypeBodyC::AttributeTypeBodyC(const StringC &nname,const StringC &ndesc,bool nCanRead,bool nCanWrite)
    : name(nname),
      description(ndesc),
      canRead(nCanRead),
      canWrite(nCanWrite)
  {}
  

  //: Get hint about type of value attribute has.
  
  AttributeValueTypeT AttributeTypeBodyC::ValueType() const
  { return AVT_Invalid; }
  
  //: Set control to default value.
  
  bool AttributeTypeBodyC::SetToDefault(AttributeCtrlC &ctrl) const {
    RavlAssertMsg(0,"AttributeTypeBodyC::SetToDefault(), ERROR: Abstract method called. ");
    return false;
  }

//: Save attribute to stream 
bool AttributeTypeBodyC::Save(ostream & strm) const {
  strm << name << "\t" << description << "\t" << canRead << "\t" << canWrite ; 
  return true ; 
}

//: Output to stream 
ostream & operator << (ostream & strm, const AttributeTypeBodyC & obj) 
{ 
  strm << "Name: " << obj.Name()  << "\t" << obj.Description() << "\tCan Read: " << obj.CanRead() << "\t Can Write: " << obj.CanWrite() ; 
  //obj.Save(strm) ; 
return strm ; 
}

  
}


