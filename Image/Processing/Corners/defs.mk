# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Corners/defs.mk"

PACKAGE=Ravl/Image

HEADERS=Corner.hh CornerDetector.hh CornerDetectorHarris.hh

SOURCES=Corner.cc CornerDetector.cc CornerDetectorHarris.cc

PLIB=RavlImageProc

LIBDEPS=RavlImageCorner.def

USESLIBS=RavlImageProc

EXAMPLES= exCorner.cc

EHT= Ravl.Images.Corner_Detection.html

PROGLIBS=RavlImageIO RavlDPDisplay
#  RavlImgIOV4L
