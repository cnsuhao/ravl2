# This file is part of QMake, Quick Make System 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
##########################
# Directories used in making.
# $Id$
#! rcsid="$Id$"
#! file="Ravl/QMake/Dirs.mk"

ifndef MAKEHOME
 MAKEHOME = /vol/vssp/cpug/amma/src/Util/QMake#
endif

ifndef ARC
  ARC=$(shell $(MAKEHOME)/config.arc)#
endif

ifndef BASELIBRARY
 BASE_LIBRARY = $(MAKEHOME)/../..#
endif

ifndef BASE_VERSION
 BASE_VERSION=stable
endif

ifndef PACKAGE
 PACKAGE=local
endif

ifdef QMAKE_INFO
  SHOWIT = 
else
  SHOWIT = @
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
     ifeq ($(VAR),shared)
       BASE_VAR=shared#
     else
       BASE_VAR=check#
     endif
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

##########
# Working directories...


PROJ_ID := $(subst ~,,$(PROJECT_OUT))

LOCALTMP:=$(TMP)/$(LOGNAME)/qm/$(PROJ_ID)/

ifndef ROOTDIR
  ROOTDIR:=$(PROJECT_OUT)
endif
#ifndef BUILDDIR
## The following is useful if you have several versions of
## code which you want test e.g. alpha/beta/release 
#  ifeq ($(BASE_VAR),none) # Is amma version irrelavent ?
#    BUILDDIR:=$(PROJECT_OUT)/$(ARC)/$(VAR)
#  else
#    BUILDDIR:=$(PROJECT_OUT)/$(ARC)/$(BASE_VERSION)/$(VAR)
#  endif
#endif

BUILDDIR:=$(PROJECT_OUT)/$(ARC)/$(VAR)

############################
# include info on amma system.

#INCLUDES=

#ifeq ($(BASE_VAR),none) # Is amma version irrelavent ?
#  WORKTMP=$(LOCALTMP)/$(ARC)/$(BASENAME)/$(VAR)
#else
#  WORKTMP=$(LOCALTMP)/$(ARC)/$(BASENAME)/$(BASE_VERSION)/$(VAR)
#endif

WORKTMP=$(LOCALTMP)/$(ARC)/$(BASENAME)/$(VAR)

# Were to look for .def files, First in the current directory,
# then the   current PROJECT_OUT def's and finally those that 
# were installed with the make system. 

DEF_INC = -I. -I$(INST_LIBDEF) -I$(MAKEHOME)/../../libdep

# A file that definitly doesn't exist.

NOFILE = /notme/hiya/fruitcake/whippy

#########################
# Target directories.

# Documentation

INST_AUTODOC=$(ROOTDIR)/doc/Auto
INST_DOC=$(ROOTDIR)/doc
INST_PDOC=$(INST_DOC)/$(PACKAGE)
INST_EHT=$(PROJECT_OUT)/Tools/AutoDoc/EHT
INST_HTML=$(INST_DOC)/html
INST_MAN1=$(INST_DOC)/man1
INST_MAN3=$(INST_DOC)/man3
INST_MAN5=$(INST_DOC)/man5
INST_DOCEXAMPLES=$(INST_DOC)/examples
INST_DOCNODE=$(INST_AUTODOC)/DocNode

# Auxilary files.
INST_AUX=$(ROOTDIR)/$(AUXDIR)

# Binaries
INST_LIB=$(BUILDDIR)/lib
INST_OBJS=$(WORKTMP)/objs
INST_FORCEOBJS = $(PROJECT_OUT)/$(ARC)/obj

# Test stuff.
INST_TEST=$(PROJECT_OUT)/$(ARC)/test
INST_TESTBIN=$(INST_TEST)/bin
INST_TESTLOG=$(INST_TEST)/log
INST_TESTDB =$(INST_TEST)/TestExes

INST_LIBDEF=$(ROOTDIR)/libdep
INST_BIN=$(ROOTDIR)/$(ARC)/bin
INST_INCLUDE:=$(ROOTDIR)/inc
INST_DEPEND=$(ROOTDIR)/$(ARC)/depend/$(PACKAGE)/$(BASENAME)

ifeq ($(PACKAGE),local)
INST_HEADER:=$(INST_INCLUDE)
else
INST_HEADER:=$(INST_INCLUDE)/$(PACKAGE)
endif

INST_HEADERCERT:=$(ROOTDIR)/Admin/Cert/$(PACKAGE)

# Java classes

INST_JAVA    = $(ROOTDIR)/java
INST_JAVAEXE = $(INST_BIN)

############################
# Some targets.

# Published dependancy flag.
TARG_DEPFLAG=$(ROOTDIR)/$(ARC)/depend/$(PACKAGE)/$(BASENAME)/.depend
TARG_HDRFLAG=$(ROOTDIR)/$(ARC)/depend/$(PACKAGE)/$(BASENAME)/.header

##############################
# Make setup

# Basic make.
MAKESM=$(MAKE) $(DEF_INC) $(PAR_MAKE)

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

SMAKESM=$(SHOWIT)$(MAKESM)
SMAKEMD=$(SHOWIT)$(MAKEMD)
SMAKEMO=$(SHOWIT)$(MAKEMO)
SMAKECL=$(SHOWIT)$(MAKECL)
SMAKEUT=$(SHOWIT)$(MAKEUT)
SMAKEDC=$(SHOWIT)$(MAKEDC)
