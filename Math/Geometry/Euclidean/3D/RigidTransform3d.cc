// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath


#include "Ravl/RigidTransform3d.hh"
#include <iostream.h>

namespace RavlN {

#if 0   
  RigidTransform3dC::RigidTransform3dC(const HomtmC & h)
    : trans(h.Pos()), rot(h.ExportQuartern())
  {}
#endif
  

  RigidTransform3dC RigidTransform3dC::Inverse(void) const {
    Vector3dC v(-trans[0], -trans[1], -trans[2]);
    RigidTransform3dC rt(rot.Inverse().Rotate(v), rot.Inverse());
    return rt;
  }

  RigidTransform3dC RigidTransform3dC::Abs() {
    Vector3dC v = trans.Abs();
    Quartern3dC q;
    for (int j=0; j<4; j++) {
      if (rot[j]>0.0) q[j] = rot[j];
      else            q[j] = -rot[j]; 
    }
    return RigidTransform3dC(v, q);
  }
  
  void RigidTransform3dC::Print() {
    cout << "The translation is \n"
	 << ExportTranslation() << "\n";
    rot.Print();
  }
  
  void RigidTransform3dC::LongPrint() {
    cout << "The translation is \n"
	 << ExportTranslation() << "\n";
    rot.LongPrint();
  }
  
  RigidTransform3dC &RigidTransform3dC::ApplyRotationOnly(const Quartern3dC &q) {
    rot = q * rot;
    return *this; 
  }
  
  
  RigidTransform3dC &RigidTransform3dC::ApplyRotationPivot(const Quartern3dC &q,const Vector3dC &pivot) {
    trans = q.Rotate(trans - pivot) + pivot;
    rot = q * rot;
    return *this; 
  }
  
  RigidTransform3dC &RigidTransform3dC::ApplyTranslate(const Vector3dC &t) {
    trans = trans + t;
    return *this; 
  }

  RigidTransform3dC RigidTransform3dC::operator*(const RigidTransform3dC & p) {
    Vector3dC ntrans=trans + rot.Rotate(trans);
    Quartern3dC nrot=rot * p.qRotation();
    nrot.MakePositive();
    RigidTransform3dC rt(ntrans, nrot);
    return rt;
  }
  
  VectorC ConvertRTtoV6(const RigidTransform3dC &rt) {
    VectorC   out(6);
    Vector3dC r(rt.ExportAxTheta());
    Vector3dC t(rt.ExportTranslation());
    for (int i=0; i<3; ++i) {
      out[i]   = r[i];
      out[i+3] = t[i];
    }
    return out;
  }


  RigidTransform3dC ConvertV6toRT(const VectorC &v) {
    RavlAssert(v.Size() == 6);
    Vector3dC r(v[0], v[1], v[2]); 
    Vector3dC t(v[3], v[4], v[5]); 
    RigidTransform3dC rt(t,r);
    return rt;
  }

  ostream & operator<<(ostream & outS, const RigidTransform3dC & rt) {
    outS << rt.trans << " " << rt.rot;
    return outS;
  }
  
}
