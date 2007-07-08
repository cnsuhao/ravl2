// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2007, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=Ravl3D
//! author="Charles Galambos"

#include "Ravl/3D/MeshShapes.hh"
#include "Ravl/StdConst.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SArray1d.hh"

namespace Ravl3DN {
  
  //: Create a flat plane
  
  TriMeshC CreateTriMeshPlane(RealT size) {
    SArray1dC<Vector3dC> vertex(4);
    RealT hSize = size/2.0;
    vertex[0] = Vector3dC( hSize, hSize,0);
    vertex[1] = Vector3dC( hSize,-hSize,0);
    vertex[2] = Vector3dC(-hSize,-hSize,0);
    vertex[3] = Vector3dC(-hSize, hSize,0);
    
    SArray1dC<UIntT> tri(6);
    tri[0] = 0;
    tri[1] = 1;
    tri[2] = 2;

    tri[3] = 2;
    tri[4] = 3;
    tri[5] = 0;
    
    return TriMeshC(vertex,tri);
  }
  
  
  static UIntT cubeFaces[36] = 
    { 0, 1, 2, // Front
      2, 3, 0,
      6, 5, 4, // Back
      4, 7, 6,
      4, 5, 1, // Top
      0, 4, 1,
      7, 3, 2, // Bottom
      2, 6, 7,
      4, 0, 7, // Left
      0, 3, 7,
      1, 5, 2, // Right
      5, 6, 2
    };
  
  // Create a cube.
  
  TriMeshC CreateTriMeshCube(RealT size) {
    SArray1dC<Vector3dC> vertex(8);
    RealT hSize = size/2.0;
    
    vertex[0] = Vector3dC( hSize, hSize,-hSize);
    vertex[1] = Vector3dC( hSize,-hSize,-hSize);
    vertex[2] = Vector3dC(-hSize,-hSize,-hSize);
    vertex[3] = Vector3dC(-hSize, hSize,-hSize);
    
    vertex[4] = Vector3dC( hSize, hSize,hSize);
    vertex[5] = Vector3dC( hSize,-hSize,hSize);
    vertex[6] = Vector3dC(-hSize,-hSize,hSize);
    vertex[7] = Vector3dC(-hSize, hSize,hSize);
    
    static SArray1dC<UIntT> tri(cubeFaces,36,false);
    
    return TriMeshC(vertex,tri.Copy());
  }
  
  // Create a sphere.
  
  TriMeshC CreateTriMeshSphere(UIntT layers,UIntT slices,RealT radius) {
    RavlAssert(layers >= 1);
    RavlAssert(slices >= 2);
    
    RealT sliceStep = 2*RavlConstN::pi / slices;
    RealT layerStep = RavlConstN::pi / layers;
    
    SArray1dC<Vector3dC> vertex(2 + (layers-1) * slices);
    UIntT numTri = slices * 2 + (layers-2) * slices * 2;
    SArray1dC<UIntT> tri(numTri * 3);
    UIntT tn = 0,vn = 0;
    
    // Cache cos and sin values for slice angles.
    SArray1dC<RealT> sliceCos(slices);
    SArray1dC<RealT> sliceSin(slices);
    
    RealT sliceAngle = 0;
    for(SArray1dIter2C<RealT,RealT> it(sliceCos,sliceSin);it;it++) {
      it.Data1() = Cos(sliceAngle) * radius;
      it.Data2() = Sin(sliceAngle) * radius;
      sliceAngle += sliceStep;
    }
      
    // Vertex's on last layer
    SArray1dC<UIntT> vLastLayer(slices);
    
    // ----- Put in top fan. -----
    
    IntT topVert = vn;
    vertex[vn++] = Vector3dC(0,0,radius);

    RealT layerAngle = layerStep;
    
    RealT lc = Cos(layerAngle) * radius;
    RealT ls = Sin(layerAngle);
      
    vLastLayer[0] = vn;
    vertex[vn++] = Vector3dC(ls * sliceSin[0],ls  * sliceCos[0],lc);
    
    for(UIntT s = 1;s < slices;s++) {
      // Put together face.
      tri[tn++] = vn-1;
      tri[tn++] = topVert;
      tri[tn++] = vn;
      
      vLastLayer[s] = vn;
      vertex[vn++] = Vector3dC(ls * sliceSin[s],ls  * sliceCos[s],lc);
    }
    
    // Put together final face on top fan
    tri[tn++] = vn-1;
    tri[tn++] = topVert;
    tri[tn++] = vLastLayer[0];
    
    
    // ---- Put in mid layers ----
    
    for(UIntT l = 1;l < (layers-1);l++) {
      layerAngle += layerStep;
      lc = Cos(layerAngle) * radius;
      ls = Sin(layerAngle);
      
      UIntT lastTopVert = vLastLayer[0];
      UIntT lastBotVert = vn;
      UIntT firstVirt = vn;
      vertex[vn++] = Vector3dC(ls * sliceSin[0],ls  * sliceCos[0],lc);
      
      for(UIntT s = 1;s < slices;s++) {
	// Put in face triangles.
 	tri[tn++] = lastTopVert;
	tri[tn++] = vn;
	tri[tn++] = lastBotVert;
	
 	tri[tn++] = lastTopVert;
	tri[tn++] = vLastLayer[s];
	tri[tn++] = vn;
	
	// Put in new vertex.
	lastTopVert = vLastLayer[s];
	lastBotVert = vn;
	vLastLayer[s] = vn;
	vertex[vn++] = Vector3dC(ls * sliceSin[s],ls  * sliceCos[s],lc);
      }
      
      // Put in final face triangles.
      tri[tn++] = lastTopVert;
      tri[tn++] = firstVirt;
      tri[tn++] = lastBotVert;
      
      tri[tn++] = lastTopVert;
      tri[tn++] = vLastLayer[0];
      tri[tn++] = firstVirt;
      
      vLastLayer[0] = firstVirt;
    }
    
    // ---- Put in bottom fan ----
    
    IntT botVert = vn;
    vertex[vn++] = Vector3dC(0,0,-radius);
    
    // Put together face.
    tri[tn++] = botVert;
    tri[tn++] = vLastLayer[slices-1];
    UIntT lastVert = vLastLayer[0];
    tri[tn++] = lastVert;
    
    for(UIntT s = 1;s < slices;s++) {
      // Put together face.
      tri[tn++] = botVert;
      tri[tn++] = lastVert;
      lastVert = vLastLayer[s];
      tri[tn++] = lastVert;
    }
    
    RavlAssert(tn == tri.Size());
    RavlAssert(vn == vertex.Size());
    
    TriMeshC ret(vertex,tri);
    ret.UpdateVertexNormals();
    return ret;
  }
  
}


