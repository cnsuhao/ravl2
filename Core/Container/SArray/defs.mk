# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#*********************************************************************
#*********************************************************************
# This is a part of a makefile for C and C++ programs under AMMA project
# $Id$
#! rcsid="$Id$"

# -----------  Specification of your project -----------------------

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
 SArray1d.hh SArr1Iter.hh SArr1Iter2.hh SArr1Iter3.hh SArr1Iter4.hh \
 SArray2d.hh SArr2Iter.hh SArr2Iter2.hh SArr2Iter3.hh 

# SArray3d.hh SArr3Iter.hh SArr3Iter2.hh SArr3Iter3.hh 

#            \
#	  SArr1RangeIter.hh \
#	  SArr2RangeIter.hh \
#	    \
#	  SArr3RangeIter.hh

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
TESTEXES = testSArray1d.cc testSArray2d.cc testSArrIter.cc 
#testSArr3D.cc

# Documentation - html pages
HTML = 

# Documentation - man1 pages on executables
MAN1 = 

# Documentation - man3 pages on libraries
MAN3 =
