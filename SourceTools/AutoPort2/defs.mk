# This file is part of VCPP, Visual C++ porting tool for QMake projects 
# Copyright (C) 2006, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
#! rcsid="$Id: fixSource.cfg 5642 2006-06-23 10:51:11Z craftit $"


PACKAGENAME= VCPP

DESCRIPTION = Visual C++ porting tool for QMake projects

DONOT_SUPPORT=

LICENSE = GPL

PACKAGE=Ravl/AutoPort2

HEADERS=AutoPortSource.hh AutoPortGenerator.hh ExtLib.hh ExtLibTable.hh

SOURCES=AutoPortSource.cc AutoPortGenerator.cc ExtLib.cc ExtLibTable.cc

MAINS= autoport2.cc

TESTEXES=autoport2.cc

PLIB=RavlAutoPort2

PROGLIBS= 

USESLIBS = RavlOS RavlSourceTools RavlCore RavlIO RavlMath GTK

AUXFILES= header.tmpl guid.tmpl externalLib.xml  sln.tmpl vcproj.tmpl solution.guid.tmpl \
 testProgram.guid.tmpl testProgram.tmpl exampleProgram.tmpl mainProgram.tmpl program.stmpl \
 mainProgram.guid.tmpl exampleProgram.guid.tmpl

AUXDIR= share/RAVL/AutoPort2

