// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! file="Ravl/Logic/Base/LiteralIO.cc"

#include "Ravl/Logic/Literal.hh"
#include "Ravl/Logic/LiteralIO.hh"
#include "Ravl/Stack.hh"
#include "Ravl/Logic/Tuple.hh"
#include "Ravl/Logic/NamedVar.hh"
#include "Ravl/Logic/NamedLiteral.hh"
#include "Ravl/DList.hh"
#include "Ravl/Logic/State.hh"

namespace RavlLogicN {

  //! userlevel=Normal
  //: Parse error.
  
  class ExceptionParseErrorC 
    : public ExceptionC
  {
  public:
    ExceptionParseErrorC(const char *msg)
      : ExceptionC(msg)
    {}
    //: Constructor.
    
    ExceptionParseErrorC(const char *ntext,bool copy)
      : ExceptionC(ntext,copy)
    {}
    //: Constructor.
    // if copy is true, make a copy of ntext.

  };
  
  //: Load data from filename into state.
  
  bool LoadState(const StringC &filename,StateC &state,ContextC &context) {
    IStreamC is(filename);
    if(!is)
      return false;
    return LoadState(is,state,context);
  }
  
  bool LoadState(IStreamC &is,StateC &state,ContextC &loadContext) {
    StackC<DListC<LiteralC> > context;
    int ln = 0;
    try {
      while(!is.IsEndOfStream()) { // Any more characters.
	char let = is.GetChar();
	bool var = false;
	switch(let) {
	case '(': { // Open tuple
	  DListC<LiteralC> lits;
	  context.Push(lits);	    
	} break;
	case ')': { // Close tuple
	  if(context.IsEmpty()) {
	    cerr << "ERROR: Parse error at line " << ln << ", unmatched ')' found. \n";
	    throw ExceptionParseErrorC("Unexpected ')' found. ");
	  }
	  int n = context.Top().Size();
	  TupleC tup(n);
	  int i = 0;
	  for(DLIterC<LiteralC> it(context.Top());it;it++,i++)
	    tup.SetArg(i,*it);
	  context.DelTop();
	  if(!context.IsEmpty())
	    context.Top().InsLast(tup);
	  else
	    state.Tell(tup);
	} break;
	case ';': // Comment until end of line.
	  is.SkipTo('\n');
	  // Fall through.
	case '\n':
	  ln++; // Count lines.
	case '\r':
	case '\t':
	case ' ':
	  break; // Ignore whitespace.
	case '#':
	case '$':
	  break; // Ignore these characters silently for now.
	case '@':
	case '~':
	case '!':
	case '¬':
	case '{':
	case '}':
	case '[':
	case ']':
	case '^':
	case '*':
	case '%':
	case '£':
	case '\'':
	case '`':
	case '+':
	case ':':
	case '>':
 	case '<':
 	case '.':
 	case ',':
 	case '\\':
 	case '/':
 	case '|':
 	case '=':
	  cerr << "WARNING: Illegal character '" << let << "' found in stream on line " << ln << ". \n";
 	  break;
	case '"': { // String constant.
	  StringC val = is.ClipTo('"');
	  // FIXME:- If the string constant contains new lines, we'll loose our line number count.
	  
	  LiteralC lit;
	  if(!loadContext.Lookup(val,lit))
	    lit = NamedLiteralC(val);
	  if(!context.IsEmpty())
	    context.Top().InsLast(lit);
	  else
	    state.Tell(lit);
	} break;
	case '?': // Variable marker.
	  var = true;
	  // Fall through.
	default: { // Constant
	  StringC x(let);
	  x += is.ClipWord(" \t\n\r()\\/:;+<>{}[]|=%*^.,£#$@!~¬");
	  // Check for numbers ?
	  LiteralC lit;
	  if(!loadContext.Lookup(x,lit)) {
	    if(var)
	      lit = NamedVarC(x);
	    else
	      lit = NamedLiteralC(x);
	  } else {
	    if(var && !lit.IsVariable())
	      throw ExceptionParseErrorC("Conflicting literal variable/literal types.");
	  }
	  if(!context.IsEmpty())
	    context.Top().InsLast(lit);
	  else
	    state.Tell(lit);
	  } break;
	}
      }
    } catch(ExceptionEndOfStreamC &eos) {
    } catch(ExceptionParseErrorC &eos) {
      return false;
    } 
    
    if(!context.IsEmpty()) {
      cerr << "Unexpected end of file. \n";
      return false;
    }
    return true;
  }

  //: Save data to file from state.
  
  bool SaveState(const StringC &filename,StateC &state) {
    OStreamC os(filename);
    return SaveState(os,state);
  }

  //: Save data into stream.
  
  bool SaveState(OStreamC &os,StateC &state) {
    if(!os)
      return false;
    state.Dump(os);
    return true;
  }
  
  
  
}
