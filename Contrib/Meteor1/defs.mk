# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5240 2005-12-06 17:16:50Z plugger $"
#! file="Ravl/Contrib/Meteor1/defs.mk"
#! author="Charles Galambos"

DESCRIPTION = Meteor driver

PACKAGE = Ravl/Image

SUPPORT_ONLY = linux

MAINS= tuneMeteor.cc

HEADERS = ImgIOMeteor1.hh Meteor1Format.hh 

LOCALHEADERS = ioctl_meteor.h ioctl_himemfb.h

SOURCES = ImgIOMeteor1.cc Meteor1Format.cc 

MUSTLINK = InitMeteor1.cc

EXAMPLES = exMeteor.cc

PLIB = RavlImgIOMeteor1

EHT= Ravl.API.Images.Video.Video_IO.Meteor1.html

USESLIBS = RavlImageIO

PROGLIBS = RavlGUI RavlGUI2D
