// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_NLPAGENDA_HEADER
#define RAVLLOGIC_NLPAGENDA_HEADER 1
///////////////////////////////////////////////////////
//! author="Charles Galambos"
//! date="16/12/1996"
//! docentry="Logic.Planning"
//! userlevel=Develop
//! rcsid="$Id$"
//! file="Ravl/Logic/PlanNL/NLPAgenda.hh"
//! lib=RavlLogicNLP

#include "Ravl/BStack.hh"
#include "Ravl/Logic/NLPAgendaItem.hh"

namespace RavlLogicN { 

  //: Agenda for non linear plan.
  // This is a small object, but its cheap to copy.

  class NLPAgendaC 
  {
  public:  
    inline NLPAgendaC()
      : OpenGoalCount(0) 
    {}
    //: Default constructor.
    // Creats an empty agenda.
    
    inline void Insert(const NLPAgendaThreatC &Item)
    { threats.InsFirst(Item); }
    // Insert Threat into agenda.
    
    inline void Insert(const NLPAgendaOpenGoalC &Item);
    // Insert Open Goal into agenda.
  
    inline void InsFirst(const NLPAgendaItemC &Item);
    // Insert item into agenda.
    
    inline NLPAgendaItemC GetFirst();
    // Get First item from agenda.
  
    inline NLPAgendaItemC First();
    // Look at first item in agenda.
    
    void Del(NLPStepNodeT &Step);
    // Remove item from the agenda that are caused by this step.
    
    void DelThreat(NLPCausalLinkT &Victim);
    // Remove threats to causal link 'victim'.
  
    inline bool IsEmpty() const 
    { return threats.IsEmpty() && singleOpenGoal.IsEmpty() && OpenGoal.IsEmpty(); }
    // Is agenda empty ?
    
    void Empty(void);
    // Empty agenda.
  
    int GetNoOpenGoals(void) const { return OpenGoalCount; }
    // Get number of open goals.
  
  protected:
    BStackC<NLPAgendaThreatC> threats;
    BStackC<NLPAgendaOpenGoalC> singleOpenGoal;
    BStackC<NLPAgendaOpenGoalC> OpenGoal;  
    int OpenGoalCount;
  };

  /////////////////////////////////////////////////////////////////////////
  
  inline 
  void NLPAgendaC::Insert(const NLPAgendaOpenGoalC &Item) { 
    OpenGoalCount++;
    if(Item.IsSingle())
      singleOpenGoal.Push(Item);
    else
      OpenGoal.Push(Item);
  }

  inline 
  void NLPAgendaC::InsFirst(const NLPAgendaItemC &Item) {
    if(Item.IsThreat()) {
      Insert(NLPAgendaThreatC(const_cast<NLPAgendaItemC &>(Item)));
      return;
    }
    RavlAssert(Item.IsOpenGoal());
    Insert(NLPAgendaOpenGoalC(const_cast<NLPAgendaItemC &>(Item)));
  }

  inline 
  NLPAgendaItemC NLPAgendaC::GetFirst() {
    if(!threats.IsEmpty())
      return threats.Pop();
    OpenGoalCount--;
    if(!singleOpenGoal.IsEmpty())
      return singleOpenGoal.Pop();
    return OpenGoal.Pop();
  }

  inline 
  NLPAgendaItemC NLPAgendaC::First() {
    if(!threats.IsEmpty())
      return threats.First();
    if(!singleOpenGoal.IsEmpty())
      return singleOpenGoal.First();
    return OpenGoal.First();
  }
  
}
#endif
