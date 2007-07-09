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

//: 3D View window example.

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/View3D.hh"
#include "Ravl/Option.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/3D/TexTriMesh.hh"
#include "Ravl/GUI/DTexTriMesh3D.hh"
#include "Ravl/GUI/DTriMesh3D.hh"
#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/3D/MeshShapes.hh"

#include <GL/gl.h>

using namespace RavlN;
using namespace RavlGUIN;
using namespace Ravl3DN;

int main(int nargs,char *args[]) 
{
  OptionC opts(nargs,args); // Make sure help option is detected.
  StringC file = opts.String("i",PROJECT_OUT "/share/RAVL/data/cube.tri","input filename");
  bool verbose = opts.Boolean("v",false,"Verbose mode. ");
  bool texture = opts.Boolean("t",false,"Use texture. ");
  IntT shapeId = opts.Int("s",-1,"Use shape, 0=Plane, 1=Cube, 2=Sphere. ");
  opts.Check();
  
  DObject3DC object;
  if(shapeId >= 0) {
    TriMeshC mesh;
    switch(shapeId) 
      {
      case 0: // Plane 
        mesh = CreateTriMeshPlane();
        break;
      case 1: // Cube
        mesh = CreateTriMeshCube();
        break;
      case 2: // Sphere
        mesh = CreateTriMeshSphere(5,8,1.0);
        break;
      default:
        cerr << "Invalid shape id " << shapeId << "\n";
        return -1;
        break;
      }
    object = DTexTriMesh3DC(mesh);
  } else { 
    if(texture) {
      TexTriMeshC mesh;
      if (!Load(file,mesh,"",verbose)) {
        cerr << "Could not load input file " << file << endl;
        return 1;
      }
      object = DTexTriMesh3DC(mesh);
    } else {
      TriMeshC mesh;
      if (!Load(file,mesh,"",verbose)) {
        cerr << "Could not load input file " << file << endl;
        return 1;
      }
      object = DTriMesh3DC(mesh);
    }
  }
  
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
