# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2004, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

REQUIRES = libehs

PACKAGE = Ravl

HEADERS = HTTPRequest.hh HTTPResponse.hh HTTPServer.hh EHS.hh

SOURCES = HTTPRequest.cc HTTPResponse.cc HTTPServer.cc EHS.cc

PLIB = RavlEHS

USESLIBS = EHS RavlThreads RavlOS RavlCore

PROGLIBS =

TESTEXES = 

AUXDIR = lib/RAVL/libdep
 
AUXFILES = EHS.def

