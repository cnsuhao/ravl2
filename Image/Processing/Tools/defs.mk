# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Tools/defs.mk"

PACKAGE=Ravl/Image

HEADERS=Rectangle2dIter.hh SobolImage.hh SubSample.hh SummedAreaTable.hh

SOURCES=Rectangle2dIter.cc SobolImage.cc 

PLIB= RavlImageProc

USESLIBS=RavlImage RavlThreads RavlMath

EHT=Ravl.Images.Misc.html 

TESTEXES=testImageTools.cc
