// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DPIOCONNECT_HEADER
#define RAVL_DPIOCONNECT_HEADER 1
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlIO
//! author="Charles Galambos"
//! docentry="Ravl.Core.Data Processing" 
//! date="06/07/1998"
//! example=exDataProc.cc
//! file="Ravl/Core/IO/IOConnect.hh"

#include "Ravl/DP/Port.hh"
#include "Ravl/DP/IOJoin.hh"

namespace RavlN {

  //////////////////////////
  //! userlevel=Develop
  //: Connect some IOPorts body.
  
  template<class DataT>
  class DPIOConnectBodyC 
    : public DPEntityBodyC 
  {
  public:
    DPIOConnectBodyC(const DPIPortC<DataT> &from,const DPOPortC<DataT> &to);
    //: Constructor.
    
    bool Run(void);
    //: Do processing.
    
    bool Step();
    //: Do a single processing step.
  private:
    DPIPortC<DataT> from;
    DPOPortC<DataT> to;
  };

  ////////////////////////////////
  //! userlevel=Normal
  //: Connect some IOPorts.
  
  template<class DataT>
  class DPIOConnectC
    : public DPEntityC
  {
  public:
    DPIOConnectC(const DPIPortC<DataT> &from,const DPOPortC<DataT> &to)
      : DPEntityC(*new DPIOConnectBodyC<DataT>(from,to))
    {}
    //: Constructor.
    
  protected:
    inline DPIOConnectBodyC<DataT> &Body() 
    { return dynamic_cast<DPIOConnectBodyC<DataT> &>(DPEntityC::Body()); }
    //: Access body.
    
    inline const DPIOConnectBodyC<DataT> &Body() const
    { return dynamic_cast<const DPIOConnectBodyC<DataT> &>(DPEntityC::Body()); }
    //: Access body.

  public:
    inline bool Run()
    { return Body().Run(); }
    //: Do processing.
    
    inline void Dummy() 
    {}
    //: Used to avoid some warnings.

  };
  
  //////////////////////////////
  
  template<class DataT>
  DPIOConnectC<DataT> Connect(const DPIPortC<DataT> &from,const DPOPortC<DataT> &to)
  { return DPIOConnectC<DataT>(from,to); }
  
  /////////////////////////////////////////
  
  template<class DataT>
  DPIOConnectBodyC<DataT>::DPIOConnectBodyC(const DPIPortC<DataT> &nfrom,const DPOPortC<DataT> &nto) 
    : from(nfrom),
      to(nto)
  {
    RavlAssert(from.IsValid());
    RavlAssert(to.IsValid());
  }
  
  template<class DataT>
  bool DPIOConnectBodyC<DataT>::Run(void) {
    DataT buff;
    while(1) {
      if(!from.Get(buff))
	break;
      if(!to.Put(buff))
	break;
    }
    to.PutEOS(); // Put a termination marker.
    return true;
  }
  
  template<class DataT>
  bool DPIOConnectBodyC<DataT>::Step() {
    if(!from.IsGetReady()) {
      to.PutEOS();
      return false;
    }
    if(!to.Put(from.Get()))
      return false;
    return true;
  }
  
  ///////////////////////////////
  
  //: Single Threaded composition operators.
  
  template<class DataT>
  DPIOConnectC<DataT> operator>>(const DPIPortC<DataT> &in,const DPOPortC<DataT> &out) { 
    DPIOConnectC<DataT> tmp(in,out);
    //cerr << "operator>>(const DPIPortC<DataT> &in,const DPOPortC<DataT> &out) Called. \n";
    tmp.Run();
    return tmp;
  }
  
  template<class DataT,class OutT>
  DPIOConnectC<DataT> operator>>(const DPIPortC<DataT> &in,const DPIOPortC<DataT,OutT> &out) { 
    DPIOConnectC<DataT> tmp(in,out); 
    //cerr << "operator>>(const DPIPortC<DataT> &in,const DPIOPortC<DataT,OutT> &out) Called. \n";
    tmp.Run();
    return tmp;
  }
  
  template<class InT,class DataT>
  DPOPortC<InT> operator>>(const DPIOPortC<DataT,InT> &in,const DPOPortC<DataT> &out)  { 
    DPIOConnectC<DataT> tmp(in,out); 
    //cerr << "operator>>(const DPIOPortC<DataT,InT> &in,const DPOPortC<DataT> &out) Called. \n";
    tmp.Run();
    return in;
  }

#if 0  
  template<class DataT>
  inline void operator>>= (const DPIPortC<DataT> &in,const DPOPortC<DataT> &out)
  { DPIOConnectC<DataT>(in,out).Dummy(); }
  
  template<class DataT,class OutT>
  inline DPIPortC<OutT> operator>>= (const DPIPortC<DataT> &in,const DPIOPortC<OutT,DataT> &out)
  { DPIOConnectC<DataT>(in,out).Dummy(); return out; }
  
  template<class InT,class DataT>
  inline DPOPortC<InT> operator>>= (const DPIOPortC<DataT,InT> &in,const DPOPortC<DataT> &out) 
  { DPIOConnectC<DataT>(in,out).Dummy(); return in; }
  
  template<class InT,class DataT,class OutT>
  inline DPIOPortC<InT,OutT> operator>>= (const DPIOPortC<DataT,OutT> &in,const DPIOPortC<InT,DataT> &out) { 
    DPIOConnectC<DataT>(in,out).Dummy(); 
    return DPIOPortJoinC<InT,OutT>(out,in); 
  }
#endif  
}
#endif
