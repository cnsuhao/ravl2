# This file is part of QMake, Quick Make System 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/QMake/Main.mk"

ifndef MAKEHOME
  MAKEHOME=.
endif

ifndef INSTALLHOME
 INSTALLHOME = $(MAKEHOME)/../../..#
endif

export TARGET

MAKEFLAGS += --no-print-directory -r 

ifndef QCWD
 QCWD :=$(shell sh -c "if [ -x /usr/bin/pawd ] ; then /usr/bin/pawd ; else pwd ; fi")
endif

# Setup default pager.
ifndef PAGER
 PAGER = more
endif

# The following is needed to avoid problems with
SYNC=sync

#########################
# Include user make info.

# Setup defaults first

ANSIFLAG = -ansi

ifdef USERBUILD
 USESLIBS = Auto
endif

ifndef VAR
 VAR=check
endif

# Include a local system file
include $(MAKEHOME)/config.local.$(ARC)

# Include system stuff.

include $(MAKEHOME)/config.$(ARC)

# Include users stuff.

-include $(QCWD)/defs.mk

#########################
# Setup defaults.

BINDEP := perl $(MAKEHOME)/BinDep.pl
QLIBS := perl $(MAKEHOME)/QLibs.pl

ifndef TOUCH
  TOUCH=touch
endif

ifeq ($(VAR),shared)
  LIBEXT:=.so
else
  LIBEXT:=.a
endif

# Default Object file extension
ifndef OBJEXT
  OBJEXT:=.o#
endif

# Default C++ source file extension.
ifndef CXXEXT
  CXXEXT:=.cc#
endif

# Default C++ auxilary source file extension. (used to force template instansiation.)
ifndef CXXAUXEXT
  CXXAUXEXT:=.cxx#
endif

# Default C++ header file extension.
ifndef CHXXEXT
  CHXXEXT:=.hh#
endif

# Default C source file extension.
ifndef CEXT
  CEXT:=.c#
endif

# Default C header file extension.
ifndef CHEXT
  CHEXT:=.h#
endif

# Extension expected on executables.
ifndef EXEEXT
  EXEEXT:=#
endif


##########################
# Clean up defs stuff.

ifdef PLIB
 PLIB:=$(strip $(PLIB))#
endif
ifdef USESLIBS
 USESLIBS:=$(strip $(USESLIBS))#
endif

AUXDIR:=$(strip $(AUXDIR))#

UNTOUCH:=$(INSTALLHOME)/lib/RAVL/$(ARC)/bin/untouch

###########################
# Platform supported ?

ifneq (,$(SUPPORT_ONLY))
 ifeq ($(ARC),$(filter $(ARC),$(SUPPORT_ONLY)))
  SUPPORT_OK=yes
 else
  SUPPORT_OK=no
  NOINCDEFS=1
 endif
else
 ifeq ($(ARC),$(filter $(ARC),$(DONOT_SUPPORT)))
  SUPPORT_OK=no
  NOINCDEFS=1
 else
  SUPPORT_OK=yes
 endif
endif

########################
# Setup directories etc.

# Compile examples as well when doing a test build.
ifeq ($(TARGET),testbuild)
  MAINS := $(sort $(MAINS) $(EXAMPLES))
endif

include $(MAKEHOME)/Dirs.mk

ifndef MKMUSTLINK
  MKMUSTLINK := $(patsubst %$(CEXT),$(INST_FORCEOBJS)/%$(OBJEXT), $(patsubst %$(CXXEXT),%$(CEXT), $(MUSTLINK)))
endif

ifdef USESLIBS
 ifndef LIBDEPS
  ifdef PLIB
   LOCAL_DEFBASE=$(PLIB)#
   DEFVARNAME:=$(LOCAL_DEFBASE)_AUTO_DEF#
   $(DEFVARNAME) := 1
  endif
 else
  LOCAL_DEFBASE = $(patsubst %.def,%,$(LIBDEPS))
  DEFVARNAME:=$(LOCAL_DEFBASE)_AUTO_DEF#
  $(DEFVARNAME) := 1
 endif
endif

ifdef USESLIBS
 ifneq ($(USESLIBS),)
  ifneq ($(USESLIBS),None)
   ifeq ($(filter Auto,$(USESLIBS)),Auto)
    AUTOUSELIBS := $(shell $(QLIBS) -use -d -p $(ROOTDIR))
    EXTRA_USESLIBS = $(AUTOUSELIBS) $(patsubst %,%.def,$(filter-out Auto,$(USESLIBS)))
    ifdef LIBDEPS
     ifdef PLIB
      AUTOUSELIBS := $(PLIB).def $(AUTOUSELIBS)
     endif 
    endif
   else
    EXTRA_USESLIBS = $(patsubst %,%.def,$(USESLIBS))
   endif
   ifndef NOINCDEFS
    ifneq ($(strip $(EXTRA_USESLIBS)),)
     include $(EXTRA_USESLIBS)
    endif
   endif
  endif
 endif
else
 ifdef LIBDEPS
# -include $(patsubst %,$(INST_LIBDEF)/%,$(LIBDEPS))
  -include $(LIBDEPS)
 endif
endif
ifdef PLIB
 EXELIB := $(MKMUSTLINK) -l$(PLIB) $(EXELIB)
endif
LIBLIBS := $(EXELIB)
ifndef NOINCDEFS
 REQUIRED_PROGLIBS=$(patsubst %,%.def,$(filter-out %.opt,$(PROGLIBS)))
 OPTIONAL_PROGLIBS=$(patsubst %.opt,%.def,$(PROGLIBS))
 ifneq ($(strip $(REQUIRED_PROGLIBS)),)
  include $(REQUIRED_PROGLIBS)
 endif
 ifneq ($(strip $(OPTIONAL_PROGLIBS)),)
  -include $(OPTIONAL_PROGLIBS)
$(OPTIONAL_PROGLIBS) :
	@true;
 endif
endif
ifeq ($(filter Auto,$(USESLIBS)),Auto)
 ifneq ($(strip $(MAINS) $(TESTEXES)),)
  AUTOPROGLIBS := $(shell $(QLIBS) -prog -d -p $(ROOTDIR))
  ifdef LIBDEPS
   AUTOPROGLIBS := $(filter-out $(LIBDEPS),$(AUTOPROGLIBS))
  endif
  ifdef PLIB
   AUTOPROGLIBS := $(PLIB).def $(AUTOPROGLIBS)
  endif
  ifndef NOINCDEFS
   ifneq ($(strip $(AUTOPROGLIBS)),)
    include $(AUTOPROGLIBS)
   endif
  endif
 endif
endif

LINKLIBS := $(EXELIB)
EXELIB := $(LIBLIBS)


VPATH = $(QCWD)

.PRECIOUS : %$(CXXEXT) %$(CHXXEXT) %$(CEXT) %$(CHEXT) %.tcc %.icc %.def %.tab.cc %.yy.cc 


############################
# Misc setup

# Tell the programs where they'll live.
# Usefull for making default paths to data files.

PREPROCFLAGS = -DPROJECT_OUT=\"$(PROJECT_OUT)\" -DCPUG_ARCH=\"$(ARC)\"

ifeq ($(VAR),shared)
PREPROCFLAGS += -DCPUG_VAR_SHARED=1
endif

ifdef LOCALHEADERS
 INCLUDES+=-I.
endif

# C Flags. 
CPPFLAGS += $(USERCPPFLAGS) $(PREPROCFLAGS)
CFLAGS += $(USERCFLAGS) $(ANSIFLAG)

# C++ Flags
CCPPFLAGS += $(USERCPPFLAGS) $(PREPROCFLAGS) 
CCFLAGS += $(USERCFLAGS) $(ANSIFLAG)


ifdef QMAKE_INFO
  SHOWIT=
else
  SHOWIT=@
endif

#####################
# Build targets.

# $(LOCALHEADERS)
JAVA_SRC = $(filter %.java,$(SOURCES) $(MAINS))

ifeq ($(SUPPORT_OK),yes)
 TARG_MUSTLINK_OBJS=$(patsubst %$(CEXT),$(INST_FORCEOBJS)/%$(OBJEXT), \
    $(patsubst %$(CXXEXT),$(INST_FORCEOBJS)/%$(OBJEXT), $(MUSTLINK)))
 TARG_BASEOBJS=$(patsubst %$(CEXT),$(INST_OBJS)/%$(OBJEXT), \
    $(patsubst %.S,$(INST_OBJS)/%$(OBJEXT), \
    $(patsubst %.y,$(INST_OBJS)/%.tab$(OBJEXT), \
    $(patsubst %.l,$(INST_OBJS)/%.yy$(OBJEXT), \
    $(patsubst %$(CXXEXT),$(INST_OBJS)/%$(OBJEXT),$(SOURCES))))))
 TARG_OBJS=$(patsubst %$(CXXAUXEXT),$(INST_OBJS)/%$(OBJEXT),$(TARG_BASEOBJS))
 TARG_HDRS:=$(patsubst %,$(INST_HEADER)/%,$(HEADERS))
 ifdef FULLCHECKING
  TARG_HDRCERTS:=$(patsubst %$(CHXXEXT),$(INST_HEADERCERT)/%$(CHXXEXT),$(HEADERS)) $(patsubst %$(CHEXT),$(INST_HEADERCERT)/%$(CHEXT),$(HEADERS))
 else
  TARG_HDRCERTS=
 endif
#$(INST_DEPEND)/%.java.d
 TARG_DEFS=$(patsubst %,$(INST_LIBDEF)/%,$(LIBDEPS))
 TARG_EXE := $(patsubst %$(CEXT),$(INST_BIN)/%$(EXEEXT), $(patsubst %$(CXXEXT),$(INST_BIN)/%$(EXEEXT),$(filter-out %.java,$(MAINS))))
 TARG_PUREEXE := $(patsubst %$(CEXT),$(INST_BIN)/pure_%$(EXEEXT), $(patsubst %$(CXXEXT),$(INST_BIN)/pure_%$(EXEEXT),$(filter-out %.java,$(MAINS))))
 TARG_EXEOBJS=$(patsubst %$(CEXT),$(INST_OBJS)/%$(OBJEXT),$(patsubst %$(CXXEXT),$(INST_OBJS)/%$(OBJEXT),$(filter-out %.java,$(MAINS))))
 TARG_TESTEXE := $(patsubst %$(CEXT),$(INST_TESTBIN)/%$(EXEEXT), $(patsubst %$(CXXEXT),$(INST_TESTBIN)/%$(EXEEXT),$(TESTEXES)))
 TARG_TESTEXEOBJS=$(patsubst %$(CEXT),$(INST_OBJS)/%$(OBJEXT),$(patsubst %$(CXXEXT),$(INST_OBJS)/%$(OBJEXT),$(TESTEXES)))
ifndef NOEXEBUILD
 TARG_DEPEND:= $(patsubst %$(CXXAUXEXT),$(INST_DEPEND)/%.d, \
	       $(patsubst %$(CEXT),$(INST_DEPEND)/%.d, \
	       $(patsubst %.S,$(INST_DEPEND)/%.S.d, \
	       $(patsubst %.y,$(INST_DEPEND)/%.tab.d, \
	       $(patsubst %.l,$(INST_DEPEND)/%.yy.d, \
               $(patsubst %$(CXXEXT),$(INST_DEPEND)/%.d, \
	       $(patsubst %.java,,$(SOURCES) $(MUSTLINK)))))))) \
               $(patsubst %$(CEXT),$(INST_DEPEND)/%.d, \
               $(patsubst %$(CXXEXT),$(INST_DEPEND)/%.d, \
	       $(patsubst %.java,$(INST_DEPEND)/%.java.d,$(MAINS) $(TESTEXES)))) \
               $(patsubst %$(CEXT),$(INST_DEPEND)/%.$(VAR).bin.d,  \
               $(patsubst %$(CXXEXT),$(INST_DEPEND)/%.$(VAR).bin.d, \
               $(filter-out %.java,$(MAINS)))) $(INST_DEPEND)/.dir
else
 TARG_DEPEND:= $(patsubst %$(CXXAUXEXT),$(INST_DEPEND)/%.d, \
	       $(patsubst %$(CEXT),$(INST_DEPEND)/%.d, \
	       $(patsubst %.S,$(INST_DEPEND)/%.S.d, \
	       $(patsubst %.y,$(INST_DEPEND)/%.tab.d, \
	       $(patsubst %.l,$(INST_DEPEND)/%.yy.d, \
               $(patsubst %$(CXXEXT),$(INST_DEPEND)/%.d, \
	       $(patsubst %.java,,$(SOURCES) $(MUSTLINK)))))))) $(INST_DEPEND)/.dir
endif
 TARG_JAVA    =$(patsubst %.java,$(INST_JAVA)/%.class,$(JAVA_SRC))
 TARG_JAVAEXE =$(patsubst %.java,$(INST_JAVAEXE)/%,$(filter %.java,$(MAINS)))
 TARG_NESTED =$(patsubst %.r,%,$(filter %.r,$(NESTED)))
 TARG_SCRIPT =$(patsubst %,$(INST_GENBIN)/%,$(SCRIPTS))
 OBJS_DEPEND = $(patsubst %$(CEXT),$$(INST_OBJS)/%$(OBJEXT),$(patsubst %$(CXXEXT),$$(INST_OBJS)/%$(OBJEXT) ,$(SOURCES) $(MUSTLINK)))
 TARG_USESLIBS = $(patsubst %,%.def,$(filter-out Auto,$(USESLIBS)))
 TARG_AUXFILES = $(patsubst %,$(INST_AUX)/%,$(AUXFILES))

 ifdef USESLIBS
  ifndef LIBDEPS
   ifdef PLIB
    TARG_DEFS=$(INST_LIBDEF)/$(LOCAL_DEFBASE).def
   endif
  endif
 endif

 ifneq (,$(PLIB))
  TARG_LIBS=$(strip $(patsubst %,$(INST_LIB)/lib%$(LIBEXT),$(PLIB)))#
 else
  TARG_LIBS=
 endif

else
 TARG_OBJS=
 TARG_HDRS=
 TARG_HDRCERTS=
 TARG_DEFS=
 TARG_LIBS=
 TARG_EXE=
 TARG_EXEOBJS=
 TARG_TESTEXE =
 TARG_TESTEXEOBJS=
 TARG_DEPEND=$(MAKEHOME)/Sys.def
 TARG_NESTED=
 TARG_SCRIPT=
 OBJS_DEPEND=
endif

###############################
# Misc.

BASE_INSTALL := $(INSTALLHOME)#
INCLUDES := -I$(INST_INCLUDE)/$(ARC) -I$(INST_INCLUDE) $(INCLUDES) -I$(BASE_INSTALL)/include/$(ARC) -I$(BASE_INSTALL)/include

ifdef EXTPACKAGE
 INCLUDES += -I$(ROOTDIR)\inc\$(PACKAGE)
endif

CINCLUDES =  -I$(INST_HEADER) $(INCLUDES) -I$(BASE_INSTALL)/include/$(ARC) -I$(BASE_INSTALL)/include

LIBS += -L$(INST_LIB) $(EXELIB) -L$(BASE_INSTALL)/lib/RAVL/$(ARC)/$(BASE_VAR)
BINLIBS += -L$(INST_LIB) $(LINKLIBS)  -L$(BASE_INSTALL)/lib/RAVL/$(ARC)/$(BASE_VAR)

ifeq ($(VAR),shared)
 ifneq ($(BASE_VAR),none)
  LDFLAGS += $(LIBPATHSWITCH)$(ROOTDIR)/lib/RAVL/$(ARC)/$(BASE_VAR)/$(VAR) $(LIBPATHSWITCH)$(RAVL_LIB)
 else 
  LDFLAGS += $(LIBPATHSWITCH)$(ROOTDIR)/lib/RAVL/$(ARC)/$(VAR)
 endif
endif

###############################
# Basic modes.

.PHONY : srcfiles build_subdirs build_testsubdirs build_purifydirs build_libs build_exe \
         all build_aux build_test test build_pureexe fullbuild testbuild purifybuild cheadbuild \
         buildjavalibs libbuild localsrc

all: srcfiles build_aux
	@echo "Internal error: No valid build target "

fullbuild: build_subdirs build_libs build_exe build_aux  $(TARG_HDRCERTS)

testbuild: build_subdirs build_libs build_test  $(TARG_HDRCERTS)

libbuild: build_subdirs build_libs build_aux

purifybuild: build_subdirs build_libs build_pureexe

srcfiles: $(TARG_DEFS) $(TARG_HDRS) $(LOCAL_FILES) $(LOCALHEADERS) $(SOURCES) $(MAINS) $(AUXFILES) $(HEADERS) \
 $(EXAMPLES) $(TESTEXES) $(DOCNODE) $(HTML) $(MAN1) $(MAN2) $(MAN3) $(EHT) $(MUSTLINK)


ifdef FULLCHECKING
cheadbuild: build_subdirs $(TARG_HDRCERTS)
else
chead:
	echo "ERROR: chead must be used with FULLCHECKING!" ; \
	false
endif

###############################
# Make directories

.PRECIOUS : %/.dir

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


###########################
# Nested directories

build_subdirs: srcfiles
ifneq ($(strip $(TARG_NESTED)),)
	+ $(SHOWIT)for SUBDIR in $(TARG_NESTED) ; do \
	  if [ -d $$SUBDIR ] ; then \
	   echo "------ Making $(DPATH)/"$$SUBDIR ; \
	   if ( $(MAKEMD) $(TARGET) TARGET=$(TARGET) -C $$SUBDIR DPATH=$(DPATH)/$$SUBDIR ) ; then \
	     true; \
	   else \
	     echo "Error making $(QCWD)/"$$SUBDIR ; \
	     exit 1 ; \
	   fi \
	  else \
	   echo "----- Directory $$SUBDIR not found, skipping. " ; \
	  fi \
	done
else
	@true
endif

src_all: srcfiles
ifneq ($(strip $(TARG_NESTED)),)
	+ $(SHOWIT)for SUBDIR in $(TARG_NESTED) ; do \
	  if [ -d $$SUBDIR ] ; then \
	   echo "------ Source $(DPATH)/"$$SUBDIR; \
	   if ( $(MAKEMO) src_all -C $$SUBDIR DPATH=$(DPATH)/$$SUBDIR ) ; then \
	     true ; \
	   else \
	     echo "Error sourcing $(QCWD)/"$$SUBDIR ; \
	     exit 1 ; \
	   fi \
	  else \
	   echo "----- Directory $$SUBDIR not found, skipping. " ; \
	  fi \
	done
else
	@true
endif

###########################
# Source header files.

ifdef FULLCHECKING
# Check headers.

$(INST_HEADERCERT)/%$(CHXXEXT) : %$(CHXXEXT) $(TARG_HDRS) $(INST_HEADERCERT)/.dir $(WORKTMP)/.dir
	$(SHOWIT)echo "--- Checking header $(@F)" ; \
	cat $< $< > $(WORKTMP)/$<$(CXXEXT) ; \
	if $(CXX) -c $(CCPPFLAGS) $(CCFLAGS) $(INCLUDES) -o $(WORKTMP)/$<$(OBJEXT) $(WORKTMP)/$<$(CXXEXT)  ; then \
	  $(TOUCH) $(INST_HEADERCERT)/$< ; \
	else  \
	  $(RM) $(WORKTMP)/$<$(OBJEXT) $(WORKTMP)/$<$(CXXEXT) ; \
	  exit 1 ; \
	fi ; \
	$(RM) $(WORKTMP)/$<$(OBJEXT) $(WORKTMP)/$<$(CXXEXT)  

$(INST_HEADERCERT)/%$(CHEXT) : %$(CHEXT) $(TARG_HDRS) $(INST_HEADERCERT)/.dir $(WORKTMP)/.dir
	$(SHOWIT)echo "--- Checking header $(@F)" ; \
	cat $< $< > $(WORKTMP)/$<$(CEXT) ; \
	if $(CC) -c $(CPPFLAGS) $(CFLAGS) $(CINCLUDES) -o $(WORKTMP)/$<$(OBJEXT) $(WORKTMP)/$<$(CEXT)  ; then \
	  $(TOUCH) $(INST_HEADERCERT)/$< ; \
	else \
	  $(RM) $(WORKTMP)/$<$(OBJEXT) $(WORKTMP)/$<$(CEXT) ; \
	  exit 1 ; \
	fi ; \
	$(RM) $(WORKTMP)/$<$(OBJEXT) $(WORKTMP)/$<$(CEXT)
endif

$(TARG_HDRS) : $(INST_HEADER)/% : % $(INST_HEADER)/.dir
	$(SHOWIT)echo "--- Install header $(@F)" ; \
	if [ -f $(INST_HEADER)/$(@F) ] ; then \
	  $(CHMOD) +w $(INST_HEADER)/$(@F) ; \
	fi ; \
	echo "#line 1 \"$(QCWD)/$(@F)\"" > $(INST_HEADER)/$(@F) ; \
	cat  $< >> $(INST_HEADER)/$(@F) ; \
	$(CHMOD) a-w,a+r,a-x $(INST_HEADER)/$(@F)

build_aux: $(TARG_AUXFILES)

ifndef AUXINSTALL
  AUXINSTALL=$(CP)
endif

$(TARG_AUXFILES) : $(INST_AUX)/% : % $(INST_AUX)/.dir
	$(SHOWIT)echo "--- Install aux file $(@F)" ; \
	if [ -f $(INST_AUX)/$(@F) ] ; then \
	  $(CHMOD) +w $(INST_AUX)/$(@F) ; \
	fi ; \
	$(AUXINSTALL) $< $(INST_AUX)/$(@F) ; \
	$(CHMOD) a-w $(INST_AUX)/$(@F)


#############################
# Build depends

# Binary depends.

$(INST_DEPEND)/%.$(VAR).bin.d : %$(CXXEXT) $(QCWD)/defs.mk $(MAKEHOME)/Dirs.mk $(TARG_DEFS) $(INST_DEPEND)/.dir
	$(SHOWIT)echo "--- Binary dependency" $* ; \
	$(BINDEP) $(LDFLAGS) -P'$$(INST_BIN)/$* : $$(INST_OBJS)/$*$(OBJEXT) $(OBJS_DEPEND)' -T$(INST_LIB)/lib$(PLIB)$(LIBEXT) $(BINLIBS) >$(INST_DEPEND)/$(@F)

$(INST_DEPEND)/%.$(VAR).bin.d : %$(CEXT) $(QCWD)/defs.mk $(MAKEHOME)/Dirs.mk $(TARG_DEFS) $(INST_DEPEND)/.dir
	$(SHOWIT)echo "--- Binary dependency" $* ; \
	$(BINDEP) $(LDFLAGS) -P'$$(INST_BIN)/$* : $$(INST_OBJS)/$*$(OBJEXT) $(OBJS_DEPEND)' -T$(INST_LIB)/lib$(PLIB)$(LIBEXT) $(BINLIBS) >$(INST_DEPEND)/$(@F)

# Depend flag

$(TARG_DEPFLAG) :: $(INST_DEPEND)/.dir
	@echo "#Just a dummy file. " > $(TARG_DEPFLAG)

$(TARG_HDRFLAG) : $(TARG_HDRS) $(LOCAL_FILES) $(LOCALHEADERS) $(INST_DEPEND)/.dir
	@echo "#Just a dummy file. " > $(TARG_HDRFLAG)

ifdef LOCAL_DEFBASE
 LOCALDEF_FILE = $(INST_LIBDEF)/$(LOCAL_DEFBASE).def 
endif

###########################
# compile objects.

 $(TARG_MUSTLINK_OBJS) : $(INST_FORCEOBJS)/%$(OBJEXT) : $(INST_OBJS)/%$(OBJEXT) $(INST_FORCEOBJS)/.dir
	$(SHOWIT)echo "--- Must Link $(@F) " ; \
	if [ -f $(INST_FORCEOBJS)/$(@F) ] ; then \
	  $(CHMOD) +w $(INST_FORCEOBJS)/$(@F) ; \
	fi ; \
	$(CP) $(INST_OBJS)/$*$(OBJEXT) $(INST_FORCEOBJS)/$*$(OBJEXT) ; \
	$(CHMOD) a-w $(INST_FORCEOBJS)/$*$(OBJEXT) 

$(INST_OBJS)/%$(OBJEXT) $(INST_DEPEND)/%.d : %$(CXXAUXEXT) $(INST_OBJS)/.dir $(INST_DEPEND)/.dir
	$(SHOWIT)echo "--- Compile" $(VAR) $< ; \
	if [ -f $(WORKTMP)/$*.d ] ; then \
	  rm $(WORKTMP)/$*.d ; \
	fi ; \
	if $(CXX) -c $(CCPPFLAGS) $(CCFLAGS) $(INCLUDES) $(AMKDEPFLAGS) -o $(INST_OBJS)/$*$(OBJEXT) $< ; then \
	  $(MKDEPUP) ; \
	else \
	  false ; \
	fi ; \

$(INST_OBJS)/%$(OBJEXT) $(INST_DEPEND)/%.d : %$(CXXEXT) $(INST_OBJS)/.dir $(INST_DEPEND)/.dir
	$(SHOWIT)echo "--- Compile" $(VAR) $< ; \
	if [ -f $(WORKTMP)/$*.d ] ; then \
	  rm $(WORKTMP)/$*.d ; \
	fi ; \
	if $(CXX) -c $(CCPPFLAGS) $(CCFLAGS) $(INCLUDES) $(AMKDEPFLAGS) -o $(INST_OBJS)/$*$(OBJEXT) $< ;  then \
	  $(MKDEPUP) ; \
	else \
	  false ; \
	fi 

$(INST_OBJS)/%$(OBJEXT) $(INST_DEPEND)/%.d : %$(CEXT) $(INST_OBJS)/.dir $(INST_DEPEND)/.dir
	$(SHOWIT)echo "--- Compile" $(VAR) $< ; \
	if [ -f $(WORKTMP)/$*.d ] ; then \
	  rm $(WORKTMP)/$*.d ; \
	fi ; \
	if $(CC) -c $(CPPFLAGS) $(CFLAGS) $(CINCLUDES)  $(AMKDEPFLAGS) -o $(INST_OBJS)/$*$(OBJEXT) $< ; then \
	  $(MKDEPUP) ; \
	else \
	  false ; \
	fi 

$(INST_OBJS)/%$(OBJEXT) : %.S $(INST_OBJS)/.dir
	$(SHOWIT)echo "--- Assemble" $(VAR) $< ; \
	$(CC) -c -D__ASSEMBLY__=1 $(CPPFLAGS) $(CFLAGS) $(CINCLUDES) -o $(INST_OBJS)/$(@F) $<

# $(UNTOUCH) $(INST_LIB)/lib$(PLIB)$(LIBEXT)  ; \

# Sort out some default.

ifndef BISON
 BISON=bison
endif
ifndef FLEX
 FLEX=flex
endif

%.tab$(CXXEXT) %.tab$(CHEXT) : %.y 
	$(SHOWIT)echo "--- Bison" $< ; \
	$(BISON) -d -o$*.tab$(CEXT) $< ; \
	mv $*.tab$(CEXT) $*.tab$(CXXEXT)

%.yy$(CXXEXT) : %.l
	$(SHOWIT)echo "--- Flex" $< ; \
	$(FLEX) -o$*.yy$(CXXEXT) $<


#############################
# Build libraries.

.SECONDARY : $(INST_LIB)/dummymain$(OBJEXT) 

ifneq ($(strip $(TARG_JAVA)),)
build_libs: $(TARG_LIBS) buildjavalibs
#build_libs: $(TARG_LIBS) $(strip $(TARG_LIBS))($(strip $(TARG_BASEOBJS))) buildjavalibs
else
ifneq ($(strip $(PLIB)),)
ifneq ($(strip $(SOURCES)),)
build_libs: $(TARG_LIBS) $(TARG_LIBS)
#build_libs: $(TARG_LIBS) $(strip $(TARG_LIBS))($(strip $(TARG_BASEOBJS)))
else
build_libs:
endif
else
build_libs:
endif
endif

#$(TARG_JAVA)

$(INST_LIB)/dummymain$(OBJEXT) :: $(MAKEHOME)/dummymain$(CEXT) $(INST_LIB)/.dir
	$(SHOWIT)echo "--- Compile internal dummymain$(OBJEXT) " ; \
	$(CC) -c $(MAKEHOME)/dummymain$(CEXT) $(CFLAGS) $(CPPFLAGS) -o $(INST_LIB)/dummymain$(OBJEXT)


# This lib update is nasty but fast, especialy if you have many objects.
ifndef XARGS
  XARGS = xargs
endif

ifneq ($(VAR),shared)
$(INST_LIB)/lib$(PLIB)$(LIBEXT) : $(TARG_OBJS) $(TARG_MUSTLINK_OBJS) $(INST_LIB)/dummymain$(OBJEXT) $(INST_LIB)/.dir
	$(SHOWIT)echo "--- Building" $(@F) ; \
	$(AR) $(ARFLAGS) $(INST_LIB)/$(@F) $(TARG_OBJS) ; \
	if $(CXX) $(LDFLAGS) $(INST_LIB)/dummymain$(OBJEXT) $(TARG_OBJS) $(LIBS) -o $(WORKTMP)/a.out ; then \
	  rm $(WORKTMP)/a.out ; \
	  $(AR) $(ARFLAGS) $(INST_LIB)/$(@F) $(TARG_OBJS) ; \
	  $(UNTOUCH) $(INST_LIB)/$(@F) $(TARG_OBJS) $(TARG_MUSTLINK_OBJS) ; \
	else \
	  if [ -f $(WORKTMP)/a.out ] ; then \
	    rm $(WORKTMP)/a.out ; \
	  fi ; \
	  exit 1 ; \
	fi
else
$(INST_LIB)/lib$(PLIB)$(LIBEXT) :  $(TARG_OBJS) $(TARG_MUSTLINK_OBJS) $(INST_LIB)/dummymain$(OBJEXT) $(INST_LIB)/.dir
	$(SHOWIT)echo "--- Building" $(@F) ; \
	if [ ! -f $(INST_LIB)/$(@F) ] ; then \
	  $(CC) $(LDLIBFLAGS) -o $(INST_LIB)/$(@F) $(TARG_OBJS) ; \
	fi ; \
	echo "---- Building object list " ; \
	echo "$(patsubst %$(OBJEXT),%$(OBJEXT)@,$(TARG_OBJS))" | tr '@' '\n' >> $(INST_OBJS)/libObjs.txt ; \
	sort -b -u $(INST_OBJS)/libObjs.txt -o $(INST_OBJS)/libObjs.txt ; \
	echo "---- Resolve C++ symbols " ; \
	if $(CXX) $(LDFLAGS) $(INST_LIB)/dummymain$(OBJEXT) $(TARG_OBJS) $(LIBS) -o $(WORKTMP)/a.out ; then \
	  rm $(WORKTMP)/a.out ; \
	  echo "---- Doing final build " ; \
	  $(XARGS) $(CXX) $(LDLIBFLAGS) -o $(INST_LIB)/$(@F) < $(INST_OBJS)/libObjs.txt  ; \
	  $(UNTOUCH) $(INST_LIB)/$(@F) $(TARG_OBJS) $(TARG_MUSTLINK_OBJS) ; \
	else \
	  if [ -f $(WORKTMP)/a.out ] ; then \
	    rm $(WORKTMP)/a.out ; \
	  fi ; \
	  exit 1 ; \
	fi
endif

$(INST_LIB)/lib$(PLIB)$(LIBEXT)(%$(OBJEXT)) : $(INST_OBJS)/%$(OBJEXT)
	@true

$(INST_LIB)/%$(OBJEXT) : $(INST_OBJS)/%$(OBJEXT)
	$(SHOWIT)echo "--- MustLink $(VAR)" $*$(OBJEXT)  ; \
	if [ -f $(INST_LIB)/$*$(OBJEXT) ] ; then \
	  rm -f $(INST_LIB)/$*$(OBJEXT); \
	fi ; \
	cp /$< $(INST_LIB)/$*$(OBJEXT) ; \
	$(CHMOD) a-w $(INST_LIB)/$*$(OBJEXT)

#############################
# Build executables.

ifndef NOEXEBUILD
build_exe: $(TARG_EXE) $(TARG_SCRIPT) $(TARG_JAVAEXE)
else
build_exe:
	@true
endif

build_pureexe: $(TARG_PUREEXE)

ifndef SCRIPT_INSTALL
SCRIPT_INSTALL=$(CP)
endif

$(TARG_SCRIPT) : $(INST_GENBIN)/% : % $(INST_GENBIN)/.dir
	$(SHOWIT)echo "--- Script $(@F) " ; \
	if [ -f $(INST_GENBIN)/$(@F) ] ; then \
	  $(CHMOD) +w $(INST_GENBIN)/$(@F) ; \
	fi ; \
	$(SCRIPT_INSTALL) $* $(INST_GENBIN)/$* ; \
	$(CHMOD) 555 $(INST_GENBIN)/$* 


# If there's no library include objects from SOURCES directly.
# Always include MUSTLINK_OBJS from this directory.

ifndef PLIB
 EXTRAOBJS = $(TARG_OBJS) $(TARG_MUSTLINK_OBJS) 
else
 EXTRAOBJS = 
#$(TARG_MUSTLINK_OBJS)
endif

$(TARG_PUREEXE) : $(INST_BIN)/pure_%$(EXEEXT) : $(INST_OBJS)/%$(OBJEXT) $(EXTRAOBJS) $(TARG_LIBS) $(INST_BIN)/.dir $(TARG_HDRCERTS)
	$(SHOWIT)echo "--- Purify $(@F)  ( $(INST_BIN)/$(@F) ) " ; \
	purify -g++ -best-effort $(CXX) $(LDFLAGS) $(INST_OBJS)/$*$(OBJEXT) $(EXTRAOBJS) $(BINLIBS) -o $(INST_BIN)/$(@F)$(EXEEXT) ; 

$(TARG_EXE) : $(INST_BIN)/%$(EXEEXT) : $(INST_OBJS)/%$(OBJEXT) $(INST_GENBIN)/% $(EXTRAOBJS) $(TARG_LIBS) $(INST_BIN)/.dir $(TARG_HDRCERTS)
	$(SHOWIT)echo "--- Linking $(VAR) $(@F) ( $(INST_BIN)/$*$(EXEEXT) ) " ; \
	if [ -f $(INST_BIN)/$(@F) ] ; then \
	  $(CHMOD) +w $(INST_BIN)/$(@F)$(EXEEXT) ; \
	fi ; \
	if $(CXX) $(LDFLAGS) $(INST_OBJS)/$*$(OBJEXT) $(EXTRAOBJS) $(BINLIBS) -o $(INST_BIN)/$(@F) ; then \
	  $(SYNC) ; \
	  $(CHMOD) 555 $(INST_BIN)/$(@F) ; \
	else \
	  exit 1; \
	fi

$(ROOTDIR)/share/RAVL/config.arc : $(ROOTDIR)/share/RAVL/.dir $(MAKEHOME)/config.arc
	$(SHOWIT)if [ -f $(ROOTDIR)/share/RAVL/config.arc ] ; then \
	  $(CHMOD) +w $(ROOTDIR)/share/RAVL/config.arc ; \
	  $(RM) $(ROOTDIR)/share/RAVL/config.arc ; \
	fi ; \
	cp $(MAKEHOME)/config.arc $(ROOTDIR)/share/RAVL/config.arc ; \
	$(CHMOD) 555 $(ROOTDIR)/share/RAVL/config.arc

$(INST_GENBIN)/RAVLExec : $(INST_GENBIN)/.dir $(MAKEHOME)/RAVLExec $(ROOTDIR)/share/RAVL/config.arc
	$(SHOWIT)if [ -f $(INST_GENBIN)/RAVLExec ] ; then \
	  $(CHMOD) +w $(INST_GENBIN)/RAVLExec ; \
	  $(RM) $(INST_GENBIN)/RAVLExec ; \
	fi ; \
	perl $(MAKEHOME)/Install.pl $(PROJECT_OUT)/share/RAVL/QMake $(PROJECT_OUT) $(MAKEHOME)/RAVLExec $(INST_GENBIN)/RAVLExec ; \
	$(CHMOD) 555 $(INST_GENBIN)/RAVLExec

# This rule to be a hard link to RAVLExec, but it causes problems on some systems.

$(INST_GENBIN)/% : $(INST_GENBIN)/RAVLExec
	$(SHOWIT)echo "--- Creating redirect for $(@F)." ; \
	if [ -f $(INST_GENBIN)/$(@F) ] ; then \
	  $(CHMOD) +w $(INST_GENBIN)/$(@F) ; \
	  $(RM) $(INST_GENBIN)/$(@F) ; \
	fi ; \
	$(CP) $(INST_GENBIN)/RAVLExec $(INST_GENBIN)/$(@F) ; \
	$(CHMOD) 555 $(INST_GENBIN)/$(@F)

ifndef NOEXEBUILD
build_test: $(TARG_TESTEXE)
else
build_test:
	@true
endif


$(TARG_TESTEXE) : $(INST_TESTBIN)/%$(EXEEXT) : $(INST_OBJS)/%$(OBJEXT) $(TARG_LIBS) $(EXTRAOBJS) $(TARG_HDRCERTS) $(INST_TESTBIN)/.dir
	$(SHOWIT)echo "--- Linking test program $(@F)  ( $(INST_TESTBIN)/$(@F) ) " ; \
	if $(CXX) $(LDFLAGS) $(INST_OBJS)/$*$(OBJEXT)  $(EXTRAOBJS) $(BINLIBS) -o $(INST_TESTBIN)/$(@F) ; then \
	  $(SYNC) ; \
	  $(CHMOD) 555 $(INST_TESTBIN)/$(@F) ; \
	  echo "$(@F)" >> $(INST_TESTDB) ; \
	else \
	  exit 1; \
	fi


###########################
# Java

ifndef JAVAC
  JAVAC =javac
endif

# : $(INST_JAVA)/%.class %.java
buildjavalibs : $(JAVA_SRC) $(INST_JAVA)/.dir
ifneq ($(strip $(JAVA_SRC)),)
	$(SHOWIT)echo "--- Compiling java $(filter-out $(INST_JAVA)/.dir,$?) " ; \
	$(JAVAC) $(filter-out $(INST_JAVA)/.dir,$?) -d $(INST_JAVA) -classpath "$(CLASSPATH):$(INST_JAVA)"
else
	@true
endif

$(TARG_JAVAEXE) : $(INST_JAVAEXE)/% : %.java $(INST_JAVA)/%.class $(TARG_JAVA) $(INST_JAVAEXE)/.dir
	$(SHOWIT)echo "--- Installing java program '$(@F)'   ( $(INST_BIN)/$(@F) )" ; \
	if [ -f $(INST_BIN)/$(@F) ] ; then \
	  $(CHMOD) +w $(INST_BIN)/$(@F) ; \
	fi ; \
	echo "#\!/bin/sh" > $(INST_BIN)/$(@F) ; \
	echo "java -classpath $(CLASSPATH):$(INST_JAVA) $(@F) $1 $2 $3 $4 $5 $6 " >> $(INST_BIN)/$(@F) ; \
	$(CHMOD) a-w+x $(INST_BIN)/$(@F)

### .def files ############################################################################

$(INST_LIBDEF)/%.def : %.def $(INST_LIBDEF)/.dir
	$(SHOWIT)echo "--- Install def $(@F)" ;  \
	if [ -f $(INST_LIBDEF)/$(@F) ] ; then \
	  $(CHMOD) +w $(INST_LIBDEF)/$(@F) ; \
	fi ; \
	$(CP) $< $(INST_LIBDEF)/$(@F) ; \
        $(SYNC) ; \
	$(CHMOD) 444 $(INST_LIBDEF)/$(@F)


ifdef BASEINSTALL
      MLOBJPATH=$(patsubst %$(CEXT),$$(INSTALLHOME)/lib/RAVL/$$(ARC)/obj/%$(OBJEXT), $(patsubst %$(CXXEXT),%$(CEXT), $(MUSTLINK)))
else
      MLOBJPATH=$(patsubst %$(CEXT),$$(ROOTDIR)/lib/RAVL/$$(ARC)/obj/%$(OBJEXT), $(patsubst %$(CXXEXT),%$(CEXT), $(MUSTLINK)))
endif


ifdef LOCAL_DEFBASE
ifdef USESLIBS
 ifneq (($(filter Auto,$(USESLIBS)),Auto),Auto)
$(INST_LIBDEF)/$(LOCAL_DEFBASE).def: defs.mk $(INST_LIBDEF)/.dir
 else
  ifndef AUTOUSELIBS
   AUTOUSELIBS := $(shell $(QLIBS) -use -d -p $(ROOTDIR))
  endif
$(INST_LIBDEF)/$(LOCAL_DEFBASE).def: defs.mk $(INST_LIBDEF)/.dir $(HEADERS) $(SOURCES) $(MAINS)
 endif
	$(SHOWIT)echo "--- Creating $(@F)" ; \
	if [ -f $(INST_LIBDEF)/$(@F) ] ; then \
	  $(CHMOD) +w $(INST_LIBDEF)/$(@F) ; \
	fi ; \
	echo 'ifndef $(LOCAL_DEFBASE)_AUTO_DEF' > $(INST_LIBDEF)/$(@F) ; \
	echo '$(LOCAL_DEFBASE)_AUTO_DEF=1' >> $(INST_LIBDEF)/$(@F) ; 
 ifdef USESLIBS
  ifneq ($(USESLIBS),)
   ifneq ($(USESLIBS),None)
    ifneq ($(filter Auto,$(USESLIBS)),Auto)
     ifneq ($(strip $(TARG_USESLIBS)),)
	$(SHOWIT)echo 'include $(TARG_USESLIBS)' >> $(INST_LIBDEF)/$(@F) ;
     endif
    else
     ifneq ($(strip $(AUTOUSELIBS)),)
	$(SHOWIT)echo 'include $(EXTRA_USESLIBS)' >> $(INST_LIBDEF)/$(@F) ;
     endif
    endif
   endif
  endif
 endif
 ifdef PLIB
  ifndef LIBDEPS
	$(SHOWIT)echo 'EXELIB := -l$(PLIB) $$(EXELIB)' >> $(INST_LIBDEF)/$(@F) ;
  endif
 endif
 ifdef MUSTLINK
	$(SHOWIT)echo 'EXELIB := $(MLOBJPATH) $$(EXELIB)' >> $(INST_LIBDEF)/$(@F) ;
 endif
 ifdef EXTPACKAGE
        $(SHOWIT)echo 'INCLUDES := -I$$(INSTALLHOME)\include\$(PACKAGE) $$(INCLUDES) '
        $(SHOWIT)echo 'ifneq ($(BASE_VAR),none)' ;
        $(SHOWIT)echo ' INCLUDES := -I$$(BASE_INC)\$(PACKAGE) $$(INCLUDES)' ;
        $(SHOWIT)echo 'endif' ;
 endif
	$(SHOWIT)echo 'endif' >> $(INST_LIBDEF)/$(@F) ; \
	$(CHMOD) 444 $(INST_LIBDEF)/$(@F)
endif
endif
###############################
# RCS.

#include $(MAKEHOME)/rcs.mk

###########################

lib_info:
	@echo "Libs: $(LIBS)"

info:
	@echo "C++ Compiler    :" $(CXX) 
	@echo "C++ Flags       :" $(CCFLAGS) $(CCPPFLAGS)
	@echo "C Compiler      :" $(CC) 
	@echo "C Flags         :" $(CFLAGS) $(CPPFLAGS)
	@echo "Link Flags      :" $(LDFLAGS)
	@echo "Includes        :" $(INCLUDES)
	@echo "Library libs    :" $(EXELIB)
	@echo "Executable libs :" $(LINKLIBS)
	@echo "Temp            :" $(LOCALTMP)
	@echo "Auto            :" $(AUTOUSELIBS)

#	@echo "Supported       :" $(SUPPORT_OK)
#   " - " $(findstring $(ARC),$(DONOT_SUPPORT)) " - " $(findstring $(ARC),$(SUPPORT_ONLY))
#	@echo "Directory supported:" $(SUPPORT_ONLY) " - " $(DONOT_SUPPORT)

%:
	@echo "ERROR: Don't know how to make " $@ ; \
	exit 1
