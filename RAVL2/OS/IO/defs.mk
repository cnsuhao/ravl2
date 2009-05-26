# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/OS/IO/defs.mk"

PACKAGE=Ravl/DP

HEADERS=FileSequence.hh SequenceIO.hh FileListIO.hh CompositeStream.hh \
 FileFormatComposite.hh  PlayList.hh  SubSequenceSpec.hh EditSpec.hh  \
 FileFormatDynamic.hh DynamicLink.hh DynamicIO.hh

SOURCES=FileSequence.cc SequenceIO.cc FileListIO.cc CompositeStream.cc  \
 FileFormatComposite.cc  PlayList.cc  SubSequenceSpec.cc EditSpec.cc \
 FileFormatDynamic.cc DynamicLink.cc 

MUSTLINK=RavlOSIOMustLink.cc

PLIB=RavlOSIO

USESLIBS=RavlOS RavlIO DynLink system

TESTEXES= testSequenceIO.cc

EXAMPLES=  exCompositeStream.cc exDynamicLink.cc exDynamicFormat.cc 

EHT=Ravl.API.OS.Sequence.html Ravl.API.OS.Sequence.Numbered_Files.html
