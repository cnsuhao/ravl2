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
  PROJECT_OUT := $(shell 'pwd')
else
ifeq ($(PROJECT_OUT),"")
  PROJECT_OUT := $(shell 'pwd')
endif
endif

export PROJECT_OUT

# Setup default build target.

TARGET=fullbuild

include $(MAKEHOME)/config.$(ARC)
NOVAR=1
include $(MAKEHOME)/Dirs.mk

# The following is for logging only.
-include $(QCWD)/defs.mk


VPATH=$(QCWD)

ifdef QMAKE_INFO
  export QMAKE_INFO
endif

.PHONY : all depend opt qopt qdb debug develop qd check distclean \
 clean pack unpack org help isdep srcp srcd org orgopt orgdebug chead \
 lib_info defs mdoc notes qc qcheck src mirror srcinst doconly log \
 fulldoc fullcheck fullsrc fulltest fullbuild shared

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
# Compilation targets.

src:
	$(SMAKEMO) src_all NOINCDEFS=1 TARGET=src_all 

novar:
	$(SMAKEMD) fullbuild TARGET=fullbuild  

opt:
	$(SMAKEMD) fullbuild VAR=opt TARGET=fullbuild  

shared:
	$(SMAKEMD) fullbuild VAR=shared TARGET=fullbuild  

debug:
	$(SMAKEMD) fullbuild VAR=debug TARGET=fullbuild  

debugall:
	$(SMAKEMD) fullbuild VAR=debug BASE_VAR=debug TARGET=fullbuild  

check:
	$(SMAKEMD) fullbuild VAR=check TARGET=fullbuild  

purify:
	$(SMAKEMD) purifybuild VAR=debug PROCS=1 TARGET=purifybuild  

prof:
	$(SMAKEMD) fullbuild VAR=prof TARGET=fullbuild  

gprof:
	$(SMAKEMD) fullbuild VAR=gprof TARGET=fullbuild  

chead:
	$(SMAKEMD) cheadbuild FULLCHECKING=1 TARGET=cheadbuild  

ne:	
	$(SMAKEMD) fullbuild VAR=check TARGET=fullbuild NOEXEBUILD=1 

optne:
	$(SMAKEMD) fullbuild VAR=opt TARGET=fullbuild NOEXEBUILD=1 

debugne:
	$(SMAKEMD) fullbuild VAR=debug TARGET=fullbuild NOEXEBUILD=1 

gprofne:
	$(SMAKEMD) fullbuild VAR=gprof TARGET=fullbuild NOEXEBUILD=1 

sharedne:
	$(SMAKEMD) fullbuild VAR=shared TARGET=fullbuild NOEXEBUILD=1

test: src
	@if [ ! -d $(INST_TESTBIN) ] ; then \
	  $(MKDIR) $(INST_TESTBIN); \
	fi 
	@if [ ! -d $(INST_TESTLOG) ] ; then \
	  $(MKDIR) $(INST_TESTLOG); \
	fi 
	+ $(SHOWIT)touch $(INST_TESTDB); \
	if $(MAKEMD) VAR=check testbuild FULLCHECKING=1 NOEXEBUILD=1 TARGET=testbuild ; then true ; \
	else \
	  echo "test: Failed to do inital build for test. "; \
	  exit 1 ; \
	fi ; \
	if $(MAKEMD) VAR=check testbuild FULLCHECKING=1 TARGET=testbuild ; then true ; \
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
	if $(MAKEMD) libbuild VAR=check TARGET=libbuild NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: check library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) libbuild VAR=debug TARGET=libbuild NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: debug library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) libbuild VAR=opt TARGET=libbuild NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: opt library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) fullbuild VAR=opt TARGET=fullbuild  ; then true; \
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

FULLBUILDSRC := BASE_VAR=none FULLCHECKING=1

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

fullbuild:
	+ $(SHOWIT)if $(MAKEMO) $(FULLBUILDFLAGS) src_all NOINCDEFS=1 ; then true; \
        else \
	  echo "QMAKE: Installation of header files failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) libbuild VAR=check TARGET=libbuild NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: check library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) libbuild VAR=debug TARGET=libbuild NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: debug library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) libbuild VAR=opt TARGET=libbuild NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: opt library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) fullbuild VAR=opt TARGET=fullbuild  ; then true; \
        else \
	  echo "QMAKE: executable build failed. " ; \
	  exit 1; \
        fi ; \
	echo "Building documentation. " ; \
	$(MAKEDC) $(FULLBUILDFLAGS) doc 

rpmbuild:
	+ $(SHOWIT)if $(MAKEMO) $(FULLBUILDFLAGS) src_all NOINCDEFS=1 ; then true; \
        else \
	  echo "QMAKE: Installation of header files failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) libbuild VAR=check TARGET=libbuild NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: check library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) libbuild VAR=debug TARGET=libbuild NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: debug library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) libbuild VAR=opt TARGET=libbuild NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: opt library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) libbuild VAR=shared TARGET=libbuild NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: shared library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) fullbuild VAR=shared TARGET=fullbuild  ; then true; \
        else \
	  echo "QMAKE: executable build failed. " ; \
	  exit 1; \
        fi ; \
	echo "Building documentation. " ; \
	$(MAKEDC) $(FULLBUILDFLAGS) doc 

fullshared:
	+ $(SHOWIT)if $(MAKEMD) $(FULLBUILDFLAGS) fullbuild VAR=shared TARGET=fullbuild NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: Shared library build failed. " ; \
	  exit 1; \
        fi ; \

fulldoc:
	$(SMAKEDC) doc    $(FULLBUILDFLAGS)

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
	$(SMAKECL) clean TARGET=clean

cleanlib:
	$(SMAKECL) cleanlib TARGET=cleanlib

cleandep:
	$(SMAKECL) cleandep TARGET=cleandep

optclean:
	$(SMAKECL) clean VAR=opt TARGET=clean

dbclean:
	$(SMAKECL) clean VAR=debug TARGET=clean

chkclean:
	$(SMAKECL) clean VAR=check TARGET=clean

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
	@echo "--- Cleaning project out. \n"; \
	rm -rf $(ROOTDIR)/*

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

notes:
	@$(PAGER) $(MAKEHOME)/Notes.txt

defs:
	@$(PAGER) $(MAKEHOME)/Defs.txt

defs.mk:
	@echo "Can't find defs.mk in current directory, aborting. ";
	@echo "Use 'qm defs' for more information. ";

.DEFAULT help:
	@$(PAGER) $(MAKEHOME)/Help.txt
