// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDF_DFFACTORY_HEADER
#define RAVLDF_DFFACTORY_HEADER 1
//! rcsid="$Id: Factory.hh 1533 2002-08-08 16:03:23Z craftit $"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"
//! file="Ravl/Applications/VisualDataFlow/Factory.hh"

#include "Ravl/Text/ConfigFile.hh"
#include "Ravl/DF/DFObject.hh"
#include "Ravl/GUI/Pixmap.hh"
#include "Ravl/Calls.hh"
#include "Ravl/Hash.hh"

namespace RavlDFN {
  using namespace RavlN;
  using namespace RavlGUIN;
  
  //! userlevel=Develop
  //: Factory base class.
  
  class FactoryBodyC 
    : public RCBodyVC
  {
  public:
    FactoryBodyC(const StringC &nName);
    //: Constructor.
    
    FactoryBodyC(const StringC &nName,const PixmapC &pm);
    //: Constructor.
    
    FactoryBodyC(const StringC &nName,const PixmapC &pm,const CallFunc0C<DFObjectC> &func);
    //: Constructor.
    
    FactoryBodyC(ConfigFileC &cfg);
    //: Constructor.
    
    bool Load(ConfigFileC &cfg);
    //: Load configuration from a file.
    
    const StringC &Name() const
    { return name; }
    //: Get name of object.
    
    PixmapC Icon() const;
    //: Get an icon for the object.
    
    virtual DFObjectC Create();
    //: Create a new object.
    
    CallFunc0C<DFObjectC> &CreateFunction()
    { return func; }
    //: Access create function.
    
    const DListC<StringC> Section() const
    { return section; }
    //: Section for factory.
    
    const DListC<StringC> Section(const StringC &section);
    //: Set section.
    // Expects a . seperated string.
    
  protected:
    HashC<StringC,StringC> nameMapping; // IO Name mappings.
    StringC name;
    PixmapC icon;
    CallFunc0C<DFObjectC> func;
    DListC<StringC> section;
  };
  
  //! userlevel=Normal
  //: Factory base class.

  class FactoryC
    : public RCHandleC<FactoryBodyC>
  {
  public:
    FactoryC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

    FactoryC(const StringC &name)
      : RCHandleC<FactoryBodyC>(*new FactoryBodyC(name))
    {}
    //: Create a no-op factory.
    
    FactoryC(const StringC &name,const PixmapC &pixmap)
      : RCHandleC<FactoryBodyC>(*new FactoryBodyC(name,pixmap))
    {}
    //: Create a no-op factory.
    
    FactoryC(const StringC &nName,const PixmapC &pm,const CallFunc0C<DFObjectC> &func)
      : RCHandleC<FactoryBodyC>(*new FactoryBodyC(nName,pm,func))
    {}
    //: Constructor.
    
    FactoryC(ConfigFileC &cfg)
      : RCHandleC<FactoryBodyC>(*new FactoryBodyC(cfg))
    {}
    //: Init from configuration.
    
  protected:
    FactoryC(FactoryBodyC &bod)
      : RCHandleC<FactoryBodyC>(bod)
    {}
    //: Body constructor.
    
    FactoryBodyC &Body()
    { return RCHandleC<FactoryBodyC>::Body(); }
    //: Access body.
    
    const FactoryBodyC &Body() const
    { return RCHandleC<FactoryBodyC>::Body(); }
    //: Access body.
    
  public:
    bool Load(ConfigFileC &cfg)
    { return Load(cfg); }
    //: Load configuration from a file.
    
    const StringC &Name() const
    { return Body().Name(); }
    //: Get name of object.
    
    PixmapC Icon() const
    { return Body().Icon(); }
    //: Get an icon for the object.
    
    DFObjectC Create()
    { return Body().Create(); }
    //: Create a new object.
    
    CallFunc0C<DFObjectC> &CreateFunction()
    { return Body().CreateFunction(); }
    //: Access create function.
    
    const DListC<StringC> Section() const
    { return Body().Section(); }
    //: Section for factory.
    
    const DListC<StringC> Section(const StringC &section)
    { return Body().Section(section); }
    //: Set section.
    // Expects a . seperated string.
    
    friend class FactoryBodyC;
  };
}


#endif
