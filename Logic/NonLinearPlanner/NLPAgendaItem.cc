// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////
// Logic2/PlanNL/NLPAgendaItem.cc  4/1/97   By Charles Galambos
// $Id$
//! rcsid="$Id$"
//! lib=RavlLogicNLP

#include "Ravl/Logic/NLPAgendaItem.hh"
//#include "Ravl/Logic/NLPlanner.hh"
#include "Ravl/Logic/NLPAction.hh"
#include "Ravl/Assert.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlLogicN {
  
  // Get action to remedy problem.
  
  NLPActionC NLPAgendaItemBodyC::GetAction(NonLinearPlanC &plan) {
    RavlAssert(0); // Abstract method.
    return NLPActionC();
  }
  
  // Get action to remedy problem.
  
  NLPActionC NLPAgendaItemC::GetAction(NonLinearPlanC &plan) 
  { return Body().GetAction(plan); }
  
  
  //////////////////////////////////////////////////////////////////
  // Constructor.
  
  NLPAgendaOpenGoalBodyC::NLPAgendaOpenGoalBodyC(const NLPStepNodeT &aStep,
						 const MinTermC &aMTR,
						 NonLinearPlanC &plan) 
    : NLPAgendaItemBodyC(aStep),
      aCond(aMTR.Copy())
  {
    //VLOCKOBJ(plan);
    RavlAssert(plan.IsValid(aStep));
    newSteps = plan.ListSteps(aCond,Step().Data().PreCondition());
    
    // FIXME :- Do this properly.
    if(newSteps.IsEmpty())
      priority = 1;
    else
      priority = 4;
  
#if 0
    switch(PossSteps.List().Size() + newSteps.List().Size())
      {
      case 0: return 2; // No solitions.
      case 1: return 3; // One solition.
      }
#endif

  }
  
  //: Get action to remedy problem.
  
  NLPActionC NLPAgendaOpenGoalBodyC::GetAction(NonLinearPlanC &aPlan) 
  { return NLPActionOpenGoalC(aPlan,*this); }
  
  //: This is an open goal.
  
  bool NLPAgendaOpenGoalBodyC::IsOpenGoal() const 
  { return true; }
  
  /////////////////////////////////////////////////////////////
  
  //: Yep this is a threat.
  
  bool NLPAgendaThreatBodyC::IsThreat() const 
  { return true; }
  
  //: Get action to remedy problem.
  
  NLPActionC NLPAgendaThreatBodyC::GetAction(NonLinearPlanC &aPlan) 
  { return NLPActionThreatC(aPlan,*this); }
}
