// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDPFUNC2STREAM_HEADER
#define RAVLDPFUNC2STREAM_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Data Processing"
//! file="Ravl/StdType/DataProc/Func2Stream.hh"
//! lib=RavlIO
//! author="Charles Galambos"
//! date="09/07/98"

#include "Ravl/DP/StreamOp.hh"
#include "Ravl/DP/IOJoin.hh"
#include "Ravl/SArr1Iter2.hh"

namespace RavlN {

  //////////////////////////////
  //! userlevel=Develop
  //: Wrapped function input stream body.
  
  template<class InT,class OutT,class ParamT>
  class DPFuncIStreamBodyC 
    : public DPIStreamOpBodyC<InT,OutT>
  {
  public:
    typedef OutT (*FuncT)(ParamT);
    FuncT func;
    
    DPFuncIStreamBodyC(const DPIPortC<InT> &nin,FuncT nfunc)
      : DPIStreamOpBodyC<InT,OutT>(nin),
      func(nfunc)
      {}
    //: Constructor.
    
    virtual OutT Get()  { 
      RavlAssert(input.IsValid());
      return func(input.Get()); 
    }
    //: Process next piece of data.
    
    virtual bool Get(OutT &outbuff) { 
      InT buff;
      RavlAssert(input.IsValid());
      if(!input.Get(buff))
	return false;
      outbuff = func(buff);
      return true;
    }
    //: Process some data.  
    
    virtual IntT GetArray(SArray1dC<OutT> &dest) {
      RavlAssert(input.IsValid());
      SArray1dC<InT> src(dest.Size());
      int rem = input.GetArray(src);
      if(rem > 0)
	src = SArray1dC<InT>(src,rem);
      for(SArray1dIter2C<InT,OutT> it(src,dest);it;it++)
	it.Data2() = func(it.Data1());
      return rem;
    }
    //: Get an array of data from stream.
    
  }; 
  
  //////////////////////////////
  //! userlevel=Develop
  //: Wrapped function input stream body.
  
  template<class InT,class OutT,class ParamT>
  class DPCPFuncIStreamBodyC 
    : public DPIStreamOpBodyC<InT,OutT>
  {
  public:
    typedef OutT (*FuncT)(const ParamT &);
    FuncT func;
    
    DPCPFuncIStreamBodyC(const DPIPortC<InT> &nin,FuncT nfunc)
      : DPIStreamOpBodyC<InT,OutT>(nin),
      func(nfunc)
      {}
    //: Constructor.
    
    virtual OutT Get() { 
      RavlAssert(input.IsValid());
      return func(input.Get()); 
    }
    //: Process next piece of data.
    
    virtual bool Get(OutT &outbuff) { 
      InT buff;
      RavlAssert(input.IsValid());
      if(!input.Get(buff))
      return false;
      outbuff = func(buff);
      return true;
    }
    //: Process some data.  
    
    virtual IntT GetArray(SArray1dC<OutT> &dest) {
      RavlAssert(input.IsValid());
      SArray1dC<InT> src(dest.Size());
      int rem = input.GetArray(src);
      if(rem > 0)
	src = SArray1dC<InT>(src,dest.Size() - rem);
      for(SArray1dIter2C<InT,OutT> it(src,dest);it;it++)
	it.Data2() = func(it.Data1());
      return rem;
    }
    //: Get an array of data from stream.
    
  }; 

  //////////////////////////////
  //! userlevel=Develop
  //: Wrapped function output stream body.
  
  template<class InT,class OutT,class ParamT>
  class DPFuncOStreamBodyC 
    : public DPOStreamOpBodyC<InT,OutT>
  {
  public:
    typedef OutT (*FuncT)(ParamT);
    FuncT func;
    
    DPFuncOStreamBodyC(const DPOPortC<OutT> &nin,FuncT nfunc)
      : DPOStreamOpBodyC<InT,OutT>(nin),
      func(nfunc)
      {}
    //: Constructor.
  
    virtual bool Put(const InT &buff) { 
      RavlAssert(output.IsValid());
      return output.Put(func(buff)); 
    }
    //: Process some data.  
    
    virtual IntT PutArray(const SArray1dC<InT> &src) {
      SArray1dC<OutT> dest(src.Size());
      for(SArray1dIter2C<InT,OutT> it(src,dest);it;it++)
	it.Data2() = func(it.Data1());
      return output.PutArray(dest);
    }
    //: Put an array of data to stream.
    // returns the number of elements processed.
    
  }; 
  
  //////////////////////////////
  //! userlevel=Develop
  //: Wrapped function output stream body.
  
  template<class InT,class OutT,class ParamT>
  class DPCPFuncOStreamBodyC 
    : public DPOStreamOpBodyC<InT,OutT>
  {
  public:
    typedef OutT (*FuncT)(const ParamT &);
    FuncT func;
    
    DPCPFuncOStreamBodyC(const DPOPortC<OutT> &nin,FuncT nfunc)
      : DPOStreamOpBodyC<InT,OutT>(nin),
      func(nfunc)
      {}
    //: Constructor.
    
    virtual bool Put(const InT &buff) { 
      RavlAssert(output.IsValid());
      return output.Put(func(buff)); 
    }
    //: Process some data.  
    
    virtual IntT PutArray(const SArray1dC<InT> &src) {
      SArray1dC<OutT> dest(src.Size());
      for(SArray1dIter2C<InT,OutT> it(src,dest);it;it++)
	it.Data2() = func(it.Data1());
      return output.PutArray(dest);
    }
    //: Put an array of data to stream.
    // returns the number of elements processed
    
  }; 
  
  ///////////////////////////////////
  //! userlevel=Normal
  //: Wrapped function input stream.

  template<class InT,class OutT,class ParamT>
  class DPFuncIStreamC : public DPIStreamOpC<InT,OutT> {
  public:
    typedef OutT (*FuncT)(ParamT);
    typedef OutT (*CPFuncT)(const ParamT &);
    
    DPFuncIStreamC() {}
    //: Default Constructor.
    
    DPFuncIStreamC(const DPIPortC<InT> &nin,FuncT func)
      : DPIStreamOpC<InT,OutT>((DPIPortBodyC<OutT> &) *new DPFuncIStreamBodyC<InT,OutT,ParamT>(nin,func))
      {}
    //: Constructor.
    
    DPFuncIStreamC(const DPIPortC<InT> &nin,CPFuncT func)
      : DPIStreamOpC<InT,OutT>((DPIPortBodyC<OutT> &) *new DPCPFuncIStreamBodyC<InT,OutT,ParamT>(nin,func))
      {}
    //: Constructor.
    
    DPFuncIStreamC(const DPFuncIStreamC<InT,OutT,ParamT> &oth) 
      : DPIStreamOpC<InT,OutT>(oth)
      {}
    //: Copy Constructor.
    
  };
  
  ///////////////////////////////////
  //! userlevel=Normal
  //: Wrapped function output stream.
  
  template<class InT,class OutT,class ParamT>
  class DPFuncOStreamC : public DPOStreamOpC<InT,OutT> {
  public:
    typedef OutT (*FuncT)(ParamT);
    typedef OutT (*CPFuncT)(const ParamT &);
    
    DPFuncOStreamC() {}
    //: Default Constructor.
    
    DPFuncOStreamC(const DPOPortC<OutT> &nin,FuncT func)
      : DPOStreamOpC<InT,OutT>(*new DPFuncOStreamBodyC<InT,OutT,ParamT>(nin,func))
      {}
    //: Constructor.
    
    DPFuncOStreamC(const DPOPortC<OutT> &nin,CPFuncT func)
      : DPOStreamOpC<InT,OutT>(*new DPCPFuncOStreamBodyC<InT,OutT,ParamT>(nin,func))
      {}
    //: Constructor.
    
    DPFuncOStreamC(const DPFuncOStreamC<InT,OutT,ParamT> &oth) 
      : DPOStreamOpC<InT,OutT>(oth)
      {}
    //: Copy Constructor.
    
  };
  
  ///////////////////////////////
  //: Composition operators.
  
  template<class InT,class OutT>
  DPIPortC<OutT> operator>>(const DPIPortC<InT> &in,OutT (*func)(InT))
  { return DPFuncIStreamC<InT,OutT,InT> (in,func); }
  
  template<class InT,class OutT,class DataT>
  DPIOPortC<OutT,DataT> operator>>(const DPIOPortC<InT,DataT> &in,OutT (*func)(InT))
  { return DPIOPortJoinC<OutT,DataT>(DPFuncIStreamC<InT,OutT,InT> (in,func),in); }

  template<class InT,class OutT>
  DPOPortC<InT> operator>>(OutT (*func)(InT),const DPOPortC<OutT> &in)
  { return DPFuncOStreamC<InT,OutT,InT> (in,func); }
  
  template<class InT,class OutT,class DataT>
  DPIOPortC<DataT,InT> operator>>(OutT (*func)(InT),const DPIOPortC<DataT,OutT> &in)
  { return DPIOPortJoinC<DataT,InT>(in,DPFuncOStreamC<InT,OutT,InT> (in,func)); }
  
  // Version with constant paramiter.
  
  template<class InT,class OutT>
  DPIPortC<OutT> operator>>(const DPIPortC<InT> &in,OutT (*func)(const InT &))
  { return DPFuncIStreamC<InT,OutT,InT> (in,func); }
  
  template<class InT,class OutT,class DataT>
  DPIOPortC<OutT,DataT> operator>>(const DPIOPortC<InT,DataT> &in,OutT (*func)(const InT &))
  { return DPIOPortJoinC<OutT,DataT>(DPFuncIStreamC<InT,OutT,InT> (in,func),in); }
  
  template<class InT,class OutT>
  DPOPortC<InT> operator>>(OutT (*func)(const InT &),const DPOPortC<OutT> &in)
  { return DPFuncOStreamC<InT,OutT,InT> (in,func); }
  
  template<class InT,class OutT,class DataT>
  DPIOPortC<DataT,InT> operator>>(OutT (*func)(const InT &),const DPIOPortC<DataT,OutT> &in)
  { return DPIOPortJoinC<DataT,InT>(in,DPFuncOStreamC<InT,OutT,InT> (in,func)); }
}

#endif
