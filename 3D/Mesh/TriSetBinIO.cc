
#include "Ravl/3D/TriSet.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/SArr1Iter.hh"

namespace Ravl3DN {
  
  BinOStreamC &operator<<(BinOStreamC &s,const VertexC &v) {
    s << v.Position() << v.Normal();
    return s;
  }
  
  BinIStreamC &operator>>(BinIStreamC &s,VertexC &v) {
    s >> v.Position() >> v.Normal();
    return s;    
  }
  
  
  BinOStreamC &operator<<(BinOStreamC &s,const TriSetC &ts) {
    RavlAssert(ts.IsValid());
    s << ts.Vertices(); 
    s << ts.Faces().Size(); 
    const VertexC *x = &(ts.Vertices()[0]);
    for(SArray1dIterC<TriC> it(ts.Faces());it;it++)
      s << (it->VertexPtr(0) - x)  << (it->VertexPtr(1) - x) << (it->VertexPtr(2) - x);
    return s;
  }
  
  BinIStreamC &operator>>(BinIStreamC &s,TriSetC &ts) {
    SArray1dC<VertexC> vecs;
    s >> vecs;
    UIntT nfaces,i1,i2,i3;
    s >> nfaces;
    SArray1dC<TriC> faces(nfaces);
    for(SArray1dIterC<TriC> it(faces);it;it++) {
      s >> i1 >> i2 >> i3;
      it->VertexPtr(0) = &(vecs[i1]);
      it->VertexPtr(1) = &(vecs[i2]);
      it->VertexPtr(2) = &(vecs[i3]);
      it->UpdateFaceNormal();
    }
    return s;
  }
  
}
