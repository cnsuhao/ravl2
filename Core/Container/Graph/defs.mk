# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
# $Id$
#! rcsid="$Id$"
#! file="Ravl/Core/Container/Graph/defs.mk"

PACKAGE=Ravl

HEADERS=GraphBase.hh Graph.hh GraphNode.hh GraphEdge.hh GraphAdj.hh \
 GraphBaseLinearIter.hh GraphLinearIter.hh GraphBestRoute.hh GraphConnIt.hh \
 GraphBConIt.hh

SOURCES=GraphBase.cc Graph.cc GraphBaseLinearIter.cc  GraphBConIt.cc

PLIB=RavlCore

LIBDEPS=RavlGraph.def

TESTEXES= testGraph.cc

EXAMPLES=exGraph.cc

USESLIBS=RavlCore

EHT=Ravl.Core.Graphs.eht
