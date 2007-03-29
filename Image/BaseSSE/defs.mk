# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Base/defs.mk"

REQUIRES=USE_SSE2

PACKAGE=Ravl/Image

HEADERS=

SOURCES=ImageConvSSE.cc

HEADERS=ImageConvSSE.hh

MUSTLINK=InitImageConvSSE.cc

PLIB=RavlImage

USESLIBS=RavlCore

USERCPPFLAGS=-msse2

