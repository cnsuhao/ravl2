# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 6383 2007-10-08 14:42:03Z ees1wc $"
#! file="Ravl/Image/Processing/Filters/defs.mk"

PACKAGE=Ravl/Image

NESTED = GaborComplex.r

MAINS=doHomomorphicFilter.cc unDistort.cc 

HEADERS=  HomomorphicFilter.hh HistogramEqualise.hh \
 PixelMixer.hh RemoveDistortion.hh DeinterlaceStream.hh \
 DCT2d.hh ImageExtend.hh ImagePyramid.hh 

SOURCES= HomomorphicFilter.cc  DCT2d.cc DeinterlaceStream.cc 


LIBDEPS=RavlImageMisc.def

PLIB=RavlImageProc

USESLIBS=RavlImageProc RavlMath

PROGLIBS=RavlIO RavlImageIO RavlExtImgIO RavlOSIO RavlOptimise  RavlDPDisplay.opt


