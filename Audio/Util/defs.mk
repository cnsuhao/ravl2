# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

PACKAGE=Ravl/Audio

HEADERS=AudioIO.hh  Types.hh WindowSignal.hh

SOURCES=AudioIO.cc WindowSignal.cc 

PLIB=RavlAudioUtil

USESLIBS=RavlIO

EHT= Ravl.Audio.IO.html

TESTEXES= testAudioUtil.cc
