
#include "Ravl/RealHistogram1d.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  
  BinOStreamC &operator<<(BinOStreamC & strm,const RealHistogram1dC &hist)  {
    strm << hist.Offset() << hist.Scale() << ((const SArray1dC<UIntC> &)hist);
    return strm;
  }
  
  BinIStreamC &operator<<(BinIStreamC & strm,RealHistogram1dC &hist) {
    RealT offset,scale;
    SArray1dC<UIntC> xhist;
    strm >> offset >> scale >> xhist;
    hist = RealHistogram1dC(offset,scale,xhist);
    return strm;
  }
  
}
