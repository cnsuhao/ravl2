# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
PACKAGE=Ravl/3D
HEADERS=VoxelSet.hh PointSet.hh
SOURCES=VoxelSet.cc PointSet.cc
PLIB=Ravl3D
LIBDEPS=RavlCarve3D.def
USESLIBS=RavlCore RavlMath RavlImage RavlCameraCal
EHT=Ravl.3D.Carve3D.html
