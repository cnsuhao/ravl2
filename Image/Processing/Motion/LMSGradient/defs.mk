# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

PACKAGE = Ravl/Image

MAINS = exLMSOptic.cc exLMSMultiScale.cc
# #exLMSRegion.cc  testim.cc

SOURCES = LMSOpticFlow.cc LMSMultiScaleMotion.cc

HEADERS = LMSOpticFlow.hh LMSMultiScaleMotion.hh

#LMSRegionMatch.hh 

PLIB = LMSMotion

USESLIBS = RavlImageIO Auto

PROGLIBS = RavlDPDisplay

EXAMPLES = 
#exLMSOptic.cc exLMSRegion.cc exMultiScale.cc

EHT = 
#Image.Motion_Estimation.LMS_Gradient.eht
