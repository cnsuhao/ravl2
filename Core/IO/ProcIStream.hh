// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef DPPROCWRAP_HEADER
#define DPPROCWRAP_HEADER 1
/////////////////////////////////////////////////////
//! example=exDataProc.cc
//! file="Ravl/Core/IO/ProcIStream.hh"
//! lib=RavlIO
//! author="Charles Galambos"
//! docentry="Ravl.Core.Data Processing" 
//! date="06/07/98"
//! rcsid="$Id$"
//! userlevel=Default

#include "Ravl/DP/StreamOp.hh"
#include "Ravl/DP/Process.hh"
#include "Ravl/DP/IOJoin.hh"

namespace RavlN {
  //! userlevel=Develop
  //: Convert process into input stream operator, body.
  
  template<class InT,class OutT>
  class DPProcIStreamBodyC 
    : public DPProcessC<InT,OutT>,
      public DPIStreamOpBodyC<InT,OutT>
  {
  public:
    DPProcIStreamBodyC(const DPProcessC<InT,OutT> &bod,const DPIPortC<InT> &nin)
      : DPProcessC<InT,OutT>(bod),
      DPIStreamOpBodyC<InT,OutT>(nin)
      {}
    //: Constructor.
    
    DPProcIStreamBodyC(const DPProcIStreamBodyC<InT,OutT> &oth);
    //: Copy Constructor.
    
    virtual OutT Get()  { 
      RavlAssert(input.IsValid());
      return Apply(input.Get()); 
    }
    //: Process next piece of data.
    
    virtual bool Get(OutT &outbuff) { 
      InT buff;
      RavlAssert(input.IsValid());
      if(!input.Get(buff))
	return false;
      outbuff = Apply(buff);
      return true;
    }
    //: Process some data.  
    
    virtual IntT GetArray(SArray1dC<OutT> &dest) {
      SArray1dC<InT> src(dest.Size());
      IntT ret = input.GetArray(src);
      if(ret > 0)
	src = SArray1dC<InT>(src,ret);
#ifndef NDEBUG
      IntT ap = 
#endif
	ApplyArray(src,dest);
      RavlAssert(ap == (IntT) src.Size()); // Expect the all to be processed.
      return ret;
    }
    //: Get Array of data.
    
    virtual RCBodyVC &Copy() const { 
      if(!IsStateless())
	return *new DPProcIStreamBodyC(*this); 
      return const_cast<RCBodyVC &>((RCBodyVC &)*this);
    }
    //: Creat a copy of this object.
  }; 
  
  //! userlevel=Normal
  //: Convert process into input stream operator, handle.
  
  template<class InT,class OutT>
  class DPProcIStreamC 
    : public DPIStreamOpC<InT,OutT> 
  {
  public:
    DPProcIStreamC() 
      : DPEntityC(true)
      {}
    //: Default Constructor.
    // Creates an invalid handle.
    
    DPProcIStreamC(const DPProcessC<InT,OutT> &bod,const DPIPortC<InT> &nin)
      : DPEntityC((DPIPortBodyC<OutT> &) *new DPProcIStreamBodyC<InT,OutT>(bod,nin))
      {}
    //: Constructor.
    
    DPProcIStreamC(const DPProcIStreamC<IntT,OutT> &oth) 
      : DPEntityC(oth),
      DPIStreamOpC<InT,OutT>(oth)
      {}
    //: Copy Constructor.
    
  };
  
  ///////////////////////////////
  //: Composition operator.
  
  template<class InT,class OutT>
  DPIPortC<OutT> operator>>(const DPIPortC<InT> &in,const DPProcessC<InT,OutT> &proc) 
  { return DPProcIStreamC<InT,OutT> (proc,in); }
  
  template<class InT,class OutT,class InterT>
  DPIOPortC<OutT,InterT> operator>>(const DPIOPortC<InT,InterT> &in,const DPProcessC<InT,OutT> &proc) 
  { return DPIOPortJoin(DPProcIStreamC<InT,OutT> (proc,in),in); }
  
  //////////////////////////////////////////////////////////
  
  template<class InT,class OutT>
  DPProcIStreamBodyC<InT,OutT>::DPProcIStreamBodyC(const DPProcIStreamBodyC<InT,OutT> &oth)
    : DPProcessC<InT,OutT>(oth.Copy()),
      DPIStreamOpBodyC<InT,OutT>(oth)
  {}
  //: Copy Constructor.
  
}
#endif
