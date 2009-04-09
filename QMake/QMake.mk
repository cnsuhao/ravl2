# This file is part of QMake, Quick Make System 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/QMake/QMake.mk"

# Setup make flags.

ifndef MAKEHOME
  MAKEHOME=.
endif

ifndef INSTALLHOME
 INSTALLHOME=$(MAKEHOME)/../../..#
endif

# a slight change, now ARC is ALWAYS defined from the config.arc script
#ifndef ARC
  ARC=$(shell $(MAKEHOME)/config.arc)#
#endif

export ARC

ifndef LOCALARC
  LOCALARC=$(shell $(MAKEHOME)/config.arc)#
endif

export LOCALARC

MAKEDEFS:=perl -f $(MAKEHOME)/mkdefs.pl

# Set default uses lib to auto?

ifdef USERBUILD
  export USERBUILD
endif

# Make sure PAGER is defined.

ifndef PAGER 
  PAGER=more
endif

export ARC
export LOCALBIN := $(INSTALLHOME)/lib/RAVL/$(LOCALARC)/bin
export DPATH:=$(shell basename $(shell 'pwd'))
export TARGET

SYSCONF:=$(LOCALBIN)/SysConf

ifndef PROCS
  PROCS=$(shell $(SYSCONF) -a )
endif

export PROCS

ifndef PROJECT_OUT
  PROJECT_OUT := /tmp/$(USER)/ProjectOut
else
ifeq ($(PROJECT_OUT),"")
  PROJECT_OUT := /tmp/$(USER)/ProjectOut
endif
endif

export PROJECT_OUT

###############################################################################
# Check for project out 

# Basicly add BUILD_TAG=SomeName to your alias and then only QMake will only
# work on project outs with the same tag.

ifdef BUILD_TAG
PROJECT_OUT_BUILD_TAG :=$(strip $(shell cat $(PROJECT_OUT)/buildTag 2> /dev/null ))#
ifeq ($(PROJECT_OUT_BUILD_TAG),)
$(shell echo "$(BUILD_TAG)" > $(PROJECT_OUT)/buildTag )
else
ifneq ($(BUILD_TAG),$(PROJECT_OUT_BUILD_TAG))
$(error "Errr.. you didn't mean to do that.  (BUILD_TAG doesn't match the project. )")
endif
SOURCE_BUILD_TAG :=$(strip $(shell $(LOCALBIN)/findBuildTag $(shell 'pwd')))#
ifneq ($(BUILD_TAG),$(SOURCE_BUILD_TAG))
$(error "Errr.. you didn't mean to do that.  (BUILD_TAG doesn't match the source tag. )")
endif
endif
endif

##############################################################################

# Setup default build target.
TARGET=fullbuild

ifndef QMAKECONFIGHOME
QMAKECONFIGHOME = $(MAKEHOME)
endif

# Include a local config file 
ifdef CONFIGFILE
include ${CONFIGFILE}
else
include $(QMAKECONFIGHOME)/config.local.$(ARC)
endif

# Include system config and Directories 

-include $(MAKEHOME)/*.qpr 
# $(INSTALLHOME)/lib/RAVL/libdep/*.qpr

include $(MAKEHOME)/config.$(ARC)
NOVAR=1
include $(MAKEHOME)/Dirs.mk

# The following is for logging only.
-include $(QCWD)/defs.mk

VPATH=$(QCWD)

ifdef QMAKE_INFO
  export QMAKE_INFO
endif

.PHONY : all depend opt qopt qdb develop qd distclean \
 clean pack unpack org help isdep srcp srcd org orgopt orgdebug chead \
 lib_info defs mdoc notes qc qcheck src mirror srcinst doconly log \
 fulldoc fullcheck fullsrc fulltest fullbuild \
 check checkshared checkne checksharedne shared ne sharedne \
 debug debugshared debugne debugsharedne ds dsne \
 debugall debugsharedall debugneall debugsharedneall \
 opt optshared optne optsharedne os osne

##################################
# Do makes.

MAKEFLAGS += --no-print-directory -r $(PAR_MAKE)

# Where commands are prefixed by 'q' frozen dependancies are used.
# NB. Frozen dependancies can only be used where  normal make has 
#  successfully built ALL the depenacies for that directories, this
#  can be done using the target depend.

# Make with dependancies

ifdef MIRROR
all: mirror
else
 ifdef CIMSG
all: ci
 else
  ifdef VAR
all: novar
  else
all: check
  endif
 endif
endif
allns: all

############################
# Some compile shortcuts.

shared: checkshared

ne: checkne

sharedne: checksharedne

os: optshared 

osne: optsharedne

ds: debugshared

dsne: debugsharedne

############################
# Test targets

TEST_TARGET := $(firstword $(TEST_TARGET))

# Default (check build)
TEST_TARGET_PARAMS := VAR=check
TEST_TARGET := $(patsubst check%,%,$(TEST_TARGET))

# set and remove 'debug' or 'opt' target component
ifneq ($(strip $(filter debug%,$(TEST_TARGET))),)
  TEST_TARGET := $(patsubst debug%,%,$(TEST_TARGET))
  TEST_TARGET_PARAMS := VAR=debug
else
  ifneq ($(strip $(filter opt%,$(TEST_TARGET))),)
    TEST_TARGET := $(patsubst opt%,%,$(TEST_TARGET))
    TEST_TARGET_PARAMS := VAR=opt
  endif
endif

# set and remove 'shared' target component
ifneq ($(strip $(filter shared%,$(TEST_TARGET))),)
  TEST_TARGET := $(patsubst shared%,%,$(TEST_TARGET))
  TEST_TARGET_PARAMS += SHAREDBUILD=1
endif

# remove 'ne' target component
TEST_TARGET := $(patsubst ne%,%,$(TEST_TARGET))

# set the 'all' debug target component
ifneq ($(strip $(findstring VAR=debug,$(TEST_TARGET_PARAMS))),)
  ifeq ($(strip $(TEST_TARGET)),all)
    TEST_TARGET_PARAMS += BASE_VAR=debug
  endif
endif

############################
# Compilation targets.

src:
	$(SMAKEMO) src_all TARGET=src_all NOINCDEFS=1 

novar:
	$(SMAKEMD) fullbuild TARGET=fullbuild  

check:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=check  

opt:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=opt

debug:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=debug

debugall:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=debug                            BASE_VAR=debug

checkshared:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=check SHAREDBUILD=1  

optshared:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=opt   SHAREDBUILD=1 

debugshared:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=debug SHAREDBUILD=1

debugsharedall:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=debug SHAREDBUILD=1              BASE_VAR=debug

checkne:	
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=check               NOEXEBUILD=1 

optne:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=opt                 NOEXEBUILD=1 

debugne:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=debug               NOEXEBUILD=1 

debugneall:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=debug               NOEXEBUILD=1 BASE_VAR=debug

checksharedne:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=check SHAREDBUILD=1 NOEXEBUILD=1

optsharedne:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=opt   SHAREDBUILD=1 NOEXEBUILD=1

debugsharedne:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=debug SHAREDBUILD=1 NOEXEBUILD=1

debugsharedneall:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=debug SHAREDBUILD=1 NOEXEBUILD=1 BASE_VAR=debug

purify:
	$(SMAKEMD) purifybuild TARGET=purifybuild VAR=debug PROCS=1  

prof:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=prof  

gprof:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=gprof  

gprofne:
	$(SMAKEMD) fullbuild TARGET=fullbuild VAR=gprof NOEXEBUILD=1 

chead:
	$(SMAKEMD) cheadbuild TARGET=cheadbuild FULLCHECKING=1  

test: src
	@if [ ! -d $(INST_TESTBIN) ] ; then \
	  $(MKDIR) $(INST_TESTBIN); \
	fi 
	@if [ ! -d $(INST_TESTLOG) ] ; then \
	  $(MKDIR) $(INST_TESTLOG); \
	fi 
	+ $(SHOWIT)touch $(INST_TESTDB); \
	if $(MAKEMD) testbuild TARGET=testbuild $(TEST_TARGET_PARAMS) FULLCHECKING=1 NOEXEBUILD=1 ; then true ; \
	else \
	  echo "test: Failed to do initial build for test. "; \
	  exit 1 ; \
	fi ; \
	if $(MAKEMD) testbuild TARGET=testbuild $(TEST_TARGET_PARAMS) FULLCHECKING=1 ; then true ; \
	else \
	  echo "test: Failed to do executable build. " ; \
	  exit 1 ; \
	fi ;
ifeq ($(ARC),$(LOCALARC))
	$(SHOWIT)sort -u -o$(INST_TESTDB) $(INST_TESTDB); \
	$(LOCALBIN)/Validate -v $(INST_TEST)
endif

retest:
	$(SHOWIT)sort -u -o$(INST_TESTDB) $(INST_TESTDB) ; \
	$(LOCALBIN)/Validate -v $(INST_TEST)	

# Build everything.

buildall:
	$(SHOWIT)if $(MAKEMO) FULLCHECKING=1 src_all NOINCDEFS=1 ; then true; \
        else \
	  echo "QMAKE: Installation of header files failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) libbuild TARGET=libbuild VAR=check NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: check library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) libbuild TARGET=libbuild VAR=debug NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: debug library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) libbuild TARGET=libbuild VAR=opt NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: opt library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) fullbuild TARGET=fullbuild VAR=opt ; then true; \
        else \
	  echo "QMAKE: executable build failed. " ; \
	  exit 1; \
        fi ; \
	echo "Building documentation. " ; \
	$(MAKEDC) doc 

###########################################################
# Utilities for RAVL installation.

# The last INST_LIBDEF is because the calling PROJECT_OUT may not
# be the one we using.

FULLBUILDSRC := FULLCHECKING=1

FULLBUILDFLAGS = NOCHECKOUT=1  $(FULLBUILDSRC)

# Check out latest version.

fullsrc:	
	$(SMAKEMO) NOINCDEFS=1 src_all $(FULLBUILDSRC)

fullhdr:	
	$(SMAKEMO) NOINCDEFS=1 src_all $(FULLBUILDFLAGS)

# Build check of latest version.

fullcheck:	
	$(SMAKEMD) fullbuild VAR=check $(FULLBUILDFLAGS) TARGET=fullbuild

fulldebug:	
	$(SMAKEMD) fullbuild VAR=debug $(FULLBUILDFLAGS) TARGET=fullbuild

fullopt:	
	$(SMAKEMD) fullbuild VAR=opt $(FULLBUILDFLAGS) TARGET=fullbuild

fullinfo:	
	$(SMAKEMO) info VAR=check $(FULLBUILDFLAGS)

fullclean:
	$(SMAKECL) clean VAR=check $(FULLBUILDFLAGS) TARGET=clean

libbuild: 
	$(SMAKEMD) libbuild  $(FULLBUILDFLAGS) TARGET=libbuild

# Build Ravl.
# Proceeds as follows:
#  1-Src the latest version of the source.
#  2-Compile all libraries.
#  3-Build executables.
#  4-Build documentation

#add some defaults if FULLBUILD_TARGETS has not been defined
FULLBUILD_TARGETS ?= check opt checkshared optbin doc

# replace shared alias for checkshared
ifneq ($(strip $(filter shared,$(FULLBUILD_TARGETS))),)
FULLBUILD_TARGETS := $(patsubst shared,checkshared,$(FULLBUILD_TARGETS))
endif 

# make sure check libs get built before trying to build check binaries 
ifneq ($(strip $(filter checkbin,$(FULLBUILD_TARGETS))),)
FULLBUILD_TARGETS += check 
endif 

# make sure opt libs get built before trying to build opt binaries 
ifneq ($(strip $(filter optbin,$(FULLBUILD_TARGETS))),)
FULLBUILD_TARGETS += opt 
endif 

fullbuild:
	+ $(SHOWIT)if $(MAKEMO) $(FULLBUILDFLAGS) src_all NOINCDEFS=1 ; then true; \
        else \
	  echo "QMAKE: Installation of header files failed. " ; \
	  exit 1; \
        fi ; 

        # check build
        ifeq ($(strip $(filter-out $(FULLBUILD_TARGETS),check)),)
	+ $(SHOWIT)if $(MAKEMD) $(FULLBUILDFLAGS) libbuild TARGET=libbuild VAR=check NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: check library build failed. " ; \
	  exit 1; \
        fi ; 
        endif 

        # debug build
        ifeq ($(strip $(filter-out $(FULLBUILD_TARGETS),debug)),)
	+ $(SHOWIT)if $(MAKEMD) $(FULLBUILDFLAGS) libbuild TARGET=libbuild VAR=debug NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: debug library build failed. " ; \
	  exit 1; \
        fi ; 
        endif

        # opt build
        ifeq ($(strip $(filter-out $(FULLBUILD_TARGETS),opt)),)
	+ $(SHOWIT)if $(MAKEMD) $(FULLBUILDFLAGS) libbuild TARGET=libbuild VAR=opt NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: opt library build failed. " ; \
	  exit 1; \
        fi ; 
        endif 

        # checkshared build 
        ifeq ($(strip $(filter-out $(FULLBUILD_TARGETS),checkshared)),)
	+ $(SHOWIT)if $(MAKEMD) $(FULLBUILDFLAGS) libbuild TARGET=libbuild VAR=check SHAREDBUILD=1 NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: check shared library build failed. " ; \
	  exit 1; \
        fi ;
        endif

        # debugshared build 
        ifeq ($(strip $(filter-out $(FULLBUILD_TARGETS),debugshared)),)
	+ $(SHOWIT)if $(MAKEMD) $(FULLBUILDFLAGS) libbuild TARGET=libbuild VAR=debug SHAREDBUILD=1 NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: debug-shared library build failed. " ; \
	  exit 1; \
        fi ; 
        endif 

         # optshared build
        ifeq ($(strip $(filter-out $(FULLBUILD_TARGETS),optshared)),)
	+ $(SHOWIT)if $(MAKEMD) $(FULLBUILDFLAGS) libbuild TARGET=libbuild VAR=opt SHAREDBUILD=1 NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: opt-shared library build failed. " ; \
	  exit 1; \
        fi ;
        endif

        # checkbin build (builds the binaries - must have libs already)
        ifeq ($(strip $(filter-out $(FULLBUILD_TARGETS),checkbin)),)
	+ $(SHOWIT)if $(MAKEMD) $(FULLBUILDFLAGS) fullbuild TARGET=fullbuild VAR=check ; then true; \
        else \
	  echo "QMAKE: check binaries build failed. " ; \
	  exit 1; \
        fi ;
        endif 

        # optbin build (builds the binaries - must have libs already)
        ifeq ($(strip $(filter-out $(FULLBUILD_TARGETS),optbin)),)
	+ $(SHOWIT)if $(MAKEMD) $(FULLBUILDFLAGS) fullbuild TARGET=fullbuild VAR=opt ; then true; \
        else \
	  echo "QMAKE: opt binaries build failed. " ; \
	  exit 1; \
        fi ;
        endif 

        # documentation 
        ifeq ($(strip $(filter-out $(FULLBUILD_TARGETS),doc)),)
	$(SHOWIT)echo "Building documentation. " ; \
	$(MAKEDC) $(FULLBUILDFLAGS) doc 
         endif 

rpmbuild:
	+ $(SHOWIT)if $(MAKEMO) $(FULLBUILDFLAGS) src_all NOINCDEFS=1 ; then true; \
        else \
	  echo "QMAKE: Installation of header files failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) libbuild TARGET=libbuild VAR=check NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: check library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) libbuild TARGET=libbuild VAR=debug NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: debug library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) libbuild TARGET=libbuild VAR=opt NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: opt library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) libbuild TARGET=libbuild VAR=check SHAREDBUILD=1 NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: check shared library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) fullbuild TARGET=fullbuild VAR=check SHAREDBUILD=1 ; then true; \
        else \
	  echo "QMAKE: check binary build failed. " ; \
	  exit 1; \
        fi ; \
	echo "Building documentation. " ; \
	$(MAKEDC) $(FULLBUILDFLAGS) doc 

fullshared:
	+ $(SHOWIT)if $(MAKEMD) $(FULLBUILDFLAGS) fullbuild TARGET=fullbuild VAR=check SHAREDBUILD=1 NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: Shared library build failed. " ; \
	  exit 1; \
        fi ; \

fulldoc:
	$(SMAKEDC) doc $(FULLBUILDFLAGS)

# Make a defs.mk file automaticly.

mkdef:
	$(MAKEDEFS) -i .

##########################################################
# Util

mirror:
	$(SMAKEUT) mirror

srcinst:
	$(SMAKEUT) srcinst

listoff:
	$(SMAKEUT) listoff

listco:
	$(SMAKEUT) listco

listfix:
	$(SMAKEUT) listfix

listlocked:
	$(SMAKEUT) listlocked

################################
# Admin

clean:
	-$(SMAKECL) clean TARGET=clean

cleanlib:
	$(SMAKECL) cleanlib TARGET=cleanlib

cleandep:
	$(SMAKECL) cleandep TARGET=cleandep

cleandoc:
	$(SMAKECL) cleandoc TARGET=cleandoc 

optclean:
	$(SMAKECL) clean TARGET=clean VAR=opt

dbclean:
	$(SMAKECL) clean TARGET=clean VAR=debug

chkclean:
	$(SMAKECL) clean TARGET=clean VAR=check

lib_info:
	$(SMAKEMO) lib_info

info:
	$(SMAKEMO) info

udchangelog:
	$(SMAKEUT) udchangelog

co:
	$(SMAKEUT) co

ci:
	$(SMAKEUT) ci

pack:
	$(SMAKEMO) NOINCDEFS=1 pack

unpack:
	$(SMAKEMO) NOINCDEFS=1 unpack

################################
# Documentation.

# Install files, build documentation
doc: src
	$(SMAKEDC) doc

# Just install files.
docinit: src
	$(SMAKEDC) docinit

# Just build documentation
redoc:
	$(SMAKEDC) doc


###################################
# Clean up.

distclean:
	@echo "--- Cleaning project out. "; \
	rm -rf $(ROOTDIR)/* \
	rm -rf $(LOCALTMP)/*

###############################################
# Misc

$(MAKEHOME)/config.$(ARC) :
	@true

$(MAKEHOME)/Dirs.mk :
	@true

$(MAKEHOME)/GlobalMake :
	@true

$(MAKEHOME)/MainDep.mk :
	@true

###############################################
# Help

defs:
	@$(PAGER) $(MAKEHOME)/Defs.txt

defs.mk:
	@echo "Can't find defs.mk in current directory, aborting. ";
	@echo "Use 'qm defs' for more information. ";

.DEFAULT help:
	@$(PAGER) $(MAKEHOME)/Help.txt
