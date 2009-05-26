// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_VARIABLEPROPOSITION_HEADER
#define RAVLPROB_VARIABLEPROPOSITION_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/RCHandleV.hh"
#include "Ravl/Prob/Variable.hh"

namespace RavlProbN {
  using namespace RavlN;

  class VariablePropositionC;

  //! userlevel=Develop
  //: Base class for all random variable values
  //
  // A random variable value is a proposition about a random variable. It
  // asserts that a variable takes on a particular value from its domain. For
  // instance, Cavity=false, or alternatively Cavity=¬cavity. Also X=4.02,
  // Weather=snow.
  class VariablePropositionBodyC
    : public RCBodyVC {
  public:
    VariablePropositionBodyC(const VariableC& variable);
    //: Constructor
    //!param: variable - the variable that this is an instance of

    VariablePropositionBodyC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream

    VariablePropositionBodyC(BinIStreamC &in);
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
    
    virtual ~VariablePropositionBodyC();
    //: Destructor

    const VariableC& Variable() const;
    //: Get access to the random variable that this is an instance of

    virtual StringC ToString() const =0;
    //: Get a string representation of the values that the variable can take

    virtual bool operator==(const VariablePropositionC& other) const=0;
    //: Equality operator

    virtual UIntT Hash() const=0;
    //: Hash function based on variable

  private:
    void SetVariable(const VariableC& variable);
    //: Set the random variable
    //!param: variable - the variable that this is an instance of

  private:
    VariableC m_variable;
    //: The random variable
  };

  //! userlevel=Normal
  //: Base class for all random variable values
  //!cwiz:author
  
  class VariablePropositionC
    : public RCHandleVC<VariablePropositionBodyC>
  {
  public:
    VariablePropositionC()
    {}
    //: Default constructor makes invalid handle

    VariablePropositionC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream
    
    VariablePropositionC(BinIStreamC &in);
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
    
    const VariableC& Variable() const
    { return Body().Variable(); }
    //: Get access to the random variable that this is an instance of
    //!cwiz:author

    StringC ToString() const
    { if (IsValid()) return Body().ToString(); else return "VariablePropositionC::<<NULL>>"; }
    //: Get a string representation of the value
    //!cwiz:author

    bool operator==(const VariablePropositionC& other) const
    { return Body().operator==(other); }
    //: Equality operator
    //!cwiz:author

    bool operator!=(const VariablePropositionC& other) const
    { return !Body().operator==(other); }
    //: Inequality operator
    //!cwiz:author

    UIntT Hash() const
    { return Body().Hash(); }
    //: Hash function based on variable

  protected:
    VariablePropositionC(VariablePropositionBodyC &bod)
     : RCHandleVC<VariablePropositionBodyC>(bod)
    {}
    //: Body constructor. 
    
    VariablePropositionC(const VariablePropositionBodyC *bod)
     : RCHandleVC<VariablePropositionBodyC>(bod)
    {}
    //: Body constructor. 
    
    VariablePropositionBodyC& Body()
    { return static_cast<VariablePropositionBodyC &>(RCHandleVC<VariablePropositionBodyC>::Body()); }
    //: Body Access. 
    
    const VariablePropositionBodyC& Body() const
    { return static_cast<const VariablePropositionBodyC &>(RCHandleVC<VariablePropositionBodyC>::Body()); }
    //: Body Access. 
    
  };

  ostream &operator<<(ostream &s, const VariablePropositionC &obj);
  
  istream &operator>>(istream &s, VariablePropositionC &obj);

  BinOStreamC &operator<<(BinOStreamC &s, const VariablePropositionC &obj);
    
  BinIStreamC &operator>>(BinIStreamC &s, VariablePropositionC &obj);
  
}

#endif
