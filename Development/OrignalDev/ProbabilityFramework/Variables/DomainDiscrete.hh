// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_DOMAINDISCRETE_HEADER
#define RAVLPROB_DOMAINDISCRETE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"


#include "Ravl/RCHandleV.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/String.hh"
#include "Ravl/Hash.hh"
#include "Ravl/SArray1d.hh"

namespace RavlProbN {
  using namespace RavlN;

  class DomainDiscreteC;

  //! userlevel=Develop
  //: Describes the domain of possible values for a discrete random variable
  class DomainDiscreteBodyC
    : public RCBodyVC {
  public:
    DomainDiscreteBodyC();
    //: Constructor

    DomainDiscreteBodyC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream

    DomainDiscreteBodyC(BinIStreamC &in);
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
    
    virtual ~DomainDiscreteBodyC();
    //: Destructor
    
    void Insert(const StringC& value);
    //: Insert a value into the domain
    
    void Remove(const StringC& value);
    //: Remove a value from the domain
    
    bool Contains(const StringC& value) const;
    //: Check if the domain contains the specified value
    
    IndexC Index(const StringC& value) const;
    //: Find the index of a specified value
    
    const StringC& Value(IndexC index) const;
    //: Lookup a value by index
    
    SizeT Size() const;
    //: The number of values in the domain
    
    SArray1dIterC<StringC> Iterator() const;
    //: Get an iterator over the collection of values

    StringC ToString() const;
    //: Get a string representation of the values
    
    bool operator==(const DomainDiscreteBodyC& other) const;
    //: Equality operator

    UIntT Hash() const;
    //: Hash function based on name

  private:
    void CreateValueHash();
    //: Generate the value hash table from the array
    
  private:
    HashC<StringC,IndexC> m_valueHash;
    //: Hash table of values and their index number
    
    SArray1dC<StringC> m_valueArray;
    //: Array of values for rapid indexing
  };

  //! userlevel=Normal
  //: Describes the domain of possible values for a discrete random variable
  //!cwiz:author
  
  class DomainDiscreteC
    : public RCHandleVC<DomainDiscreteBodyC>
  {
  public:
    DomainDiscreteC()
      : RCHandleVC<DomainDiscreteBodyC>(new DomainDiscreteBodyC())
    {}
    //: Default constructor

    DomainDiscreteC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream
    
    DomainDiscreteC(BinIStreamC &in);
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
    
    void Insert(const StringC& value)
    { Body().Insert(value); }
    //: Insert a value into the domain
    
    void Remove(const StringC& value)
    { Body().Remove(value); }
    //: Remove a value from the domain
    
    bool Contains(const StringC& value) const
    { return Body().Contains(value); }
    //: Check if the domain contains the specified value
    
    IndexC Index(const StringC& value) const
    { return Body().Index(value); }
    //: Find the index of a specified value
    
    const StringC& Value(IndexC index) const
    { return Body().Value(index); }
    //: Lookup a value by index
    
    SizeT Size() const
    { return Body().Size(); }
    //: The number of values in the domain
    
    SArray1dIterC<StringC> Iterator() const
    { return Body().Iterator(); }
    //: Get an iterator over the collection of values

    StringC ToString() const
    { return Body().ToString(); }
    //: Get a string representation of the domain
    //!cwiz:author

    bool operator==(const DomainDiscreteC& other) const
    { return Body().operator==(other.Body()); }
    //: Equality operator
    //!cwiz:author

    bool operator!=(const DomainDiscreteC& other) const
    { return !Body().operator==(other.Body()); }
    //: Inequality operator
    //!cwiz:author
    
    UIntT Hash() const
    { return Body().Hash(); }
    //: Hash function based on name

  protected:
    DomainDiscreteC(DomainDiscreteBodyC &bod)
     : RCHandleVC<DomainDiscreteBodyC>(bod)
    {}
    //: Body constructor. 
    
    DomainDiscreteC(const DomainDiscreteBodyC *bod)
     : RCHandleVC<DomainDiscreteBodyC>(bod)
    {}
    //: Body constructor. 
    
    DomainDiscreteBodyC& Body()
    { return static_cast<DomainDiscreteBodyC &>(RCHandleVC<DomainDiscreteBodyC>::Body()); }
    //: Body Access. 
    
    const DomainDiscreteBodyC& Body() const
    { return static_cast<const DomainDiscreteBodyC &>(RCHandleVC<DomainDiscreteBodyC>::Body()); }
    //: Body Access. 
  };

  ostream &operator<<(ostream &s, const DomainDiscreteC &obj);
  
  istream &operator>>(istream &s, DomainDiscreteC &obj);

  BinOStreamC &operator<<(BinOStreamC &s, const DomainDiscreteC &obj);
    
  BinIStreamC &operator>>(BinIStreamC &s, DomainDiscreteC &obj);
  
}

#endif
