
PACKAGE=Ravl/3D

HEADERS= TriFileIO.hh FormatTriFile.hh

SOURCES= TriFileIO.cc FormatTriFile.cc TriSetIO.cc

MUSTLINK= RavlMeshIO.cc

PLIB=Ravl3DIO

USESLIBS=Ravl3D RavlIO
