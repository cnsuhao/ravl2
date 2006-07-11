# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
###############################################
#! rcsid="$Id$"
#! file="Ravl/Applications/AVPlay/defs.mk"

DESCRIPTION = AVPlay - Audio / Video Player.

DONOT_SUPPORT=arm

REQUIRES = libGTK

PACKAGE = Ravl/VPlay

MAINS= AVPlay.cc 

PROGLIBS = RavlAV RavlVPlay RavlDV.opt RavlImgIOV4L.opt RavlExtImgIO RavlDPDisplay \
 RavlImageIO RavlVideoIO CSPDriver.opt RavlURLIO.opt RavlAudioFile.opt RavlDevAudio.opt RavlAudioIO


