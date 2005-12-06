// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI3D
//! docentry="Ravl.API.GUI.3D"
//! author="James Smith"
//! userlevel=Normal

//: Textured mesh display example.

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/View3D.hh"
#include "Ravl/Option.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/3D/TexTriMesh.hh"
#include "Ravl/GUI/DTexTriMesh3D.hh"
#include "Ravl/GUI/DTriMesh3D.hh"
#include "Ravl/DP/FileFormatIO.hh"

#include <GL/gl.h>

using namespace RavlN;
using namespace RavlGUIN;
using namespace Ravl3DN;

int main(int nargs,char *args[]) 
{
  OptionC opts(nargs,args); // Make sure help option is detected.
  StringC file = opts.String("i",PROJECT_OUT "/share/RAVL/pixmaps/monkey.ppm","input filename");
  bool verbose = opts.Boolean("v",false,"Verbose mode. ");
  //bool texture = opts.Boolean("t",false,"Use texture. ");
  opts.Check();
  
  DObject3DC object;

  // Load an image.
  
  ImageC<ByteRGBValueC> img;
  if (!Load(file,img,"",verbose)) {
    cerr << "Could not load input file " << file << endl;
    return 1;
  }
  
  // Create a simple mesh.
  
  SArray1dC<Vector3dC> verts(4);
  verts[0] = Vector3dC(0,0,0);
  verts[1] = Vector3dC(0,1,0);
  verts[2] = Vector3dC(1,1,0);
  verts[3] = Vector3dC(1,0,0);
  
  SArray1dC<UIntT> faces(6);
  faces [0] = 2;
  faces [1] = 1;
  faces [2] = 0;
  faces [3] = 0;
  faces [4] = 3;
  faces [5] = 2;
  
  TexTriMeshC mesh(verts,faces);

  // Add a texture to the mesh.
  // This uses the default texture coordinates, which aren't quite right.
  
  SArray1dC<ImageC<ByteRGBValueC> > textures(1);
  textures[0] = img;
  mesh.Textures() = textures;
  
  // Create a display object for the mesh
  
  object = DTexTriMesh3DC(mesh);
  
  Manager.Init(nargs,args);
  
  WindowC win(100,100,file);  
  View3DC view(400,400);  
  win.Add(view);
  win.Show();  
  
  cerr << "Starting gui. \n";
  Manager.Execute();
  
  view.Add(object);
  view.SceneComplete();
  
  Manager.Wait();

  return 0;
}
