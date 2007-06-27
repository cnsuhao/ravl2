# This file is part of QMake, Quick Make System 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/QMake/Dirs.mk"

# Directories used in making.

ifndef MAKEHOME
 MAKEHOME = /vol/vssp/cpug/Ravl/src/Util/QMake#
endif

ifndef ARC
  ARC=$(shell $(MAKEHOME)/config.arc)#
endif

ifndef INSTALLHOME
 INSTALLHOME = $(MAKEHOME)/../../..#
endif

ifndef PACKAGE
 PACKAGE=local
endif

ifdef QMAKE_INFO
  SHOWIT = 
else
  SHOWIT = @
endif

# FIXME: PACKAGEDIR is intented to replace all the RAVL's hardwired into
# the make system.  Before it can be used we have to disentangle
# what is QMAKE and the base installation.

ifndef PACKAGENAME
  PACKAGEDIR=RAVL
else
  PACKAGEDIR=$(PACKAGENAME)
endif

PACKAGE:=$(strip $(PACKAGE))#

ifndef QCWD
 QCWD :=$(shell 'pwd')#
endif

ifndef PLIB
  BASENAME:=$(PACKAGE)/None#
else
  BASENAME:=$(PLIB)#
endif

##########################
# Varient information

ifndef NOVAR
 ifndef VAR
   VAR=check#
 endif
endif

ifndef BASE_VAR
 ifeq ($(VAR),prof)
  BASE_VAR=opt#
 else
  ifeq ($(VAR),gprof)
   BASE_VAR=opt#
  else
   ifeq ($(VAR),opt)
    BASE_VAR=opt#
   else
    BASE_VAR=check#
   endif 
  endif
 endif
endif

##########################
# Roots of working directories.

#################
# Temporary directories...

ifndef DEFAULTTMP 
 TMP=/tmp
else
 TMP=$(DEFAULTTMP)
endif

ifndef SHAREDBUILD 
WORKTMP=$(LOCALTMP)/$(ARC)/$(BASENAME)/$(VAR)
else
WORKTMP=$(LOCALTMP)/$(ARC)/$(BASENAME)/$(VAR)/shared
endif 

# A file that definitly doesn't exist.
#NOFILE = /notme/hiya/fruitcake/whippy

##########
# Working directories...

PROJ_ID := $(subst ~,,$(PROJECT_OUT))

LOCALTMP:=$(TMP)/$(LOGNAME)/qm/$(PROJ_ID)/

# ROOTDIR is where the software will be installed.

ifndef ROOTDIR
  ROOTDIR:=$(PROJECT_OUT)
endif

#########################
# Target directories.

# Admin files used in build but not needed after.

INST_ADMIN=$(ROOTDIR)/share/RAVL/Admin

# Documentation

INST_AUTODOC=$(ROOTDIR)/share/doc/Auto
INST_DOCNODE=$(INST_AUTODOC)/DocNode
INST_DOC= $(ROOTDIR)/share/doc/RAVL
INST_PDOC=$(INST_DOC)/$(PACKAGE)
INST_HTML=$(INST_DOC)/html
INST_DOCEXAMPLES=$(INST_DOC)/examples
INST_EHT= $(INST_ADMIN)/AutoDoc/EHT
INST_MAN1=$(ROOTDIR)/share/man/man1
INST_MAN3=$(ROOTDIR)/share/man/man3
INST_MAN5=$(ROOTDIR)/share/man/man5

# Auxilary files.
INST_AUX=$(ROOTDIR)/$(AUXDIR)

# Binaries

ifndef SHAREDBUILD 
INST_LIB=$(ROOTDIR)/lib/RAVL/$(ARC)/$(VAR)
else 
INST_LIB=$(ROOTDIR)/lib/RAVL/$(ARC)/$(VAR)/shared
endif 
INST_OBJS=$(WORKTMP)/objs
INST_FORCEOBJS = $(ROOTDIR)/lib/RAVL/$(ARC)/obj

# Test stuff.
INST_TEST=$(INST_ADMIN)/$(ARC)/test
INST_TESTBIN=$(INST_TEST)/bin
INST_TESTLOG=$(INST_TEST)/log
INST_TESTDB =$(INST_TEST)/TestExes

INST_LIBDEF=$(ROOTDIR)/lib/RAVL/libdep
INST_BIN=$(ROOTDIR)/lib/RAVL/$(ARC)/bin# Machine dependent programs.
INST_GENBIN=$(ROOTDIR)/bin# Machine independent scripts.
INST_INCLUDE:=$(ROOTDIR)/include
INST_DEPEND=$(INST_ADMIN)/$(ARC)/depend/$(PACKAGE)/$(BASENAME)

ifeq ($(PACKAGE),local)
INST_HEADER:=$(INST_INCLUDE)
else
INST_HEADER:=$(INST_INCLUDE)/$(PACKAGE)
endif

INST_HEADERCERT:=$(INST_ADMIN)/Cert/$(PACKAGE)

# Java classes

INST_JAVA    = $(ROOTDIR)/java
INST_JAVAEXE = $(INST_BIN)

############################
# include info on RAVL system.

#INCLUDES=


# Were to look for .def files, First in the current directory,
# then the   current PROJECT_OUT def's and finally those that 
# were installed with the make system. 

DEF_INC = -I. -I$(INST_LIBDEF) -I$(INSTALLHOME)/lib/RAVL/libdep

############################
# Some targets.

# Published dependancy flag.
TARG_DEPFLAG=$(INST_ADMIN)/$(ARC)/depend/$(PACKAGE)/$(BASENAME)/.depend
TARG_HDRFLAG=$(INST_ADMIN)/$(ARC)/depend/$(PACKAGE)/$(BASENAME)/.header

##############################
# Make setup

# Basic make.
MAKESM=$(MAKE) $(DEF_INC) 
#$(PAR_MAKE)

# Make with dependancies
MAKEMD=$(MAKESM) -f $(MAKEHOME)/MainDep.mk

# Make with dependancies
MAKEMO=$(MAKESM) -f $(MAKEHOME)/Main.mk

# Clean up makefile.
MAKECL=$(MAKESM) -f $(MAKEHOME)/Clean.mk

# Clean up makefile.
MAKEUT=$(MAKESM) -f $(MAKEHOME)/Util.mk

# Clean up makefile.
MAKEDC=$(MAKESM) -f $(MAKEHOME)/Doc.mk

# With Show it prefix.

SMAKESM=+ $(SHOWIT)$(MAKESM)
SMAKEMD=+ $(SHOWIT)$(MAKEMD)
SMAKEMO=+ $(SHOWIT)$(MAKEMO)
SMAKECL=+ $(SHOWIT)$(MAKECL)
SMAKEUT=+ $(SHOWIT)$(MAKEUT)
SMAKEDC=+ $(SHOWIT)$(MAKEDC)
