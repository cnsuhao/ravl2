// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDF_DFSYSTEM_HEADER
#define RAVLDF_DFSYSTEM_HEADER 1
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"

#include "Ravl/DF/DFObject.hh"
#include "Ravl/String.hh"
#include "Ravl/DList.hh"
#include "Ravl/Threads/Signal2.hh"

namespace RavlDFN {
  
  enum DFObjectUpdateT { DFOU_ADDED,DFOU_DELETED,DFOU_CHANGED };
  
  //! userlevel=Develop
  //: System of DFObjects.
  
  class DFSystemBodyC
    : public RCBodyC
  {
  public:
    DFSystemBodyC(const StringC &nname);
    //: Constructor.
    
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
    
    DFObjectC CreateLink(const DFObjectC &obj1,const DFObjectC &obj2,bool autoConvert = false);
    //: Attempt to link two objects.
    // Will return an invalid handle if operation fails.
    
    DFObjectC LoadObject(const StringC &fn);
    //: Load object from file and add it the system.
    
    Signal2C<DFObjectUpdateT,DFObjectC> &SigChange()
    { return sigChange; }
    //: Signal change to an object.
    
  protected:
    StringC name;
    DListC<DFObjectC> objects; // Objects in the system.
    Signal2C<DFObjectUpdateT,DFObjectC> sigChange; // Signal change in object.
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
    
  protected:
    DFSystemBodyC &Body()
    { return RCHandleC<DFSystemBodyC>::Body(); }
    //: Access body.
    
    const DFSystemBodyC &Body() const
    { return RCHandleC<DFSystemBodyC>::Body(); }
    //: Access body.
  public:
    
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
    
    DFObjectC CreateLink(const DFObjectC &obj1,const DFObjectC &obj2,bool autoConvert = false)
    { return Body().CreateLink(obj1,obj2,autoConvert); }
    //: Attempt to link two objects.
    // Will return an invalid handle if operation fails.
    
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
  };
}

#endif
