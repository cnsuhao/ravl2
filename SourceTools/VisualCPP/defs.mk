# $Id$

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
AUXFILES = libs.tmpl examples.tmpl tests.tmpl mains.tmpl Ravl.dsw.tmpl

AUXDIR= Tools/AutoPort

