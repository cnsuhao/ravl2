// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDPTYPEINFO_HEADER
#define RAVLDPTYPEINFO_HEADER 1
////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlIO
//! docentry="Ravl.Core.IO.Type Converter"
//! file="Ravl/Core/IO/TypeInfo.hh"
//! author="Charles Galambos"
//! date="19/08/98"
//! userlevel=Default

#include "Ravl/DP/Entity.hh"
//#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/DP/Pipes.hh"

#include "Ravl/RCWrap.hh"
#include "Ravl/String.hh"
#include "Ravl/Hash.hh"

namespace RavlN {

  template <class DataT> class DListC;
  class DPTypeInfoC;
  
  ///////////////////////////////
  //! userlevel=Develop
  //: Type information body.
  
  class DPTypeInfoBodyC : public DPEntityBodyC {
  public:
    DPTypeInfoBodyC(const type_info &typeInfo);
    //: Default constructor.
    
    StringC Name() const { return StringC(typeInfo.name()); }
    //: Get name of type.
    
    const type_info & TypeInfo() const { return typeInfo; }
    //: Access type information.
    
    virtual RCWrapAbstractC Create() const;
    //: Create instance of the type with the default constructor.
    
    virtual RCWrapAbstractC Create(istream &strm) const;
    //: Create instance of the type from stream constructor.
    
    virtual RCWrapAbstractC Load(const StringC &fn,const StringC &fmtName = "",bool verb = false) const;
    //: Attempt to load object from a file.
    
    virtual bool Put(DPOPortBaseC &port,const RCWrapAbstractC &obj) throw(ExceptionErrorCastC);
    //: Put generic object to port.
    // Will throw ExceptionErrorCastC if types aren't correct, or in debug mode
    // an assert may fail.
  
    virtual RCWrapAbstractC Get(DPIPortBaseC &port) throw(ExceptionErrorCastC);
    //: Get generic object from port.
    // Will throw ExceptionErrorCastC if types aren't correct, or in debug mode
    // an assert may fail.
    
    virtual DPIPipeBaseC CreateIPipe(const DPEntityC &hold = DPEntityC(true)) const;
    //: Create an input pipe for this type.
    
    virtual DPOPipeBaseC CreateOPipe(const DPEntityC &hold = DPEntityC(true)) const;
    //: Create an output pipe for this type.
    
    static HashC<const char *,DPTypeInfoC> &Types();
    //: Access type list.
    
    UIntT Hash() const { return Name().Hash(); }
    //: Calculate hash value.
  protected:
    const type_info &typeInfo;
  };

  
  ///////////////////////////////
  //! userlevel=Normal
  //: Type information handle.

  class DPTypeInfoC : public DPEntityC {
  public:
    DPTypeInfoC()
      : DPEntityC(true)
      {}
    //: Default constructor.
  
    DPTypeInfoC(const type_info &);
    //: Lookup type. 
    // Creates an invalid handle if failed.
    
    DPTypeInfoC(DPTypeInfoBodyC &bod)
      : DPEntityC(bod)
      {}
    //: Body constructor.
    
    inline DPTypeInfoBodyC &Body() 
      { return static_cast<DPTypeInfoBodyC & > (DPEntityC::Body()); }
    //: Access body.
    
    inline const DPTypeInfoBodyC &Body() const
      { return static_cast<const DPTypeInfoBodyC & > (DPEntityC::Body()); }
    //: Access body.
    
    inline StringC Name() const 
      { return Body().Name(); }
    //: Get name of type.
    
    inline const type_info & TypeInfo() const 
      { return Body().TypeInfo(); }
    //: Access type information.
    
    inline RCWrapAbstractC Create() const
      { return Body().Create(); }
    //: Create instance of the type with the default constructor.
    
    inline RCWrapAbstractC Create(istream &in) const
      { return Body().Create(in); }
    //: Create instance of the type with the default constructor.
    
    inline bool Put(DPOPortBaseC &port,const RCWrapAbstractC &obj) throw(ExceptionErrorCastC)
      { return Body().Put(port,obj); }
    //: Put generic object to port.
    // Will throw ExceptionErrorCastC if types aren't correct, or in debug mode
    // an assert may fail.
    
    inline RCWrapAbstractC Get(DPIPortBaseC &port) throw(ExceptionErrorCastC)
      { return Body().Get(port); }
    //: Get generic object from port.
    // Will throw ExceptionErrorCastC if types aren't correct, or in debug mode
    // an assert may fail.
    
    inline DPIPipeBaseC CreateIPipe(const DPEntityC &hold = DPEntityC(true)) const
      { return Body().CreateIPipe(hold); }
    //: Create an input pipe for this type.
    
    inline DPOPipeBaseC CreateOPipe(const DPEntityC &hold = DPEntityC(true)) const
      { return Body().CreateOPipe(hold); }
    //: Create an output pipe for this type.
    
    inline UIntT Hash() const 
      { return Body().Hash(); }
    //: Calculate hash value.  
  };
  
  ///////////////////////////////
  //! userlevel=Normal
  //: Type information instance body.
  
  template<class DataT>
  class DPTypeInfoInstBodyC : public DPTypeInfoBodyC {
  public:  
    DPTypeInfoInstBodyC();
    //: Default constructor.
    
    virtual RCWrapAbstractC Create() const 
      { return RCWrapC<DataT>(); }
    //: Create instance of the type with the default constructor.
    
    virtual RCWrapAbstractC Create(istream &strm) const
    { return RCWrapC<DataT>(strm); }
    //: Create instance of the type from stream constructor.
    
    virtual RCWrapAbstractC Load(const StringC &fn,const StringC &fmtName = "",bool verb = false) const {
#if 0
      DPIPortC<DataT> in(StdIO::BaseLoad(fn,fmtName,typeid(DataT),verb));
      if(!in.IsValid())
	return RCWrapAbstractC(); // Failed.
      return RCWrapC<DataT>(in.Get());
#else
      return RCWrapAbstractC(); // Failed.
#endif
    }
    //: Attempt to load object from a file.
    
    virtual bool Put(DPOPortBaseC &port,const RCWrapAbstractC &obj) throw(ExceptionErrorCastC) { 
      if(!obj.IsValid() || !port.IsValid()) {
	cerr << "DPTypeInfoInstBodyC::Put(), ERROR: Invalid arguments. \n";
	assert(0);
	return false;
      }
      DPOPortC<DataT> oport(port);
      if(!oport.IsValid()) {
	assert(0);
	throw ExceptionErrorCastC("DPTypeInfoInstBodyC::Put(), 1",
			 typeid(port.OutputType()),
			 typeid(DataT));
      }
      RCWrapC<DataT> wo(obj,false);
      if(!wo.IsValid()) {
	assert(0);
	throw ExceptionErrorCastC("DPTypeInfoInstBodyC::Put(), 2",
			 obj.DataType(),
			 typeid(DataT));
      }
      return oport.Put((DataT &) wo);
    }
    //: Put generic object to port.
    // Will throw ExceptionErrorCastC if types aren't correct, or in debug mode
    // an assert may fail.
    
    virtual RCWrapAbstractC Get(DPIPortBaseC &port) throw(ExceptionErrorCastC) {
      if(!port.IsValid()) {
	cerr << "DPTypeInfoInstBodyC::Get(), ERROR: Invalid arguments. \n";
	assert(0);
	return RCWrapAbstractC();
      }
      DPIPortC<DataT> iport(port);
      if(!iport.IsValid()) {
	assert(0);
	throw ExceptionErrorCastC("DPTypeInfoInstBodyC::Get(), ",
			 typeid(port.InputType()),
			 typeid(DataT));
      }
      return RCWrapC<DataT>(iport.Get());
    }
    //: Get generic object from port.
    // Will throw ExceptionErrorCastC if types aren't correct, or in debug mode
    // an assert may fail.
    
    virtual DPIPipeBaseC CreateIPipe(const DPEntityC &hold = DPEntityC(true)) const
      { return DPIPipeC<DataT>(hold); }
    //: Create an input pipe
    
    virtual DPOPipeBaseC CreateOPipe(const DPEntityC &hold = DPEntityC(true)) const
      { return DPOPipeC<DataT>(hold); }
    //: Create an output pipe
    
  };
  

  ///////////////////////////////
  //! userlevel=Normal
  //: Type information instance body.
  
  template<class DataT>
  class DPTypeInfoInstC : public DPTypeInfoC {
  protected:
    DPTypeInfoInstC(DPTypeInfoInstBodyC<DataT> &bod)
      : DPTypeInfoC(bod)
      {}
    //: Body constructor.
    
  public:
    DPTypeInfoInstC()
      {
	if(!DPTypeInfoBodyC::Types().IsElm(typeid(DataT).name()))
	  (*this) = DPTypeInfoInstC(*new DPTypeInfoInstBodyC<DataT>());
      }
    //: Default constructor.
  };
  
  //////////////////////////////////////// 
}
#include "Ravl/DP/Converter.hh"

namespace RavlN {  
  template<class DataT>
  DPTypeInfoInstBodyC<DataT>::DPTypeInfoInstBodyC()
    : DPTypeInfoBodyC(typeid(DataT))
  {
    //  static DPConverterFuncC<DataT,RCWrapAbstractC,DPTypeInfoInstBodyC<DataT>::Convert2Wrapper> ConvToWrapper(1);
    // Register wrapper converter.
  }
  
  inline
  const DPTypeInfoC &TypeInfo(const type_info &ti)
  { return DPTypeInfoBodyC::Types()[ti.name()]; }
  //: Access extra information about a type.
  
  inline
  const DPTypeInfoC &TypeInfo(const char *tn)
  { return DPTypeInfoBodyC::Types()[tn]; }
  //: Access extra information about a type.
}
#endif
