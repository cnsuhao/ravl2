# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5796 2006-08-09 08:59:30Z ees1wc $"
#! file="Ravl/3D/Carve3D/defs.mk"
PACKAGE=Ravl/3D
HEADERS=VoxelSet.hh PointSet.hh SurfacePoint3dArray.hh
SOURCES=VoxelSet.cc PointSet.cc SurfacePoint3dArray.cc
PLIB=Ravl3D
LIBDEPS=RavlCarve3D.def
USESLIBS=RavlCore RavlMath RavlImage # RavlCameraCal

#Unlinked EHT as it no longer seems to be relevant
#EHT=Ravl.API.3D.Carve3D.html
