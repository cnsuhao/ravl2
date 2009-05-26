// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! date="12/10/98"
//! lib=RavlDPMT
//! file="Ravl/OS/DataProc/Governor.cc"

#include "Ravl/DP/Governor.hh"

namespace RavlN {
  
  //: Wait for timeup.
  
  void DPGovernorBaseBodyC::WaitForTimeup() {
    // Any delay set ?
    if(delay <= 0 && minDelay <= 0)
      return ;
    // What time is it now ?
    DateC now(true);
    RealT diff = (next - now).Double();
    if(diff < minDelay) {
      if(minDelay > 0) {
	next = now;
	next += minDelay;
      }
    }
    next.Wait();
    next.SetToNow();
    next += delay;
    frameCnt++;    
  }

  //: Set new delay.
  bool DPGovernorBaseBodyC::SetDelay(RealT newDelay) { 
    if(newDelay < 0) {
      delay = 0;
      return false;
    }
    delay = newDelay; 
    return true;
  }
  
  
}
