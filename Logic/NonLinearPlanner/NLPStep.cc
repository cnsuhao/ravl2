// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlLogicNLP


#include "Ravl/Logic/NLPStep.hh"

namespace RavlLogicN {

  //: Name of step.
  
  StringC NLPStepC::Name() const {
    return act.Name() + "{" + pre.Name() + " -> " + post.Name() + "}";
  }
  
  
  NLPStepC NLPStepC::ReplaceVars(HashC<LiteralC,LiteralC> &subs) const {
    LiteralC xAct;  // Action id.
    MinTermC xPre;  // Precondition for step.
    MinTermC xPost; // Post condition for step.
    bool change = act.ReplaceVars(subs,xAct);
    change |= pre.ReplaceVars(subs,xPre);
    change |= post.ReplaceVars(subs,xPost);
    return NLPStepC(xAct,xPre,xPost,confidence);
  }
  
}
