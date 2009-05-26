PACKAGE = Ravl/Threads

HEADERS = MemModule.hh MemModules.hh MemoryItem.hh \
          VamInRamImOnDisk.hh VamBase.hh \
          MemoryItemXMLdisk.hh # VamXMLFile.hh

SOURCES = MemModule.cc MemModules.cc MemoryItem.cc \
          VamInRamImOnDisk.cc VamBase.cc \
          MemoryItemXMLdisk.cc # VamXMLFile.cc
          

PLIB = VampireShortTerm
 
USESLIBS=  RavlCore RavlImage RavlOS RavlThreads RavlImageIO

EHT = ThreadedMemory.html Wrapper.html ModuleSet.html MainProg.html

