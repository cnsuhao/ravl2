//! date="6/8/1995"
//! author="Radek Marik"

#include "Ravl/Moments2d2.hh"

namespace RavlN {

  ostream &operator<<(ostream & os, const  Moments2d2C & mom) {
    os << mom.M00() << ' ' << mom.M10() << ' ' << mom.M01() << ' '
       << mom.M20() << ' ' << mom.M11() << ' ' << mom.M02();
    return os;
  }
  
  istream &operator>>(istream & is, Moments2d2C & mom) {
    is >> mom.m00 >> mom.m10 >> mom.m01
       >> mom.m20 >> mom.m11 >> mom.m02;
    return is;
  }

}
