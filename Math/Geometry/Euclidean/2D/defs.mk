# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Math/Geometry/Euclidean/2D/defs.mk"

PACKAGE=Ravl

HEADERS= LineABC2d.hh Curve2d.hh Curve2dLine.hh Curve2dLineSegment.hh \
 Line2dIter.hh Affine2d.hh Moments2d2.hh LinePP2d.hh Projection2d.hh \
 Point2d.hh

SOURCES= LineABC2d.cc Curve2d.cc Curve2dLine.cc Curve2dLineFit.cc \
 Curve2dLineSegment.cc Line2dIter.cc Affine2d.cc Moments2d2.cc \
 LinePP2d.cc Projection2d.cc Point2d.cc

PLIB=RavlMath

LIBDEPS=RavlMath2D.def

USESLIBS=RavlMath

TESTEXES=testLine2d.cc testGeom2d.cc
