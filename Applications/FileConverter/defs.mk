# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Applications/FileConverter/defs.mk"

DESCRIPTION= General purpose file converter.

MAINS = conv.cc

USESLIBS= RavlCore RavlOSIO RavlImage RavlOS RavlImageIO RavlVideoIO  \
	 Ravl3DIO RavlMathIO

PROGLIBS= RavlDPDisplay.opt RavlExtImgIO.opt RavlDV.opt RavlImgIOV4L.opt  \
 RavlPatternRecIO CSPDriver.opt RavlURLIO.opt RavlDevAudio.opt RavlAudioFile.opt \
 RavlDMeda.opt RavlImgIOMeteor1.opt RavlDPGraph.opt RavlAudioIO.opt \
 RavlImgIO1394dc.opt RavlLibMPEG2.opt  RavlImgIOJasper.opt RavlLibFFmpeg.opt RavlGrabIO.opt
#RavlMPEG2.opt

#EHT = execonv.eht
