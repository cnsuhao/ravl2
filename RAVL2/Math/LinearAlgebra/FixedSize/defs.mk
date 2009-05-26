# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Math/LinearAlgebra/FixedSize/defs.mk"

PACKAGE=Ravl

HEADERS= FVector.hh Vector2d.hh Vector3d.hh Vector4d.hh \
        FMatrix.hh Matrix2d.hh Matrix3d.hh Matrix4d.hh \
	FVectorMatrix.hh VectorMatrix2d.hh VectorMatrix3d.hh \
        VectorMatrix4d.hh TFMatrixDecomposition.hh

SOURCES= Vector2d.cc Matrix3d.cc \
        VectorMatrix2d.cc VectorMatrix3d.cc VectorMatrix4d.cc Matrix2d.cc

TESTEXES= testSpecificFMatrix.cc

PLIB=RavlMath

LIBDEPS=RavlFSLinear.def

USESLIBS=RavlMath

