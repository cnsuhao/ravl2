# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

PACKAGE=Ravl

HEADERS = PrimitiveBinaryPolynomial.hh SobolSequence.hh \
 CircleIter.hh PermutationIter.hh CombinationIter.hh \
 SquareIter.hh

SOURCES= PrimitiveBinaryPolynomial.cc SobolSequence.cc \
  CircleIter.cc SquareIter.cc

TESTEXES = testCircleIter.cc testCombinationIter.cc  

EXAMPLES = exPrimiteBinaryPolynomial.cc testSquareIterFill.cc

PLIB=RavlMath

LIBDEPS=RavlMathSequence.def

USESLIBS=RavlMath

PROGLIBS=RavlImage RavlImageIO

EHT=Ravl.Math.Sequences.html