// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_VARIABLEPROPOSITIONBOOLEAN_HEADER
#define RAVLPROB_VARIABLEPROPOSITIONBOOLEAN_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/VariablePropositionDiscrete.hh"
#include "Ravl/Prob/VariableBoolean.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Implementation of a boolean random variable value
  class VariablePropositionBooleanBodyC
    : public VariablePropositionDiscreteBodyC {
  public:
    VariablePropositionBooleanBodyC(const VariableBooleanC& variable, bool value);
    //: Constructor
    //!param: variable - the variable that this is an instance of
    //!param: value - the value of the random variable

    VariablePropositionBooleanBodyC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream

    VariablePropositionBooleanBodyC(BinIStreamC &in);
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
    
    virtual ~VariablePropositionBooleanBodyC();
    //: Destructor
    
    bool BooleanValue() const;
    //: Get access to the value

  private:
    void SetBooleanValue(bool value);
    //: Set the value of the random variable

    virtual void SetValue(const StringC& value);
    //: Set the value of the random variable

    VariableBooleanC VariableBoolean() const;
    //: Get access to the boolean random variable that this is an instance of

  private:
    bool m_booleanValue;
    //: The value of the random variable
  };

  //! userlevel=Normal
  //: Implementation of a boolean random variable value
  //!cwiz:author
  
  class VariablePropositionBooleanC
    : public VariablePropositionDiscreteC
  {
  public:
  	VariablePropositionBooleanC()
  	{}
  	//: Default constructors make invalid object
  	
    VariablePropositionBooleanC(const VariableBooleanC& variable, bool value)
      : VariablePropositionDiscreteC(new VariablePropositionBooleanBodyC(variable, value))
    {}
    //: Constructor
    //!param: variable - the variable that this is an instance of
    //!param: value - the value of the random variable

    VariablePropositionBooleanC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream
    
    VariablePropositionBooleanC(BinIStreamC &in);
    //: Construct from binary stream
    //!param: in - binary input stream
    
    bool BooleanValue() const
    { return Body().BooleanValue(); }
    //: Get access to the value

  protected:
    VariablePropositionBooleanC(VariablePropositionBooleanBodyC &bod)
     : VariablePropositionDiscreteC(bod)
    {}
    //: Body constructor. 
    
    VariablePropositionBooleanC(const VariablePropositionBooleanBodyC *bod)
     : VariablePropositionDiscreteC(bod)
    {}
    //: Body constructor. 
    
    VariablePropositionBooleanBodyC& Body()
    { return static_cast<VariablePropositionBooleanBodyC &>(VariablePropositionDiscreteC::Body()); }
    //: Body Access. 
    
    const VariablePropositionBooleanBodyC& Body() const
    { return static_cast<const VariablePropositionBooleanBodyC &>(VariablePropositionDiscreteC::Body()); }
    //: Body Access. 
    
  };

}

#endif
