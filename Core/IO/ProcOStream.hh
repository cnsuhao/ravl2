// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDPPROCOSTREAM_HEADER
#define RAVLDPPROCOSTREAM_HEADER 1
/////////////////////////////////////////////////////
//! example=exDataProc.cc
//! rcsid="$Id: ProcOStream.hh 5240 2005-12-06 17:16:50Z plugger $"
//! file="Ravl/Core/IO/ProcOStream.hh"
//! lib=RavlIO
//! author="Charles Galambos"
//! docentry="Ravl.API.Core.Data Processing.Internal" 
//! date="06/07/98"
//! userlevel=Default

#include "Ravl/DP/StreamOp.hh"
#include "Ravl/DP/Process.hh"

namespace RavlN {
  
  ////////////////////////////////////////
  //! userlevel=Develop
  //: Wrapped process body.
  
  template<class InT,class OutT>
  class DPProcOStreamBodyC 
    : public DPProcessC<InT,OutT>,
      public DPOStreamOpBodyC<InT,OutT>
  {
  public:
    DPProcOStreamBodyC(const DPProcessC<InT,OutT> &bod,const DPOPortC<OutT> &nout)
      : DPProcessC<InT,OutT>(bod),
      DPOStreamOpBodyC<InT,OutT>(nout)
      {}
    //: Constructor.
    
    virtual bool Put(const InT &dat) { 
      RavlAssert(this->output.IsValid());
      return this->output.Put(Apply(dat)); 
    }
    //: Process next piece of data.  
    
    virtual IntT PutArray(SArray1dC<InT> &src) {
      SArray1dC<OutT> dest(src.Size());
#ifdef NDEBUG
      ApplyArray(src,dest);
#else
      RavlAssert((UIntT) ApplyArray(src,dest) == src.Size());
#endif
      return this->output.PutArray(dest);
    }
    //: Get Array of data.
    
    virtual bool Save(ostream &out) const 
    { return DPOStreamOpBodyC<InT,OutT>::Save(out); }
    //: Save to ostream.
    
  }; 

  /////////////////////////////////
  //! userlevel=Normal
  //: Wrapped Proccess handle.
  
  template<class InT,class OutT>
  class DPProcOStreamC 
    : public DPOStreamOpC<InT,OutT> 
  {
  public:
    DPProcOStreamC() 
      : DPEntityC(true)
      {}
    //: Default Constructor.
    // Creates an invalid handle.
    
    DPProcOStreamC(const DPProcessC<InT,OutT> &bod,const DPOPortC<OutT> &nout)
      : DPEntityC((DPOPortBodyC<InT> &) *new DPProcOStreamBodyC<InT,OutT>(bod,nout))
      {}
    //: Constructor.
    // 
    
    DPProcOStreamC(const DPProcOStreamC<IntT,OutT> &oth) 
      : DPEntityC(oth),
      DPOStreamOpC<InT,OutT>(oth)
      {}
    //: Copy Constructor.
    
  };
  
  ///////////////////////////////
  //: Composition operator.
  
  template<class InT,class OutT>
  DPProcOStreamC<InT,OutT> operator>>(const DPProcessC<InT,OutT> &proc,const DPOPortC<OutT> &out) 
  { return DPProcOStreamC<InT,OutT> (proc,out); }
  
}

#endif
