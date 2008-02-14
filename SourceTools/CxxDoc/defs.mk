# This file is part of CxxDoc, The RAVL C++ Documentation tool 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/SourceTools/CxxDoc/defs.mk"

DONOT_SUPPORT=VCPP

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
 Strings.cc Executables.cc \
 cxx.tab.cc tokenizer.yy.cc # (1) Comment out this line is you do not wish to use the pre-generated lexer/parser
# cxx.y tokenizer.l # (2) Uncomment this line to generate a new lexer/parser
# If you wish to generate a new lexer/parser with flex/bison then 
# comment out the line marked (1) and uncomment the line marked (2).
# Please note that FlexLexer.h is provided by the flex package and is
# not usable with lexers generated from different versions.

PLIB = RavlCxxDoc

MAINS = CxxDoc.cc 

EHT= Ravl.API.Source_Tools.CxxDoc.html Documentation.html \
 Documentation.Code.html Documentation.Sections.html \
 Documentation.docentry.html Documentation.Changes.html\
 Ravl.API.Source_Tools.CxxDoc.Templates.html Ravl.API.Source_Tools.CxxDoc.Internal.html \
 Ravl.undocumented.html Ravl.undocumented.anonymous.html
# Documentation.Formatting.html

USESLIBS=  RavlCore RavlOS RavlSourceTools

PROGLIBS=  
