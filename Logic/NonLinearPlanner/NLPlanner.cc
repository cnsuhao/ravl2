// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////
// L2World/NLPlanner.cc   4/1/97    By Charles Galambos
// $Id$
//! rcsid="$Id$"
//! lib=RavlLogicNLP

#include "Ravl/Logic/NLPlanner.hh"
#include "Ravl/PriQueueL.hh"
#include "Ravl/Logic/NLPAction.hh"
#include "Ravl/Logic/State.hh"

#include <stdio.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlLogicN {

  //////////////////////////
  // Default constructor.

  NLPlannerBodyC::NLPlannerBodyC() 
    : planCount(0),
      allocCondID(1),
      maxSearch(-1),
      limSearch(-1),
      curSearch(0)
  { RavlAssert(0); }

  
  ///////////////////////
  //: Construct plan.

  DListC<NLPStepC> NLPlannerBodyC::Apply(const StateC &state,const MinTermC &goals) 
  {
    ONDEBUG(cerr << "NLPlannerBodyC::Apply(), Called. \n");
    NewPlan(state,goals);
    if(!CompletePlan()) {
      ONDEBUG(cerr << "NLPlannerBodyC::Apply(), No Complete plan found. \n");
      return DListC<NLPStepC>(); // No plan found.
    }
    ONDEBUG(cerr << "NLPlannerBodyC::Apply(), Generating linear plan. \n");
    // Get linear plan.
    return GetBestLinearPlan();
  }

  ////////////////////
  // Create a new plan.
  
  bool NLPlannerBodyC::NewPlan(const StateC &start,const MinTermC &goal) {
    // Generate MinTerm reflecting all thats asserted in state,
    // this does NOT include negations.
    // Anything not assert in the inital state is assumed to be
    // false by the planner.
    // FIXME :- A better way of doing this.
    //          Make start state special ??
    planCount = 0;
    MinTermC inital(true); // Clear inital state.
    
    for(LiteralIterC it(start.List());it;it++)
      inital *= it.Data();
    
    // Create new plan.
    NonLinearPlanC plan(*this);
  
    curSearch = 0;
    limSearch = maxSearch;
    bestSize = MaxBest;
    bestPlan.Invalidate(); // No Best plan yet.
    MinTermC NA_MT(true);
    LiteralC NA_Act("NA_Act");
    init = inital; // VLMinTerm(*Inital);
    initS = NLPStepC(NA_MT,NA_Act,inital);
    startNode = plan.InsStep(initS);
    goalNode  = plan.InsStep(NLPStepC(goal,NA_Act,NA_MT));
    plan.InsOrderLink(startNode,goalNode);
    //printf("Inital Step:%p \n",&(*initS));
    DoDBCheck(plan);
    ONDEBUG(printf("\nNLPlannerBodyC::NewPlan(), ------------ Goal:%s ---------- \n",goal.GetName().chars()));
    ONDEBUG(printf("NLPlannerBodyC::NewPlan(), Start:%s \n",inital.GetName().chars()));
    if(plan.IsComplete()) {
      // No Goal ?
      return true;
    }
    // Get item from agenda and put into the queue.
    NLPActionC act = plan.GetTopOfAgenda().GetAction(plan);
    plans.Empty();
    plans.Insert(plan.Score(),act);
    //RavlAssert(plans.Size() == 1);
    // And we're ready !
    return goalNode.IsValid();
  }

  //////////////////////
  // Complete a plan.

  bool NLPlannerBodyC::CompletePlan() {
    ONDEBUG(printf("NLPlannerBodyC::CompletePlan(), Called. \n"));
    NonLinearPlanC newPlan;
    bestSize = MaxBest;
    while(!plans.IsEmpty()) {
      ONDEBUG(printf("NLPlannerBodyC::CompletePlan(), Top plan. Score:%d \n",plans.Top().Plan().Score()));
      if(!plans.Top().Next(newPlan)) {
	plans.DelTop();
	continue; // Out of actions.
      }
      DoDBCheck(newPlan);
      if(newPlan.IsComplete()) {
	ONDEBUG(printf("NLPlannerBodyC::CompletePlan(), !!!!! Complete plan found !!!!!! \n"));
	ONDEBUG(printf("NLPlannerBodyC::CompletePlan(), Init:%s \n",init.GetName().chars()));
	IntT newSize = newPlan.Steps();
	if(newSize < bestSize) {
	  bestPlan = newPlan;
	  bestSize = newSize;
	  limSearch = (int) ((double) curSearch * 1.5);
	  break; // Done.
	}
      } else {
	// Check new plan is an actual improvement on the old one.
      
	// Put new plan back into queue.
	NLPActionC act = newPlan.GetTopOfAgenda().GetAction(newPlan);
	plans.Insert(newPlan.Score(),act);
	DoDBCheck(newPlan);
      }
      curSearch++;
      if(limSearch > 0) {
	if(curSearch >= limSearch) {
	  ONDEBUG(printf("NLPlannerBodyC::CompletePlan(), Search limit exceeded. \n"));
	  break; // Give-up and return results.
	}
      }
    }
    if(!IsComplete() && plans.IsEmpty()) {
      ONDEBUG(printf("NLPlannerBodyC::CompletePlan(), plans exausted. \n"));
    }
    return IsComplete();
  }

  //////////////////////
  // Create a linear plan.

  bool NLPlannerBodyC::GetLinearPlan(DListC<NLPStepC> &lPlan) {
    if(!IsComplete()) {
      printf("NLPlannerBodyC::GetLinearPlan(), Called on incomplete plan. \n");
      RavlAssert(0);
      lPlan.Empty();
      return false;
    }
    lPlan = bestPlan.GetLinear();
    return true;
  }

  //////////////////////
  // List steps that achive a goal.
  
  DListC<NLPStepC> NLPlannerBodyC::ListSteps(const MinTermC &postCond) 
  {
    DListC<NLPStepC> ret;
    return ret;
  }

  //////////////////////
  // GoalCond :- Condition that must be meet by Step,
  // FullCond :- 'Wish list' of conditions that also will be needed.
  //
  // Heuristic ordering of steps, place the most likly to
  // be usefull first.
  
  DListC<NLPStepC> NLPlannerBodyC::OptListSteps(const MinTermC &GoalCond,const MinTermC &FullCond) {
    DListC<NLPStepC> inital = ListSteps(GoalCond);
#if 0
    //printf("NLPlannerBodyC::OptListSteps(), Goal:%s Full:%s \n",GoalCond.GetName().chars(),FullCond.GetName().chars());
    DListC<NLPStepC> ret;
    PriQueueLC<int,NLPStepC> Que;
    int Count = 0;
    for(DLIterC<NLPStepC> It(inital);It.IsElm();It.Next()) {
      Que.Insert(Distance(It.Data().PostCond(),FullCond),It.Data()); // Find all distances.
      Count++;
    }
    while(Que.IsElm()) {
      //printf("NLPlannerBodyC::OptListSteps(), %d - %s \n",Que.TopKey(),Que.Top().GetName().chars());
      ret.InsLast(Que.GetTop());
    }
    return ret;
#else
    return inital;
#endif
  }

  /////////////////////////////////////////////
  // Find distance between minterms.
  
  template<class DataT>
  bool Contains(const SArray1dC<DataT> &sa,const DataT &item) {
    for(SArray1dIterC<DataT> it(sa);it;it++)
      if(*it == item)
	return true;
    return false;
  }
  // 0=Identical.
  
  int NLPlannerBodyC::Distance(const MinTermC &MT1, const MinTermC &MT2) {
    int dist = 0;
    SArray1dIterC<LiteralC> It(MT1.Pos());
    for(;It.IsElm();It.Next()) {
      if(Contains(MT2.Neg(),It.Data()))
	dist += 5;
      if(!Contains(MT2.Pos(),It.Data()))
	dist += 1;
    }
    It = MT1.Neg();
    for(;It.IsElm();It.Next()) {
      if(Contains(MT2.Pos(),It.Data()))
	dist += 5;
      if(!Contains(MT2.Neg(),It.Data()))
	dist += 1;
    }
    It = MT2.Pos();
    for(;It.IsElm();It.Next()) {
      if(!Contains(MT1.Pos(),It.Data()))
	dist += 1;
    }
    It = MT2.Neg();
    for(;It.IsElm();It.Next()) {
      if(!Contains(MT1.Neg(),It.Data()))
	dist += 1;
    }
    return dist;
  }
  
  ///////////////////////////
  // Debuging checks.

  void NLPlannerBodyC::DoDBCheck(NonLinearPlanBodyC &/*APlan*/) {
#if 0
    BindSetC BTmp;
    if(APlan.Plan.NodeData(startNode.ID()).PostCond().Unify(*Init,BTmp) 
       && (&(*InitS) == &(*APlan.Plan.NodeData(startNode.ID()))))
      return ; // Alls ok.
    printf("NLPlannerBodyC::DoDBCheck(), FAILED. Step:%p (%d) InitS:%p \n",&(*APlan.Plan.NodeData(startNode.ID())),startNode.ID().V(),&(*InitS));
    APlan.Dump();
    printf("Post should be:'%s' \n",init.GetName().chars());
    RavlAssert(0);
#endif
  }


}
