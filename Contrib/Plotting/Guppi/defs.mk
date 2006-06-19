# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Contrib/Plotting/Guppi/defs.mk"

ORGANISATION=OmniPerception Ltd.

PACKAGE=Ravl/Plot

HEADERS=GuppiTypes.hh GuppiHeaders.hh GuppiElement.hh GuppiGroup.hh GuppiCanvas.hh \
 GuppiScalarSequence.hh GuppiLineGraph.hh GuppiGraph.hh

SOURCES=GuppiElement.cc GuppiGroup.cc GuppiCanvas.cc GuppiScalarSequence.cc \
 GuppiLineGraph.cc GuppiGraph.cc GuppiInit.cc

PLIB=RavlGuppi

USESLIBS=RavlPlot RavlGUI Guppi

EXAMPLES=exGuppi.cc

AUXDIR=lib/RAVL/libdep

AUXFILES=Guppi.def
