// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/LiteralIndexBase.hh"
#include "Ravl/Logic/LiteralIndexNode.hh"
#include "Ravl/Logic/Tuple.hh"
#include "Ravl/Logic/Unify.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlLogicN {

  //: Lookup value associated with the key in the index.
  // return an invalid handle if not found.
  
  LiteralIndexLeafC LiteralIndexBaseBodyC::Lookup(const LiteralC &key) {
    LiteralIndexLeafC ret;
    map.Lookup(key,ret);
    return ret; // If the lookup didn't work 'ret' will be invalid.
#if 0
    // Didn't work, so search through tree.   
    LiteralIndexElementC place = root;
    while(place.IsValid()) {
      if(place.Lookup(key,place)) 
	return LiteralIndexLeafC(place);
    }
    return ret;
#endif
  }

  //: Generate a new leaf.
  
  LiteralIndexLeafC LiteralIndexBaseBodyC::NewLeaf(const LiteralC &key) {
    RavlAssertMsg(0,"ERROR: Default routine not overriden. ");
    return LiteralIndexLeafC(key);
  }

  //: Pick next term to use in the index.
  // used is an array set to true for all the terms already used.
  // 'key' is the key we're updating the index for.
  
  UIntT LiteralIndexBaseBodyC::PickNextTerm(const SArray1dC<bool> &used,const LiteralC &key) {
    for(SArray1dIterC<bool> it(used);it ;it++) {
      if(*it) 
	continue;
      return it.Index().V();
    }
    cerr << "Used:" << used << "\n";
    RavlAssertMsg(0,"LiteralIndexBaseBodyC::PickNextTerm(), I'm confused! Out of terms to index with. "); 
    return 0;
  }
  
  //: Insert key into index.
  // Returns false if key already exists.
  
  LiteralIndexLeafC  LiteralIndexBaseBodyC::Insert(const LiteralC &key) {
    ONDEBUG(cerr << "LiteralIndexBaseBodyC::Insert() Key=" << key.Name() << "\n");
    TupleC tuple(key);
    if(!tuple.IsValid()) {
      LiteralIndexLeafC &elem = map[key];
      if(!elem.IsValid())
	elem = NewLeaf(key);
      RavlAssert(elem.IsValid());
      return elem;
    }
    // Do a quick check to see if its here already.
    LiteralIndexLeafC elem;
    if(map.Lookup(key,elem))
      return elem;
    
    // There's no identical so add one.
    
    SArray1dC<bool> used(tuple.Arity()); // Set of used index's in tuple.
    used.Fill(false);
    
    LiteralIndexElementC last,place;
    place = root;
    do {
      ONDEBUG(cerr << "LIBB:Insert(), Inital Place=" << place.Name() << "\n");
      while(place.IsValid()) {
	LiteralIndexNodeC lin(place);
	if(!lin.IsValid()) 
	  break; // Its a leaf...
	used[lin.Term()] = true; // Mark as used.
	last = place;
	place.Lookup(tuple,place);
      }
      if(!place.IsValid()) { // No leaf in the way, just add a new one.
	LiteralIndexLeafC lil = NewLeaf(key);
	RavlAssert(lil.IsValid());
	map[key] = lil; // Put it in the map as well.
	if(last.IsValid())
	  last.Insert(tuple,lil);
	else
	  root = lil;
	return lil;
      }
      // There's a leaf that doesn't match the new key in the tree.
      ONDEBUG(cerr << "LIBB:Insert(), Leaf Place=" << place.Name() << "\n");
      LiteralIndexLeafC lil(place);
      RavlAssert(lil.IsValid()); 
      // Is the leaf the one we want to insert ?
      if(lil.Key() == key) {
	ONDEBUG(cerr << "Matching key found. Key=" << key.Name() << "\n");
	return lil; // Leaf has the correct key, return it.
      }
      // We have to add a new node.
      ONDEBUG(cerr << "Adding new node for key " << key.Name() << "\n");
      // Find a term to index on.
      UIntT nInd = PickNextTerm(used,key);
      RavlAssert(!used[nInd]); // Check its sane.
      
      // Creat new branch in the tree.
      LiteralIndexNodeC newNode(nInd);
      if(!last.IsValid())
	root = newNode;
      else
	last.Insert(tuple,newNode); // Replace old leaf with new node.
      // Put the old leaf into the new branch.
      newNode.Insert(TupleC(lil.Key()),place);
      // Go around again and try and add a leaf to the new node.
      place = newNode;
    } while(1);
    RavlAssertMsg(0,"Should never get here. ");
    //: Should never get this far.
    return LiteralIndexLeafC();
  }
  
  //: Delete key from index.
  // returns true if key existed, false otherwise.
  
  bool LiteralIndexBaseBodyC::Del(const LiteralC &key) {
    RavlAssertMsg(0,"Not implemented. ");
    return false;
  }

  //: Dump index in human readable form.
  
  void LiteralIndexBaseBodyC::Dump(ostream &out,int level) {
    out << Indent(level) << "IndexBase:" << ((void *) this) << " \n";
    for(HashIterC<LiteralC,LiteralIndexLeafC> it(map);it;it++) {
      TupleC tup(it.Key());
      if(tup.IsValid())
	continue;
      //out << Indent(level+1) << "Literal " << it.Key().Name() << " \n";
      it.Data().Dump(out,level+2);
    }
    if(root.IsValid())
      root.Dump(out,level+1);
  }
  
}
