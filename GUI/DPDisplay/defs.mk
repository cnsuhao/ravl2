
PACKAGE=Ravl/GUI

HEADERS=DPWindow.hh DPDisplayObj.hh DPDisplayImage.hh DPWindowOPort.hh \
 DPWindowFormat.hh DPDisplayView.hh

SOURCES=DPWindow.cc DPDisplayObj.cc DPDisplayImage.cc DPWindowOPort.cc \
 DPWindowFormat.cc DPDisplayView.cc

PLIB=RavlGUIDisplay

MUSTLINK=RavlGUIDisplay.cc

USESLIBS=RavlIO RavlGUI RavlImageIO

MAINS=testDPWindow.cc
