// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=Ravl3DIO

#include "Ravl/3D/MeshIOObj.hh"
#include "Ravl/SArr1Iter.hh"

namespace Ravl3DN {
  //: Open file.
  
  DPIMeshObjBodyC::DPIMeshObjBodyC(const StringC &fn)
    : inf(fn),
      done(false)
  {}
  
  //: Open file.
  
  DPIMeshObjBodyC::DPIMeshObjBodyC(IStreamC &is)
    : inf(is),
      done(false)
  {}
  
  //: Is valid data ?
  
  bool DPIMeshObjBodyC::IsGetEOS() const 
  { return !done && inf; }
  
  //: Get next piece of data.
  
  TriMeshC DPIMeshObjBodyC::Get() {
    if(done)
      return TriMeshC();
    TriMeshC ret;
    //CollectionC<VertexC> verts;
    
    ret.UpdateVertexNormals();
    return ret;
  }

  ////////////////////////////////////////////////////////////////////////////////////////

  //: Open file.
  
  DPOMeshObjBodyC::DPOMeshObjBodyC(const StringC &fn)
    : outf(fn),
      done(false)
  {}
  
  //: Open file.
  
  DPOMeshObjBodyC::DPOMeshObjBodyC(OStreamC &is)
    : outf(is),
      done(false)
  {}
  
  //: Put data.
  
  bool DPOMeshObjBodyC::Put(const TriMeshC &dat) {
    if(done || !outf)
      return false;
    for(SArray1dIterC<VertexC> vit(dat.Vertices());vit;vit++)
      outf << "v " <<  vit->Position() << '\n';
    for(SArray1dIterC<VertexC> vit(dat.Vertices());vit;vit++)
      outf << "vn " <<  vit->Normal() << '\n';
    // Texture co-ordinates.
    for(SArray1dIterC<VertexC> vit(dat.Vertices());vit;vit++)
      outf << "vt " <<  vit->Normal() << '\n';
    for(SArray1dIterC<TriC> it(dat.Faces());it;it++) {
      outf << "f ";
      for(int i = 0;i < 3;i++) {
	IntT ind = dat.Index(*it,i) + 1;
	// Vertex/Normal/Texture
	outf << ind << '/' << ind << '/' << ind << ' '; 
      }
    }
      
    return true;
  }
  
  //: Is port ready for data ?
  
  bool DPOMeshObjBodyC::IsPutReady() const 
  { return !done && outf; }

}
