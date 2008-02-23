
#include "Ravl/GUI/DPointSet3d.hh"
#include "Ravl/GUI/DTriMesh3D.hh"
#include "Ravl/GUI/DTexTriMesh3D.hh"
#include "Ravl/GUI/DSurfacePointVertexByteRGBArray.hh"
#include "Ravl/GUI/DSurfacePointVertexArray.hh"

#include "Ravl/DP/Converter.hh"
#include "Ravl/TypeName.hh"

namespace RavlGUIN {
  
  static TypeNameC type1(typeid(DObject3DC),"RavlGUIN::DObject3DC");
  
  DObject3DC PointSet3d2DObject3d(const PointSet3dC &points) 
  { return DPointSet3dC(points);  }
  
  DObject3DC TriMeshC2DObject3d(const TriMeshC &mesh) 
  { return DTriMesh3DC(mesh);  }
  
  DObject3DC TexTriMeshC2DObject3d(const TexTriMeshC &mesh) 
  { return DTexTriMesh3DC(mesh); }

  DObject3DC SurfacePoint3dArrayC_VertexC2DObject3d(const SurfacePoint3dArrayC<VertexC> &mesh) 
  { return DSurfacePointVertexArrayC(mesh); }
  
  DObject3DC SurfacePoint3dArrayC_VertexColourByteRGBC2DObject3d(const SurfacePoint3dArrayC<VertexColourByteRGBC> &mesh) 
  { return DSurfacePointVertexByteRGBArrayC(mesh); }
  
  DP_REGISTER_CONVERSION_NAMED(PointSet3d2DObject3d,1,"RavlGUIN::DObject3DC PointSet3d2DObject3d(const RavlN::PointSet3dC &)");
  DP_REGISTER_CONVERSION_NAMED(TriMeshC2DObject3d,1,"RavlGUIN::DObject3DC TriMeshC2DObject3d(const Ravl3DN::TriMeshC &)");
  DP_REGISTER_CONVERSION_NAMED(TexTriMeshC2DObject3d,1,"RavlGUIN::DObject3DC TexTriMeshC2DObject3d(const Ravl3DN::TexTriMeshC &)");
  
  DP_REGISTER_CONVERSION_NAMED(SurfacePoint3dArrayC_VertexC2DObject3d,1,"RavlGUIN::DObject3DC SurfacePoint3dArrayC_VertexC2DObject3d(const Ravl3DN::SurfacePoint3dArrayC<VertexC> &)");
  
  DP_REGISTER_CONVERSION_NAMED(SurfacePoint3dArrayC_VertexColourByteRGBC2DObject3d,1,"RavlGUIN::DObject3DC SurfacePoint3dArrayC_VertexColourByteRGBC2DObject3d(const Ravl3DN::SurfacePoint3dArrayC<VertexColourByteRGBC> &)");
  
  
  void InitDPDisplay3dConv() 
  {}
}
