# This file is part of QMake, Quick Make System 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
################################
# Quick RAVL make system
# $Id$
#! rcsid="$Id$"
#! file="Ravl/QMake/Clean.mk"

ifndef MAKEHOME
 MAKEHOME = /vol/vssp/cpug/RAVL/src/Util/QMake
endif

MAKEFLAGS += --no-print-directory -r 

ifndef ARC
  ARC=$(shell $(MAKEHOME)/config.arc)#
endif

ifdef QMAKE_INFO
  SHOWIT = 
else
  SHOWIT = @
endif

ifndef QCWD
  QCWD := $(shell 'pwd')
endif

include $(MAKEHOME)/config.$(ARC)
-include $(QCWD)/defs.mk

##########################
# Clean up defs stuff.

ifndef PLIB
ifdef SLIB
PLIB=$(SLIB)
endif
endif

SLIB:=$(strip $(SLIB))
PLIB:=$(strip $(PLIB))

include $(MAKEHOME)/Dirs.mk

.PHONY : clean cleandep cleanii

VPATH = $(QCWD)


TARG_NESTED =$(patsubst %.r,%,$(filter %.r,$(NESTED)))

#############################
# Clean up.

#	$(SHOWIT)if [ -d $(WORKTMP) ] ; then \
#	  $(RM) -r $(WORKTMP) ; \
#	fi ; 

#	if [ -r ii_files ] ; then \
#	  $(RM) ii_files ; \
#	fi ; 

clean: subdirs
	$(SHOWIT)if [ -d $(WORKTMP) ] ; then \
	  $(RM) -r $(WORKTMP) ; \
	fi ; 

cleanlib: subdirs
	$(SHOWIT)if [ -d $(WORKTMP) ] ; then \
	  $(RM) -r $(WORKTMP) ; \
	fi ; \
	if [ -f $(INST_LIB)/lib$(PLIB).a ] ; then \
	  $(RM) $(INST_LIB)/lib$(PLIB).a ; \
	fi ; 

cleandep: subdirs
	$(SHOWIT)if [ -d $(INST_DEPEND) ] ; then \
	  $(RM) -r $(INST_DEPEND)/*.d ; \
	fi ; 

subdirs:
	$(SHOWIT)echo "------ Cleaning $(ARC)/$(VAR)/$(BASENAME)   $(TARGET)" ; \
	for SUBDIR in stupid_for_loop_thing $(TARG_NESTED) ; do \
	  if [ -d $$SUBDIR ] ; then \
	   $(MAKE) $(TARGET) TARGET=$(TARGET) -C $$SUBDIR -f $(MAKEHOME)/Clean.mk $(DEF_INC) ; \
	  fi  \
	done

#include $(MAKEHOME)/rcs.mk
