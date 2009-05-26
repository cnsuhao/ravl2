# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2006, OmniPerception Ltd
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here

SUPPORT_ONLY=VCPP

REQUIRES = LibDirectShow

PACKAGE = Ravl/Image

HEADERS = FileFormatDirectShowRGB.hh WindowsMediaConverter.hh

SOURCES = FileFormatDirectShowRGB.cc WindowsMediaConverter.cc

PLIB = RavlDirectShow

USESLIBS = RavlCore RavlIO RavlOS RavlImage LibDirectShow

PROGLIBS =  

TESTEXES = 

EXAMPLES = 

AUXDIR = lib/RAVL/libdep
 
AUXFILES = LibDirectShow.def
