// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ATTRIBUTECTRL_HEADER
#define RAVL_ATTRIBUTECTRL_HEADER 1
//! author="Charles Galambos"
//! date="23/8/2003"
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/AttributeCtrl.hh"

#include "Ravl/DP/Entity.hh"
#include "Ravl/String.hh"

namespace RavlN {
  class AttributeTypeC;
  class AttributeCtrlC;
  class TriggerC;
  template<class DataT> class DListC;
  class AttributeCtrlInternalC;
  
  //! userlevel=Develop
  //: Interface for reading and writting attribute values.
  
  class AttributeCtrlBodyC 
    : virtual public DPEntityBodyC 
  {
  public:
    AttributeCtrlBodyC();
    //: Default constructor.
    
    AttributeCtrlBodyC(istream &in);
    //: Stream constructor.
    
    AttributeCtrlBodyC(const AttributeCtrlBodyC &bod);
    //: Copy constructor.
    
    virtual ~AttributeCtrlBodyC();
    //: Destructor.
    
    AttributeCtrlBodyC &operator=(const AttributeCtrlBodyC &);
    //: Assignment operator.
    
    virtual AttributeCtrlC ParentCtrl() const;
    //: Get Parent attribute control.

    StringC GetAttr(const StringC &attrName);
    //: Get named attribute.
    
    virtual bool GetAttr(const StringC &attrName,StringC &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const StringC &attrValue);
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,IntT &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const IntT &attrValue);
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,RealT &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const RealT &attrValue);
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,bool &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const bool &attrValue);
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttrList(DListC<StringC> &list) const;
    //: Get list of attributes available.
    // This method will ADD all available attribute names to 'list'.
    
    virtual bool GetAttrTypes(DListC<AttributeTypeC> &list) const;
    //: Get a list of available attribute types.
    
    virtual AttributeTypeC GetAttrType(const StringC &attrName) const;
    //: Get type of a particular attribute. 
    // Returns an invalid handle if attribute is unknown.
    
    virtual IntT RegisterChangedSignal(const TriggerC &trig);
    //: Register a value changed signal.
    // Note: This method may not be implemented for all AttributeCtrl's.
    // Returns an id for the trigger, or -1 if operation fails.
    
    virtual bool RemoveChangedSignal(IntT id);
    //: Remove a changed signal.
    // Note: This method may not be implemented for all AttributeCtrl's.

    virtual bool RegisterAttribute(const AttributeTypeC &attr);
    //: Register a new attribute type.

  protected:
    virtual bool SignalChange(const StringC &attrName);
    //: Signal that an attribute has changed.
    
  private:
    AttributeCtrlInternalC *attrInfo;
  };
  
  //! userlevel=Normal
  //: Interface for reading and writting attribute values.
  
  class AttributeCtrlC 
    : virtual public DPEntityC 
  {
  public:   
    AttributeCtrlC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    AttributeCtrlC(istream &strm)
      : DPEntityC(strm)
    {}
    //: Stream constructor.
    
  protected:
    AttributeCtrlC(AttributeCtrlBodyC &bod)
      : DPEntityC(bod)
    {}
    //: Body constructor.
    
    inline AttributeCtrlBodyC &Body() 
    { return dynamic_cast<AttributeCtrlBodyC &> (DPEntityC::Body()); }
    //: Access body.
    
    inline const AttributeCtrlBodyC &Body() const
    { return dynamic_cast<const AttributeCtrlBodyC &> (DPEntityC::Body()); }
    //: Access body.
    
  public:
    StringC GetAttr(const StringC &attrName);
    //: Get a attribute.
    // Return the value of an attribute or an empty string if its unkown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    inline bool GetAttr(const StringC &attrName,StringC &attrValue)
    { return Body().GetAttr(attrName,attrValue); }    
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    inline bool SetAttr(const StringC &attrName,const StringC &attrValue)
    { return Body().SetAttr(attrName,attrValue); }
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.

    inline bool GetAttr(const StringC &attrName,IntT &attrValue)
    { return Body().GetAttr(attrName,attrValue); }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    inline bool SetAttr(const StringC &attrName,const IntT &attrValue)
    { return Body().SetAttr(attrName,attrValue); }
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    inline bool GetAttr(const StringC &attrName,RealT &attrValue)
    { return Body().GetAttr(attrName,attrValue); }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    inline bool SetAttr(const StringC &attrName,const RealT &attrValue)
    { return Body().SetAttr(attrName,attrValue); }
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    inline bool GetAttr(const StringC &attrName,bool &attrValue)
    { return Body().GetAttr(attrName,attrValue); }
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    inline bool SetAttr(const StringC &attrName,const bool &attrValue)
    { return Body().SetAttr(attrName,attrValue); }
    //: Set a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    inline bool GetAttrList(DListC<StringC> &list) const
    { return Body().GetAttrList(list); }
    //: Get list of attributes available.
    
    inline bool GetAttrTypes(DListC<AttributeTypeC> &list) const
    { return Body().GetAttrTypes(list); }
    //: Get a list of available attribute types.
    
    AttributeTypeC GetAttrType(const StringC &attrName) const;
    //: Get type of a particular attribute. 
    // Returns an invalid handle if attribute is unknown.
    
    IntT RegisterChangedSignal(const TriggerC &trig)
    { return Body().RegisterChangedSignal(trig); }
    //: Register a value changed signal.
    // Note: This method may not be implemented for all AttributeCtrl's.
    // Returns an id for the trigger, or -1 if operation fails.
    
    bool RemoveChangedSignal(IntT id)
    { return Body().RemoveChangedSignal(id); }
    //: Remove a changed signal.
    // Note: This method may not be implemented for all AttributeCtrl's.
    
    bool RegisterAttribute(const AttributeTypeC &attr) 
    { return Body().RegisterAttribute(attr); }
    //: Register a new attribute type.
    // Returns true if attribute of the same name already exists.
    
    friend class AttributeCtrlBodyC;
  };
}


#endif
