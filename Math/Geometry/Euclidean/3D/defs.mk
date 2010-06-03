# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 6535 2008-02-01 13:57:33Z craftit $"
#! file="Ravl/Math/Geometry/Euclidean/3D/defs.mk"

PACKAGE=Ravl

HEADERS= LinePP3d.hh  LinePV3d.hh  PlaneABCD3d.hh  PlanePVV3d.hh Point3d.hh \
 Quatern3d.hh RigidTransform3d.hh EulerAngle.hh AxisAngle.hh PointSet3d.hh \
 HEMesh3d.hh Affine3d.hh

SOURCES= LinePP3d.cc  LinePV3d.cc  PlaneABCD3d.cc  PlanePVV3d.cc \
 Quatern3d.cc RigidTransform3d.cc EulerAngle.cc AxisAngle.cc PointSet3d.cc \
 HEMesh3d.cc Affine3d.cc FitPlaneABCD3d.cc FitPlanePVV3d.cc

PLIB=RavlMath

LIBDEPS=RavlMath3D.def

USESLIBS=RavlMath

TESTEXES = testGeom3d.cc


