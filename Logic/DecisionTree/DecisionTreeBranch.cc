// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! file="Ravl/Logic/DecisionTree/DecisionTreeBranch.cc"

#include "Ravl/Logic/DecisionTreeBranch.hh"

namespace RavlLogicN {

  DecisionTreeBranchBodyC::DecisionTreeBranchBodyC()
  {}
  
  //: Dump node in human readable form,
  
  void DecisionTreeBranchBodyC::Dump(ostream &out,IntT level) const {
    cerr << "DecisionTreeBranchBodyC::Dump(), Abstract method called \n";
  }
  
}
