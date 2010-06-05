# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2009, OmniPerception Ltd
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! author=Charles Galambos
#! docentry=Ravl.API.Images.XMLFactory

PACKAGE=Ravl/Image

ORGANISATION=OmniPerception Ltd

HEADERS=XMLFactoryVideoIO.hh

SOURCES= XMLFactoryVideoIO.cc
#XMLFactoryGaussConvolve.cc

PLIB=RavlImageXMLFactory

USESLIBS=RavlIO RavlXMLFactory RavlImage RavlOSIO RavlImageIO

MUSTLINK=linkRavlImageXMLFactory.cc
