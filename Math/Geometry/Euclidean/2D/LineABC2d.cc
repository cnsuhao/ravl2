
#include "Ravl/LineABC2d.hh"
#include <iostream.h>

namespace RavlN {

  ostream & operator<<(ostream & outS, const LineABC2dC & line) {
    outS << line.Normal() << ' ' << line.C();
    return(outS);
  }
  
  istream & operator>>(istream & inS, LineABC2dC & line) {
    inS >> line.normal >> line.d;
    return(inS);
  }
}

