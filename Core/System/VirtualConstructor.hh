// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_VIRTUALCONSTRUCTOR_HEADER
#define RAVL_VIRTUALCONSTRUCTOR_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! docentry="Ravl.Core.Misc"
//! lib=RavlCore

#include "Ravl/RCHandleV.hh"
#include "Ravl/Hash.hh"
#include "Ravl/TypeName.hh"

#if RAVL_HAVE_ANSICPPHEADERS
#include <typeinfo>
#else
#include <typeinfo.h>
#endif

namespace RavlN {
  class VirtualConstructorC;
  
  //! userlevel=Develop
  //: Virtual constructor base class.
  
  class VirtualConstructorBodyC
    : public RCBodyVC
  {
  public:
    VirtualConstructorBodyC(const type_info &,const char *typesname);
    //: Default constructor.
    
    VirtualConstructorBodyC(istream &in);
    //: Construct from an istream.
    // Dummy method.

    VirtualConstructorBodyC(BinIStreamC &in);
    //: Construct from an istream.
    // Dummy method
    
    virtual RCBodyVC *Load(istream &in) const;
    //: Load an object of this type from an istream
    
    virtual RCBodyVC *Load(BinIStreamC &in) const;
    //: Load an object of this type from a BinIStreamC    
  };

  //! userlevel=Normal
  //: Virtual constructor base class.
  
  class VirtualConstructorC
    : public RCHandleC<VirtualConstructorBodyC>
  {
  public:
    VirtualConstructorC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    RCBodyVC *Load(istream &in) const
    { return Body().Load(in); }
    //: Load an object of this type from an istream
    
    RCBodyVC *Load(BinIStreamC &in) const
    { return Body().Load(in); }
    //: Load an object of this type from a BinIStreamC

  protected:
    VirtualConstructorC(VirtualConstructorBodyC &bod)
      : RCHandleC<VirtualConstructorBodyC>(bod)
    {}
    //: Body constructor.
    
    friend class VirtualConstructorBodyC;
  };
  
  //! userlevel=Develop
  //: Virtual constructor instance.
  
  template<class DataT>
  class VirtualConstructorInstBodyC
    : public VirtualConstructorBodyC
  {
  public:
    VirtualConstructorInstBodyC(const char *typesname)
      : VirtualConstructorBodyC(typeid(DataT),typesname)
    {}
    //: Default constructor.
    
    virtual RCBodyVC *Load(istream &in) const
    { return new DataT(in); }
    //: Load an object of this type from an istream.
    
    virtual RCBodyVC *Load(BinIStreamC &in) const
    { return new DataT(in); }
    //: Load an object of this type from a BinIStreamC using a virtual constructor.
    
  };
  
  //! userlevel=Normal
  //: Virtual constructor instance.

  template<class DataT>
  class VirtualConstructorInstC 
    : public VirtualConstructorC
  {
  public:
    VirtualConstructorInstC(const char *typesname)
      : VirtualConstructorC(*new VirtualConstructorInstBodyC<DataT>(typesname))
    {}
    //: Constructor.
  };
  
  RCBodyVC *VCLoad(istream &s);
  //: Load object from a stream via a virtual constructor
  
  RCBodyVC *VCLoad(BinIStreamC &s);
  //: Load object from a binary stream via a virtual constructor
  
#define RAVL_INITVIRTUALCONSTRUCTOR(bodyname) \
 static VirtualConstructorInstC<bodyname> vc_function(# bodyname );

  // Just initalise the virtual constructor.

#define RAVL_VIRTUALCONSTRUCTOR_HANDLE(bodyname,handlename,basename) \
 handlename::handlename(istream &strm) \
  : basename(RAVL_VIRTUALCONSTRUCTOR(strm,bodyname)) \
 {} \
 handlename::handlename(BinIStreamC &strm) \
  : basename(RAVL_VIRTUALCONSTRUCTOR(strm,bodyname)) \
 {}

  // Sort out the constructors for the handle.
  
#define RAVL_INITVIRTUALCONSTRUCTOR_FULL(bodyname,handlename,basename) \
 RAVL_INITVIRTUALCONSTRUCTOR(bodyname) \
 RAVL_VIRTUALCONSTRUCTOR_HANDLE(bodyname,handlename,basename)

  // Initalise the virtual constructor and the handle

  
}

#endif
