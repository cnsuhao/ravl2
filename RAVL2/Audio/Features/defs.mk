# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5544 2006-06-08 12:10:18Z craftit $"
#! file="Ravl/Audio/Features/defs.mk"

PACKAGE=Ravl/Audio

MAINS=
#exFeatureMFCC.cc

HEADERS=MelSpectrum.hh MelCepstrum.hh PreEmphasis.hh FeatureMFCC.hh VectorDelta012.hh

# LabelFeatures.hh

SOURCES=MelSpectrum.cc MelCepstrum.cc FeatureMFCC.cc VectorDelta012.cc 
# LabelFeatures.cc

PLIB=RavlAudioFeatures

USESLIBS=RavlAudioUtil RavlMath RavlOS RavlAudioIO

TESTEXES=testAudioFeatures.cc

EXAMPLES= exFeatureMFCC.cc

PROGLIBS=RavlOSIO RavlDevAudio.opt  RavlAudioIO RavlAudioFile.opt
