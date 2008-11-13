# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2004, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/GUI/LibGlade/defs.mk"

REQUIRES=libglade2 libGTK2

PACKAGE=Ravl/GUI

HEADERS= GladeWidget.hh GladeXML.hh GladeWindow.hh

SOURCES= GladeWidget.cc GladeXML.cc GladeWindow.cc

PLIB= RavlLibGlade

USESLIBS= RavlGUI libglade system

AUXFILES= exlibgladecustommain.glade  exlibgladecustomwidget.glade  exlibglade.glade

AUXDIR=share/RAVL/Glade

EXAMPLES= exLibGlade.cc exLibGladeCustom.cc
