// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! file="Ravl/Logic/Index/LiteralIndexFilterBase.cc"

#include "Ravl/Logic/LiteralIndexFilterBase.hh"
#include "Ravl/Logic/Unify.hh"
#include "Ravl/Logic/LiteralIndexIter.hh"
#include "Ravl/Logic/LiteralIndexLeafIter.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlLogicN {

  //: Construct a new filter.
  
  LiteralIndexFilterBaseBodyC::LiteralIndexFilterBaseBodyC(const LiteralIndexBaseC &nindex,const LiteralC &nfilter) 
    : binds(true),
      filter(nfilter),
      index(nindex)
  { 
    ONDEBUG(cerr << "LiteralIndexFilterBaseBodyC::LiteralIndexFilterBaseBodyC(), Called. Filter [" << nfilter << "]\n");
    First(); 
  }
  
  //: Goto first data element.
  // returns true if next element is valid.
  
  bool LiteralIndexFilterBaseBodyC::First() {
    RavlAssert(filter.IsValid());
    RavlAssert(index.IsValid());
    stack.Empty();
    binds.Empty();
    ONDEBUG(cerr << "LiteralIndexFilterBaseBodyC::First(), Filter=" << filter <<" IsGrounded=" << filter.IsGrounded() << "\n");
    IntT bindLoop = 0;

    // Filtering with a simple variable ?
    while(filter.IsVariable()) {
      LiteralC newUn;
      // See if filter is bound to anything.
      if(!binds.Resolve(filter,newUn) || bindLoop > 1000) {
	if(bindLoop > 1000) {
	  // FIXME:- Check more intelligently for a loop. with a set of visited variables ?
	  // This shouldn't happen, but issue a warning and make at a guess at what we should do.
	  cerr << "LiteralIndexFilterBaseBodyC::First(), ERROR: Probably a bind loop detected. Iterating all values. \n";
	  RavlAssert(0); // In debug mode flag a problem.
	}
	// We're filtering on a unbound variable.
	ONDEBUG(cerr << "LiteralIndexFilterBaseBodyC::First(), Filter on var. \n");
	LiteralIndexLeafIterC it(index); // Just iterate through the index.
	stack.Push(LiteralIndexFilterChoicePointC(index.Body().root,binds.Mark(),filter,(LiteralMapIterC<LiteralIndexElementC> &) it));
	if(it) {
	  at = it.MappedData();
	  ONDEBUG(cerr << "LiteralIndexFilterBaseBodyC::First(), Filter on var, solutions found. \n");
	  return true;
	}
	ONDEBUG(cerr << "LiteralIndexFilterBaseBodyC::First(), Filter on var, no solutions. \n");
	return false; // No values to iteratate through!
      }
      filter = newUn; // Replace filter with bound value.
      bindLoop++; // Increment loop detection counter.
    }
    
    // Check if the operation is trivial.
    if(filter.IsGrounded()) {
      at = index.Lookup(filter); 
      ONDEBUG(cerr << "LiteralIndexFilterBaseBodyC::First(), Grounded filter [" << filter << "], just doing a lookup. \n");
      return at.IsValid();
    }
    // Setup for Next().
    ONDEBUG(cerr << "LiteralIndexFilterBaseBodyC::First(), Setup filter on [" << filter << "] \n");
    // Find first valid solution.
    if(ExploreMatches(index.Body().root))
      return true;
    return Next();
  }
  
  
  //: Expore matches.
  
  bool LiteralIndexFilterBaseBodyC::ExploreMatches(LiteralIndexElementC place) {
    // Follow up on rest of args.
    LiteralIndexElementC next; 
    LiteralMapIterC<LiteralIndexElementC> filterIter;
    LiteralC nextvar; // Holder for next variable to bind if there is one.
    while(place.IsValid()) {
      ONDEBUG(cerr << "LiteralIndexFilterBaseBodyC::ExploreMatches(), Filtering. \n");
      filterIter = place.Filter(filter,next,nextvar);
      if(filterIter.IsValid()) {
	// We have a choice...
	if(filterIter.IsElm()) {
	  stack.Push(LiteralIndexFilterChoicePointC(place,binds.Mark(),nextvar,filterIter));
	  place = filterIter.MappedData();
	  RavlAssert(nextvar.IsValid());
	  binds.Bind(nextvar,filterIter.Data());
	  continue;
	}
      }
      if(!next.IsValid()) {
	// Either this is a deadend or we've found a solution.
	at = place;
	if(at.IsValid()) {
	  ONDEBUG(cerr << "LiteralIndexFilterBaseBodyC::ExploreMatches(), Checking match between " << filter << " and " << at.Key() << " \n");
	  // We've got a leaf!
	  if(Unify(filter,at.Key(),binds)) {
	    ONDEBUG(cerr << "LiteralIndexFilterBaseBodyC::ExploreMatches(), Found match! \n");
	    return true; 
	  }
	}
      }
      place = next;
    }
    ONDEBUG(cerr << "LiteralIndexFilterBaseBodyC::ExploreMatches(), Out of choices, have to backtrack. \n");
    return false;
  }
  

  //: Goto next data element.
  // returns true if next element is valid.
  
  bool LiteralIndexFilterBaseBodyC::Next() {
    ONDEBUG(cerr << "LiteralIndexFilterBaseBodyC::Next(), Called. Filter : '" << filter << "' \n");
    while(!stack.IsEmpty()) {
      // Back track.
      binds.Undo(stack.Top().BindMark());
      if(!stack.Top().Iter().IsValid()) { // Reached init
	stack.DelTop(); // Empty stack.
	break; // Leave.
      }
      if(!stack.Top().Iter().Next()) {
	stack.DelTop(); // Backup some more.
	continue;
      }
      // Bind new value to var. (Var maybe null for the root node.)
      RavlAssert(stack.Top().Iter()); // Next should have returns false if this isn't true.
      LiteralC &var =stack.Top().Var();
      if(var.IsValid()) {
	ONDEBUG(cerr << "LiteralIndexFilterBaseBodyC::Next(), Binding " << var << " to " << stack.Top().Iter().Data() << " \n");
	binds.Bind(var,stack.Top().Iter().Data());
      }
      if(ExploreMatches(stack.Top().Iter().MappedData()))
	return true;
    }
    ONDEBUG(cerr << "LiteralIndexFilterBaseBodyC::Next(), Failed to find solution. \n");
    at.Invalidate();
    return false;
  }
  
  
}
