# This file is part of CxxDoc, The RAVL C++ Documentation tool 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/SourceTools/CxxDoc/defs.mk"

PACKAGENAME = CxxDoc

DESCRIPTION = The RAVL C++ Documentation tool

LICENSE = GPL

ifeq ($(ARC),sgi)
CCFLAGS += -CG:longbranch_limit=100000
endif

PACKAGE= Ravl/CxxDoc

NESTED = Templates.r

LOCALHEADERS= tokenizer.h FlexLexer.h

HEADERS= Object.hh Document.hh Parser.hh CxxElements.hh \
 CxxScope.hh DocNode.hh DocTree.hh

SOURCES = Object.cc tokenizer.l cxx.y Document.cc Parser.cc \
 CxxElements.cc CxxScope.cc DocExe.cc DocNode.cc DocTree.cc

PLIB = RavlCxxDoc

MAINS = CxxDoc.cc 
#doDocTree.cc

EHT= Ravl.Source_Tools.CxxDoc.html Ravl.Introduction.Documentation.html \
 Ravl.Introduction.Documentation.Code.html Ravl.Introduction.Documentation.Sections.html \
 Ravl.Introduction.Documentation.docentry.html Ravl.Introduction.Documentation.Formatting.html \
 Ravl.Source_Tools.CxxDoc.Templates.html

USESLIBS=  RavlCore RavlOS

PROGLIBS=  



