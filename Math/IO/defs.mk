# $Id$

DESCRIPTION= IO for maths objects.

PACKAGE=Ravl

HEADERS= MathIO.hh

SOURCES= FixedVectorIO.cc FixedPointIO.cc FixedMatrixIO.cc

MUSTLINK = MathIO.cc

PLIB= RavlMathIO

USESLIBS = RavlMath RavlIO

