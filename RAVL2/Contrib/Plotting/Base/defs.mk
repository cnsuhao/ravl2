# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 6697 2008-04-08 10:07:24Z ees1wc $"
#! file="Ravl/Contrib/Plotting/Base/defs.mk"

REQUIRES=libGuppi

PACKAGE=Ravl/Plot

HEADERS= GraphData2d.hh

SOURCES= GraphData2d.cc

PLIB=RavlPlot

USESLIBS=RavlCore RavlIO
