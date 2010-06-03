// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDF_DFSYSTEM_HEADER
#define RAVLDF_DFSYSTEM_HEADER 1
//! rcsid="$Id: DFSystem.hh 2941 2003-05-25 17:01:40Z craftit $"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"
//! file="Ravl/Applications/VisualDataFlow/DFSystem.hh"

#include "Ravl/DF/DFObject.hh"
#include "Ravl/String.hh"
#include "Ravl/DList.hh"
#include "Ravl/Threads/Signal2.hh"
#include "Ravl/XMLStream.hh"
#include "Ravl/DF/FactorySet.hh"

namespace RavlDFN {
  
  extern void InitDFSystemIO();
  //: Function to force linking of system IO.
  
  enum DFObjectUpdateT { DFOU_ADDED,DFOU_DELETED,DFOU_CHANGED };
  
  //! userlevel=Develop
  //: System of DFObjects.
  
  class DFSystemBodyC
    : public RCBodyC
  {
  public:
    DFSystemBodyC(const StringC &nname);
    //: Constructor.
    
    DFSystemBodyC(istream &is);
    //: Read from istream.
    
    DFSystemBodyC(BinIStreamC &is);
    //: Read from istream.
    
    DFSystemBodyC(XMLIStreamC &is);
    //: Read from istream.
    
    bool Save(ostream &strm) const;
    //: Save ostream.
    
    bool Save(BinOStreamC &strm) const;
    //: Save ostream.
    
    bool Save(XMLOStreamC &strm) const;
    //: Save ostream.
    
    DListC<DFObjectC> Objects()
    { return objects; }
    //: Access list of objects in the system.
    
    const StringC &Name() const
    { return name; }
    //: System name.
    
    bool AddObject(DFObjectC &obj);
    //: Add an object to the system.
    
    bool DelObject(DFObjectC &obj);
    //: Remove an object from the system.
    // Returns true if object was in the system.
    
    DFObjectC CreateIPort(const StringC &name = StringC(""));
    //: Create an input port.
    
    DFObjectC CreateOPort(const StringC &name = StringC(""));
    //: Create an output port.
    
    DFObjectC CreateIPlug(const StringC &name = StringC(""));
    //: Create an input port.
    
    DFObjectC CreateOPlug(const StringC &name = StringC(""));
    //: Create an output port.
    
    DFObjectC LoadObject(const StringC &fn);
    //: Load object from file and add it the system.
    
    Signal2C<DFObjectUpdateT,DFObjectC> &SigChange()
    { return sigChange; }
    //: Signal change to an object.
    
    bool Factory(const FactorySetC &nfactory)
    { factory = nfactory; return true;}
    //: Set object factory.
    
    FactorySetC &Factory()
    { return factory; }
    //: Access factory.
    
  protected:
    StringC name;
    DListC<DFObjectC> objects; // Objects in the system.
    Signal2C<DFObjectUpdateT,DFObjectC> sigChange; // Signal change in object.
    FactorySetC factory; // Needed for loading systems.
  };
  
  //! userlevel=Normal
  //: System of DFObjects.
  
  class DFSystemC
    : public RCHandleC<DFSystemBodyC>
  {
  public:
    DFSystemC()
    {}
    //: Default constructor.
    
    DFSystemC(const StringC &nname)
      : RCHandleC<DFSystemBodyC>(* new DFSystemBodyC(nname))
    {}
    //: Construct a new system named 'nname'
    
    DFSystemC(istream &strm)
      : RCHandleC<DFSystemBodyC>(* new DFSystemBodyC(strm))
    {} 
    //: Construct from istream.
    
    DFSystemC(BinIStreamC &strm)
      : RCHandleC<DFSystemBodyC>(* new DFSystemBodyC(strm))
    {} 
    //: Construct from a BinIStreamC
    
  protected:
    DFSystemBodyC &Body()
    { return RCHandleC<DFSystemBodyC>::Body(); }
    //: Access body.
    
    const DFSystemBodyC &Body() const
    { return RCHandleC<DFSystemBodyC>::Body(); }
    //: Access body.
  public:
    bool Save(ostream &strm) const
    { return Body().Save(strm); }
    //: Save ostream.
    
    bool Save(BinOStreamC &strm) const
    { return Body().Save(strm); }
    //: Save ostream.
    
    DListC<DFObjectC> Objects()
    { return Body().Objects(); }
    //: Access list of objects in the system.
    
    const StringC &Name() const
    { return Body().Name(); }
    //: System name.
    
    Signal2C<DFObjectUpdateT,DFObjectC> &SigChange()
    { return Body().SigChange(); }
    //: Signal change to an object.

    DFObjectC CreateIPort(const StringC &name = StringC(""))
    { return Body().CreateIPort(name); }
    //: Create an input port.
    
    DFObjectC CreateOPort(const StringC &name = StringC(""))
    { return Body().CreateOPort(name); }
    //: Create an output port.

    DFObjectC CreateIPlug(const StringC &name = StringC(""))
    { return Body().CreateIPlug(name); }
    //: Create an input port.
    
    DFObjectC CreateOPlug(const StringC &name = StringC(""))
    { return Body().CreateIPlug(name); }
    //: Create an output port.
    
    DFObjectC LoadObject(const StringC &fn)
    { return Body().LoadObject(fn); }
    //: Load object from file and add it the system.
    
    bool AddObject(DFObjectC &obj)
    { return Body().AddObject(obj); }
    //: Add an object to the system.
    
    bool DelObject(DFObjectC &obj)
    { return Body().DelObject(obj); }
    //: Remove an object from the system.
    // Returns true if object was in the system.
    
    bool Factory(const FactorySetC &nfactory)
    { return Body().Factory(nfactory); }
    //: Set object factory.
    
    FactorySetC &Factory()
    { return Body().Factory(); }
    //: Access factory.

  };
  
  ostream &operator<<(ostream &strm,const DFSystemC &dfa);
  //: Write to an ostream.
  
  istream &operator>>(istream &strm,DFSystemC &dfa);
  //: Read from an istream.
  
  BinOStreamC &operator<<(BinOStreamC &strm,const DFSystemC &dfa);
  //: Write to an ostream.
  
  BinIStreamC &operator>>(BinIStreamC &strm,DFSystemC &dfa);
  //: Read from an istream.

}

#endif
