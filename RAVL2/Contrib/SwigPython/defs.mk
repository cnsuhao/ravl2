# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2006, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html

#NOSHAREDLIBDEPENDS=1

DONOT_SUPPORT=VCPP

#REQUIRES=Swig SwigPython

PACKAGE=Ravl/Swig

HEADERS=

SOURCES=Ravl.i

PLIB=RavlPythonSwig

USESLIBS=RavlDPDisplay.opt RavlCore RavlMath RavlImage RavlImageIO Python RavlNet RavlOSIO

PROGLIBS=

SWIGOPTS=-python

AUXDIR=/share/Python

AUXFILES=Ravl.py
