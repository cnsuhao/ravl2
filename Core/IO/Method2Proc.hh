// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DPMETHODPROC_HEADER
#define RAVL_DPMETHODPROC_HEADER 1
///////////////////////////////////////////////
//! docentry="Data Processing"
//! lib=RavlIO
//! file="Ravl/StdType/DataProc/Method2Proc.hh"
//! author="Charles Galambos"
//! date="09/07/98"
//! rcsid="$Id$"

#include "Ravl/DP/Process.hh"

namespace RavlN {

  ////////////////////////////
  //! userlevel=Develop
  //: Methodtion body.
  
  template<class InT,class OutT,class ObjT>
  class DPMethod2ProcBodyC 
    : public DPProcessBodyC<InT,OutT>
  {
  public:
    typedef OutT (ObjT::*FuncT)(const InT &);
    
    DPMethod2ProcBodyC(const ObjT &nobj,FuncT nfunc,bool stateless = true)
      : obj(nobj),
	func(nfunc),
	stateless(true)
    {}
    //: Constructor.
    
    virtual OutT Apply(const InT &dat) 
    { return (obj.*func)(dat); }
    //: Apply operation.
    
    virtual IntT ApplyArray(const SArray1dC<InT> &in,SArray1dC<OutT>  &out) { 
      RavlAssert(out.Size() >= in.Size());
      for(SArray1dIter2C<InT,OutT> it(in,out);it;it++)
	it.Data2() = (obj.*func)(it.Data1());
      return in.Size();
    }
    //: Apply operation to an array of elements.
    
    virtual bool IsStateless() const 
    { return stateless; }
    //: Is operation stateless ?
    
  protected:
    ObjT obj;
    FuncT func;
    bool stateless;
  };
  
  ///////////////////////////////
  //! userlevel=Develop
  //: Methodtion handle.
  
  template<class InT,class OutT,class ObjT>
  class DPMethod2ProcC
    : public DPProcessC<InT,OutT>
  {
  public:
    DPMethod2ProcC(const ObjT &nobj,DPMethod2ProcBodyC<InT,OutT,ObjT>::FuncT func,bool stateless = true)
      : DPProcessC<InT,OutT>(*new DPMethod2ProcBodyC<InT,OutT,ObjT>(nobj,func,stateless))
    {}
    //: Default constructor.
  };
  
  template<class InT,class OutT,class ObjT>
  DPMethod2ProcC<InT,OutT,ObjT> Process(const ObjT &nclass,OutT (ObjT::*nmethod)(const InT &))
  { return DPMethod2ProcC<InT,OutT,ObjT>(nclass,nmethod); }
  //: Turn a function into a process.
}

#endif
