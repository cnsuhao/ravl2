// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_PROPOSITIONSET_HEADER
#define RAVLPROB_PROPOSITIONSET_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"


#include "Ravl/RCHandleV.hh"
#include "Ravl/Prob/VariableSet.hh"
#include "Ravl/Prob/VariableProposition.hh"
#include "Ravl/HSet.hh"

namespace RavlProbN {
  using namespace RavlN;

  class PropositionSetC;

  //! userlevel=Develop
  //: Class used to represent a proposition in a domain of random variables
  //
  // A proposition indicates a set of values or propositions about a subset of
  // variables in a domain. Eg given a VariableSet with Weather, Cavity and X,
  // represent the proposition that Weather=snow, Cavity=true and X is unknown.
  class PropositionSetBodyC
    : public RCBodyVC {
  public:
    PropositionSetBodyC(const VariableSetC& variableSet, const HSetC<VariablePropositionC>& values);
    //: Constructor
    //!param: variableSet - the variableSet for the proposition
    //!param: values - list of random variables values contained in this proposition
    
    PropositionSetBodyC(const VariableSetC& variableSet, const RCHashC<VariableC,VariablePropositionC>& values);
    //: Constructor
    //!param: variableSet - the variableSet for the proposition
    //!param: values - list of random variables values contained in this proposition
    
    PropositionSetBodyC(const VariableSetC& variableSet, const VariablePropositionC& value);
    //: Constructor for a single value
    //!param: variableSet - the variableSet for the proposition
    //!param: value - single random variable value contained in this proposition

    PropositionSetBodyC(const VariablePropositionC& value);
    //: Constructor for a single value with single variable
    //!param: value - single random variable value contained in this proposition

    PropositionSetBodyC(const PropositionSetBodyC& other, const VariablePropositionC& value);
    //: Extended constructor
    //!param: other = another proposition
    //!param: value - a value to extend the proposition with

    PropositionSetBodyC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream

    PropositionSetBodyC(BinIStreamC &in);
    //: Construct from binary stream
    //!param: in - binary input stream
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using stream constructor
    //!param: out - standard output stream
    //!return: true if the object was successfully saved

    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using binary stream constructor
    //!param: out - binary output stream
    //!return: true if the object was successfully saved
    
    virtual ~PropositionSetBodyC();
    //: Destructor

    StringC ToString() const;
    //: Create a string representation of the variableSet

    StringC LotteryName() const;
    //: Create a lottery name for this proposition
    
    const VariableSetC& VariableSet() const
    { return m_variableSet; }
    //: Get the variableSet

    SizeT Size() const
    { return Values().Size(); }
    //: Get the number of values in the proposition
    
    bool FindProposition(const VariableC &varName,VariablePropositionC &proposition) const
    { return m_values.Lookup(varName,proposition); }
    //: Find propersition for variable if set.
    // Returns false if variable is free
    
    const RCHashC<VariableC,VariablePropositionC>& Values() const
    { return m_values; }
    //: Get the random variable values in the variableSet
    
    const VariablePropositionC& Value(IndexC index) const;
    //: Get a random variable value by index

    PropositionSetC SubPropositionSet(const VariableSetC& subVariableSet) const;
    //: Create a proposition for a subset of current variables, subvariableSet
    
    bool operator==(const PropositionSetBodyC& other) const;
    //: Equality operator
    
    UIntT Hash() const;
    //: Hash function based set of values

  private:
    void SetVariableSet(const VariableSetC& variableSet);
    //: Set the variableSet

    void SetValues(const HSetC<VariablePropositionC>& values);
    //: Set the random variable values in the variableSet
    
    void SetSingleValue(const VariablePropositionC& value);
    //: Set a single random variable value in the variableSet
    
  private:
    VariableSetC m_variableSet;
    //: The variableSet of the proposition
    
    RCHashC<VariableC,VariablePropositionC> m_values;
    //: Mapping between variable and proposed value 
  };

  //! userlevel=Normal
  //: Class used to represent a proposition in a variableSet of random variables
  //!cwiz:author
  
  class PropositionSetC
    : public RCHandleVC<PropositionSetBodyC>
  {
  public:
    PropositionSetC()
    {}
    //: Default constructor makes invalid handle

    PropositionSetC(const VariableSetC& variableSet, const RCHashC<VariableC,VariablePropositionC>& values)
      : RCHandleVC<PropositionSetBodyC>(new PropositionSetBodyC(variableSet, values))
    {}
    //: Constructor
    //!param: variableSet - the variableSet for the proposition
    //!param: values - list of random variables values contained in this proposition

    PropositionSetC(const VariableSetC& variableSet, const HSetC<VariablePropositionC>& values)
      : RCHandleVC<PropositionSetBodyC>(new PropositionSetBodyC(variableSet, values))
    {}

    PropositionSetC(const VariableSetC& variableSet, const VariablePropositionC& value)
      : RCHandleVC<PropositionSetBodyC>(new PropositionSetBodyC(variableSet, value))
    {}
    //: Constructor for a single value
    //!param: variableSet - the variableSet for the proposition
    //!param: value - single random variable value contained in this proposition

    PropositionSetC(const VariablePropositionC& value)
      : RCHandleVC<PropositionSetBodyC>(new PropositionSetBodyC(value))
    {}
    //: Constructor for a single value with single variable
    //!param: value - single random variable value contained in this proposition

    PropositionSetC(const PropositionSetC& other, const VariablePropositionC& value)
      : RCHandleVC<PropositionSetBodyC>(new PropositionSetBodyC(other.Body(), value))
    {}
    //: Extended constructor
    //!param: other = another proposition
    //!param: value - a value to extend the proposition with

    PropositionSetC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream
    
    PropositionSetC(BinIStreamC &in);
    //: Construct from binary stream
    //!param: in - binary input stream
    
    bool Save(ostream &out) const
    { return Body().Save(out); }
    //: Writes object to stream, can be loaded using stream constructor 
    //!param: out - standard output stream
    //!return: true if the object was successfully saved
    //!cwiz:author
    
    bool Save(BinOStreamC &out) const
    { return Body().Save(out); }
    //: Writes object to stream, can be loaded using binary stream constructor 
    //!param: out - binary output stream
    //!return: true if the object was successfully saved
    //!cwiz:author
    
    StringC ToString() const
    { return Body().ToString(); }
    //: Create a string representation of the variableSet
    //!cwiz:author

    StringC LotteryName() const
    { return Body().LotteryName(); }
    //: Create a lottery name for this proposition
    //!cwiz:author

    const VariableSetC& VariableSet() const
    { return Body().VariableSet(); }
    //: Get the variableSet

    SizeT Size() const
    { return Body().Size(); }
    //: Get the number of values in the proposition
    
    const RCHashC<VariableC,VariablePropositionC>& Values() const
    { return Body().Values(); }
    //: Get the random variable values in the variableSet
    //!cwiz:author
    
    bool FindProposition(const VariableC &varName,VariablePropositionC &prop) const
    { return Body().FindProposition(varName,prop); }
    //: Find propersition for variable if set.
    // Returns false if variable is free
    
    const VariablePropositionC& Value(IndexC index) const
    { return Body().Value(index); }
    //: Get a random variable value by index
    //!cwiz:author

    PropositionSetC SubPropositionSet(const VariableSetC& subVariableSet) const
    { return Body().SubPropositionSet(subVariableSet); }
    //: Create a proposition for a subvariableSet
    //!cwiz:author

    bool operator==(const PropositionSetC& other) const
    { return Body().operator==(other.Body()); }
    //: Equality operator
    //!cwiz:author

    bool operator!=(const PropositionSetC& other) const
    { return !Body().operator==(other.Body()); }
    //: Inequality operator
    //!cwiz:author

    UIntT Hash() const
    { return Body().Hash(); }
    //: Hash function based on name

  protected:
    PropositionSetC(PropositionSetBodyC &bod)
     : RCHandleVC<PropositionSetBodyC>(bod)
    {}
    //: Body constructor. 
    
    PropositionSetC(const PropositionSetBodyC *bod)
     : RCHandleVC<PropositionSetBodyC>(bod)
    {}
    //: Body constructor. 
    
    PropositionSetBodyC& Body()
    { return static_cast<PropositionSetBodyC &>(RCHandleVC<PropositionSetBodyC>::Body()); }
    //: Body Access. 
    
    const PropositionSetBodyC& Body() const
    { return static_cast<const PropositionSetBodyC &>(RCHandleVC<PropositionSetBodyC>::Body()); }
    //: Body Access. 
    
  };

  ostream &operator<<(ostream &s, const PropositionSetC &obj);
  
  istream &operator>>(istream &s, PropositionSetC &obj);

  BinOStreamC &operator<<(BinOStreamC &s, const PropositionSetC &obj);
    
  BinIStreamC &operator>>(BinIStreamC &s, PropositionSetC &obj);
  
}

#endif
