# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2005, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/CompVision/ActiveAppearanceModels/defs.mk"

ORGANISATION=OmniPerception Ltd.

DESCRIPTION = Active appearance models

PACKAGE = Ravl/Image

DONOT_SUPPORT = arm

MAINS = aamTestApp.cc aamBuildShapeModel.cc aamBuildAppearanceModel.cc aamBuildActiveAppearanceModel.cc aamCombineActiveAppearanceModel.cc aamViewShapeModel.cc aamAppearance2xml.cc

HEADERS = AAMAppearance.hh AAMShapeModel.hh AAMAppearanceModel.hh AAMActiveAppearanceModel.hh \
 AAMAffineShapeModel.hh AAMScaleRotationShapeModel.hh AAMSampleStream.hh \
 AAMAppearanceUtil.hh

SOURCES = AAMAppearance.cc AAMShapeModel.cc AAMAppearanceModel.cc AAMActiveAppearanceModel.cc \
 AAMActiveAppearanceModelsIO.cc  AAMAffineShapeModel.cc AAMScaleRotationShapeModel.cc \
 AAMSampleStream.cc AAMAppearanceUtil.cc

MUSTLINK = AAMActiveAppearanceModelMustLink.cc

PLIB = RavlAAM

USESLIBS=  RavlCore RavlImageProc  RavlMath RavlOS RavlPatternRec RavlOptimise RavlIO 
PROGLIBS = RavlImageIO RavlMathIO RavlDPDisplay.opt RavlGUI RavlGUI2D

EHT = AAM.html
