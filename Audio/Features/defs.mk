# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

PACKAGE=Ravl/Audio

HEADERS=MelSpectrum.hh MelCepstrum.hh FeatureMFCC.hh

SOURCES=MelSpectrum.cc MelCepstrum.cc FeatureMFCC.cc

PLIB=RavlAudioFeatures

USESLIBS=RavlAudioUtil RavlMath

TESTEXES=testAudioFeatures.cc

