///////////////////////////////////////////
// L2World/TPlan.cc  1/1/97 By Charles Galambos
// $Id$

#include <stdio.h>
#include "Ravl/Logic/NonLinearPlan.hh"
#include "Ravl/Logic/NLPlanner.hh"
#include "Ravl/Logic/Not.hh"
#include "Ravl/Logic/And.hh"
#include "Ravl/Logic/Or.hh"
#include "Ravl/Logic/Var.hh"
#include "Ravl/Logic/State.hh"
#include "Ravl/Option.hh"

int SimpleTest();
int LoopTest();

using namespace RavlLogicN;
using namespace RavlN;

int main(int argc,char **argv) 
{
  OptionC  option(argc,argv,true);
  //BooleanT verbose  = option.Boolean("v",FALSE,"Verbose mode.");
  option.Check();
  int ret;
#if 1
  if((ret = SimpleTest()) != 0) {
    cerr << "Test failed. :" << ret << "\n";
    return 1;
  }
#endif
#if 0
  if((ret = LoopTest()) != 0) {
    cerr << "Test failed. :" << ret << "\n";
    return 1;
  }
#endif
  cout << "Test passed. \n";
  return 0;
}

int SimpleTest()
{
  LiteralC goalSymb;
  LiteralC startCond;
  
  LiteralC see("See");
  LiteralC inv("Inv");
  LiteralC ball("Ball");
  LiteralC bat("Bat");
  LiteralC igloo("Igloo");
  startCond = TupleC(see,ball) * TupleC(inv,bat) * TupleC(see,igloo);
  
  cerr << "Setting up goals.  \n";
  goalSymb = TupleC(inv,ball) * !TupleC(inv,bat) * TupleC(see,bat) * 
    !TupleC(see,igloo) * !TupleC(inv,igloo);
  
  cerr << "Setting up rules.  \n";
  VarC var1("var1");
  DListC<NLPStepC> rules;
  
  rules.InsLast(NLPStepC(TupleC(see,var1),
			 TupleC(LiteralC("Remove"),var1),
			 !TupleC(see,var1)
			 )
		);
  rules.InsLast(NLPStepC(TupleC(see,var1),
			 TupleC(LiteralC("get"),var1),
			 TupleC(inv,var1) *!TupleC(see,var1)
			 )
		);
  
  rules.InsLast(NLPStepC(TupleC(inv,var1),
			 TupleC(LiteralC("put"),var1),
			 TupleC(see,var1)*!TupleC(inv,var1)
			 )
		);
  
  //theory.Dump();
  cerr << "Constructing planner.  \n";
  
  NLPlannerC planner(rules);
  StateC init(true);
  init.Tell(startCond);
  DListC<NLPStepC> plan = planner.Apply(init,goalSymb);
  if(!plan.IsValid()) {
    cerr << "Unable to complete plan. \n";
    return 1;
  }
  
  return 0;
}

#if 0
int LoopTest() 
{
  LiteralC goalSymb;
  LiteralC startCond;
  
  cerr << "Setting up start conduition.  \n";
  LiteralC see("see");
  LiteralC bat("bat ");
  LiteralC inv("inv");
  LiteralC ball("ball");
  
  startCond = TupleC(see,bat);
  cerr << "Setting up goals.  \n";
  goalSymb = TupleC(inv,ball);
  
  cerr << "Setting up rules.  \n";
  VLVarC var1("var1");
  
  rules.InsLast(NLPStepC(SeeT(var1),
			    GetT(var1),
			    InvT(var1) *!SeeT(var1)
			    )
		    );
  
  rules.InsLast(NLPStepC(InvT(var1),
			PutT(var1),
			SeeT(var1)*!InvT(var1))
		);
  
  //theory.Dump();
  cerr << "Constructing planner.  \n";
  
  VLExprSetC spc(aTRUE);
  
  VLNLPlannerC planner(ruleModel);
  
  spc.Assert(startCond);
  VLPlanLinearStepC plan = planner.Apply(spc,VLMinTermC(goalSymb));
  
  return 0;
}
#endif
