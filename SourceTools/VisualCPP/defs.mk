# This file is part of VCPP, Visual C++ porting tool for QMake projects 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
# $Id$
#! rcsid="$Id$"
#! file="Ravl/SourceTools/VisualCPP/defs.mk"

PACKAGENAME= VCPP

DESCRIPTION = Visual C++ porting tool for QMake projects

LICENSE = GPL

PACKAGE=Ravl/SourceTools

HEADERS= AutoPortSource.hh AutoPortGenerator.hh
#VCPP.hh

SOURCES = AutoPortSource.cc AutoPortGenerator.cc
#VCPP.cc

MAINS = autoport.cc

USESLIBS = RavlOS RavlSourceTools

EHT = autoport.eht

# Deal with template files.
AUXFILES = libs.tmpl examples.tmpl tests.tmpl mains.tmpl Ravl.dsw.tmpl \
	   Examples.dsw.tmpl Tests.dsw.tmpl Mains.dsw.tmpl

AUXDIR= share/RAVL/AutoPort

