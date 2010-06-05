// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDF_DFFACTORYSET_HEADER
#define RAVLDF_DFFACTORYSET_HEADER 1
//! rcsid="$Id: FactorySet.hh 1533 2002-08-08 16:03:23Z craftit $"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"
//! file="Ravl/Applications/VisualDataFlow/FactorySet.hh"

#include "Ravl/DF/Factory.hh"

namespace RavlDFN {

  //! userlevel=Develop
  //: Set of factories.
  
  class FactorySetBodyC
    : public RCBodyC
  {
  public:
    FactorySetBodyC()
    {}
    //: Default constructor.
    
    FactorySetBodyC(const StringC &fn);
    //: Load from a file.
    
    bool LoadDefault();
    //: Load default converters.
    
    bool Load(const StringC &fn);
    //: Load a factory descriptor file.
    
    bool LookupFactory(const StringC &tag,FactoryC &factory) const
    { return tag2factory.Lookup(tag,factory); }
    //: Lookup factory with given tag.
    // Returns true if the factory is found.
    
    bool Register(FactoryC &fac) { 
      tag2factory[fac.Name()] = fac; 
      return true;
    }
    //: Register new factory.
    
    DFObjectC Create(const StringC &tag);
    //: Create an object of type 'tag'
    // If the tag is not found an invalid handle is returned.
    
    DListC<FactoryC> List() const;
    //: Create a list of factories.
    
  protected:
    
    HashC<StringC,FactoryC> tag2factory;
  };

  //! userlevel=Normal
  //: Set of factories.
  
  class FactorySetC
    : public RCHandleC<FactorySetBodyC>
  {
  public:
    FactorySetC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    FactorySetC(const StringC &fn)
      : RCHandleC<FactorySetBodyC>(*new FactorySetBodyC(fn))
    {}
    //: Load from a file.
    
  protected:
    FactorySetC(FactorySetBodyC &bod)
      : RCHandleC<FactorySetBodyC>(bod)
    {}
    //: Body constructor.
    
    FactorySetBodyC &Body()
    { return RCHandleC<FactorySetBodyC>::Body(); }
    //: Access body.

    const FactorySetBodyC &Body() const
    { return RCHandleC<FactorySetBodyC>::Body(); }
    //: Access body.
    
  public:
    bool Load(const StringC &fn)
    { return Body().Load(fn); }
    //: Load a factory descriptor file.
    
    bool LookupFactory(const StringC &tag,FactoryC &factory) const
    { return Body().LookupFactory(tag,factory); }
    //: Lookup factory with given tag.
    // Returns true if the factory is found.
    
    DFObjectC Create(const StringC &tag)
    { return Body().Create(tag); }
    //: Create an object of type 'tag'
    // If the tag is not found an invalid handle is returned.
    
    DListC<FactoryC> List() const
    { return Body().List(); }
    //: Create a list of factories.
    
  };
    
}

#endif
