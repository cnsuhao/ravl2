// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGICLITERALINDEXLEAFITER_HEADER
#define RAVLLOGICLITERALINDEXLEAFITER_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Logic.Index"
//! lib=RavlLogic
//! file="Ravl/Logic/Index/LiteralIndexLeafIter.hh"

#include "Ravl/Logic/LiteralIter.hh"
#include "Ravl/Logic/LiteralIndex.hh"
#include "Ravl/Logic/LiteralMapIter.hh"
#include "Ravl/HashIter.hh"

namespace RavlLogicN {

  //! userlevel=Develop
  //: Literal Index leaf iterator.
  // This class is used by LiteralIndexFilterBaseC to iterate through an
  // index as if it was a node in the index tree. This is when the filter
  // is just a simple variable to bind it to every key found in the
  // index.
  
  class LiteralIndexLeafBodyIterC 
    : public LiteralMapIterBodyC<LiteralIndexElementC>
  {
  public:
    LiteralIndexLeafBodyIterC()
    {}
    //: Default constructor
    
    LiteralIndexLeafBodyIterC(const LiteralIndexBaseC &ind);
    //: Constructor

    virtual bool First()
      { return hit.First(); }
    //: Goto first element.
    
    virtual bool Next()
    { return hit.Next(); }
    //: Goto next element.
    // returns true if its valid.
    
    virtual bool IsElm() const 
    { return hit.IsElm(); }
    //: At a valid element ?
    
    virtual LiteralC Data()
    { return hit.Key(); }
    //: Get key for current item.
    
    virtual LiteralIndexElementC &MappedData()
    { return hit.Data(); }
    //: Access data.
    
    virtual const LiteralIndexElementC &MappedData() const
    { return hit.Data(); }
    //: Access data.

    
  protected:
    void Dummy();
    // Dummy function to give the compiler
    // a hint about where it can generate code.
    
    HashIterC<LiteralC,LiteralIndexLeafC>  hit;
  };


  //! userlevel=Advanced
  //: Literal Index leaf iterator.
  // This class is used by LiteralIndexFilterBaseC to iterate through an
  // index as if it was a node in the index tree. This is when the filter
  // is just a simple variable to bind it to every key found in the
  // index.
  
  class LiteralIndexLeafIterC 
    : public LiteralMapIterC<LiteralIndexElementC>
  {
  public:
    LiteralIndexLeafIterC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    LiteralIndexLeafIterC(const LiteralIndexBaseC &ind);
    //: Constructor.
    
  };
}
#endif
