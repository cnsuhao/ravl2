# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
######################################################
#! rcsid="$Id$"
#! file="Ravl/GUI/3D/defs.mk"

PACKAGE=Ravl/GUI

LICENSE=LGPL

#ifeq ($(ARC),sol2)
ifneq ($(filter $(ARC), sol2_7 sol2_9),)
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

MAINS = #v3d.cc

HEADERS = gdkgl.h gtkglarea.h gdkgl_gtk2.h gtkglarea_gtk2.h \
 DObject3D.hh DLight3D.hh Util.hh Canvas3D.hh DViewPoint3D.hh \
 DCube3D.hh DTriMesh3D.hh DPointSet3D.hh DPinholeCamera03D.hh \
 DTexTriMesh3D.hh View3D.hh DSurfacePointVertexArray.hh \
 DSurfacePointVertexByteRGBArray.hh

SOURCES = gdkgl.c gtkglarea.c DObject3D.cc  DLight3D.cc \
 Util.cc Canvas3D.cc DViewPoint3D.cc DCube3D.cc DTriMesh3D.cc \
 DPointSet3D.cc DPinholeCamera03D.cc DTexTriMesh3D.cc View3D.cc \
 DSurfacePointVertexArray.cc DSurfacePointVertexByteRGBArray.cc

PLIB = RavlGUI3D

EXAMPLES = exCanvas3D.cc exView3D.cc

USESLIBS = RavlCore RavlGeom RavlGUI OpenGL Ravl3D x11

EHT = Ravl.GUI.3D.html

PROGLIBS = Ravl3DIO RavlOS RavlImageIO RavlExtImgIO
