// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_VARIABLEPROPOSITIONCONTINUOUS_HEADER
#define RAVLPROB_VARIABLEPROPOSITIONCONTINUOUS_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/VariableProposition.hh"
#include "Ravl/Prob/VariableContinuous.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Implementation of a continuous random variable value
  class VariablePropositionContinuousBodyC
    : public VariablePropositionBodyC {
  public:
    VariablePropositionContinuousBodyC(const VariableContinuousC& variable, RealRangeC valueRange);
    //: Constructor
    //!param: variable - the variable that this is an instance of
    //!param: valueRange - the value of the random variable

    VariablePropositionContinuousBodyC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream

    VariablePropositionContinuousBodyC(BinIStreamC &in);
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
    
    virtual ~VariablePropositionContinuousBodyC();
    //: Destructor
    
    virtual StringC ToString() const;
    //: Get a string representation of the value

    virtual RealRangeC ValueRange() const;
    //: Get access to the value range

    virtual bool operator==(const VariablePropositionC& other) const;
    //: Equality operator

    virtual UIntT Hash() const;
    //: Hash function based on variable and value

  private:
    virtual void SetValueRange(RealRangeC valueRange);
    //: Set the value range of the random variable

    VariableContinuousC VariableContinuous() const;
    //: Get access to the continuous random variable that this is an instance of

  private:
    RealRangeC m_valueRange;
    //: The value range of the random variable
  };

  //! userlevel=Normal
  //: Implementation of a continuous random variable value
  //!cwiz:author
  
  class VariablePropositionContinuousC
    : public VariablePropositionC
  {
  public:
  	VariablePropositionContinuousC()
  	{}
  	//: Default constructor makes invalid handle
  	
    VariablePropositionContinuousC(const VariableContinuousC& variable, RealRangeC valueRange)
      : VariablePropositionC(new VariablePropositionContinuousBodyC(variable, valueRange))
    {}
    //: Constructor
    //!param: variable - the variable that this is an instance of
    //!param: valueRange - the value range of the random variable

    VariablePropositionContinuousC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream
    
    VariablePropositionContinuousC(BinIStreamC &in);
    //: Construct from binary stream
    //!param: in - binary input stream
    
    VariablePropositionContinuousC(const VariablePropositionC& value)
      : VariablePropositionC(dynamic_cast<const VariablePropositionContinuousBodyC *>(BodyPtr(value)))
    {}
    //: Upcast constructor
    // Creates an invalid handle if types don't match
    
    RealRangeC ValueRange() const
    { return Body().ValueRange(); }
    //: Get access to the value range

  protected:
    VariablePropositionContinuousC(VariablePropositionContinuousBodyC &bod)
     : VariablePropositionC(bod)
    {}
    //: Body constructor. 
    
    VariablePropositionContinuousC(const VariablePropositionContinuousBodyC *bod)
     : VariablePropositionC(bod)
    {}
    //: Body constructor. 
    
    VariablePropositionContinuousBodyC& Body()
    { return static_cast<VariablePropositionContinuousBodyC &>(VariablePropositionC::Body()); }
    //: Body Access. 
    
    const VariablePropositionContinuousBodyC& Body() const
    { return static_cast<const VariablePropositionContinuousBodyC &>(VariablePropositionC::Body()); }
    //: Body Access. 
    
  };

}

#endif
