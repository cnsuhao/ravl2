# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2004, Omniperception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 6224 2007-06-27 10:28:24Z craftit $"

REQUIRES = LibGnome libGTK2

ORGANISATION=Omniperception Ltd.

PACKAGE =Ravl/GUI

HEADERS= Gnome.hh

SOURCES= Gnome.cc

PLIB=RavlGUIGnome

EXTERNALLIBS= LibGnome.def

USESLIBS=RavlGUI LibGnome

EXAMPLES=exGnome.cc
