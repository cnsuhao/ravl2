
#include "Ravl/3D/Vertex.hh"

namespace Ravl3DN {
  
  ostream &operator<<(ostream &s,const VertexC &v) { 
    s << v.Position() << ' ' << v.Normal();
    return s;
  }

  istream &operator>>(istream &s,VertexC &v) { 
    s >> v.Position() >> v.Normal();
    return s;
  }

}
