// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ATTRIBUTEVALUETYPES_HEADER
#define RAVL_ATTRIBUTEVALUETYPES_HEADER 1
//! author="Charles Galambos"
//! date="23/8/2003"
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/AttributeValueTypes.hh"
//! docentry="Ravl.Core.Data_Processing.Attributes"

#include "Ravl/DP/AttributeType.hh"
#include "Ravl/DList.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Boolean attribute type.
  
  class AttributeTypeBoolBodyC
    : public AttributeTypeBodyC
  {
  public:
    AttributeTypeBoolBodyC(const StringC &name,const StringC &desc,bool nCanRead = true,bool nCanWrite = true,
			   bool ndefaultValue = false);
    //: Constructor
    
    virtual AttributeValueTypeT ValueType() const;
    //: Get hint about type of value attribute has.
    
    bool Default() const
    { return defaultValue; }
    //: Access defaultValue value
    
    virtual bool SetToDefault(AttributeCtrlC &ctrl) const;
    //: Set control to default value.
    
  protected:
    bool defaultValue;
  };
  
  //! userlevel=Normal
  //: Boolean attribute type.
  
  class AttributeTypeBoolC
    : public AttributeTypeC
  {
  public:
    AttributeTypeBoolC()
    {}
    //: DefaultValue constructor.
    // Creates an invalid handle.
    
    AttributeTypeBoolC(const StringC &name,const StringC &desc,bool nCanRead = true,bool nCanWrite = true,bool ndefaultValue = false)
      : AttributeTypeC(*new AttributeTypeBoolBodyC(name,desc,nCanRead,nCanWrite,ndefaultValue))
    {}
    //: Constructor.
    
    AttributeTypeBoolC(const AttributeTypeC &base)
      : AttributeTypeC(base)
    {
      if(dynamic_cast<AttributeTypeBoolBodyC *>(&AttributeTypeC::Body()) == 0)
	Invalidate();
    }
    //: Construct from a base handle
    // Creates an invalid handle if object is not of the correct type.
    
  protected:
    AttributeTypeBoolC(AttributeTypeBoolBodyC &bod)
      : AttributeTypeC(bod)
    {}
    //: Body constructor.
    
    AttributeTypeBoolBodyC &Body()
    { return static_cast<AttributeTypeBoolBodyC &> (AttributeTypeC::Body()); }
    //: Access body.
    
    const AttributeTypeBoolBodyC &Body() const
    { return static_cast<const AttributeTypeBoolBodyC &> (AttributeTypeC::Body()); }
    //: Access body.
    
  public:
    bool Default() const
    { return Body().Default(); }
    //: DefaultValue value.
  };
  
  //:-----------------------------------------------------------------------------------
  
  //! userlevel=Develop
  //: Integer attribute value type.
  
  template<typename ValueT> 
  class AttributeTypeNumBodyC
    : public AttributeTypeBodyC
  {
  public:
    AttributeTypeNumBodyC()
    {}
    //: DefaultValue constructor.
    
    AttributeTypeNumBodyC(const StringC &name,const StringC &desc,bool nCanRead = true,bool nCanWrite = true,
			  ValueT nmin = ValueT(),ValueT nmax = ValueT(),ValueT nstep = ValueT(),ValueT ndefaultValue = ValueT())
      : AttributeTypeBodyC(name,desc,nCanRead,nCanWrite),
	min(nmin),max(nmax),step(nstep),defaultValue(ndefaultValue)
    {}
    //: Constructor.
    
    virtual AttributeValueTypeT ValueType() const{
      if(typeid(ValueT) == typeid(int))
	return AVT_Int;
      if(typeid(ValueT) == typeid(RealT))
	return AVT_Real;
      return AVT_Invalid;
    }
    //: Get hint about type of value attribute has.
    
    ValueT Min() const
    { return min; }
    //: Minimum value
    
    ValueT Max() const
    { return max; }
    //: Maximum value
    
    ValueT Step() const
    { return step; }
    //: Increment steps.
    
    ValueT Default() const
    { return defaultValue; }
    //: DefaultValue value.
    
    virtual bool SetToDefault(AttributeCtrlC &ctrl) const
    { return ctrl.SetAttr(name,defaultValue); }
    //: Set control to default value.
    
  protected:
    ValueT min;
    ValueT max;
    ValueT step;
    ValueT defaultValue;
  };


  //! userlevel=Develop
  //: Integer attribute value type.
  
  template<typename ValueT> 
  class AttributeTypeNumC
    : public AttributeTypeC
  {
  public:
    AttributeTypeNumC()
    {}
    //: DefaultValue constructor.
    // Creates an invalid handle.
    
    AttributeTypeNumC(const StringC &name,const StringC &desc,bool nCanRead = true,bool nCanWrite = true,
		      ValueT nmin = ValueT(),ValueT nmax = ValueT(),ValueT nstep = ValueT(),ValueT ndefaultValue = ValueT())
      : AttributeTypeC(*new AttributeTypeNumBodyC<ValueT>(name,desc,nCanRead,nCanWrite,nmin,nmax,nstep,ndefaultValue))
    {}
    //: Constructor.

    AttributeTypeNumC(const AttributeTypeC &base)
      : AttributeTypeC(base)
    {
      if(dynamic_cast<AttributeTypeNumBodyC<ValueT> *>(&AttributeTypeC::Body()) == 0)
	Invalidate();
    }
    //: Construct from a base handle
    // Creates an invalid handle if object is not of the correct type.
    
  protected:
    AttributeTypeNumC(AttributeTypeNumBodyC<ValueT> &bod)
      : AttributeTypeC(bod)
    {}
    //: Body constructor.
    
    AttributeTypeNumBodyC<ValueT> &Body()
    { return static_cast<AttributeTypeNumBodyC<ValueT> &> (AttributeTypeC::Body()); }
    //: Access body.

    const AttributeTypeNumBodyC<ValueT> &Body() const
    { return static_cast<const AttributeTypeNumBodyC<ValueT> &> (AttributeTypeC::Body()); }
    //: Access body.
    
  public:
    ValueT Min() const
    { return Body().Min(); }
    //: Minimum value
    
    ValueT Max() const
    { return Body().Max(); }
    //: Maximum value
    
    ValueT Step() const
    { return Body().Step(); }
    //: Increment steps.
    
    ValueT Default() const
    { return Body().Default(); }
    //: DefaultValue value.
    
  };

  //:-----------------------------------------------------------------------------------
  
  //! userlevel=Develop
  //: Boolean attribute type.
  
  class AttributeTypeStringBodyC
    : public AttributeTypeBodyC
  {
  public:
    AttributeTypeStringBodyC(const StringC &name,const StringC &desc,bool nCanRead = true,bool nCanWrite = true,
			     const StringC &ndefaultValue = StringC(),IntT maxLength = 65000);
    //: Constructor
    
    virtual AttributeValueTypeT ValueType() const;
    //: Get hint about type of value attribute has.

    StringC Default() const
    { return defaultValue; }
    //: Access defaultValue value
    
    IntT MaxLength() const
    { return maxLength; }
    //: Get maximum length for the string.
    
    virtual bool SetToDefault(AttributeCtrlC &ctrl) const;
    //: Set control to default value.
    
  protected:
    StringC defaultValue;
    IntT maxLength;
  };
  
  //! userlevel=Normal
  //: Boolean attribute type.
  
  class AttributeTypeStringC
    : public AttributeTypeC
  {
  public:
    AttributeTypeStringC()
    {}
    //: DefaultValue constructor.
    // Creates an invalid handle.
    
    AttributeTypeStringC(const StringC &name,const StringC &desc,bool nCanRead = true,bool nCanWrite = true,
			 StringC ndefaultValue = StringC(),IntT nMaxLength = 65000)
      : AttributeTypeC(*new AttributeTypeStringBodyC(name,desc,nCanRead,nCanWrite,ndefaultValue,nMaxLength))
    {}
    //: Constructor.
    
    AttributeTypeStringC(const AttributeTypeC &base)
      : AttributeTypeC(base)
    {
      if(dynamic_cast<AttributeTypeStringBodyC *>(&AttributeTypeC::Body()) == 0)
	Invalidate();
    }
    //: Construct from a base handle
    // Creates an invalid handle if object is not of the correct type.
    
  protected:
    AttributeTypeStringC(AttributeTypeStringBodyC &bod)
      : AttributeTypeC(bod)
    {}
    //: Body constructor.
    
    AttributeTypeStringBodyC &Body()
    { return static_cast<AttributeTypeStringBodyC &> (AttributeTypeC::Body()); }
    //: Access body.
    
    const AttributeTypeStringBodyC &Body() const
    { return static_cast<const AttributeTypeStringBodyC &> (AttributeTypeC::Body()); }
    //: Access body.
    
  public:
    StringC Default() const
    { return Body().Default(); }
    //: Default value.
    
    IntT MaxLength() const
    { return Body().MaxLength(); }
    //: Get maximum length for the string.
    
  };

  //:-----------------------------------------------------------------------------------
  
  //! userlevel=Develop
  //: Boolean attribute type.
  
  class AttributeTypeEnumBodyC
    : public AttributeTypeBodyC
  {
  public:
    AttributeTypeEnumBodyC(const StringC &name,const StringC &desc,bool nCanRead = true,bool nCanWrite = true,
			   const DListC<StringC> &values = DListC<StringC>(),const StringC &ndefaultValue = StringC());
    //: Constructor
    
    virtual AttributeValueTypeT ValueType() const;
    //: Get hint about type of value attribute has.

    StringC Default() const
    { return defaultValue; }
    //: Access defaultValue value
    
    const DListC<StringC> &Values() const
    { return values; }
    // Possible values for enum.
    
    virtual bool SetToDefault(AttributeCtrlC &ctrl) const;
    //: Set control to default value.
    
  protected:
    StringC defaultValue;
    DListC<StringC> values; // Possible values for enum.
  };
  
  //! userlevel=Normal
  //: Boolean attribute type.
  
  class AttributeTypeEnumC
    : public AttributeTypeC
  {
  public:
    AttributeTypeEnumC()
    {}
    //: DefaultValue constructor.
    // Creates an invalid handle.
    
    AttributeTypeEnumC(const StringC &name,const StringC &desc,bool nCanRead = true,bool nCanWrite = true,
		       const DListC<StringC> &nvalues = DListC<StringC>(),const StringC &ndefaultValue = StringC())
      : AttributeTypeC(*new AttributeTypeEnumBodyC(name,desc,nCanRead,nCanWrite,nvalues,ndefaultValue))
    {}
    //: Constructor.

    AttributeTypeEnumC(const AttributeTypeC &base)
      : AttributeTypeC(base)
    {
      if(dynamic_cast<AttributeTypeEnumBodyC *>(&AttributeTypeC::Body()) == 0)
	Invalidate();
    }
    //: Construct from a base handle
    // Creates an invalid handle if object is not of the correct type.
    
  protected:
    AttributeTypeEnumC(AttributeTypeEnumBodyC &bod)
      : AttributeTypeC(bod)
    {}
    //: Body constructor.
    
    AttributeTypeEnumBodyC &Body()
    { return static_cast<AttributeTypeEnumBodyC &> (AttributeTypeC::Body()); }
    //: Access body.
    
    const AttributeTypeEnumBodyC &Body() const
    { return static_cast<const AttributeTypeEnumBodyC &> (AttributeTypeC::Body()); }
    //: Access body.
    
  public:
    StringC Default() const
    { return Body().Default(); }
    //: Default value.
    
    const DListC<StringC> &Values() const
    { return Body().Values(); }
    // Possible values for enum.
    
  };

  //:-----------------------------------------------------------------------------------
  
  //! userlevel=Develop
  //: Miscean attribute type.
  
  class AttributeTypeMiscBodyC
    : public AttributeTypeBodyC
  {
  public:
    AttributeTypeMiscBodyC(const StringC &name,const StringC &desc,const AttributeValueTypeT &valType,bool nCanRead = true,bool nCanWrite = true);
    //: Constructor
    
    virtual AttributeValueTypeT ValueType() const;
    //: Get hint about type of value attribute has.
    
    virtual bool SetToDefault(AttributeCtrlC &ctrl) const;
    //: Set control to default value.
    
  protected:
    AttributeValueTypeT valType;
  };
  
  //! userlevel=Normal
  //: Miscean attribute type.
  
  class AttributeTypeMiscC
    : public AttributeTypeC
  {
  public:
    AttributeTypeMiscC()
    {}
    //: DefaultValue constructor.
    // Creates an invalid handle.
    
    AttributeTypeMiscC(const StringC &name,const StringC &desc,const AttributeValueTypeT &valType,bool nCanRead = true,bool nCanWrite = true)
      : AttributeTypeC(*new AttributeTypeMiscBodyC(name,desc,valType,nCanRead,nCanWrite))
    {}
    //: Constructor.
    
    AttributeTypeMiscC(const AttributeTypeC &base)
      : AttributeTypeC(base)
    {
      if(dynamic_cast<AttributeTypeMiscBodyC *>(&AttributeTypeC::Body()) == 0)
	Invalidate();
    }
    //: Construct from a base handle
    // Creates an invalid handle if object is not of the correct type.
    
  protected:
    AttributeTypeMiscC(AttributeTypeMiscBodyC &bod)
      : AttributeTypeC(bod)
    {}
    //: Body constructor.
    
    AttributeTypeMiscBodyC &Body()
    { return static_cast<AttributeTypeMiscBodyC &> (AttributeTypeC::Body()); }
    //: Access body.
    
    const AttributeTypeMiscBodyC &Body() const
    { return static_cast<const AttributeTypeMiscBodyC &> (AttributeTypeC::Body()); }
    //: Access body.
    
  public:
  };

}


#endif
