// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDPFUNC2PROCESS_HEADER
#define RAVLDPFUNC2PROCESS_HEADER 1
///////////////////////////////////////////////
//! docentry="Ravl.Core.Data Processing" 
//! lib=RavlIO
//! rcsid="$Id$"
//! file="Ravl/Core/IO/Func2Proc.hh"
//! author="Charles Galambos"
//! date="09/07/98"
//! userlevel=Default

#include "Ravl/DP/Process.hh"

namespace RavlN {
  /////////////////////////////
  //! userlevel=Develop
  //: Function body.
  
  template<class InT,class OutT,OutT (Func)(const InT &)>
  class DPFunc2ProcBodyC 
    : public DPProcessBodyC<InT,OutT>
  {
  public:
    DPFunc2ProcBodyC() //FuncT nfunc
      {}
    //: Constructor.
    
    virtual OutT Apply(const InT &dat) 
      { return Func(dat); }
    //: Apply operation.

    virtual IntT ApplyArray(const SArray1dC<InT> &in,SArray1dC<OutT> &out) {
      RavlAssert(in.Size() <= out.Size());
      for(SArray1dIter2C<InT,OutT> it(in,out);it;it++)
	it.Data2() = Func(it.Data1());
      return in.Size();
    }
    //: Apply operation to an array.
    
    virtual bool IsStateless() const 
      { return true; }
    //: Is operation stateless ?
    
  protected:
  };
  
  ///////////////////////////////
  //! userlevel=Develop
  //: Function handle.
  
  template<class InT,class OutT,OutT (Func)(const InT &)>
  class DPFunc2ProcC
    : public DPProcessC<InT,OutT>
  {
  public:
    DPFunc2ProcC() // DPFunc2ProcBodyC<InT,OutT>::FuncT func
      : DPProcessC<InT,OutT>(*new DPFunc2ProcBodyC<InT,OutT,Func>())
      {}
    //: Default constructor.
  };
    
}

#endif

