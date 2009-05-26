// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_VARIABLE_HEADER
#define RAVLPROB_VARIABLE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/RCHandleV.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/String.hh"

namespace RavlProbN {
  using namespace RavlN;

  class VariableC;

  //! userlevel=Develop
  //: Base class for all random variable types
  //
  // A random variable is the base element of the probability notation. It can
  // be thought of as referring to a 'part' of the world whole 'status' is initially
  // unknown. For example, "Cavity" might refer to whether my lower left wisdom
  // tooth has a cavity. We always capitalize the names of random variables.
  // Each random variable has a domain of values that it can take on. We will
  // use lowercase for the names of values.
  //
  // There are three types of random variable:
  // 1: Boolean random variables, such as Cavity, have the domain <true,false>.
  // 2: Discrete random variables, which include Boolean random variables as a
  // special case, take on values from a countable domain. For example, the domain
  // of Weather might be <sunny,rainy,cloudy,snow>. The values in the domain must
  // be mutually exclusive and exhaustive.
  // 3: Continuous random variables take on values from the real numbers. The domain
  // can be either the entire real line or some subset such as the interval [0,1].
  // For example, the proposition X=4.02 asserts that the random variable X has the
  // exact value 4.02.
  
  class VariableBodyC
    : public RCBodyVC {
  public:
    VariableBodyC(const StringC& name);
    //: Constructor
    //!param: name - convention is that it starts with a Capital letter, eg Face

    VariableBodyC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream

    VariableBodyC(BinIStreamC &in);
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
    
    virtual ~VariableBodyC();
    //: Destructor

    const StringC& Name() const;
    //: Get access to the name of the random variable

    virtual StringC ToString() const =0;
    //: Get a string representation of the values that the variable can take
    
    bool operator==(const VariableC& other) const;
    //: Equality operator

    UIntT Hash() const;
    //: Hash function based on name

  private:
    void SetName(const StringC& name);
    //: Set the name of the random variable
    //!param: name - convention is that it starts with a Capital letter, eg Face

  private:
    StringC m_name;
    //: The name of the random variable
  };

  //! userlevel=Normal
  //: Base class for all random variable types
  //!cwiz:author
  
  class VariableC
    : public RCHandleVC<VariableBodyC>
  {
  public:
    VariableC()
    {}
    //: Default constructor makes invalid handle

    VariableC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream
    
    VariableC(BinIStreamC &in);
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
    
    const StringC& Name() const
    { return Body().Name(); }
    //: Get access to the name of the random variable
    //!cwiz:author

    StringC ToString() const
    { if (IsValid()) return Body().ToString(); else return "VariableC::<<NULL>>"; }
    //: Get a string representation of the values that the variable can take
    //!cwiz:author

    bool operator==(const VariableC& other) const
    { return Body().operator==(other); }
    //: Equality operator
    //!cwiz:author

    bool operator!=(const VariableC& other) const
    { return !Body().operator==(other); }
    //: Inequality operator
    //!cwiz:author

    UIntT Hash() const
    { return Body().Hash(); }
    //: Hash function based on name

  protected:
    VariableC(VariableBodyC &bod)
     : RCHandleVC<VariableBodyC>(bod)
    {}
    //: Body constructor. 
    
    VariableC(const VariableBodyC *bod)
     : RCHandleVC<VariableBodyC>(bod)
    {}
    //: Body constructor. 
    
    VariableBodyC& Body()
    { return static_cast<VariableBodyC &>(RCHandleVC<VariableBodyC>::Body()); }
    //: Body Access. 
    
    const VariableBodyC& Body() const
    { return static_cast<const VariableBodyC &>(RCHandleVC<VariableBodyC>::Body()); }
    //: Body Access. 
    
  };

  ostream &operator<<(ostream &s, const VariableC &obj);
  
  istream &operator>>(istream &s, VariableC &obj);

  BinOStreamC &operator<<(BinOStreamC &s, const VariableC &obj);
    
  BinIStreamC &operator>>(BinIStreamC &s, VariableC &obj);
  
}

#endif
