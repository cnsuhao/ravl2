// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGICLITERALINDEX_HEADER
#define RAVLLOGICLITERALINDEX_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! docentry="Ravl.Logic.Index"

#include "Ravl/Logic/LiteralIndexBase.hh"
#include "Ravl/Logic/LiteralIndexLeaf.hh"

namespace RavlLogicN {
   
  template<class DataT> class LiteralIndexIterC;
  
  //! userlevel=Develop
  //: Literal index.
  
  template<class DataT>
  class LiteralIndexBodyC
    : public LiteralIndexBaseBodyC
  {
  public:
    LiteralIndexBodyC()
    {}
    //: Default constructor.
    
  protected:

    virtual LiteralIndexLeafC NewLeaf(const LiteralC &key)
    { return LiteralIndexLeafDataC<DataT>(true,key); }
    //: Generate a new leaf.
    
  public:
    bool Lookup(const LiteralC &key,DataT &val) {
      LiteralIndexLeafC leaf = LiteralIndexBaseBodyC::Lookup(key);
      if(!leaf.IsValid())
	return false;
      LiteralIndexLeafDataC<DataT> t(leaf);
      val = t.Data();
      return true;
    }
    //: Lookup value associated with the key in the index.
    //  if cound copy the value to 'val' and true is return.

    bool Insert(const LiteralC &key,const DataT &data) {
      LiteralIndexLeafDataC<DataT> t(LiteralIndexBaseBodyC::Insert(key));
      RavlAssert(t.IsValid());
      t.Data() = data;
      return true;
    }
    //: Insert data with given key into index.
    // Returns false if key already exists.
    
    DataT &Access(const LiteralC &key) {
      LiteralIndexLeafDataC<DataT> t(LiteralIndexBaseBodyC::Insert(key));
      RavlAssert(t.IsValid());
      return t.Data();
    }
    //: Access data associated with a literal.
    
  };
  
  //! userlevel=Normal
  //! autolink="on"
  //: Literal index.
  // This is an index of 'DataT's based on a Literal key. It maybe queryied directly
  // with 'Lookup' or iterated through for data items matching a pattern with a 
  // 'LiteralIndexFilterC'
  
  template<class DataT>
  class LiteralIndexC
    : public LiteralIndexBaseC
  {
  public:
    LiteralIndexC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    LiteralIndexC(bool)
      : LiteralIndexBaseC(*new LiteralIndexBodyC<DataT>())
      {}
    //: Constructor.
    
  protected:
    LiteralIndexC(LiteralIndexBodyC<DataT> &bod)
      : LiteralIndexBaseC(bod)
    {}
    //: Body constructor.
    
    LiteralIndexBodyC<DataT> &Body()
    { return static_cast<LiteralIndexBodyC<DataT> &>(LiteralIndexBaseC::Body()); }
    //: Access body.

    const LiteralIndexBodyC<DataT> &Body() const
    { return static_cast<const LiteralIndexBodyC<DataT> &>(LiteralIndexBaseC::Body()); }
    //: Access body.
    
  public:
    bool Lookup(const LiteralC &key,DataT &val)
    { return Body().Lookup(key,val); }
    //: Lookup value associated with the key in the index.
    //  if cound copy the value to 'val' and true is return.
    
    bool Insert(const LiteralC &key,const DataT &leaf)
    { return Body().Insert(key,leaf); }
    //: Insert data with given key into index.
    // Returns false if key already exists.


    DataT &Access(const LiteralC &key) 
    { return Body().Access(key); }
    //: Access data associated with a literal.
    
    DataT &operator[](const LiteralC &key)
    { return Body().Access(key); }
    //: Access data associated with a literal.
    
    friend class LiteralIndexIterC<DataT>;
  };
}


#endif
