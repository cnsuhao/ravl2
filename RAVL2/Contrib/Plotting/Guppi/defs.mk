# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 6715 2008-04-15 08:07:09Z kier $"
#! file="Ravl/Contrib/Plotting/Guppi/defs.mk"

REQUIRES=libGuppi

ORGANISATION=OmniPerception Ltd.

DONOT_SUPPORT=VCPP

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
