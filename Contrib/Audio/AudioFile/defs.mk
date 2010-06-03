
# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5969 2006-11-20 17:56:28Z craftit $"
#! file="Ravl/Contrib/Audio/AudioFile/defs.mk"

REQUIRES = libAudioFile

DONOT_SUPPORT=VCPP

PACKAGE= Ravl/Audio

HEADERS= AudioFileIO.hh AudioFileFormat.hh

SOURCES= AudioFileIO.cc AudioFileFormat.cc

EXAMPLES= exAudioFile.cc 

PLIB=RavlAudioFile

MUSTLINK=RavlAudioFile.cc

USESLIBS=RavlIO AudioFile RavlAudioUtil RavlAudioIO

