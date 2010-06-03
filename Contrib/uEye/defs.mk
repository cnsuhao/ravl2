# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2008, OmniPerception Ltd.
# This code may be redistributed under the terms of the MIT
# License. See http://www.opensource.org/licenses/mit-license.html
# file-header-ends-here

SUPPORT_ONLY = linux linux64

REQUIRES = uEyeSDK

PACKAGE = Ravl/Image

HEADERS=ImgIOuEye.hh uEyeFileFormat.hh

SOURCES=ImgIOuEye.cc uEyeFileFormat.cc

PLIB= RavlImgIOuEye

USESLIBS=RavlImageIO RavlThreads uEye RavlOS 

MUSTLINK=linkRavlImgIOuEye.cc

PROGLIBS=RavlDPDisplay

EXTERNALLIBS = uEye.def
