# $Id$

PACKAGENAME= VCPP

DESCRIPTION = Visual C++ porting tool for QMake projects

LICENSE = GPL

PACKAGE=Ravl/SourceTools

HEADERS= SourceAutoPort.hh
#VCPP.hh

SOURCES = SourceAutoPort.cc
#VCPP.cc

MAINS = doVCPP.cc

USESLIBS = RavlOS RavlSourceTools

EHT = exedoVCPP.eht

# Deal with template files.

AUXFILES = lib5.dsp con5.dsp lib6.dsp con6.dsp

AUXDIR= Tools/VCPP

