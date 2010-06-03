# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 7289 2009-10-01 10:07:21Z cyberplug $"
#! file="Ravl/OS/Exec/defs.mk"

PACKAGE=Ravl/OS

HEADERS= OSProcess.hh ChildOSProcess.hh CPUInfo.hh

SOURCES= OSProcess.cc ChildOSProcess.cc ChildOSProcessWait.cc \
 ChildOSProcessStream.cc MailUser.cc FileUser.cc CPUInfo.cc

PLIB=RavlOS

USESLIBS=RavlOS RavlCore

LIBDEPS=RavlOSExec.def

TESTEXES= testChildProc.cc

EXAMPLES= exChild.cc

EHT=Ravl.API.OS.Exec.html
