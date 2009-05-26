// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_VARIABLESET_HEADER
#define RAVLPROB_VARIABLESET_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"


#include "Ravl/RCHandleV.hh"
#include "Ravl/HSet.hh"
#include "Ravl/Prob/Variable.hh"

namespace RavlProbN {
  using namespace RavlN;

  class VariableSetC;

  //! userlevel=Develop
  //: Class used to represent a domain set of random variable
  //
  // Note that this is not to be confused with the domain of a particular random
  // variable, eg Weather=<sunny,rainy,cloudy,snow>. In this case we are referring
  // to a set of random variables, eg Weather, Cavity and X
  class VariableSetBodyC
    : public RCBodyVC {
  public:
    VariableSetBodyC(const HSetC<VariableC>& variables);
    //: Constructor
    //!param: variables - set of random variables contained in this domain

    VariableSetBodyC(const VariableC& variable);
    //: Constructor for a single variable
    //!param: variable - single random variables contained in this domain

    VariableSetBodyC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream

    VariableSetBodyC(BinIStreamC &in);
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
    
    virtual ~VariableSetBodyC();
    //: Destructor

    bool operator==(const VariableSetBodyC& other) const;
    //: Check if the two domains are equal

    bool Contains(const VariableC& variable) const;
    //: Check if the domain contains the specified random variable

    SizeT Size() const;
    //: Get the number of variables in the domain

    const HSetC<VariableC>& Variables() const;
    //: Get the random variables in the domain

    const VariableC& Variable(IndexC index) const;
    //: Get a random variable by index

    IndexC Index(const VariableC& variable) const;
    //: Find the index of a specified variable

    StringC ToString() const;
    //: Create a string representation of the domain

    bool operator==(const VariableSetC& other) const;
    //: Equality operator

    UIntT Hash() const;
    //: Hash function based set of values

  private:
    void SetVariables(const HSetC<VariableC>& variables);
    //: Set the random variables in the domain
    
    void SetSingleVariable(const VariableC& variable);
    //: Set a single random variable in the domain

  private:
    HSetC<VariableC> m_variables;
    //: The set of variables
  };

  //! userlevel=Normal
  //: Class used to represent a domain set of random variable
  //!cwiz:author
  
  class VariableSetC
    : public RCHandleVC<VariableSetBodyC>
  {
  public:
    VariableSetC()
    {}
    //: Default constructor makes invalid handle
    
    VariableSetC(const HSetC<VariableC>& variables)
      : RCHandleVC<VariableSetBodyC>(new VariableSetBodyC(variables))
    {}
    
    VariableSetC(const VariableC& variable)
      : RCHandleVC<VariableSetBodyC>(new VariableSetBodyC(variable))
    {}

    VariableSetC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream
    
    VariableSetC(BinIStreamC &in);
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
    
    bool operator==(const VariableSetC& other) const
    { return Body().operator==(other.Body()); }
    //: Check if the two domains are equal
    //!cwiz:author

    bool operator!=(const VariableSetC& other) const
    { return !Body().operator==(other.Body()); }
    //: Check if the two domains are different
    //!cwiz:author

    bool Contains(const VariableC& variable) const
    { return Body().Contains(variable); }
    //: Check if the domain contains the specified random variable
    //!cwiz:author

    SizeT Size() const
    { return Body().Size(); }
    //: Get the number of variables in the domain

    const HSetC<VariableC>& Variables() const
    { return Body().Variables(); }
    //: Get the random variables in the domain

    const VariableC& Variable(IndexC index) const
    { return Body().Variable(index); }
    //: Get a random variable by index

    IndexC Index(const VariableC& variable) const
    { return Body().Index(variable); }
    //: Find the index of a specified variable

    StringC ToString() const
    { return Body().ToString(); }
    //: Create a string representation of the domain
    //!cwiz:author

    UIntT Hash() const
    { return Body().Hash(); }
    //: Hash function based on name

  protected:
    VariableSetC(VariableSetBodyC &bod)
     : RCHandleVC<VariableSetBodyC>(bod)
    {}
    //: Body constructor. 
    
    VariableSetC(const VariableSetBodyC *bod)
     : RCHandleVC<VariableSetBodyC>(bod)
    {}
    //: Body constructor. 
    
    VariableSetBodyC& Body()
    { return static_cast<VariableSetBodyC &>(RCHandleVC<VariableSetBodyC>::Body()); }
    //: Body Access. 
    
    const VariableSetBodyC& Body() const
    { return static_cast<const VariableSetBodyC &>(RCHandleVC<VariableSetBodyC>::Body()); }
    //: Body Access. 
    
  };

  ostream &operator<<(ostream &s, const VariableSetC &obj);
  
  istream &operator>>(istream &s, VariableSetC &obj);

  BinOStreamC &operator<<(BinOStreamC &s, const VariableSetC &obj);
    
  BinIStreamC &operator>>(BinIStreamC &s, VariableSetC &obj);
  
}

#endif
