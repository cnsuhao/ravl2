# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Filters/defs.mk"

PACKAGE=Ravl/Image

MAINS= doThinPlateWarp.cc 

HEADERS=  WarpScale.hh WarpAffine.hh WarpProjective.hh \
  WarpThinPlateSpline.hh WarpMesh2d.hh WarpScale2d.hh

SOURCES=  WarpThinPlateSpline.cc WarpMesh2d.cc

LIBDEPS=RavlImageWarp.def

PLIB=RavlImageProc

USESLIBS=RavlImageProc

PROGLIBS=RavlIO RavlImageIO RavlExtImgIO RavlOSIO RavlOptimise  RavlDPDisplay.opt

EHT=  Ravl.API.Images.Warping.html

TESTEXES = testWarp.cc

