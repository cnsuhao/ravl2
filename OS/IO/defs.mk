# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/OS/IO/defs.mk"

PACKAGE=Ravl/DP

HEADERS=FileSequence.hh SequenceIO.hh FileListIO.hh

SOURCES=FileSequence.cc SequenceIO.cc FileListIO.cc

PLIB=RavlOSIO

USESLIBS=RavlOS RavlIO

TESTEXES= testSequenceIO.cc

EHT=Ravl.OS.Sequence.html Ravl.OS.Sequence.Numbered_Files.html
