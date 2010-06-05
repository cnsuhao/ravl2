# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2005, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 7512 2010-02-11 18:34:12Z craftit $"
#! file="Ravl/CompVision/ActiveAppearanceModels/defs.mk"

DESCRIPTION = Active appearance models

PACKAGE = Ravl/Image

DONOT_SUPPORT = arm

MAINS = aamBuildShapeModel.cc aamViewShapeModel.cc  aamBuildAppearanceModel.cc \
 aamBuildActiveAppearanceModel.cc  aamCombineActiveAppearanceModel.cc \
 aamLocaliseFace.cc aamBuildPoseEstimator.cc aamSynthesizeFrontal.cc aamTrackFace.cc

EXAMPLES = aamBuildShapeModel.cc aamViewShapeModel.cc aamBuildAppearanceModel.cc \
 aamBuildActiveAppearanceModel.cc aamCombineActiveAppearanceModel.cc aamLocaliseFace.cc \
 aamBuildPoseEstimator.cc aamSynthesizeFrontal.cc

HEADERS = AAMAppearance.hh AAMShapeModel.hh AAMAffineShapeModel.hh AAMScaleRotationShapeModel.hh \
 AAMAppearanceModel.hh AAMAppearanceUtil.hh AAMActiveAppearanceModel.hh AAMSampleStream.hh \
 AAMMultiResActiveAppearanceModel.hh AAMFaceLocalisation.hh AAMPoseEstimateCostFunction.hh \
 AAMPoseEstimate.hh AAMFaceCorrection.hh AAMSampleStreamFileList.hh AAMViewLib.hh

SOURCES = AAMAppearance.cc AAMShapeModel.cc AAMAffineShapeModel.cc AAMScaleRotationShapeModel.cc \
 AAMAppearanceModel.cc AAMAppearanceUtil.cc AAMActiveAppearanceModel.cc AAMSampleStream.cc \
 AAMMultiResActiveAppearanceModel.cc AAMFaceLocalisation.cc AAMPoseEstimateCostFunction.cc \
 AAMPoseEstimate.cc AAMFaceCorrection.cc AAMActiveAppearanceModelsIO.cc AAMSampleStreamFileList.cc \
 AAMViewLib.cc

MUSTLINK = AAMActiveAppearanceModelMustLink.cc

PLIB = RavlAAM

USESLIBS = RavlCore RavlImage RavlImageProc  RavlMath RavlOS RavlPatternRec RavlOptimise \
 RavlIO Optimisation RavlGUI2D

PROGLIBS = RavlImageIO RavlExtImgIO RavlMathIO RavlGUI.opt RavlDPDisplay.opt RavlImgIOV4L2.opt

EHT = AAM.html

AUXDIR=share/doc/RAVL/Images/AAM

AUXFILES= 000_1_2_090.png 000_1_2_090.xml
