
# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Contrib/Audio/AudioFile/defs.mk"

REQUIRES = libAudioFile

PACKAGE= Ravl/Audio

HEADERS= AudioFileIO.hh AudioFileFormat.hh

SOURCES= AudioFileIO.cc AudioFileFormat.cc

EXAMPLES= exAudioFile.cc 

PLIB=RavlAudioFile

MUSTLINK=RavlAudioFile.cc

USESLIBS=RavlIO AudioFile RavlAudioUtil RavlAudioIO

