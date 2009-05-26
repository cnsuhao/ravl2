# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Contrib/Audio/DevAudio/defs.mk"

ORGANISATION=OmniPerception Ltd.

SUPPORT_ONLY = linux  linux64

PACKAGE= Ravl/Audio

HEADERS= DevAudioIO.hh DevAudioFormat.hh

SOURCES= DevAudioIO.cc DevAudioFormat.cc

MUSTLINK = RavlDevAudio.cc

PLIB = RavlDevAudio

USESLIBS=RavlIO RavlAudioUtil RavlOSIO RavlAudioIO

EHT = Audio_IO.html

EXAMPLES= exAudioIO.cc

PROGLIBS=RavlCore
