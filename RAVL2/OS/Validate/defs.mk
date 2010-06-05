# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
################################################
#! rcsid="$Id: defs.mk 5535 2006-06-07 15:29:58Z craftit $"
#! file="Ravl/OS/Validate/defs.mk"

DONOT_SUPPORT=VCPP

DESCRIPTION= Ravl Validation programs

SOURCES = Extra.cc

MAINS = Validate.cc

USESLIBS = RavlCore RavlOS

EHT = 
#exeValidate.eht
