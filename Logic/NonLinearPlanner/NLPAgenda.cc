// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////
// NLPlan/NLPAgenda.cc  4/1/97   By Charles Galambos
// $Id$
//! rcsid="$Id$"
//! lib=RavlLogicNLP

#include "Ravl/Logic/NLPAgenda.hh"

namespace RavlLogicN {
  
  void NLPAgendaC::Del(NLPStepNodeT &Step) {
    RavlAssert(0); // Obsolete.
#if 1
    while(!threats.IsEmpty()) {
      if(!(threats.Top().Step() == Step))
	break;
      threats.DelFirst();
    }
#else
    for(DLIterC<ThreatRefT> iter(threats);iter.IsElm();iter.Next()) {
      if(!(iter.Data().Step() == Step))
	break;
      iter.Del();
    }
#endif
    while(!singleOpenGoal.IsEmpty()) {
      if(!(singleOpenGoal.Top().Step() == Step))
	break;
      singleOpenGoal.DelFirst();
      OpenGoalCount--;
    }
    while(!OpenGoal.IsEmpty()) {
      if(!(OpenGoal.Top().Step() == Step))
	break;
      OpenGoal.DelFirst();
      OpenGoalCount--;
    }
  }
  
  void NLPAgendaC::DelThreat(NLPCausalLinkT &Victim) {
    RavlAssert(0); // Obsolete.
#if 1 
    while(!threats.IsEmpty()) {
      if(!(threats.Top().TheVictim() == Victim))
	break;
      threats.DelFirst();
    }
#else
    for(DLIterC<ThreatRefT> iter(threats);iter.IsElm();iter.Next()) {
      if(!(iter.Data().TheVictim() == Victim))
	break;
      iter.Del();
    }
#endif
  }
  
  ///////////////////////////////
  // Empty agenda.
  
  void NLPAgendaC::Empty() {
    threats.Empty();
    singleOpenGoal.Empty();
    OpenGoal.Empty();
  }
}

