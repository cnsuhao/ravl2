# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, Charles Galambos
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Logic/Agent/defs.mk"

PACKAGE=Ravl/Logic

HEADERS=ActiveBlackboard.hh

SOURCES=ActiveBlackboard.cc

PLIB=RavlLogicAgent

USESLIBS=RavlLogic RavlDPMT

TESTEXES= testActiveBlackboard.cc
