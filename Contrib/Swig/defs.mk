# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2006, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html

REQUIRES=Swig

PACKAGE=Ravl/Swig

HEADERS=Types.i Point2d.i Polygon2d.i Image.i IndexRange2d.i Index2d.i Array2d.i Index.i String.i \
 IO.i Font.i SArray1d.i Affine2d.i DList.i Date.i

SOURCES=Ravl.i

PLIB=RavlPythonSwig

USESLIBS=RavlDPDisplay RavlCore RavlMath RavlImage RavlImageIO Python 

SWIGOPTS=-python

PROGLIBS=

AUXDIR=

AUXFILES=
