# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

PACKAGE = Ravl/Motion

MAINS = exLMSOptic.cc
#exMultiScale.cc  exLMSOptic.cc
# #exLMSRegion.cc  testim.cc

SOURCES = LMSOpticFlow.cc 
#MultiScaleMotion.cc

HEADERS = LMSOpticFlow.hh 
#LMSRegionMatch.hh 
#MultiScaleMotion.hh

PLIB = LMSMotion

USESLIBS = RavlImageIO RavlDPDisplay Auto

EXAMPLES = 
#exLMSOptic.cc exLMSRegion.cc exMultiScale.cc

EHT = 
#Image.Motion_Estimation.LMS_Gradient.eht
