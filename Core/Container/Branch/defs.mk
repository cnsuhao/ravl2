# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5240 2005-12-06 17:16:50Z plugger $"
#! file="Ravl/Core/Container/Branch/defs.mk"

PACKAGE=Ravl

HEADERS=BLink.hh BList.hh BListIter.hh BHash.hh BHashIter.hh BStack.hh \
 BDAGraph.hh    BGraphEdgeIter.hh  BGraphBase.hh  \
 BGraph.hh      BGraphLinearIter.hh BGraphBaseIter.hh  BGraphNodeIter.hh \
 BGraphEdge.hh  BGraphNode.hh

SOURCES=BGraphBase.cc BGraphBaseIter.cc BGraphLinearIter.cc

PLIB=RavlCore

TESTEXES= testBGraph.cc testBranch.cc

EHT= Ravl.API.Core.Branch.html

USESLIBS=RavlCore
