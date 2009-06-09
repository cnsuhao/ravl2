PACKAGE = Ravl/Threads

HEADERS = MemModule.hh MemModules.hh MemoryItem.hh \
          VamInRamImOnDisk.hh VamBase.hh VamAccess.hh \
          MemoryItemXMLdisk.hh # VamXMLFile.hh

SOURCES = MemModule.cc MemModules.cc MemoryItem.cc \
          VamInRamImOnDisk.cc VamBase.cc \
          MemoryItemXMLdisk.cc # VamXMLFile.cc
          

PLIB = RavlMultiModules
 
USESLIBS=  RavlCore RavlImage RavlOS RavlThreads RavlImageIO

EHT = ThreadedMemory.html Modules_Header.html Wrapper.html ModuleSet.html MainProg.html Internals.html Example.html

AUXDIR = share/doc/RAVL/Images
AUXFILES = ModuleGraph.pdf Memory.pdf
