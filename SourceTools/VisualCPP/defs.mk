# $Id$

PACKAGENAME= VCPP

DESCRIPTION = Visual C++ porting tool for QMake projects

LICENSE = GPL

PACKAGE=Ravl/SourceTools

HEADERS= VCPP.hh

SOURCES = VCPP.cc

MAINS = doVCPP.cc

USESLIBS = Auto

EHT = exedoVCPP.eht

# Deal with template files.

AUXFILES = lib5.dsp con5.dsp lib6.dsp con6.dsp AMMAported

AUXDIR= Tools/VCPP

