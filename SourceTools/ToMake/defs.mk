# This file is part of VCPP, Visual C++ porting tool for QMake projects 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/SourceTools/ToMake/defs.mk"

DONOT_SUPPORT=VCPP

PACKAGENAME= TOMAKE

DESCRIPTION = Porting to the normal make system

LICENSE = GPL

PACKAGE=Ravl/SourceTools

HEADERS= 

SOURCES =

MAINS = tomake.cc

USESLIBS = RavlOS RavlSourceTools

EHT = 

# Deal with template files.
AUXFILES = Makefile.tmpl

AUXDIR= share/RAVL/AutoPort

