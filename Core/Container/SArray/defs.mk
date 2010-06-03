# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 4820 2005-03-02 10:07:57Z craftit $"
#! file="Ravl/Core/Container/SArray/defs.mk"

DESCRIPTION=Simple 1D arrays, indexed from zero.

# NESTED = all subdirectories which are built before this directory
NESTED = 

# PACKAGE = a subpath determining the name of the package
PACKAGE = Ravl

#  MAINS = all modules containing the main function separated by space.
MAINS	 = 

# SOURCES = all C modules, not containing main separated by space. The compiled
#   code of these modules is stored in the project library.
SOURCES  = 

# HEADERS = all include files of this project to be exported
HEADERS = SDArray1d.hh \
 SArray1d.hh SArray1dIter.hh SArray1dIter2.hh SArray1dIter3.hh SArray1dIter4.hh SArray1dIter5.hh\
 SArray2d.hh SArray2dIter.hh SArray2dIter2.hh SArray2dIter3.hh \
 SArray3d.hh SArray3dIter.hh SArray3dIter2.hh SArray3dIter3.hh \
 SArray1dIterR.hh

# LOCALHEADERS = all include files of this project used only for compilation
LOCALHEADERS = 

# PLIB = the project library ... where the objects will be archived
PLIB = RavlCore

# Libraries for creating tasks
LIBDEPS = RavlSArr.def

USESLIBS = RavlCore

# Examples - programs demonstrating using of software in this directory.
EXAMPLES = exSArr1.cc

# Tests - program testing runtime consistency of the software
#TESTEXES = exSArrIter.cc 
TESTEXES = testSArray1d.cc testSArray2d.cc testSArray3d.cc
#testSArr3D.cc

# Documentation - html pages
HTML = 

# Documentation - man1 pages on executables
MAN1 = 

# Documentation - man3 pages on libraries
MAN3 =
