# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Motion/LMSGradient/defs.mk"

PACKAGE = Ravl/Image

MAINS = exLMSMultiScale.cc

SOURCES = LMSOpticFlow.cc LMSMultiScaleMotion.cc LMSRegionMotion.cc

HEADERS = LMSOpticFlow.hh LMSMultiScaleMotion.hh LMSRegionMotion.hh

LOCALHEADERS = LMSRegressionEngine.hh

PLIB = RavlImageProc

LIBDEPS=RavlImageLMSMotion.def

USESLIBS = RavlCore RavlIO RavlImage RavlImageProc RavlMath

PROGLIBS = RavlImageIO RavlDPDisplay.opt RavlExtImgIO

EXAMPLES = exLMSOptic.cc exLMSMultiScale.cc exLMSRegionMotion.cc

#TESTEXES = testLMSOptic.cc
