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
//! lib=RavlCore

#include "Ravl/RCHandleV.hh"
#include "Ravl/Hash.hh"

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
    
    virtual RCBodyC *Load(istream &in) const;
    //: Load an object of this type from an istream
    
    virtual RCBodyC *Load(BinIStreamC &in) const;
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
    
    RCBodyC *Load(istream &in) const
    { return Body().Load(in); }
    //: Load an object of this type from an istream
    
    RCBodyC *Load(BinIStreamC &in) const
    { return Body().Load(in); }
    //: Load an object of this type from a BinIStreamC
    
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
    
    virtual RCBodyC *Load(istream &in) const
    { return *new DataT(in); }
    //: Load an object of this type from an istream

    virtual RCBodyC *Load(BinIStreamC &in) const
    { return *new DataT(in); }
    //: Load an object of this type from a BinIStreamC
    
  };
  
  //! userlevel=Normal
  //: Virtual constructor instance.

  template<class DataT>
  class VirtualConstructorInstC 
    : public VirtualConstructorC
  {
  public:
    VirtualConstructorInstC(const char *typesname)
      : VirtualConstructorC(*new VirtualConstructorInstC<DataT>(typesname))
    {}
    //: Constructor.
  };
  
  RCBodyC *VCLoad(istream &s);
  //: Load object from a stream.
  
  RCBodyC *VCLoad(BinIStreamC &s);
  //: Load object from a binary stream.
  
}

#endif
