// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/LiteralIndexElement.hh"
#include "Ravl/Logic/LiteralIndexLeaf.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlLogicN {
  
  
  //: Get name for element.
  // usefull for debuging.
  
  StringC LiteralIndexElementBodyC::Name() {
    return StringC("LIElem:") + StringC((UIntT) this);
  }
  

  //: Filter next level in tree.
  // If there's a choice return an iterator otherwise the next branch
  // in the tree is assigned to 'next'.  var is the variable to witch
  // the value of the iterator should be bound.
  LiteralMapIterC<LiteralIndexElementC> LiteralIndexElementBodyC::Filter(const LiteralC &key,LiteralIndexElementC &next,LiteralC &var) {
    ONDEBUG(cerr << "LiteralIndexElementBodyC::Filter(), Called. Key=" << key << " var=" << var <<"\n");
    LiteralMapIterC<LiteralIndexElementC> ret;
    next.Invalidate();
    return ret;
  }
  
  //: Lookup next level in tree.
  // returns true if this level is a leaf and leave next unchanged.
  // if no suitable node is found 'next' is made invalid.
  
  bool LiteralIndexElementBodyC::Lookup(const TupleC &key,LiteralIndexElementC &next) {
    RavlAssertMsg(0,"LiteralIndexElementC::Lookup(), Abstact method called. "); // Abstract method.
    next.Invalidate();
    return false;
  }
  
  //: Insert/Replace element into the node.
  // returns false if element already exists.
  
  bool LiteralIndexElementBodyC::Insert(const TupleC &key,LiteralIndexElementC &next) {
    RavlAssertMsg(0,"LiteralIndexElementC::Insert(), Abstact method called. ");
    // Abstract method.
    next.Invalidate();
    return false;
  }

  //: Dump index in human readable form.
  // For debugging only.
  
  void LiteralIndexElementBodyC::Dump(ostream &out,int level) {
    out << "LiteralIndexElementBodyC::Dump(), Abstract method called. \n";
  }

  //: Access iterator for all branches from this node.
  
  LiteralMapIterC<LiteralIndexElementC> LiteralIndexElementBodyC::Iterator() {
    return LiteralMapIterC<LiteralIndexElementC>();
  }
    
  //: Access iterator for all branches from this node matching filter filt.
 
  LiteralMapIterC<LiteralIndexElementC> LiteralIndexElementBodyC::Filter(const LiteralC &filt) {
    return LiteralMapIterC<LiteralIndexElementC>();
  }

}
