
#include "Ravl/RealHistogram2d.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  
  BinOStreamC &operator<<(BinOStreamC & strm,const RealHistogram2dC &hist)  {
    strm << hist.Offset() << hist.Scale() << (const SArray2dC<UIntC> &)(hist);
    return strm;
  }
  
  BinIStreamC &operator<<(BinIStreamC & strm,RealHistogram2dC &hist) {
    Point2dC offset;
    Vector2dC scale;
    SArray2dC<UIntC> xhist;
    strm >> offset >> scale >> xhist;
    hist = RealHistogram2dC(offset,scale,xhist);
    return strm;
  }
  
}
