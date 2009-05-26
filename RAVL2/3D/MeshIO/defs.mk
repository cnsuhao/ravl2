# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/3D/MeshIO/defs.mk"

PACKAGE=Ravl/3D

HEADERS= RavlMeshIO.hh \
         VRMLFileIO.hh FormatVRMLFile.hh \
         CTriFileIO.hh FormatCTriFile.hh \
         TriFileIO.hh FormatTriFile.hh \
         MeshIOObj.hh FormatMeshObj.hh \
	 POVRayFileIO.hh FormatPOVRayFile.hh

SOURCES= VRMLFileIO.cc FormatVRMLFile.cc \
	 CTriFileIO.cc FormatCTriFile.cc \
	 TriFileIO.cc FormatTriFile.cc \
         MeshIOObj.cc FormatMeshObj.cc \
	 TriMeshIO.cc TexTriMeshIO.cc \
	 POVRayFileIO.cc FormatPOVRayFile.cc \
         MeshConv.cc

MUSTLINK= RavlMeshIO.cc

PLIB=Ravl3DIO

USESLIBS=Ravl3D RavlIO RavlOS

EHT= Ravl.API.3D.IO.html

AUXDIR = share/RAVL/data
AUXFILES = cube.tri
