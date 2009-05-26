// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_VARIABLEPROPOSITIONDISCRETE_HEADER
#define RAVLPROB_VARIABLEPROPOSITIONDISCRETE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/VariableProposition.hh"
#include "Ravl/Prob/VariableDiscrete.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Implementation of a discrete random variable value
  class VariablePropositionDiscreteBodyC
    : public VariablePropositionBodyC {
  public:
    VariablePropositionDiscreteBodyC(const VariableDiscreteC& variable, const StringC& value);
    //: Constructor
    //!param: variable - the variable that this is an instance of
    //!param: value - the value of the random variable

    VariablePropositionDiscreteBodyC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream

    VariablePropositionDiscreteBodyC(BinIStreamC &in);
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
    
    virtual ~VariablePropositionDiscreteBodyC();
    //: Destructor
    
    virtual StringC ToString() const;
    //: Get a string representation of the value

    virtual const StringC& Value() const;
    //: Get access to the value

    IndexC Index() const;
    //: Determine the index of this value

    virtual bool operator==(const VariablePropositionC& other) const;
    //: Equality operator

    virtual UIntT Hash() const;
    //: Hash function based on variable and value

  private:
    VariableDiscreteC VariableDiscrete() const;
    //: Get access to the discrete random variable that this is an instance of

  protected:
    virtual void SetValue(const StringC& value);
    //: Set the value of the random variable

    VariablePropositionDiscreteBodyC(const VariableDiscreteC& variable);
    //: Constructor
    //!param: variable - the variable that this is an instance of

  private:
    StringC m_value;
    //: The value of the random variable
  };

  //! userlevel=Normal
  //: Implementation of a discrete random variable value
  //!cwiz:author
  
  class VariablePropositionDiscreteC
    : public VariablePropositionC
  {
  public:
    VariablePropositionDiscreteC()
    {}
    //: Default constructor makes invalid handle

    VariablePropositionDiscreteC(const VariableDiscreteC& variable, const StringC& value)
      : VariablePropositionC(new VariablePropositionDiscreteBodyC(variable, value))
    {}
    //: Constructor
    //!param: variable - the variable that this is an instance of
    //!param: value - the value of the random variable

    VariablePropositionDiscreteC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream
    
    VariablePropositionDiscreteC(BinIStreamC &in);
    //: Construct from binary stream
    //!param: in - binary input stream
    
    VariablePropositionDiscreteC(const VariablePropositionC& value)
      : VariablePropositionC(dynamic_cast<const VariablePropositionDiscreteBodyC *>(BodyPtr(value)))
    {}
    //: Upcast constructor
    // Creates an invalid handle if types don't match
    
    const StringC& Value() const
    { return Body().Value(); }
    //: Get access to the value

    IndexC Index() const
    { return Body().Index(); }
    //: Determine the index of this value

  protected:
    VariablePropositionDiscreteC(VariablePropositionDiscreteBodyC &bod)
     : VariablePropositionC(bod)
    {}
    //: Body constructor. 
    
    VariablePropositionDiscreteC(const VariablePropositionDiscreteBodyC *bod)
     : VariablePropositionC(bod)
    {}
    //: Body constructor. 
    
    VariablePropositionDiscreteBodyC& Body()
    { return static_cast<VariablePropositionDiscreteBodyC &>(VariablePropositionC::Body()); }
    //: Body Access. 
    
    const VariablePropositionDiscreteBodyC& Body() const
    { return static_cast<const VariablePropositionDiscreteBodyC &>(VariablePropositionC::Body()); }
    //: Body Access. 
    
  };

}

#endif
