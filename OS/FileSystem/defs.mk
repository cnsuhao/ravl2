# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
# Makefile 
#! rcsid="$Id: defs.mk 5240 2005-12-06 17:16:50Z plugger $"
#! file="Ravl/OS/FileSystem/defs.mk"

# -----------  Specification of your project -----------------------

ANSIFLAG= 

DESCRIPTION = File system interface.

PACKAGE=Ravl/OS

#MAINS = dynLoad.cc

# HEADERS = all include files of this project to be exported
HEADERS =  FilePermission.hh Filename.hh Directory.hh UserInfo.hh \
 FileStream.hh

# SOURCES = all C modules, not containing main separated by space. The compiled
#   code of these modules is stored in the project library.
SOURCES  = FilePermission.cc Filename.cc Directory.cc FileSearch.cc \
 UserInfo.cc FileOwner.cc FileStream.cc


MUSTLINK = 
#SystemML.cc

# PLIB = the project library ... where the objects will be archived
PLIB = RavlOS

LIBDEPS=RavlFileSystem.def

# Uses libraries.
USESLIBS = RavlOS RavlCore

# Libraries needed for programs.
PROGLIBS = RavlIO

# Examples - programs demonstrating using of software in this directory.
EXAMPLES = exFilename.cc
#exDeadLine.cc exChild.cc dynLoad.cc exSerial.cc

# Tests - program testing runtime consistency of the software
TESTEXES = testFileFormat.cc
#testDate.cc exDeadLine.cc testChildProc.cc

EHT=Ravl.API.OS.File_System.eht
