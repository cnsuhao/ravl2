// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_VARIABLEDISCRETE_HEADER
#define RAVLPROB_VARIABLEDISCRETE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/Variable.hh"
#include "Ravl/Prob/DomainDiscrete.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Implementation of a discrete random variable
  class VariableDiscreteBodyC
    : public VariableBodyC {
  public:
    VariableDiscreteBodyC(const StringC& name, const DomainDiscreteC& domain);
    //: Constructor
    //!param: name - convention is that it starts with a Capital letter, eg Face
    //!param: domain - countable set of mutually exclusive values that the variable can take

    VariableDiscreteBodyC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream

    VariableDiscreteBodyC(BinIStreamC &in);
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
    
    virtual ~VariableDiscreteBodyC();
    //: Destructor
    
    virtual StringC ToString() const;
    //: Get a string representation of the values that the variable can take

    SizeT DomainSize() const;
    //: Get access to the number of legal values

    const DomainDiscreteC& Domain() const;
    //: Get access to the set of legal values

    const StringC& Value(IndexC index) const;
    //: Get the value for a particular index

    IndexC Index(const StringC& value) const;
    //: Lookup an index for a value

  protected:
    VariableDiscreteBodyC(const StringC& name);
    //: Constructor
    //!param: name - convention is that it starts with a Capital letter, eg Face
    //!param: values - countable set of mutually exclusive values that the variable can take

    void SetDomain(const DomainDiscreteC& domain);
    //: Set the countable set of mutually exclusive value that this variable can take

  private:
    DomainDiscreteC m_domain;
    //: Countable set of mutually exclusive values that the variable can take
  };

  //! userlevel=Normal
  //: Implementation of a discrete random variable
  //!cwiz:author
  
  class VariableDiscreteC
    : public VariableC
  {
  public:
    VariableDiscreteC()
    {}
    //: Default constructor makes invalid handle

    VariableDiscreteC(const StringC& name, const DomainDiscreteC& domain)
      : VariableC(new VariableDiscreteBodyC(name, domain))
    {}
    //: Constructor
    //!param: name - convention is that it starts with a Capital letter, eg Face
    //!param: values - countable set of mutually exclusive values that the variable can take

    VariableDiscreteC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream
    
    VariableDiscreteC(BinIStreamC &in);
    //: Construct from binary stream
    //!param: in - binary input stream
    
    VariableDiscreteC(const VariableC& variable)
      : VariableC(dynamic_cast<const VariableDiscreteBodyC *>(BodyPtr(variable)))
    {}
    //: Upcast constructor
    // Creates an invalid handle if types don't match
    
    SizeT DomainSize() const
    { return Body().DomainSize(); }
    //: Get access to the number of legal values

    const DomainDiscreteC& Domain() const
    { return Body().Domain(); }
    //: Get access to the set of legal values

    const StringC& Value(IndexC index) const
    { return Body().Value(index); }
    //: Get the value for a particular index

    IndexC Index(const StringC& value) const
    { return Body().Index(value); }
    //: Lookup an index for a value

  protected:
    VariableDiscreteC(VariableDiscreteBodyC &bod)
     : VariableC(bod)
    {}
    //: Body constructor. 
    
    VariableDiscreteC(const VariableDiscreteBodyC *bod)
     : VariableC(bod)
    {}
    //: Body constructor. 
    
    VariableDiscreteBodyC& Body()
    { return static_cast<VariableDiscreteBodyC &>(VariableC::Body()); }
    //: Body Access. 
    
    const VariableDiscreteBodyC& Body() const
    { return static_cast<const VariableDiscreteBodyC &>(VariableC::Body()); }
    //: Body Access. 
    
  };

}

#endif
