// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! file="Ravl/Logic/Index/LiteralIndexNode.cc"

#include "Ravl/Logic/LiteralIndexNode.hh"
#include "Ravl/Logic/LiteralIndexFilter.hh"
#include "Ravl/Logic/Tuple.hh"
#include "Ravl/HashIter.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlLogicN {
  
  //: Get name for element.
  // usefull for debuging.
  
  StringC LiteralIndexNodeBodyC::Name() {
    return StringC("LINode:") + StringC((UIntT) this);
  }
  
  //: Lookup next level in tree.
  // returns true if this level is a leaf and leave next unchanged.
  // if no suitable node is found 'next' is made invalid.
  
  bool LiteralIndexNodeBodyC::Lookup(const TupleC &tuple,LiteralIndexElementC &next) {
    if(term >= tuple.Arity()) {
      next = none;
      return false;
    }
    const LiteralC &subKey = tuple[term];
    RavlAssert(subKey.IsValid());
    if(!index.Lookup(subKey,next))
      next.Invalidate();
    return false;
  }
  
  //: Filter next level in tree.
  // If there's a choice return an iterator otherwise the next branch
  // in the tree is assigned to 'next'.  var is the variable to witch
  // the value of the iterator should be bound.
  LiteralMapIterC<LiteralIndexElementC> LiteralIndexNodeBodyC::Filter(const LiteralC &key,LiteralIndexElementC &next,LiteralC &var) {
    ONDEBUG(cerr << "LiteralIndexNodeBodyC::Filter(), Called Key:" << key << "  Var="  << var << "\n");
    TupleC tup(key);
    RavlAssert(tup.IsValid());
    const LiteralC &subkey = tup[term];
    if(subkey.IsGrounded()) {
      // There are no variables in the sub-key so we can just do 
      // a lookup.
      if(!index.Lookup(subkey,next))
	next.Invalidate(); // The lookup failed.
      return LiteralMapIterC<LiteralIndexElementC>();
    }
    var = subkey;
    // Return an iterator through possible sub keys.
    return LiteralIndexFilterC<LiteralIndexElementC>(index,subkey);
  }

  //: Insert/Replace element into the node.
  // returns false if element already exists.
  
  bool LiteralIndexNodeBodyC::Insert(const TupleC &key,LiteralIndexElementC &next) {
    RavlAssert(key.IsValid());
    if(term >= key.Arity()) {
      none = next;
      return true;
    }
    index[key[term]] = next;
    return true;
  }

  //: Dump index in human readable form.
  // For debugging only.
  
  void LiteralIndexNodeBodyC::Dump(ostream &out,int level) {
    out << Indent(level) <<"LiteralIndexNodeC Term=" << term <<"\n";      
    index.Dump(out,level+2);
    if(none.IsValid()) {
      out << Indent(level) <<"None:\n";
      none.Dump(out,level+2);
    }
  }

}
