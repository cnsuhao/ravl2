# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU
# General Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5518 2006-06-05 18:44:47Z craftit $"
#! file="Ravl/Contrib/LibFFmpeg/defs.mk"

#REQUIRES = libffmpeg

ORGANISATION=Omniperception Ltd.

DONOT_SUPPORT=VCPP

PACKAGE = Ravl/Audio

HEADERS =  LibFFmpegAudioFormat.hh FFmpegAudioPacket.hh FFmpegAudioPacketStream.hh \
 FFmpegAudioDecoder.hh AudioIOFFmpeg.hh

SOURCES =  LibFFmpegAudioFormat.cc FFmpegAudioPacket.cc FFmpegAudioPacketStream.cc \
FFmpegAudioDecoder.cc AudioIOFFmpeg.cc

PLIB = RavlLibFFmpegAudio

MUSTLINK = MustLinkLibFFmpegAudio.cc

USESLIBS =  LibFFmpeg RavlIO RavlGUI

PROGLIBS = RavlDPDisplay RavlLibFFmpeg RavlVideoIO  RavlVPlay

