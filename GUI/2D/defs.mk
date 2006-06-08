# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/GUI/2D/defs.mk"

PACKAGE=Ravl/GUI

HEADERS=Canvas.hh RawZoomCanvas.hh
#Graph1d.hh

SOURCES=Canvas.cc RawCanvas2d.cc RawZoomCanvas.cc
#Graph1d.cc

MAINS=
#exRawZoomCanvas.cc

PLIB=RavlGUI2D

USESLIBS=RavlGUI RavlImage

EXAMPLES= exCanvas.cc exRawZoomCanvas.cc

HTML=canvas_colours.html
