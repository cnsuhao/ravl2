// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include "Ravl/3D/VRMLFileIO.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/HSet.hh"
//! rcsid="$Id$"
//! lib=Ravl3DIO

namespace Ravl3DN {

  // TriMesh VRML File IO /////////////////////////////////////////////

  //: Open file.
  DPIVRMLFileBodyC::DPIVRMLFileBodyC(const StringC &fn)
    : inf(fn),
      done(false)
  {}
  
  //: Open file.
  DPIVRMLFileBodyC::DPIVRMLFileBodyC(IStreamC &is)
    : inf(is),
      done(false)
  {}
  
  //: Is valid data ?
  bool DPIVRMLFileBodyC::IsGetEOS() const {
    return !done && inf;
  }
  
  //: Get next piece of data.
  TriMeshC DPIVRMLFileBodyC::Get() {
    if(done)
      return TriMeshC();

    // TO BE IMPLEMENTED
    cerr << "Error: not implemented yet!\n";
    return TriMeshC();

    // Done
    return TriMeshC();
  }

  ////////////////////////////////////////////////////////////////////////////////////////

  //: Open file.
  DPOVRMLFileBodyC::DPOVRMLFileBodyC(const StringC &fn)
    : outf(fn),
      done(false)
  {}
  
  //: Open file.
  DPOVRMLFileBodyC::DPOVRMLFileBodyC(OStreamC &is)
    : outf(is),
      done(false)
  {}
  
  //: Put data.
  bool DPOVRMLFileBodyC::Put(const TriMeshC &dat) {
    if(done || !outf)
      return false;

    // Output header
    outf << "#VRML V2.0 utf8\n";
    outf << "DEF Sun DirectionalLight {\n";
    outf << "\tintensity 0.5\n";
    outf << "\tcolor 0.8 0.8 0.8\n";
    outf << "\tdirection 0.8824 -0.4578 -0.1085\n";
    outf << "\ton TRUE\n";
    outf << "}\n";

    // Output an IFS 
    outf << "Shape {\n";
    outf << "\tappearance Appearance {\n";
    outf << "\t\tmaterial Material {\n";
    outf << "\t\t\tdiffuseColor 0.7 0.7 0.7\n";
    outf << "\t\t}\n";
    outf << "\t}\n";
    outf << "\tgeometry IndexedFaceSet {\n";
    // Output all vertex coordinates
    outf << "\t\tcoord Coordinate {\n";
    outf << "\t\t\tpoint [\n";
    if(dat.Vertices().Size() != 0) {
      SArray1dIterC<VertexC> vit(dat.Vertices());
      for(; vit; vit++) {
        outf << "\t\t\t" << vit->Position() << ",\n";
      }
    }
    outf << "\t\t\t]\n";
    outf << "\t\t}\n";
    // Output vertex indices for tri's
    outf << "\t\tcoordIndex [\n";
    if(dat.Vertices().Size() != 0) {
      const VertexC *x = &(dat.Vertices()[0]);
      SArray1dIterC<TriC> fit(dat.Faces());
      for(; fit; fit++) {
        outf << "\t\t" << (fit->VertexPtr(0) - x) << ',' 
             << (fit->VertexPtr(1) - x) << ',' 
             << (fit->VertexPtr(2) - x) << ",-1,\n";
      }
    }
    outf << "\t\t]\n";
    // Output vertex normals
    // NOTE: This should be optional as it increases the file size
    outf << "\t\tnormal Normal {\n";
    outf << "\t\t\tvector [\n";
    if(dat.Vertices().Size() != 0) {
      SArray1dIterC<VertexC> vit(dat.Vertices());
      for(vit.First(); vit; vit++) {
        outf << "\t\t\t" << vit->Normal() << ",\n";
      }
    }
    outf << "\t\t\t]\n";
    outf << "\t\t}\n";
    // Output the normal indices
    outf << "\t\tnormalIndex [\n";
    if(dat.Vertices().Size() != 0) {
      const VertexC *x = &(dat.Vertices()[0]);
      SArray1dIterC<TriC> fit(dat.Faces());
      for(; fit; fit++) {
        outf << "\t\t" << (fit->VertexPtr(0) - x) << ',' 
             << (fit->VertexPtr(1) - x) << ',' 
             << (fit->VertexPtr(2) - x) << ",-1,\n";
      }
    }
    outf << "\t\t]\n";
    // Finish the IFS
    outf << "\t}\n";
    outf << "}\n";

    // Output the footer

    // Done
    return true;
  }
  
  //: Is port ready for data ?
  bool DPOVRMLFileBodyC::IsPutReady() const 
  { return !done && outf; }

  // TexTriMesh VRML File IO /////////////////////////////////////////////

  //: Open file.
  DPITexVRMLFileBodyC::DPITexVRMLFileBodyC(const StringC &fn)
    : inf(fn),
      done(false)
  {
    path = FilenameC(fn).PathComponent();
    if (!path.IsEmpty()) path += filenameSeperator ;
  }
  
  //: Is valid data ?
  bool DPITexVRMLFileBodyC::IsGetEOS() const {
    return !done && inf;
  }
  
  //: Get next piece of data.
  TexTriMeshC DPITexVRMLFileBodyC::Get() {
    if(done)
      return TexTriMeshC();

    // TO BE IMPLEMENTED
    cerr << "Error: not implemented yet!\n";
    return TexTriMeshC();


    // Done
    return TexTriMeshC();
  }

  ////////////////////////////////////////////////////////////////////////////////////////

  //: Open file.
  DPOTexVRMLFileBodyC::DPOTexVRMLFileBodyC(const StringC &fn)
    : outf(fn),
      done(false)
  {
    path = FilenameC(fn).PathComponent();
    if (!path.IsEmpty()) path += filenameSeperator ;
  }
  
  //: Put data.
  bool DPOTexVRMLFileBodyC::Put(const TexTriMeshC &dat) 
  {
    if(done || !outf)
      return false;

    // Output header
    outf << "#VRML V2.0 utf8\n";
    outf << "DEF Sun DirectionalLight {\n";
    outf << "\tintensity 0.5\n";
    outf << "\tcolor 0.8 0.8 0.8\n";
    outf << "\tdirection 0.8824 -0.4578 -0.1085\n";
    outf << "\ton TRUE\n";
    outf << "}\n";

    // Output each texture as a separate IFS
    outf << "Group {\n";
    outf << "\tchildren [\n";
    const SArray1dC<VertexC>& verts = dat.Vertices();
    UByteT texid;
    SArray1dIter2C<ImageC<ByteRGBValueC>,StringC> itTex(dat.Textures(),dat.TexFilenames());
    for (texid=0; itTex; texid++, itTex++) {
      // Output IFS
      outf << "\tShape {\n";
      outf << "\t\tappearance Appearance {\n";
      // Output the texture name
      outf << "\t\t\ttexture ImageTexture {\n";
      outf << "\t\t\t\turl \"" << itTex.Data2() << "\"\n";
      outf << "\t\t\t}\n";
      outf << "\t\t}\n";
      outf << "\t\tgeometry IndexedFaceSet {\n";
      // Output the vertices used by this texture 
      // and create lookups for the vertex indices
      outf << "\t\t\tcoord Coordinate {\n";
      outf << "\t\t\t\tpoint [\n";
      HashC<UIntT,UIntT> lookup, lookupnew;
      UIntT vid=0;
      SArray1dIterC<TriC> fit(dat.Faces());
      for(; fit; fit++) {
        if (fit.Data().TextureID()==texid) {
          IntT v;
          for (v=0; v<3; v++) {
            UIntT index = dat.Index(fit.Data(),v);
            if (!lookup[index]) {
              // Create lookup
              lookup[index] = vid;
              lookupnew[vid] = index;
              vid++;
              // Output vertex
              outf << "\t\t\t\t" << verts[index].Position() << ",\n";
            }
          }
        }
      }
      outf << "\t\t\t\t]\n";
      outf << "\t\t\t}\n";
      // Output new vertex indices for tri's
      outf << "\t\t\tcoordIndex [\n";
      if(vid!=0) {
        for(fit.First(); fit; fit++) {
          if (fit.Data().TextureID()==texid) {
            // Output new vertex indices for tri
            outf << "\t\t\t";
            IntT v;
            for (v=0; v<3; v++) {
              UIntT index = dat.Index(fit.Data(),v);
              outf << lookup[index] << ",";
            }
            outf << "-1,\n";
          }
        }
      }
      outf << "\t\t\t]\n";
      // Output vertex normals
      // NOTE: This should be optional as it increases the file size
      outf << "\t\t\tnormal Normal {\n";
      outf << "\t\t\t\tvector [\n";
      if(vid!=0) {
        UIntT index;
        for (index=0; index<vid; index++) {
          outf << "\t\t\t\t" << verts[lookupnew[index]].Normal() << ",\n";
        }
      }
      outf << "\t\t\t\t]\n";
      outf << "\t\t\t}\n";
      // Output new vertex indices for tri's
      outf << "\t\t\tnormalIndex [\n";
      if(vid!=0) {
        for(fit.First(); fit; fit++) {
          if (fit.Data().TextureID()==texid) {
            // Output new vertex indices for tri
            outf << "\t\t\t";
            IntT v;
            for (v=0; v<3; v++) {
              UIntT index = dat.Index(fit.Data(),v);
              outf << lookup[index] << ",";
            }
            outf << "-1,\n";
          }
        }
      }
      outf << "\t\t\t]\n";
      // Output texture coordinates
      outf << "\t\t\ttexCoord TextureCoordinate {\n";
      outf << "\t\t\t\tpoint [\n";
      if(vid!=0) {
        for(fit.First(); fit; fit++) {
          if (fit.Data().TextureID()==texid) {
            outf << "\t\t\t\t";
            IntT v;
            for (v=0; v<3; v++) {
              const Vector2dC coord = fit.Data().TextureCoord(v);
              outf << coord.X() << ' ' << -coord.Y() << ", ";
            }
            outf << '\n';
          }
        }
      }
      outf << "\t\t\t\t]\n";
      outf << "\t\t\t}\n";
      // Output texture indices
      outf << "\t\t\ttexCoordIndex [\n";
      if(vid!=0) {
        vid=0;
        for(fit.First(); fit; fit++) {
          if (fit.Data().TextureID()==texid) {
            outf << "\t\t\t" << vid << ',' << vid+1 << ',' << vid+2 << ",-1,\n";
            vid+=3;
          }
        }
      }
      outf << "\t\t\t]\n";
      // Finish the IFS
      outf << "\t\t}\n";
      outf << "\t}\n";
      // Save the texture image
      if (!RavlN::Save(path + itTex.Data2(),itTex.Data1())) {
        cerr << "Error: Could not save texture\n";
        done = true;
        return false;
      }
    }

    // Finish the group of IFS
    outf << "\t]\n";
    outf << "}\n";

    // Output the footer

    // Done
    return true;
  }
  
  //: Is port ready for data ?
  bool DPOTexVRMLFileBodyC::IsPutReady() const 
  { return !done && outf; }

}
