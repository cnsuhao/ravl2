// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_DECISIONEXAMPLES_HEADER
#define RAVLLOGIC_DECISIONEXAMPLES_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Histogram.hh"
#include "Ravl/Hash.hh"
#include "Ravl/HSet.hh"
#include "Ravl/Logic/Literal.hh"
#include "Ravl/Logic/State.hh"
#include "Ravl/IntC.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/PatternRec/DataSet2.hh"
#include "Ravl/Logic/SampleLiteral.hh"
#include "Ravl/Logic/SampleState.hh"
#include "Ravl/DList.hh"

namespace RavlLogicN {

  class DecisionExamplesC;

  class DecisionExamplesBodyC
    : public RCBodyC
  {
  public:
    DecisionExamplesBodyC()
    {}
    //: Default constructor.

    DecisionExamplesBodyC(const DataSet2C<SampleStateC,SampleLiteralC> &data);
    //: Construct from a dataset.
    
    void Dump(ostream &out) const;
    //: Dump examples to a stream.
    
    bool AddExample(const StateC &state,const LiteralC &decision);
    //: Add an example to the node.
    // Return's true if example is a new one.
    
    bool RemoveExamples(DecisionExamplesC &examples);
    //: Remove examples from this node.
    
    UIntT Frequency(const Tuple2C<StateC,LiteralC> &inst) const { 
      UIntC x;
      histogram.Lookup(inst,x);
      return x;
    }
    //: Find the frequency of an example state and decision.
    
    HashC<LiteralC,HSetC<StateC> > &Examples()
    { return examples; }
    //: Access examples table, mapping decisions to examples.

    const HashC<LiteralC,HSetC<StateC> > &Examples() const
    { return examples; }
    //: Access examples table, mapping decisions to examples.
    
    HistogramC<Tuple2C<StateC,LiteralC> > &Histogram()
    { return histogram; }
    //: Access frequency table.
    
    RealT DecisionInformation();
    //: Get an estimate of the information in decisions.
    
    bool Seperate(const LiteralC &test,DecisionExamplesC &ttrue,DecisionExamplesC &tfalse) const;
    //: Split this set into to, ones where the test is true (ttrue) and ones where its false (tfalse).
    
    UIntT Decisions() const
    { return examples.Size(); }
    //: Get the number of different decisions represented.

    DListC<LiteralC> ListDecisions() const;
    //: Make a list of decisions.

    LiteralC ProbableDecision() const;
    //: Get the most likely decision given the examples.
    
  protected:
    HashC<LiteralC,HSetC<StateC> > examples;  // Map decisions to examples.
    HistogramC<Tuple2C<StateC,LiteralC> > histogram; // Frequency of occurance. 
  };
  
  //! userlevel=Normal
  //: Decision Example Set.
  
  class DecisionExamplesC
    : public RCHandleC<DecisionExamplesBodyC>
  {
  public:
    DecisionExamplesC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

    DecisionExamplesC(bool)
      : RCHandleC<DecisionExamplesBodyC>(*new DecisionExamplesBodyC())
    {}
    //: Constructor.
    
    DecisionExamplesC(const DataSet2C<SampleStateC,SampleLiteralC> &data)
      : RCHandleC<DecisionExamplesBodyC>(*new DecisionExamplesBodyC(data))
    {}
    //: Construct from a dataset.
    
    void Dump(ostream &out) const
    { Body().Dump(out); }
    //: Dump examples to a stream.
    
    UIntT Frequency(const Tuple2C<StateC,LiteralC> &inst) const
    { return Body().Frequency(inst); }
    //: Find the frequency of an example state and decision.

    bool AddExample(const StateC &state,const LiteralC &decision)
    { return Body().AddExample(state,decision); }
    //: Add an example to the node.
    // Return's true if example is a new one.
    
    HashC<LiteralC,HSetC<StateC> > &Examples()
    { return Body().Examples(); }
    //: Access examples table.
    
    const HashC<LiteralC,HSetC<StateC> > &Examples() const
    { return Body().Examples(); }
    //: Access examples table.
    
    HistogramC<Tuple2C<StateC,LiteralC> > &Histogram()
    { return Body().Histogram(); }
    //: Access frequency table.
    
    bool Seperate(const LiteralC &test,DecisionExamplesC &ttrue,DecisionExamplesC &tfalse) const
    { return Body().Seperate(test,ttrue,tfalse); }
    //: Split this set into to, ones where the test is true (ttrue) and ones where its false (tfalse).
    
    UIntT Decisions() const
    { return Body().Decisions(); }
    //: Get the number of different decisions represented.
    
    DListC<LiteralC> ListDecisions() const
    { return Body().ListDecisions(); }
    //: Make a list of decisions.
    
    LiteralC ProbableDecision() const
    { return Body().ProbableDecision(); }
    //: Get the most likely decision given the examples.
    
  };
}

#endif
