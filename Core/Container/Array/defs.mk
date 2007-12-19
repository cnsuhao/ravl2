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

HEADERS = Array1d.hh Array1dIter.hh Array1dIter2.hh Array1dIter3.hh Array1dIter4.hh Array1dIter5.hh Array1dIter6.hh Array1dIter7.hh \
 Array2d.hh Array2dIter.hh Array2dIter2.hh Array2dIter3.hh Array2dIter4.hh Array2dIter5.hh Array2dIter6.hh Array2dIter7.hh \
 Array3d.hh Array3dIter.hh Array3dIter2.hh Array3dIter3.hh \
 Array2dSqr2Iter.hh Array2dSqr2Iter2.hh Array2dSqr3Iter.hh  \
 Array2dSqr31Iter2.hh Array2dSqr33Iter2.hh Array2dSqr311Iter3.hh Array2dSqr3111Iter4.hh \
 Array2dSqr3311Iter4.hh Array1dIterR.hh Array2dSqr51Iter2.hh Array2dSqr71Iter2.hh

PLIB = RavlCore

LIBDEPS = RavlArray.def

USESLIBS = RavlCore

EXAMPLES = exArray1.cc exArray2.cc exArray3.cc

TESTEXES = testArray1d.cc testArray2d.cc testArray3d.cc

EHT=Ravl.API.Core.Arrays.html Ravl.API.Core.Arrays.HigherD.html

PROGLIBS= RavlOS
