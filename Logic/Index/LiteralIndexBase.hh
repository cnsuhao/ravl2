// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGICLITERALINDEXBASE_HEADER
#define RAVLLOGICLITERALINDEXBASE_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Logic.Index"
//! lib=RavlLogic

#include "Ravl/Logic/Literal.hh"
#include "Ravl/Logic/LiteralIndexElement.hh"
#include "Ravl/Logic/LiteralIndexLeaf.hh"
#include "Ravl/Hash.hh"

namespace RavlLogicN {
  class LiteralIndexFilterBaseBodyC;  
  class LiteralIndexBaseIterC;
  class LiteralIndexLeafBodyIterC;
  
  //! userlevel=Develop
  //: Base class for index access.
  
  class LiteralIndexBaseBodyC
    : public RCBodyVC
  {
  public:
    LiteralIndexBaseBodyC()
      {}
    //: Default constructor.
    
    LiteralIndexLeafC Lookup(const LiteralC &key);
    //: Lookup exact match in index.
    // returns an invalid handle if not found.
    
    LiteralIndexLeafC Insert(const LiteralC &key);
    //: Insert key into index.
    // Returns false if key already exists.
    
    virtual LiteralIndexLeafC NewLeaf(const LiteralC &key);
    //: Generate a new leaf.
    
    bool Del(const LiteralC &key);
    //: Delete key from index.
    // returns true if key existed, false otherwise.
	     
    SizeT Size() const
    { return map.Size(); }
    //: Get the number of elements in the index.

    void Dump(ostream &out,int level = 0);
    //: Dump index in human readable form.
  protected:
    virtual UIntT PickNextTerm(const SArray1dC<bool> &used,const LiteralC &key);
    //: Pick next term to use in the index.
    // used is an array set to true for all the terms already used.
    // 'key' is the key we're updating the index for. <p>
    // The default version of this function just uses terms in numerical order, first
    // to last.  You may want to put a more clever heuristic in here.
    
    HashC<LiteralC,LiteralIndexLeafC> map; // Direct lookup table.
    LiteralIndexElementC root; // Root of tree.
    
    friend class LiteralIndexBaseIterC;
    friend class LiteralIndexFilterBaseBodyC;
    friend class LiteralIndexLeafBodyIterC;
  };
  
  
  //! userlevel=Advanced
  //: Base class for index access.

  class LiteralIndexBaseC
    : public RCHandleC<LiteralIndexBaseBodyC>
  {
  public:
    LiteralIndexBaseC()
      {}
    //: Default constructor.
    // creates an invalid handle.
    
  protected:
    LiteralIndexBaseC(LiteralIndexBaseBodyC &bod)
      : RCHandleC<LiteralIndexBaseBodyC>(bod)
    {}
    //: Body constructor.
    
    LiteralIndexBaseBodyC &Body()
      { return RCHandleC<LiteralIndexBaseBodyC>::Body(); }
    //: Access body.

    const LiteralIndexBaseBodyC &Body() const
      { return RCHandleC<LiteralIndexBaseBodyC>::Body(); }
    //: Access body.
    
  public:
    LiteralIndexLeafC Lookup(const LiteralC &key)
    { return Body().Lookup(key); }
    //: Lookup value associated with the key in the index.
    // returns an invalid handle if not found.
    
    LiteralIndexLeafC Insert(const LiteralC &key)
    { return Body().Insert(key); }
    //: Insert key into index.
    // Returns false if key already exists.
    
    SizeT Size() const
    { return Body().Size(); }
    //: Get the number of elements in the index.
    
    bool Del(const LiteralC &key)
    { return Body().Del(key); }
    //: Delete key from index.
    // returns true if key existed, false otherwise.
    
    void Dump(ostream &out,int level = 0) 
    { Body().Dump(out,level); }
    //: Dump index in human readable form.
    // For debugging only.
    
    friend class LiteralIndexBaseIterC;
    friend class LiteralIndexFilterBaseBodyC;
    friend class LiteralIndexLeafBodyIterC;
                 
  };
}


#endif
