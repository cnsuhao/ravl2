# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Math/Geometry/Euclidean/defs.mk"

PACKAGE=Ravl

NESTED=2D.r 3D.r

HEADERS=FPoint.hh Point2d.hh  Point4d.hh

SOURCES=Point2d.cc

PLIB=RavlMath

LIBDEPS=RavlGeom.def

USESLIBS=RavlMath RavlCore 

