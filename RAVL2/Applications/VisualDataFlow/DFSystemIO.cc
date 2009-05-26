

#include "Ravl/DF/DFSystem.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/FileFormatXMLStream.hh"

namespace RavlDFN {
  void InitDFSystemIO()
  {}
  
  FileFormatStreamC<DFSystemC> FileFormatStream_DFSystemC;
  FileFormatBinStreamC<DFSystemC> FileFormatBinStream_DFSystemC;
  FileFormatXMLStreamC<DFSystemC> FileFormatXMLStream_DFSystemC;
  
  static TypeNameC typenameDFSystemC(typeid(DFSystemC),"RavlDFN::DFSystemC");
  
}
