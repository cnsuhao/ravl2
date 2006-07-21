# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
###############################################
#! rcsid="$Id$"
#! file="Ravl/Applications/VPlay/defs.mk"

DESCRIPTION = VPlay - Video Player.

NESTED = Bitmaps.r

DONOT_SUPPORT=arm

HEADERS = GUIPlayControl.hh

SOURCES = GUIPlayControl.cc

PACKAGE = Ravl/VPlay

MAINS= VPlay.cc VCopy.cc

PLIB= RavlVPlay

USESLIBS = RavlCore RavlOS RavlImage RavlOSIO RavlGUI RavlDPMT RavlGUI2D RavlGUIUtil 

PROGLIBS =  RavlImgIOV4L.opt RavlExtImgIO.opt RavlDPDisplay \
 RavlImageIO RavlVideoIO  CSPDriver.opt RavlURLIO.opt RavlLibMPEG2.opt \
  RavlImageProc RavlNet RavlDVDRead.opt RavlAVIFile.opt \
 RavlIOV4L2.opt RavlImgIOJasper.opt RavlDV.opt RavlImgIO1394dc.opt \
 RavlLibFFmpeg.opt

#EHT = exeVPlay.eht
