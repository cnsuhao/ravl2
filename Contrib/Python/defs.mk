# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2004, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5518 2006-06-05 18:44:47Z craftit $"

REQUIRES = LibPython

PACKAGE = Ravl

HEADERS = Python.hh PythonObject.hh

SOURCES = Python.cc PythonObject.cc

PLIB = RavlPython

USESLIBS = RavlOS RavlCore RavlThreads Python 

PROGLIBS =  

TESTEXES = 

EXAMPLES = exPython.cc exPythonThreaded.cc

AUXDIR = lib/RAVL/libdep

AUXFILES = Python.def
