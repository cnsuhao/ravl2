# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Edges/defs.mk"

DESCRIPTION =Edge detection

PACKAGE=Ravl/Image

MAINS= doEdgeDet.cc

EXAMPLES=doEdgeDet.cc

HEADERS=EdgeSobel.hh EdgeDeriche.hh SqrComposition.hh \
 EdgeNonMaxSuppression.hh Edgel.hh EdgeLink.hh \
 EdgeDetector.hh Gradient.hh

SOURCES=EdgeSobel.cc EdgeDeriche.cc SqrComposition.cc \
 EdgeNonMaxSuppression.cc Edgel.cc EdgeLink.cc \
 EdgeDetector.cc EdgeIO.cc

MUSTLINK=RavlEdgeIO.cc

PLIB=RavlImageProc

LIBDEPS=RavlImageEdges.def

USESLIBS=RavlImageProc 

PROGLIBS= RavlImageIO RavlDPMT RavlOSIO RavlVideoIO RavlIO RavlDPDisplay.opt RavlExtImgIO \
 RavlImgIOV4L.opt  RavlDV.opt RavlLibFFmpeg.opt

USESLIBS=  RavlIO RavlImage 

PROGLIBS=  RavlDPMT  RavlDPDisplay.opt RavlExtImgIO \
 RavlImgIOV4L.opt  RavlDV.opt RavlLibFFmpeg.opt



EHT=Ravl.API.Images.Edges.html
