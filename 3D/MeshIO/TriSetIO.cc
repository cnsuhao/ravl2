
#include "Ravl/3D/TriSet.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"

namespace Ravl3DN {

  void InitTriSetIO() 
  {}
  
  static TypeNameC type1(typeid(TriSetC),"TriSetC");  
  
  FileFormatStreamC<TriSetC > FileFormatStream_TriSetC;
  FileFormatBinStreamC<TriSetC > FileFormatBinStream_TriSetC;
}
