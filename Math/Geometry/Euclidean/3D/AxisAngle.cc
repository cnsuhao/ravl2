
#include "Ravl/AxisAngle.hh"

namespace RavlN
{

#define SMALL_ANGLE 1E-12

  void AxisAngleToMatrix(const RealT* a, RealT* R)
  {
    RealT ang, c, v, s, x, y, z;
    ang = sqrt(a[0]*a[0] + a[1]*a[1] + a[2]*a[2]);

    if (ang > SMALL_ANGLE)
    { 
      x = a[0]/ang; y = a[1]/ang; z = a[2]/ang;
      c = cos(ang);
      s = sin(ang);
      v = 1 - c;
    }
    else 
    { 
      x = a[0];
      y = a[1];
      z = a[2];
      c = 1.0 - 0.50000000*ang*ang;
      v = 0.5 - 0.04166667*ang*ang;
      s = 1.0 - 0.16666667*ang*ang;
    }

    R[0] = x*x*v + c;   R[1] = x*y*v - z*s; R[2] = x*z*v + y*s;
    R[3] = x*y*v + z*s; R[4] = y*y*v + c;   R[5] = y*z*v - x*s;
    R[6] = x*z*v - y*s; R[7] = y*z*v + x*s; R[8] = z*z*v + c;
  }

  void MatrixToAxisAngle(const RealT* R, RealT* a)
  {
    RealT ang, s;

    ang = acos(0.5 * (R[0]+R[4]+R[8]-1.0));
  
    if (ang < -SMALL_ANGLE || ang > SMALL_ANGLE)
    {
      s = 0.5 * ang / sin(ang);
    }
    else
    { 
      // ARRGH! causes problems - should use small-angle implementation
      s = 0.5;
    }

    a[0] = (R[7]-R[5])*s;
    a[1] = (R[2]-R[6])*s;
    a[2] = (R[3]-R[1])*s;
  }

}
