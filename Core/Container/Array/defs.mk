# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Core/Container/Array/defs.mk"

DESCRIPTION=2D Array templates.

MAINS	 = 

SOURCES  = 

PACKAGE=Ravl

HEADERS = Array1d.hh Array1dIter.hh Array1dIter2.hh Array1dIter3.hh \
 Array2d.hh Array2dIter.hh Array2dIter2.hh Array2dIter3.hh

LOCALHEADERS = 

PLIB = RavlCore

LIBDEPS = RavlArray.def

USESLIBS = RavlCore

EXAMPLES = 
#exArray2.cc

TESTEXES = testArray1d.cc testArray2d.cc

EHT=Ravl.Core.Arrays.eht
