# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
# Makefile 
#! rcsid="$Id: defs.mk 7653 2010-03-09 15:09:51Z ees1wc $"
#! file="Ravl/Math/Geometry/Projective/2D/defs.mk"

# -----------  Specification of your project -----------------------

DESCRIPTION=2D Projective Geometry.

PACKAGE=Ravl

# NESTED = all subdirectories which are built before this directory
NESTED = 

#  MAINS = all modules containing the main function separated by space.
MAINS	   = 

# SOURCES = all C modules, not containing main separated by space. The compiled
#   code of these modules is stored in the project library.
SOURCES   = PPointLine2d.cc PPoint2d.cc PLine2d.cc PLinePP2d.cc \
            PProjection2d.cc PPerspective2d.cc  FundamentalMatrix2d.cc FitPProjection2d.cc

# HEADERS = all include files of this project to be exported
HEADERS = PPointLine2d.hh PPoint2d.hh PLine2d.hh PProjection2d.hh  \
          PPerspective2d.hh FundamentalMatrix2d.hh

# PLIB = the project library ... where the objects will be archived
PLIB = RavlMath

LIBDEPS = RavlMathProj2d.def

USESLIBS=RavlMath

TESTEXES= testFundamentalMatrix2d.cc testProjective2d.cc
