# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 4777 2005-01-18 14:28:18Z ees1wc $"
#! file="Ravl/Core/Machine/i386-linux-gnu/defs.mk"

DESCRIPTION= Atomic operations for i386-linux

PACKAGE=macosx386/Ravl

SUPPORT_ONLY=macosx386

HEADERS=Atomic.hh mmx.hh

PLIB=RavlCore

USESLIBS=Math
