#// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLCOMPOSESINGLE_HEADER
#define RAVLCOMPOSESINGLE_HEADER 1
////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! example=exComposeSinge.cc
//! userlevel=Normal
//! lib=RavlIO
//! docentry="Ravl.Core.Data Processing"

#include "Ravl/DP/Compose.hh"

namespace RavlComposeSingleN {

  using namespace RavlN;
  
  //: Pass data through a function.
  
  template<class InT,class OutT>
  OutT operator>>(const InT &dat,OutT (*func)(const InT &))
  { return func(dat); }
  
  //: Process a single piece of data.
  
  template<class InT,class OutT>
  OutT operator>>(const InT &in,const DPProcessC<InT,OutT> &proc)
    { return const_cast<DPProcessC<InT,OutT> &>(proc).Apply(in); }
  
  //: Propergate data to output variable.
  
  template<class DataT>
  void operator>>(const DataT &in,DataT &out)
    { out = in; }
  
  //: Input data from a port.
  
  template<class DataT>
  bool operator>>(DPIPortC<DataT> &ip,DataT &in)
    { return ip.Get(in); }
  
  //: Take data from port.
  
  template<class DataT>
  DPIPortC<DataT> &operator+= (DPIPortC<DataT> &ip,DataT &in){ 
    ip.Get(in); 
    return ip;
  }
  
  //: Output data to a port.
  
  template<class DataT>
  bool operator>>(const DataT &out,const DPOPortC<DataT> &op)
  { return DPOPortC<DataT>(op).Put(out); }
  
  //: Output data to an ioport.
  // The const in the for the 'op' is just to get write of warnings
  // about initalisation with temporary refrences.
  
  
  //: Add data into port.
  
  template<class DataT>
  DPOPortC<DataT> &operator+= (DPOPortC<DataT> &op,const DataT &out) { 
    op.Put(out); 
    return op;
  }

}

#endif
