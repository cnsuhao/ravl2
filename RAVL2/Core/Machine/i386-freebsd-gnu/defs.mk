# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! file="Ravl/Core/Machine/i386-freebsd-gnu/defs.mk"

DESCRIPTION= Atomic operations for i386-freebsd

PACKAGE=freebsd_x86/Ravl

SUPPORT_ONLY=freebsd_x86

HEADERS=Atomic.hh mmx.hh

PLIB=RavlCore

USESLIBS=Math
