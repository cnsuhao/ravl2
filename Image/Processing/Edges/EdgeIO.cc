
#include "Ravl/Image/Edgel.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/BinStream.hh"

namespace RavlImageN {
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using namespace RavlN;
#endif

  void InitEdgeIO() {}
  //: Init edge io.
  
  static TypeNameC type1(typeid(EdgelC),"EdgelC");
  static TypeNameC type2(typeid(SArray1dC<EdgelC>),"SArray1dC<EdgelC>");
  
  FileFormatStreamC<EdgelC> FileFormatStream_Edgel;
  FileFormatBinStreamC<EdgelC> FileFormatBinStream_Edgel;
  
  FileFormatStreamC<SArray1dC<EdgelC> > FileFormatStream_SArray1d_Edgel;
  FileFormatBinStreamC<SArray1dC<EdgelC> > FileFormatBinStream_SArray1d_Edgel;
  
}
