// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_VARIABLEBOOLEAN_HEADER
#define RAVLPROB_VARIABLEBOOLEAN_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/VariableDiscrete.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Implementation of a boolean random variable
  class VariableBooleanBodyC
    : public VariableDiscreteBodyC {
  public:
    VariableBooleanBodyC(const StringC& name);
    //: Constructor
    //!param: name - convention is that it starts with a Capital letter, eg Face

    VariableBooleanBodyC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream

    VariableBooleanBodyC(BinIStreamC &in);
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
    
    virtual ~VariableBooleanBodyC();
    //: Destructor

    const StringC& Value(bool value) const;
    //: Get the name used for value

  private:
    void SetValueNames();
    //: Sets trueValue and falseValue based on the variable name

  private:
    StringC m_trueValue;
    //: The name used for true values

    StringC m_falseValue;
    //: The name used for false values
  };

  //! userlevel=Normal
  //: Implementation of a boolean random variable
  //!cwiz:author
  
  class VariableBooleanC
    : public VariableDiscreteC
  {
  public:
  	VariableBooleanC()
  	{}
  	//: Default constructors makes invalid object
  	
    VariableBooleanC(const StringC& name)
      : VariableDiscreteC(new VariableBooleanBodyC(name))
    {}
    //: Constructor
    //!param: name - convention is that it starts with a Capital letter, eg Face

    VariableBooleanC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream
    
    VariableBooleanC(BinIStreamC &in);
    //: Construct from binary stream
    //!param: in - binary input stream
    
    VariableBooleanC(const VariableC& variable)
      : VariableDiscreteC(dynamic_cast<const VariableBooleanBodyC *>(BodyPtr(variable)))
    {}
    //: Upcast constructor
    // Creates an invalid handle if types don't match
    
    const StringC& Value(bool value) const
    { return Body().Value(value); }
    //: Get the name used for bool value

  protected:
    VariableBooleanC(VariableBooleanBodyC &bod)
     : VariableDiscreteC(bod)
    {}
    //: Body constructor. 
    
    VariableBooleanC(const VariableBooleanBodyC *bod)
     : VariableDiscreteC(bod)
    {}
    //: Body constructor. 
    
    VariableBooleanBodyC& Body()
    { return static_cast<VariableBooleanBodyC &>(VariableDiscreteC::Body()); }
    //: Body Access. 
    
    const VariableBooleanBodyC& Body() const
    { return static_cast<const VariableBooleanBodyC &>(VariableDiscreteC::Body()); }
    //: Body Access. 
    
  };

}

#endif
