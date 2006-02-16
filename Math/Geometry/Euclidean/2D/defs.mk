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
 Point2d.hh PointSet2d.hh Polygon2d.hh Circle2d.hh Arc2d.hh Curve2dCircle.hh \
 Curve2dArc.hh HEMesh2d.hh DelaunayTriangulation2d.hh TriMesh2d.hh Conic2d.hh \
 Ellipse2d.hh ScanPolygon2d.hh PolyLine2d.hh

SOURCES= LineABC2d.cc Curve2d.cc Curve2dLine.cc Curve2dLineFit.cc \
 Curve2dLineSegment.cc Line2dIter.cc Affine2d.cc Moments2d2.cc \
 LinePP2d.cc Projection2d.cc Point2d.cc PointSet2d.cc Polygon2d.cc \
 Circle2d.cc FitCircle2d.cc Arc2d.cc Curve2dCircle.cc Curve2dArc.cc \
 FitLineABC2d.cc ConvexHullOfPointSet.cc HEMesh2d.cc DelaunayTriangulation2d.cc \
 TriMesh2d.cc AffineTransformPolygon2d.cc ProjectiveTransformPolygon2d.cc \
 Conic2d.cc Ellipse2d.cc ScanPolygon2d.cc PolyLine2d.cc

PLIB=RavlMath

LIBDEPS=RavlMath2D.def

USESLIBS=RavlMath

PROGLIBS=RavlIO RavlDPDisplay.opt

TESTEXES=testLine2d.cc testGeom2d.cc 

EXAMPLES= exDelaunayTriangulation2d.cc exHEMesh2d.cc
