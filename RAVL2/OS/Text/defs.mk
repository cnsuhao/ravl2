# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/OS/Text/defs.mk"

DESCRIPTION= Text processing utilites

PACKAGE=Ravl/Text

MAINS = 

HEADERS = TextFileLine.hh TextBuffer.hh TextFile.hh TextCursor.hh \
 TemplateFile.hh TextFragment.hh ConfigFile.hh TemplateComplex.hh 

SOURCES = TextFileLine.cc TextBuffer.cc TextFile.cc TextCursor.cc \
 TemplateFile.cc TextFragment.cc ConfigFile.cc TemplateComplex.cc 


LOCAL_FILES = template.x template2.x test.conf

EXAMPLES = exTemplateFile.cc exTemplateComplex.cc exConfigFile.cc
# exText.cc 

TESTEXES = testTextFile.cc
#exConfig.cc

PLIB=RavlOS

LIBDEPS=RavlOSText.def

USESLIBS=RavlOS RavlCore

EHT= Ravl.API.OS.Text_Processing.html \
     Ravl.API.OS.Text_Processing.Templates.html \
     Ravl.API.OS.Configuration_Files.html

HTML= 
