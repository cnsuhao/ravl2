# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Tracking/defs.mk"

DONOT_SUPPORT=arm

MAINS=tracker.cc mosaic.cc xmosaic.cc

PROGLIBS=RavlImageProc RavlVideoIO RavlGUI2D RavlImgIOV4L.opt RavlDPDisplay.opt CSPDriver.opt


