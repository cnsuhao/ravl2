# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Tracking/defs.mk"

PACKAGE=Ravl/Image

HEADERS=PointTrack.hh PointTrackModel.hh PointTracker.hh MosaicBuilder.hh \
 MatchPatch.hh ImageTracker.hh ImageMatcher.hh MatchNormalisedCorrelation.hh \
 ForegroundSep.hh TrackingHomog.hh

SOURCES=PointTrack.cc PointTrackModel.cc PointTracker.cc MosaicBuilder.cc \
 ImageTracker.cc ImageMatcher.cc MatchNormalisedCorrelation.cc \
 ForegroundSep.cc TrackingHomog.cc

PLIB=RavlImageProc

LIBDEPS=RavlImageProcTracker.def

EHT= Ravl.API.Images.Tracking.html Ravl.API.Images.Mosaic.html 

TESTEXES=testTracking.cc
#testImageTracker.cc

USESLIBS=RavlImageProc 

PROGLIBS=RavlVideoIO RavlImgIOV4L.opt RavlDPDisplay.opt CSPDriver.opt

