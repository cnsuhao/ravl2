// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLCOMPOSE_HEADER
#define RAVLCOMPOSE_HEADER 1
////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.Core.Data Processing"
//! lib=RavlIO

#include "Ravl/DP/ProcCompose.hh"
#include "Ravl/DP/ProcIStream.hh"
//#include "Ravl/DP/Func2Stream.hh"
#include "Ravl/DP/FuncP2Proc.hh"
//#include "Ravl/DP/IOConnect.hh"
#include "Ravl/DP/Port.hh"
#include "Ravl/DP/StreamOp.hh"

namespace RavlN {

#if 0
  template<class InT,class OutT>
  DPFunc2ProcC<InT,OutT> Process(OutT (*func)(const InT &))
  { return DPFunc2ProcC<InT,OutT>(func); }
  //: Turn a function into a process.
#endif
  
  template<class InT,class MidT,class OutT>
  DPIOPortC<InT,OutT> operator>>(const DPIOPortC<InT,MidT> &in,DPIStreamOpC<MidT,OutT> dat)  {
    dat.Input() = in;
    return DPIOPortJoin(dat,in);
  }


}

#endif
