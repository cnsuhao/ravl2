// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=Ravl3D
//! author="Charles Galambos"
//! file="Ravl/3D/Mesh/TriMesh.cc"

#include "Ravl/3D/TriMesh.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/SArray1dIter2.hh"

namespace Ravl3DN {
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using namespace RavlN;
#endif
  
  //: Construct from an array of vertexes and an array of indices.
  // The length of faceInd should be a power of 3, success triples are taken
  // from it to form the faces in the mesh.
  
  TriMeshBodyC::TriMeshBodyC(const SArray1dC<Vector3dC> &v,const SArray1dC<UIntT> &faceInd) 
    : vertices(v.Size()),
      faces(faceInd.Size()/3),
      haveTexture(false)
  {
    Vector3dC zero(0,0,0);
    for(SArray1dIter2C<VertexC,Vector3dC> it(vertices,v);it;it++) {
      it.Data1().Position() = it.Data2();
      it.Data1().Normal() = zero;
    }
    RavlAssert(faceInd.Size() == (faces.Size() * 3));
    SArray1dIterC<UIntT> iit(faceInd);
    /* Create vertex pointers, and some inital vertex normals. */
    for(SArray1dIterC<TriC> fit(faces);fit;fit++) {
      int i;
      for(i = 0;i < 3;i++,iit++) {
	fit.Data1().VertexPtr(i) = &(vertices[*iit]);
      }
      fit->UpdateFaceNormal();
      Vector3dC norm = fit->FaceNormal();
      for( i = 0;i < 3;i++)
	fit->Normal(i) += norm;
    }
    /* Make unit normals. */
    for(SArray1dIterC<VertexC> itv(vertices);itv;itv++)
      itv->Normal().MakeUnit();
  }

  //: Construct from a list of vertexes and a list of indices.
  // The length of faceInd should be a power of 3, success triples are taken
  // from it to form the faces in the mesh.
  
  TriMeshBodyC::TriMeshBodyC(const DListC<Vector3dC> &v,const DListC<UIntT> &faceInd) 
    : vertices(v.Size()),
      faces(faceInd.Size()/3),
      haveTexture(false)
  {
    // Create the vertices from the vertex positions v
    Vector3dC zero(0,0,0);
    DLIterC<Vector3dC> itPos(v);
    SArray1dIterC<VertexC> itVerts(vertices);
    for (; itPos; itPos++, itVerts++) {
      itVerts.Data().Position() = itPos.Data();
      itVerts.Data().Normal() = zero;
    }
    // Create the tri faces from the face vertex indices
    RavlAssert(faceInd.Size() == (faces.Size() * 3));
    DLIterC<UIntT> iit(faceInd);
    SArray1dIterC<TriC> fit(faces);
    /* Create vertex pointers, and some inital vertex normals. */
    for(;fit;fit++) {
      int i;
      for(i = 0;i < 3;i++,iit++) {
        fit.Data().VertexPtr(i) = &(vertices[*iit]);
      }
      fit->UpdateFaceNormal();
      Vector3dC norm = fit->FaceNormal();
      for( i = 0;i < 3;i++)
        fit->Normal(i) += norm;
    }
    /* Make unit normals. */
    SArray1dIterC<VertexC> itv(vertices);
    for(; itv; itv++)
      itv->Normal().MakeUnit();
  }


  //: Copy constructor

  TriMeshBodyC::TriMeshBodyC(const TriMeshBodyC& oth)
  {
    haveTexture = oth.haveTexture;
    vertices = oth.vertices.Copy();
    faces = SArray1dC<TriC>(oth.faces.Size());
    SArray1dIter2C<TriC,TriC> it(faces,oth.faces);
    for(; it; it++) {
      int i;
      for(i=0 ; i<3; i++)
	it.Data1().VertexPtr(i) = &(vertices[oth.Index(it.Data2(),i)]);
      it.Data1().TextureID() = it.Data2().TextureID();
      it.Data1().TextureCoords() = it.Data2().TextureCoords();
      it.Data1().Colour() = it.Data2().Colour();
      it.Data1().FaceNormal() = it.Data2().FaceNormal();
    }
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
  
  //: Create an array of faces indices.
  // each successive triple of indices represents a face in the mesh.
  
  SArray1dC<UIntT> TriMeshBodyC::FaceIndices() const {
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
    Vector3dC zero(0,0,0);
    for(SArray1dIterC<VertexC> it(vertices);it;it++)
      it->Normal() = zero;
    for(SArray1dIterC<TriC> itf(faces);itf;itf++) {
      Vector3dC norm = itf->FaceNormal();
      for(int i = 0;i < 3;i++)
	itf->Normal(i) += norm;
    }
    for(SArray1dIterC<VertexC> itv(vertices);itv;itv++)
      itv->Normal() = itv->Normal().Unit();
  }
  
  ostream &operator<<(ostream &s,const TriMeshC &ts) {
    RavlAssert(ts.IsValid());
    s << ts.Vertices(); 
    s << (IntT)ts.HaveTextureCoord() << '\n';
    s << ts.Faces().Size() << '\n'; 
    const VertexC *x = &(ts.Vertices()[0]);
    SArray1dIterC<TriC> it(ts.Faces());
    for(; it; it++) {
      s << (it->VertexPtr(0) - x) << ' ' 
	<< (it->VertexPtr(1) - x) << ' ' 
	<< (it->VertexPtr(2) - x) << ' ';
      s << it->TextureID() << ' ';
      s << it->TextureCoords() << ' ';
      s << it->Colour() << '\n';
    }
    return s;
  }
  
  istream &operator>>(istream &s,TriMeshC &ts) {
    SArray1dC<VertexC> verts;
    s >> verts;
    IntT iHaveTexture;
    s >> iHaveTexture;
    bool bHaveTexture = (iHaveTexture) ? true : false;
    UIntT nfaces,i1,i2,i3;
    s >> nfaces;
    SArray1dC<TriC> faces(nfaces);
    for(SArray1dIterC<TriC> it(faces);it;it++) {
      s >> i1 >> i2 >> i3;
      s >> it->TextureID();
      s >> it->TextureCoords();
      s >> it->Colour();
      it->VertexPtr(0) = &(verts[i1]);
      it->VertexPtr(1) = &(verts[i2]);
      it->VertexPtr(2) = &(verts[i3]);
      it->UpdateFaceNormal();
    }
    ts = TriMeshC(verts,faces,bHaveTexture);
    return s;
  }

}
