// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ATTRIBUTETYPE_HEADER
#define RAVL_ATTRIBUTETYPE_HEADER 1
//! userlevel=Normal
//! author="Charles Galambos"
//! date="23/8/2003"
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/AttributeType.hh"

#include "Ravl/String.hh"
#include "Ravl/RCHandleV.hh"
#include "Ravl/DP/AttributeCtrl.hh"

namespace RavlN {

  enum AttributeValueTypeT
    { AVT_Bool,AVT_Int,AVT_Real,AVT_String,AVT_Enum, AVT_Abstract, AVT_ByteRGBImage, AVT_None, AVT_Invalid  };
  
  //! userlevel=Develop
  //: Attribute type information.
  
  class AttributeTypeBodyC 
    : public RCBodyVC
  {
  public:
    AttributeTypeBodyC();
    //: Constructor.
    
    AttributeTypeBodyC(const StringC &name,const StringC &desc,bool nCanRead = true,bool nCanWrite = true);
    //: Constructor.
    
    virtual bool SetToDefault(AttributeCtrlC &ctrl) const;
    //: Set control to default value.
    
    virtual AttributeValueTypeT ValueType() const;
    //: Get hint about type of value attribute has.
    
    const StringC &Name() const
    { return name; }
    //: Access name of attribute.
    
    const StringC &Description() const
    { return description; }
    //: Access description of attribute.
    
    bool CanRead() const
    { return canRead; }
    //: Can you read the value of this attribute ?
    
    bool CanWrite() const
    { return canWrite; }
    //: Can you write the value of this attribute.
    
  protected:
    StringC name;  // Name of attribute
    StringC description; // Optional discription
    bool canRead;  // Can be read.
    bool canWrite; // Can be written to
    
  };
  
  //! userlevel=Normal
  //: Attribute type information.
  
  class AttributeTypeC 
    : public RCHandleC<AttributeTypeBodyC>
  {
  public:
    AttributeTypeC()
    {}
    //: Default constructor
    // creates an invalid handle.
    
  protected:
    AttributeTypeC(AttributeTypeBodyC &bod)
      : RCHandleC<AttributeTypeBodyC>(bod)
    {}
    //: Body constructor.
    
    AttributeTypeBodyC &Body()
    { return RCHandleC<AttributeTypeBodyC>::Body(); }
    //: Access body.

    const AttributeTypeBodyC &Body() const
    { return RCHandleC<AttributeTypeBodyC>::Body(); }
    //: Access body.
    
  public:
    AttributeValueTypeT ValueType() const
    { return Body().ValueType(); }
    //: Get hint about type of value attribute has.
    
    const StringC &Name() const
    { return Body().Name(); }
    //: Access name of attribute.
    
    const StringC &Description() const
    { return Body().Description(); }
    //: Access description of attribute.
    
    bool CanRead() const
    { return Body().CanRead(); }
    //: Can you read the value of this attribute ?
    
    bool CanWrite() const
    { return Body().CanWrite(); }
    //: Can you write the value of this attribute.
    
    bool SetToDefault(AttributeCtrlC &ctrl) const
    { return Body().SetToDefault(ctrl); }
    //: Set control to default value.
    
  };
}

#endif
