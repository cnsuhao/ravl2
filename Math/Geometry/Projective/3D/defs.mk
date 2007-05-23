# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
# Makefile 
#! rcsid="$Id$"
#! file="Ravl/Math/Geometry/Projective/3D/defs.mk"

# -----------  Specification of your project -----------------------
DESCRIPTION=3D Projective Geometry.

PACKAGE=Ravl

# NESTED = all subdirectories which are built before this directory
NESTED = 

#  MAINS = all modules containing the main function separated by space.
MAINS	   = 

# SOURCES = all C modules, not containing main separated by space. The compiled
#   code of these modules is stored in the project library.
SOURCES   =  PPointPlane3d.cc  \
             PPoint3d.cc \
             PPlane3d.cc \
             PProjection3d.cc  \
             PPerspective3d.cc \
	     PLinePV3d.cc \
             FitPPlane3d.cc 


# HEADERS = all include files of this project to be exported
HEADERS =    PPointPlane3d.hh   \
             PPoint3d.hh  \
             PPlane3d.hh  \
             PProjection3d.hh   \
             PPerspective3d.hh \
	     PLinePV3d.hh

# PLIB = the project library ... where the objects will be archived
PLIB = RavlMath

LIBDEPS = RavlMathProj3d.def

USESLIBS=RavlMath

# Examples - programs demonstrating using of software in this directory.
EXAMPLES = 

# Tests - program testing runtime consistency of the software
TESTEXES = 

