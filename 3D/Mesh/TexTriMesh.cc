// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/3D/Mesh/TexTriMesh.cc"
//! lib=Ravl3D
//! docentry="Ravl.3D.Mesh"
//! author="Jonathan Starck"

#include "Ravl/3D/TexTriMesh.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/SArray1dIter2.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace Ravl3DN {
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using namespace RavlN;
  using namespace RavlImageN;
#endif

  //: Copy constructor
  TexTriMeshBodyC::TexTriMeshBodyC(const TexTriMeshBodyC& oth)
  {
    // Copy the data in TriMeshBody
    haveTexture = oth.haveTexture;
    vertices = oth.vertices.Copy();
    faces = SArray1dC<TriC>(oth.faces.Size());
    SArray1dIter2C<TriC,TriC> it(faces,oth.faces);
    for(; it; it++) {
      int i;
      for(i=0 ; i<3; i++) {
	it.Data1().VertexPtr(i) = &(vertices[oth.Index(it.Data2(),i)]);
      }
      it.Data1().TextureID() = it.Data2().TextureID();
      it.Data1().TextureCoords() = it.Data2().TextureCoords();
      it.Data1().Colour() = it.Data2().Colour();
      it.Data1().FaceNormal() = it.Data2().FaceNormal();
    }
    // Copy the textures
    m_strFilenames = oth.m_strFilenames.Copy();
    m_textures = SArray1dC< ImageC<ByteRGBValueC> >(oth.m_textures.Size());
    SArray1dIter2C<ImageC<ByteRGBValueC>,ImageC<ByteRGBValueC> > itTex(m_textures,oth.m_textures);
    for(; itTex; itTex++) {
      itTex.Data1() = itTex.Data2().Copy();
    }    
  }

  //: Automatically generate texture coordinates and a texture image
  bool TexTriMeshBodyC::GenerateTextureMap(void)
  { 
    ONDEBUG(cerr << "Generating a texture map...\n"); 

    // Check that we have a valid mesh
    IntT iNumFaces = faces.Size();
    if (iNumFaces==0) return false;

    // Work out how many squares we need to take all our triangles
    IntT iNumSquares = iNumFaces / 2;
    if ( (iNumFaces%2) ) iNumSquares++;
    // Work out how many squares to a side of the texture (rounded up square root)
    IntT iDim = IntT(ceil(Sqrt(iNumSquares)));
    RealT dSize = 1.0/(RealT)iDim;
    // Generate texture coordinates for each triangle.
    SArray1dIterC<TriC> itFaces(faces);
    IntT x,y;
    for (x=0; (x<iDim && itFaces); x++) {
      RealT dXBase = x*dSize;
      for (y=0; (y<iDim && itFaces); y++) {
	RealT dYBase = y*dSize;
	// Generate texture coordinates for the triangle in the top left corner of the square
	TriC& faceTL = itFaces.Data();
	faceTL.TextureID() = 0;
	faceTL.TextureCoord(0) = Vector2dC(dXBase + dSize*0.05, dYBase + dSize*0.90);
	faceTL.TextureCoord(1) = Vector2dC(dXBase + dSize*0.05, dYBase + dSize*0.05);
	faceTL.TextureCoord(2) = Vector2dC(dXBase + dSize*0.90, dYBase + dSize*0.05);
	itFaces++;
	if (itFaces) {
	  // Generate texture coordinates for the triangle in the bottom right corner of the square
	  TriC& faceBR = itFaces.Data();
	  faceBR.TextureID() = 0;
	  faceBR.TextureCoord(0) = Vector2dC(dXBase + dSize*0.95, dYBase + dSize*0.10);
	  faceBR.TextureCoord(1) = Vector2dC(dXBase + dSize*0.95, dYBase + dSize*0.95);
	  faceBR.TextureCoord(2) = Vector2dC(dXBase + dSize*0.10, dYBase + dSize*0.95);
	  itFaces++;
	}
      }
    }

    // Create the texture image
    m_textures = SArray1dC< ImageC<ByteRGBValueC> >(1);
    m_textures[0] = ImageC<ByteRGBValueC>(1024,1024);
    m_strFilenames = SArray1dC< StringC >(1);
    m_strFilenames[0] = StringC("texture.ppm");

    // Set the mesh as textured
    haveTexture = true;
    
    // Done
    return true;
  }

  ostream &operator<<(ostream &s,const TexTriMeshC &ts) 
  {
    RavlAssert(ts.IsValid());
    // Write the mesh info
    s << ts.Vertices(); 
    s << (IntT)ts.HaveTextureCoord() << '\n';
    s << ts.Faces().Size() << '\n'; 
    const VertexC *x = &(ts.Vertices()[0]);
    SArray1dIterC<TriC> it(ts.Faces());
    for(; it; it++) {
      s << (it->VertexPtr(0) - x) << ' ' 
	<< (it->VertexPtr(1) - x) << ' ' 
	<< (it->VertexPtr(2) - x) << ' ';
      s << (IntT)it->TextureID() << ' ';
      s << it->TextureCoords() << ' ';
      s << it->Colour() << '\n';
    }
    // Write the texture info
    s << ts.TexFilenames();
    s << ts.Textures();
    return s;
  }
  
  istream &operator>>(istream &s, TexTriMeshC &ts) 
  {
    // Read the mesh info
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
    // If there is no texture info generate a texture
    if (!bHaveTexture) {
      ts = TexTriMeshC(verts,faces);
      return s;
    }
    // Read the texture info
    UIntT nTex;
    s >> nTex;
    s.ignore(8,'\n');
    SArray1dC< StringC > strFilenames(nTex);
    SArray1dIterC<StringC> strit(strFilenames);
    for(; strit; strit++) {
      s >> strit.Data();
    }
    SArray1dC< ImageC<ByteRGBValueC> > textures;
    s >> textures;
    // Create the textured tri mesh
    ts = TexTriMeshC(verts,faces,textures,strFilenames);
    return s;
  }

}
