// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ATTRIBUTECTRLINTERNAL_HEADER
#define RAVL_ATTRIBUTECTRLINTERNAL_HEADER 1
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlIO
//! docentry="Ravl.Core.Data_Processing.Attributes"
//! file="Ravl/Core/IO/AttributeCtrlInternal.hh"

#include "Ravl/DP/AttributeType.hh"
#include "Ravl/Hash.hh"
#include "Ravl/DLIter.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Internal attribute ctrl structure.
  
  class AttributeCtrlInternalC {
  public:
    AttributeCtrlInternalC();
    //: Default constructor.
    
    bool RegisterAttribute(const AttributeTypeC &attr) {
      attribTypes[attr.Name()] = attr;
      attribTypeList.InsLast(attr);
      return true;
    }
    //: Register an attribute.
    
    bool GetAttrList(DListC<StringC> &list) const {
      for(DLIterC<AttributeTypeC> it(attribTypeList);it;it++)
	list.InsLast(it->Name());
      return true;
    }
    //: Get list of attributes.
    
    bool GetAttrTypes(DListC<AttributeTypeC> &list) const {
      for(DLIterC<AttributeTypeC> it(attribTypeList);it;it++)
	list.InsLast(*it);
      return true;
    }
    //: Get list of attribute info.
    
    AttributeTypeC GetAttrType(const StringC &attrName) const {
      AttributeTypeC ret;
      attribTypes.Lookup(attrName,ret);
      return ret;
    }
    
    void IssueChangedSignal(const StringC &attrName);
    //: Issue attribute changed signal.
    
    IntT RegisterChangedSignal(const StringC &attrName,const TriggerC &trig);
    //: Register a changed signal.
    
    bool RemoveChangedSignal(IntT id);
    //: Remove changed signal.
    
    DListC<AttributeTypeC> &Attributes()
    { return attribTypeList; }
    //: Get list of attributes.
    
    bool SetSchema(const DListC<AttributeTypeC> &nattribTypeList) ;
    //: Setup new schema.
    
    bool AttributeExists(const StringC &name) const
    { return attribTypes.IsElm(name); }
    //: Test if attribute exists.
    
  protected:
    //: Get type of a particular attribute. 
    
    HashC<StringC,AttributeTypeC> attribTypes;
    DListC<AttributeTypeC> attribTypeList;

    // Changed trigger.
    
    HashC<IntT,DLIterC<TriggerC> > trigId2trig;
    HashC<StringC,DListC<TriggerC> > name2trigList;
    IntT trigIdAlloc;
  };

}

#endif
