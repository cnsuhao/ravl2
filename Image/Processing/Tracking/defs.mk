# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Tracking/defs.mk"

PACKAGE=Ravl/Image

HEADERS=PointTrack.hh PointTrackModel.hh PointTracker.hh

SOURCES=PointTrack.cc PointTrackModel.cc PointTracker.cc

PLIB=RavlImageProc

LIBDEPS=RavlImageProcTracker.def

MAINS=tracker.cc

EHT= Ravl.Images.Tracking.html

EXAMPLES=tracker.cc

USESLIBS=RavlImage RavlImageProc

PROGLIBS=RavlDPDisplay RavlVideoIO RavlImageIO RavlImgIOV4L

