# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

PACKAGE=Ravl/Logic

HEADERS=DecisionTreeElement.hh DecisionTreeLeaf.hh  \
 DecisionTreeBase.hh DecisionTree.hh DecisionTreeBranchBinary.hh \
 DecisionExamples.hh Discriminator.hh

#DecisionTreeBranch.hh

SOURCES=DecisionTreeElement.cc DecisionTreeLeaf.cc \
 DecisionTreeBase.cc DecisionTreeBranchBinary.cc \
 DecisionExamples.cc Discriminator.cc

# DecisionTreeBranch.cc

TESTEXES=testDecisionTree.cc

PLIB=RavlLogic

LIBDEPS=RavlLogicDecisionTree.def

USESLIBS=RavlLogic


