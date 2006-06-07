# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2004, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Applications/ClassWizard/defs.mk"

DONOT_SUPPORT=VCPP

PACKAGE=Ravl/SourceTools

HEADERS= ClassWizard.hh SourceCursor.hh

SOURCES= ClassWizard.cc SourceCursor.cc

MAINS=cwiz.cc

PLIB=RavlClassWizard

USESLIBS=RavlCxxDoc

EHT=Ravl.API.Source_Tools.Class_Wizard.html
