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

PLIB=RavlLogic

LIBDEP=RavlLogicDecisionTree.def

USESLIBS=RavlLogic RavlCore


