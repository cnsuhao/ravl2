# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
PACKAGE=Ravl

HEADERS= FVector.hh Vector2d.hh Vector3d.hh Vector4d.hh \
        FMatrix.hh Matrix2d.hh Matrix3d.hh Matrix4d.hh

SOURCES= Vector2d.cc Matrix3d.cc

PLIB=RavlMath

LIBDEPS=RavlFSLinear.def

USESLIBS=RavlMath

