# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5240 2005-12-06 17:16:50Z plugger $"
#! file="Ravl/Logic/DecisionTree/defs.mk"

PACKAGE=Ravl/Logic

HEADERS=DecisionTreeElement.hh DecisionTreeLeaf.hh  \
 DecisionTreeBase.hh DecisionTree.hh DecisionTreeBranch.hh DecisionTreeBranchBinary.hh \
 DecisionExamples.hh Discriminator.hh \
 SampleLiteral.hh SampleState.hh

#DecisionTreeBranch.hh

SOURCES=DecisionTreeElement.cc DecisionTreeLeaf.cc \
 DecisionTreeBase.cc DecisionTreeBranch.cc DecisionTreeBranchBinary.cc \
 DecisionExamples.cc Discriminator.cc \
 SampleLiteral.cc SampleState.cc

# DecisionTreeBranch.cc

TESTEXES=testDecisionTree.cc

PLIB=RavlLogic

EHT=Ravl.API.Logic.Decision_Tree.html

LIBDEPS=RavlLogicDecisionTree.def

USESLIBS=RavlLogic 


