# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

PACKAGE=Ravl/Audio

HEADERS=SphereIO.hh SphereFormat.hh TranscriptionFiles.hh TranscriptionStream.hh

SOURCES=AudioSample.cc SphereIO.cc SphereFormat.cc TranscriptionFiles.cc \
 TranscriptionStream.cc

PLIB=RavlAudioIO

USESLIBS=RavlAudioUtil RavlOS

MUSTLINK=RavlAudioSample.cc

MAINS=audioconv.cc

PROGLIBS=RavlDevAudio.opt RavlAudioFile.opt

EXAMPLES= exTranscriptionStream.cc
