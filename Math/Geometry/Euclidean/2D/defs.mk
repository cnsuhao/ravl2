# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Math/Geometry/Euclidean/defs.mk"

PACKAGE=Ravl

HEADERS= LineABC2d.hh Curve2d.hh Curve2dLine.hh Curve2dLineSegment.hh

SOURCES= LineABC2d.cc Curve2d.cc Curve2dLine.cc Curve2dLineFit.cc Curve2dLineSegment.cc

PLIB=RavlMath

LIBDEPS=RavlGeom2d.def

USESLIBS=RavlMath RavlCore 
