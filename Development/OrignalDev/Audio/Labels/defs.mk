# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk,v 1.6 2004/11/17 11:51:33 plugger Exp $"
#! file="Ravl/Contrib/Audio/AudioFile/defs.mk"

PACKAGE = Jack

PLIB = JackLabels

MAINS = exTranscriptionLabel.cc

HEADERS = Transcription.hh

SOURCES = Transcription.cc

USESLIBS = RavlIO RavlCore RavlOS

