# This file is part of QMake, Quick Make System 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
################################
# Quick RAVL make system.
# Documentation make file.
# $Id$
#! rcsid="$Id$"
#! file="Ravl/QMake/Doc.mk"

ifndef MAKEHOME
  MAKEHOME=.
endif

ifndef INSTALLHOME
 INSTALLHOME = $(MAKEHOME)/../../..#
endif

MAKEFLAGS += --no-print-directory -r 
CXXDOC=$(INSTALLHOME)/lib/RAVL/$(ARC)/bin/CxxDoc

AUTOTEMPL=$(MAKEHOME)/../AutoDoc

#/vol/vssp/cpug/Ravl/src/doc/Auto

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

ifdef PACKAGENAME
PACKAGENAME_OPT=-pn $(PACKAGENAME)
else
PACKAGENAME_OPT= 
endif

ifdef PACKAGEDESC
PACKAGEDESC_OPT=-pd "$(DESCRIPTION)"
else
PACKAGEDESC_OPT= 
endif

ifdef INCLUDEDIR
INCLUDE_OPT=-i $(INCLUDEDIR)
else
INCLUDE_OPT= 
endif



SLIB:=$(strip $(SLIB))
PLIB:=$(strip $(PLIB))

include $(MAKEHOME)/Dirs.mk

.PHONY : doc do_html bigautodoc autodoc

.PRECIOUS : %/.dir %.html %.eht

VPATH = $(QCWD)

############################
# Some targets

TARG_NESTED =$(patsubst %.r,%,$(filter %.r,$(NESTED)))

TARG_HTML  =$(patsubst %,$(INST_HTML)/%,$(HTML))
TARG_EHT =$(patsubst %,$(INST_EHT)/%,$(EHT))

TARG_MAN1  =$(patsubst %,$(INST_MAN1)/%,$(MAN1))
TARG_MAN3  =$(patsubst %,$(INST_MAN3)/%,$(MAN3))
TARG_MAN5  =$(patsubst %,$(INST_MAN5)/%,$(MAN5))
TARG_DOCEXAMPLES  =$(patsubst %,$(INST_DOCEXAMPLES)/%,$(EXAMPLES))
TARG_DOCNODE=$(patsubst %,$(INST_DOCNODE)/%,$(DOCNODE))

###############################
# Make directories

%/.dir:
	$(SHOWIT)if [ ! -d $* ] ; then \
	  echo "--- Making dir $* "; \
	  $(MKDIR) $* ; \
	  $(TOUCH) -r $(MAKEHOME)/Main.mk $*/.dir ; \
	else  \
	  if [ ! -f $*/.dir ] ; then \
	    $(TOUCH) -r $* $*/.dir ; \
	  fi ; \
	fi; \

#	$(SHOWIT)if [ -d $(WORKTMP) ] ; then \
#	  $(RM) -r $(WORKTMP) ; \
#	fi ; 

#	if [ -r ii_files ] ; then \
#	  $(RM) ii_files ; \
#	fi ; 

#############################
# Build Documentation.

docfiles: $(TARG_MAN1) $(TARG_MAN2) $(TARG_MAN5) $(TARG_DOCEXAMPLES) $(TARG_HTML) $(TARG_EHT) $(TARG_DOCNODE)

docinit: docfiles
	+ $(SHOWIT)for SUBDIR in stupid_for_loop_thing $(TARG_NESTED) ; do \
	  if [ -d $$SUBDIR ] ; then \
	   echo "------ Documenting $(DPATH)/"$$SUBDIR; \
	   $(MAKE) docinit -C $$SUBDIR DPATH=$(DPATH)/$$SUBDIR -f $(MAKEHOME)/Doc.mk $(DEF_INC) ; \
	  fi  \
	done

doc: docinit $(INST_INCLUDE)/.dir $(TARG_DOCNODE)
ifeq ($(ARC),$(LOCALARC))
	$(SHOWIT)echo "--- Generating documentation" ; \
	$(CXXDOC) $(PACKAGENAME_OPT) $(PACKAGEDESC_OPT) $(INCLUDE_OPT) -ih $(INSTALLHOME) -p $(PROJECT_OUT)
endif

$(INST_EHT)/% : % $(INST_EHT)/.dir
	$(SHOWIT)echo "--- Installing EHT $(@F) to $(INST_EHT)" ; \
	if [ -f $(INST_EHT)/$(@F) ] ; then \
	  chmod +w $(INST_EHT)/$(@F) ; \
	fi ; \
	$(CP) $< $(INST_EHT)/$(@F) ; \
	$(CHMOD) 444 $(INST_EHT)/$(@F)

$(INST_HTML)/% : % $(INST_HTML)/.dir
	$(SHOWIT)echo "--- Installing HTML $(@F)" ; \
	if [ -f $(INST_HTML)/$(@F) ] ; then \
	  $(CHMOD) +w $(INST_HTML)/$(@F) ; \
	fi ; \
	$(CP) $< $(INST_HTML)/$(@F) ; \
	$(CHMOD) 444 $(INST_HTML)/$(@F)

$(INST_MAN1)/% : % $(INST_MAN1)/.dir
	$(SHOWIT)echo "--- Installing man 1 $(@F)" ; \
	if [ -f $(INST_MAN1)/$(@F) ] ; then \
	  $(CHMOD) +w $(INST_MAN1)/$(@F) ; \
	fi ; \
	$(CP) $< $(INST_MAN1)/$(@F) ; \
	$(CHMOD) 444 $(INST_MAN1)/$(@F)

$(INST_MAN3)/% : % $(INST_MAN3)/.dir
	$(SHOWIT)echo "--- Installing man 3 $(@F)" ; \
	if [ -f $(INST_MAN3)/$(@F) ] ; then \
	  $(CHMOD) +w $(INST_MAN3)/$(@F) ; \
	fi ; \
	$(CP) $< $(INST_MAN3)/$(@F) ; \
	$(CHMOD) 444 $(INST_MAN3)/$(@F)

$(INST_MAN5)/% : % $(INST_MAN5)/.dir
	$(SHOWIT)echo "--- Installing man 5 $(@F)" ; \
	if [ -f $(INST_MAN5)/$(@F) ] ; then \
	  $(CHMOD) +w $(INST_MAN5)/$(@F) ; \
	fi ; \
	$(CP) $< $(INST_MAN5)/$(@F) ; \
	$(CHMOD) 444 $(INST_MAN5)/$(@F)


$(INST_DOCEXAMPLES)/% : % $(INST_DOCEXAMPLES)/.dir
	$(SHOWIT)echo "--- Installing examples $(@F)" ; \
	if [ -f $(INST_DOCEXAMPLES)/$(@F) ] ; then \
	  $(CHMOD) +w $(INST_DOCEXAMPLES)/$(@F) ; \
	fi ; \
	$(CP) $< $(INST_DOCEXAMPLES)/$(@F); \
	$(CHMOD) 444 $(INST_DOCEXAMPLES)/$(@F)

$(INST_DOCNODE)/% : % $(INST_DOCNODE)/.dir
	$(SHOWIT)echo "--- Installing DocNode $(@F)" ; \
	if [ -f $(INST_DOCNODE)/$(@F) ] ; then \
	  chmod +w $(INST_DOCNODE)/$(@F) ; \
	fi ; \
	$(CP) $< $(INST_DOCNODE)/$(@F) ; \
	$(CHMOD) 444 $(INST_DOCNODE)/$(@F)
