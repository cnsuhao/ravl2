# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/defs.mk"

PACKAGE=Ravl

DESCRIPTION=RAVL, Recognition and Vision Library

#If you wish to use the 'Ravl-Contrib' code remove the
# '#' before the Contrib.r at the end of the following line.

NESTED=QMake.r Core.r OS.r CCMath.r Math.r PatternRec.r Image.r 3D.r Logic.r \
  SourceTools.r GUI.r Applications.r # Contrib.r


LOCAL_FILES=install lgpl.license gpl.license README

EHT=Ravl.eht Ravl.Introduction.eht
