// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DPMETHODIO_HEADER
#define RAVL_DPMETHODIO_HEADER 1
//////////////////////////////////////////////////////////
//! docentry="Ravl.Core.Data Processing"
//! example=exDataProc.cc
//! lib=RavlIO
//! author="Charles Galambos"
//! date="04/07/1998"
//! example=exMethodIO.cc
//! rcsid="$Id$"
//! file="Ravl/Core/IO/MethodIO.hh"

#include "Ravl/DP/Port.hh"

namespace RavlN {
  ////////////////////////////////////////////
  //! userlevel=Develop
  //: Send objects to a class method.
  
  template<class DataT,class ObjT>
  class DPOMethodBodyC 
    : public DPOPortBodyC<DataT>
  {
  public:
    typedef bool (ObjT::*Func1T)(const DataT &dat);
    
    DPOMethodBodyC() 
      : func(0)
    {}
    //: Default constructor.
    
    DPOMethodBodyC(const ObjT &nobj,Func1T meth)
      : obj(nobj),
	func(meth)
    {}
    //: Construct from a filename.
    
    virtual bool Put(const DataT &dat) 
    { return (obj.*func)(dat); }
    //: Put data.
    
    virtual IntT PutArray(const SArray1dC<DataT> &data) {
      for(SArray1dIterC<DataT> it(data);it;it++)
	if(!(obj.*func)(*it))
	  return it.Index().V();
      return data.Size();
    }
    //: Get an array of data from stream.
    
    virtual bool IsPutReady() const 
    { return func != 0; }
    //: Is port ready for data ?
    
    virtual bool Save(ostream &sout) const 
    {  return false; } // Not implemented
    //: Save to ostream.
    
  private:
    ObjT obj;
    Func1T func;
  };
  
  /////////////////////////////////////
  //! userlevel=Develop
  //: Get objects from a class method.
  
  template<class DataT,class ObjT>
  class DPIMethodBodyC 
    : public DPIPortBodyC<DataT>
  {
  public:
    typedef DataT (ObjT::*Func1T)();
    
    DPIMethodBodyC() 
      : func(0)
    {}
    //: Default constructor.
    
    DPIMethodBodyC(const ObjT &nobj,Func1T meth)
      : obj(nobj),
	func(meth)
    {}
    //: Construct from a filename.
    
    virtual bool IsGetEOS() const 
    { return func == 0; }
    //: Is valid data ?
    
    virtual DataT Get()
    { return (obj.*func)(); }
    //: Get next piece of data.
    
    virtual IntT GetArray(SArray1dC<DataT> &data) {
      for(SArray1dIterC<DataT> it(data);it;it++)
	*it = (obj.*func)();
      return data.Size();
    }
    //: Get an array of data from stream.
    
    virtual bool Save(ostream &out) const 
    {  return false; }
    //: Save to ostream.
    
  private:
    ObjT obj;
    Func1T func;
  };
  
  ///////////////////////////////
  //! userlevel=Normal
  //: Send objects to a class method.
  
  template<class DataT,class ObjT>
  class DPOMethodC 
    : public DPOPortC<DataT> 
  {
  public:
    inline DPOMethodC() 
    {}
    //: Default constructor.
    
    inline DPOMethodC(const ObjT &nobj,typename DPOMethodBodyC<DataT,ObjT>::Func1T meth)
      : DPEntityC(*new DPOMethodBodyC<DataT,ObjT>(nobj,meth))
    {}
    //: Constructor.
    
  };
  
  //////////////////////////////////
  //! userlevel=Normal
  //: Get objects from a class method.
  
  template<class DataT,class ObjT>
  class DPIMethodC 
    : public DPIPortC<DataT> 
  {
  public:
    inline DPIMethodC() 
    {}
    //: Default constructor.
    
    inline DPIMethodC(const ObjT &nobj,typename DPIMethodBodyC<DataT,ObjT>::Func1T meth)
      : DPEntityC(*new DPIMethodBodyC<DataT,ObjT>(nobj,meth))
    {}
    //: Constructor.
    
  };
  
  template<class DataT,class ObjT>
  DPIPortC<DataT> IMethod(const ObjT &nobj,DataT (ObjT::*meth)())
  { return DPIMethodC<DataT,ObjT>(nobj,meth); }
  //: Turn a class method into an input port.
  
  template<class DataT,class ObjT>
  DPOPortC<DataT> OMethod(const ObjT &nobj,bool (ObjT::*meth)(const DataT &dat))
  { return DPOMethodC<DataT,ObjT>(nobj,meth); }
  //: Turn a class method into an output port.
  
};

#endif
