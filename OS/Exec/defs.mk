# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

PACKAGE=Ravl/OS

HEADERS= OSProcess.hh ChildOSProcess.hh

SOURCES= OSProcess.cc ChildOSProcess.cc ChildOSProcessWait.cc \
 ChildOSProcessStream.cc MailUser.cc

PLIB=RavlOS

USESLIBS=RavlOS RavlCore

LIBDEPS=RavlOSExec.def

TESTEXES= testChildProc.cc

EXAMPLES= exChild.cc
