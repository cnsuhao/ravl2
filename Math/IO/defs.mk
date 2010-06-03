# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 7583 2010-02-22 13:34:21Z craftit $"
#! file="Ravl/Math/IO/defs.mk"

DESCRIPTION= IO for maths objects.

PACKAGE=Ravl

HEADERS= MathIO.hh

SOURCES= FixedVectorIO.cc FixedPointIO.cc FixedMatrixIO.cc BoundryIO.cc \
 MatrixIO.cc TMatrixIO.cc Geom2dIO.cc

MUSTLINK = MathIO.cc

PLIB= RavlMathIO

USESLIBS = RavlMath RavlIO RavlXMLFactory

