// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=Ravl3D

#include "Ravl/3D/TriMesh.hh"
#include "Ravl/SArr1Iter.hh"
#include "Ravl/SArr1Iter2.hh"

namespace Ravl3DN {
  using namespace RavlN;
  
  //: Construct from an array of vertexes and an array of indexes.
  // The length of faceInd should be a power of 3, success triples are taken
  // from it to form the faces in the mesh.
  
  TriMeshBodyC::TriMeshBodyC(const SArray1dC<Vector3dC> &v,const SArray1dC<UIntT> &faceInd) 
    : vertices(v.Size()),
      faces(faceInd.Size()/3)
  {
    for(SArray1dIter2C<VertexC,Vector3dC> it(vertices,v);it;it++)
      it.Data1().Position() = it.Data2();
    UpdateVertexNormals();    
  }

  //: Make a copy of the mesh.
  
  RCBodyVC&  TriMeshBodyC::Copy() const {
    SArray1dC<VertexC> nverts = vertices.Copy();
    SArray1dC<TriC> ntris(faces.Size());
    for(SArray1dIter2C<TriC,TriC> it(ntris,faces);it;it++) {
      for(int i = 0;i < 3;i++)
	it.Data1().VertexPtr(i) = &(nverts[Index(it.Data2(),i)]);
      it.Data1().TextureCoords() = it.Data2().TextureCoords();
      it.Data1().FaceNormal() = it.Data2().FaceNormal();
    }
    return *new TriMeshBodyC(nverts,ntris);
  }
  
  //: Flips the mesh surface
  
  void TriMeshBodyC::FlipTriangles(void) {
    for(SArray1dIterC<TriC> it(faces);it;it++)
      it->Flip();
  }

  //: Centre of triset.
  // - average vertex position
  
  Vector3dC TriMeshBodyC::Centroid() const {
    Vector3dC ret(0,0,0);
    if(ret.Size() == 0)
      return ret; // Can't take a centroid of an empty mesh.
    for(SArray1dIterC<VertexC> it(vertices);it;it++)
      ret += it->Position();
    return ret / ret.Size();
  }
  
  //: Create an array of faces indexes.
  // each successive triple of indexes represents a face in the mesh.
  
  SArray1dC<UIntT> TriMeshBodyC::FaceIndexes() const {
    SArray1dC<UIntT> ret(3 * faces.Size());
    if(faces.Size() == 0)
      return ret;
    SArray1dIterC<UIntT> rit(ret);
    const VertexC *x = &(vertices[0]);
    for(SArray1dIterC<TriC> it(faces);it;it++) {
      *rit = it->VertexPtr(0) - x; rit++;
      *rit = it->VertexPtr(1) - x; rit++;
      *rit = it->VertexPtr(2) - x; rit++;
    }
    return ret;
  }

  //: Find largest and smallest for each compoent of all vertices.
  
  void TriMeshBodyC::Limits(Vector3dC &min,Vector3dC &max) const{
    SArray1dIterC<VertexC> it(vertices);
    if(!it)
      return ; // Empty mesh!
    min = it->Position();
    max = it->Position();
    for(it++;it;it++) {
      for(int i = 0;i < 3;i++) {
	if(min[i] > it->Position()[i])
	  min[i] = it->Position()[i];
	if(max[i] < it->Position()[i])
	  max[i] = it->Position()[i];
      }
    }
  }
  
  //: Offset and Scale mesh by given values.
  
  void TriMeshBodyC::OffsetScale(const Vector3dC &off,RealT scale) {
    for(SArray1dIterC<VertexC> it(vertices);it;it++)
      it->Position() = (it->Position() + off) * scale;
  }
  
  //: Recalculate vertex normals.
  
  void TriMeshBodyC::UpdateVertexNormals() {
    for(SArray1dIterC<VertexC> it(vertices);it;it++)
      it->Normal() = Vector3dC(0,0,0);
    for(SArray1dIterC<TriC> it(faces);it;it++) {
      Vector3dC norm = it->FaceNormal();
      for(int i = 0;i < 3;i++)
	it->Normal(i) += norm;
    }
    for(SArray1dIterC<VertexC> it(vertices);it;it++)
      it->Normal() = it->Normal().Unit();
  }
  
  ostream &operator<<(ostream &s,const TriMeshC &ts) {
    RavlAssert(ts.IsValid());
    s << ts.Vertices() << '\n'; 
    s << ts.Faces().Size() << ' '; 
    const VertexC *x = &(ts.Vertices()[0]);
    for(SArray1dIterC<TriC> it(ts.Faces());it;it++)
      s << (it->VertexPtr(0) - x) << ' ' << (it->VertexPtr(1) - x) << ' ' << (it->VertexPtr(2) - x) << '\n';
    return s;
  }
  
  istream &operator>>(istream &s,TriMeshC &ts) {
    SArray1dC<VertexC> verts;
    s >> verts;
    UIntT nfaces,i1,i2,i3;
    s >> nfaces;
    SArray1dC<TriC> faces(nfaces);
    for(SArray1dIterC<TriC> it(faces);it;it++) {
      s >> i1 >> i2 >> i3;
      it->VertexPtr(0) = &(verts[i1]);
      it->VertexPtr(1) = &(verts[i2]);
      it->VertexPtr(2) = &(verts[i3]);
      it->UpdateFaceNormal();
    }
    return s;
  }

}
