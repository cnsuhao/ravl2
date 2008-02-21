# This file is part of CxxDoc, The RAVL C++ Documentation tool 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/SourceTools/CodeManager/defs.mk"

DONOT_SUPPORT=

PACKAGENAME = CxxDoc

DESCRIPTION = The RAVL C++ Documentation tool

LICENSE = GPL

PACKAGE=Ravl/SourceTools

HEADERS= DefsFile.hh SourceCodeManager.hh RCSFile.hh SourceFile.hh \
 LibInfo.hh ProgInfo.hh BuildInfo.hh

# SrcCheck.hh HdrUpdate.hh RCSFile.hh PatchMods.hh SrcMerge.hh \
#SrcInst.hh SrcFunc.hh SrcUtil.hh ManagedFile.hh

SOURCES = DefsFile.cc SourceCodeManager.cc RCSFile.cc SourceFile.cc \
 LibInfo.cc ProgInfo.cc  BuildInfo.cc

# SrcCheck.cc HdrUpdate.cc RCSFile.cc PatchMods.cc SrcMerge.cc \
#SrcInst.cc SrcFunc.cc SrcUtil.cc ManagedFile.cc
# doLog.cc

MAINS = defsCheck.cc annotate.cc  amma2ravl.cc docSubst.cc docRename.cc
# rcsinfo.cc doMerge.cc DocEntryUpdate.cc QLibs.cc

EXAMPLES=exBuildInfo.cc

AUXDIR=share/RAVL/CodeManager

AUXFILES= fixSource.cfg

EHT = Ravl.API.Source_Tools.Code_Manager.html
#exedefchk.eht exercsinfo.eht exedoMerge.eht exedoHeaders.eht exedoHeaders.eht exedoSrcInst.eht

PLIB = RavlSourceTools

USESLIBS= RavlCore RavlOS
#TextProc MstdIO system Msys MSArr1 Hash1d MstdList MRefC Mlist Mtuple

PROGLIBS=  
#Mopt Mtype Mtext

