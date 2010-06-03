# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 6715 2008-04-15 08:07:09Z kier $"
#! file="Ravl/Contrib/Plotting/DPGraph/defs.mk"

DONOT_SUPPORT=VCPP

REQUIRES=libGuppi

PACKAGE=Ravl/Plot

HEADERS= DPGraphWindow.hh DPGraphWindowOPort.hh DPGraphWindowFormat.hh

SOURCES= DPGraphWindow.cc DPGraphWindowOPort.cc DPGraphWindowFormat.cc

PLIB=RavlDPGraph

MUSTLINK=RavlDPGraphWindow.cc

USESLIBS=RavlIO RavlGUI RavlPlot RavlGuppi

EXAMPLES= exDPGraphWindow.cc

EHT=Ravl.API.GUI.Data_Plotting.html
