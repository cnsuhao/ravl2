# This file is part of QMake, Quick Make System 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
# $Id$
#! rcsid="$Id$"
#! file="Ravl/QMake/defs.mk"

PACKAGENAME= QMake

DESCRIPTION = Quick Make System

LICENSE= GPL

MAINS=SysConf.cc untouch.cc

AUXDIR=Tools/QMake

AUXFILES =  QMake.mk \
  Dirs.mk Main.mk MainDep.mk Util.mk rcs.mk Doc.mk Clean.mk \
  Sys.def Install.pl Help.txt Notes.txt Defs.txt dummymain.c \
  config.arc BinDep.pl mkdefs.pl \
  config.linux_alpha config.sgi     config.sol2 \
  config.alpha       config.unknown config.linux config.cygwin \
  QLibs.pl GlobalMake qmake.cshrc qmake.sh qm

EHT= exeSysConf.eht Ravl.QMake.html Ravl.QMake.Defs.html Ravl.QMake.Commands.html

AUXINSTALL=perl ./Install.pl $(PROJECT_OUT)/Tools/QMake
