# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
######################################################
# $Id$
#! rcsid="$Id$"
#! file="Ravl/GUI/3D/defs.mk"

PACKAGE=Ravl/GUI

LICENSE=LGPL

ifeq ($(ARC),sol2)
# The solaris x11 header files a broken, so we need
# to turn off ansi flag and make the compiler more forgiving.
ANSIFLAG=-fpermissive
endif
ifeq ($(ARC),alpha)
# The solaris x11 header files a broken, so we need
# to turn off ansi flag and make the compiler more forgiving.
ANSIFLAG=-fpermissive
endif

DESCRIPTION = Interface to open GL.

#ifneq ($(ARC),sgi)
#ANSIFLAG = -fpermissive
#endif

MAINS = 
#exView3D.cc 
#v3d.cc
#ex3DCanvas.cc

HEADERS = gdkgl.h gtkglarea.h DObject3D.hh DLight3D.hh \
 Util.hh Canvas3D.hh DViewPoint3D.hh DCube3D.hh DTriMesh3D.hh \
 DPointSet3D.hh DPinholeCamera03D.hh
#View3D.hh

#  DLines3D.hh
#      

# DPolops3D.hh  DTriSet3D.hh DCTriSet3D.hh Pixmap3D.hh

SOURCES = gdkgl.c gtkglarea.c DObject3D.cc  DLight3D.cc \
 Util.cc Canvas3D.cc DViewPoint3D.cc DCube3D.cc DTriMesh3D.cc \
 DPointSet3D.cc DPinholeCamera03D.cc
#View3D.cc

#  DLines3D.cc
#      

# DPolops3D.cc  DTriSet3D.cc  Pixmap3D.cc

PLIB = RavlGUI3D

EXAMPLES = exCanvas3D.cc
# exView3D.cc

USESLIBS = RavlCore RavlGeom RavlGUI OpenGL Ravl3D 

EHT = Ravl.GUI.3D.html

PROGLIBS = Ravl3DIO RavlOS
