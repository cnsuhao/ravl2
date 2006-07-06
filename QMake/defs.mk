# This file is part of QMake, Quick Make System 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/QMake/defs.mk"

#PACKAGENAME= QMake
DONOT_SUPPORT=VCPP

DESCRIPTION = Quick Make System

#PREBUILDSTEP=echo $(PROJECT_OUT)

LICENSE= GPL

MAINS=SysConf.cc untouch.cc findBuildTag.cc

AUXDIR=share/RAVL/QMake

AUXFILES =  QMake.mk \
  Dirs.mk Main.mk MainDep.mk Util.mk rcs.mk Doc.mk Clean.mk \
  Sys.def Install.pl Help.txt Notes.txt Defs.txt dummymain.c \
  config.arc BinDep.pl mkdefs.pl \
  config.linux_alpha config.sgi \
  config.sol2_7 config.sol2_9 \
  config.alpha       config.unknown config.linux config.linux64 config.cygwin config.arm \
  config.macosx config.local.macosx \
  QLibs.pl GlobalMake qmake.cshrc qmake.sh \
  RAVLExec AutoBuild.pl AutoBuild.sample.conf 

ifndef CONFIGFILE
# Install default config files.
AUXFILES += config.local.linux config.local.linux64 config.local.sgi config.local.sol2_7 config.local.sol2_9 config.local.arm
else
# Install users config file.
AUXFILES += $(CONFIGFILE)
endif

HTML=Example.def.html

EHT= exeSysConf.eht Ravl.QMake.html Ravl.QMake.Defs.html  \
 Ravl.QMake.Build_Structure.html Ravl.QMake.AutoBuild.html

SCRIPTS=qm QLibs

SCRIPT_INSTALL=perl ./Install.pl $(PROJECT_OUT)/share/RAVL/QMake $(PROJECT_OUT)

AUXINSTALL=perl ./Install.pl $(PROJECT_OUT)/share/RAVL/QMake $(PROJECT_OUT)
