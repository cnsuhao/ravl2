# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

PACKAGE=Ravl/Image

HEADERS=Rectangle2DIter.hh SobolImage.hh SubSample.hh
#SplitProc.hh

SOURCES=Rectangle2DIter.cc SobolImage.cc 
#SplitProc.cc

PLIB= RavlImageProc

USESLIBS=RavlImage RavlThreads RavlMath

EHT=Ravl.Images.Misc.html 

