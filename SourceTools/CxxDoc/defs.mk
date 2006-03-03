# This file is part of CxxDoc, The RAVL C++ Documentation tool 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/SourceTools/CxxDoc/defs.mk"

PACKAGENAME = Ravl

DESCRIPTION = The RAVL C++ Documentation tool

LICENSE = GPL

ifeq ($(ARC),sgi)
CCFLAGS += -CG:longbranch_limit=100000
endif

PACKAGE= Ravl/CxxDoc

NESTED = Templates.r

LOCALHEADERS= tokenizer.h FlexLexer.h

HEADERS= Object.hh Document.hh Parser.hh CxxElements.hh \
 CxxScope.hh DocNode.hh DocTree.hh Strings.hh Executables.hh

SOURCES = Object.cc Document.cc Parser.cc \
 CxxElements.cc CxxScope.cc DocExe.cc DocNode.cc DocTree.cc \
 Strings.cc   cxx.y Executables.cc tokenizer.yy.cc
#tokenizer.yy.cc
#cxx.tab.cc tokenizer.l 

# the output of flex and bison is not compatibile with gcc-3.1, it needs
# a little tweeking, so don't compile these directly :
#   

PLIB = RavlCxxDoc

MAINS = CxxDoc.cc 

EHT= Ravl.API.Source_Tools.CxxDoc.html Documentation.html \
 Documentation.Code.html Documentation.Sections.html \
 Documentation.docentry.html Documentation.Changes.html\
 Ravl.API.Source_Tools.CxxDoc.Templates.html Ravl.API.Source_Tools.CxxDoc.Internal.html \
 Ravl.undocumented.html Ravl.undocumented.anonymous.html \
#  Documentation.Formatting.html

USESLIBS=  RavlCore RavlOS RavlSourceTools

PROGLIBS=  



