# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Math/Geometry/Projective/1D/defs.mk"

DESCRIPTION=1D Projective Geometry.

PACKAGE=Ravl

# NESTED = all subdirectories which are built before this directory
NESTED = 

#  MAINS = all modules containing the main function separated by space.
MAINS	   = 

# SOURCES = all C modules, not containing main separated by space. The compiled
#   code of these modules is stored in the project library.
SOURCES   = PPoint1d.cc PProjection1d.cc    

# HEADERS = all include files of this project to be exported
HEADERS = PPoint1d.hh  PProjection1d.hh   

# PLIB = the project library ... where the objects will be archived
PLIB	= RavlMath

LIBDEPS = RavlMathProj1d.def

USESLIBS=RavlMath
