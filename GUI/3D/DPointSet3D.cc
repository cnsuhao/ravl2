// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include "Ravl/GUI/DPointSet3D.hh"
#include "Ravl/GUI/Canvas3D.hh"
#include "GL/gl.h"
//! rcsid="$Id$"
//! lib=RavlGUI3D

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  // Render object.
  bool DPointSet3DBodyC::Render(Canvas3DC& canvas) 
  {
    ONDEBUG(cerr << "DPointSet3DBodyC::Render(), Called. \n");
    // cerr << "Point set render number: " << pointSet.RenderNumber() << endl;

    if (!pointSet.IsValid()) {
      cerr << "invalid point set" << endl;
      return true; // Don't do anything.
    }
    
    SArray1dC<VertexC>& verts = pointSet.Vertices();
    if(pointSet.HaveColour()) {
      SArray1dC<ByteRGBValueC> colours = pointSet.Colours();
      glBegin(GL_POINTS);
      for (UIntT ipoint = 0; ipoint < verts.Size(); ipoint++) {
	Vector3dC &v = verts[ipoint].Position();
	ByteRGBValueC &rgb = colours[ipoint];
	glColor3d(rgb[0]/255.0,rgb[1]/255.0,rgb[2]/255.0);
	glVertex3d(v[0],v[1],v[2]);
	// cerr << "v: " << v << endl;
	// glVertex3dv(&verts[ipoint].Position()[0]);
      }
      glEnd();
      
    } else {
      glColor3d(1.0,1.0,1.0);
      glBegin(GL_POINTS);
      for (UIntT ipoint = 0; ipoint < verts.Size(); ipoint++) {
	Vector3dC &v = verts[ipoint].Position();
	glVertex3d(v[0],v[1],v[2]);
	// cerr << "v: " << v << endl;
	// glVertex3dv(&verts[ipoint].Position()[0]);
      }
      glEnd();
    }

    
#if 0
    
    cerr << "vertex[0].Position(): " << verts[0].Position() << endl;
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_DOUBLE,sizeof(VertexC),&verts[0].Position()[0]);
    glDrawArrays(GL_POINTS,0,pointSet.RenderNumber());
#endif


#if 0
    // Setup materials and colours as appropriate
    bool bColour = pointSet.HaveColour();
    if (!bColour) 
    {
      if (canvas.GetLightingMode()) 
      {
        GLfloat ambient[]  = {0.2,0.2,0.2,1.0};
        GLfloat diffuse[]  = {0.9,0.9,0.9,1.0};
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      } 
      else 
      {
        glColor3f(1.0,1.0,1.0);
      }
    }
#endif


#if 0
    // Enable rendering arrays
    SArray1dC<VertexC> verts = pointSet.Vertices();
    // glEnableClientState(GL_NORMAL_ARRAY);
    // glNormalPointer(GL_DOUBLE,sizeof(VertexC),(void *)&(verts[0].Normal()));
    // glEnableClientState(GL_VERTEX_ARRAY);

    glEnable(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_DOUBLE,sizeof(VertexC),(void *)&(verts[0].Position()));
    //if (bColour)
    //{
    // SArray1dC<ByteRGBValueC> colours = pointSet.Colours();
    //glEnableClientState(GL_COLOR_ARRAY);
    //glColorPointer(3,GL_UNSIGNED_BYTE,sizeof(ByteRGBValueC),(void *)&(colours[0]));
    //}

    // Render
    // glShadeModel(GL_FLAT);
    glDrawArrays(GL_POINTS,0,pointSet.RenderNumber());

    // Disable rendering arrays
    // glDisableClientState(GL_NORMAL_ARRAY);
    // glDisableClientState(GL_VERTEX_ARRAY);
    // if (bColour) glDisableClientState(GL_COLOR_ARRAY);

    // Finish colouring
    // if (!bColour && canvas.GetLightingMode())
    // glDisable(GL_COLOR_MATERIAL);
#endif

    return true;
  }


  //: Get center of object.
  // defaults to 0,0,0
  
  Vector3dC DPointSet3DBodyC::Center() {
    
    Vector3dC ncenter(0,0,0);
    SArray1dC<VertexC>& verts = pointSet.Vertices();
    for(SArray1dIterC<VertexC> it(verts);it;it++)
      ncenter += it->Position();
    
    ncenter /= (RealT) verts.Size();
    return ncenter;
  }
  
  //: Get extent of object.
  // defaults to 1
  
  RealT DPointSet3DBodyC::Extent() {
    Vector3dC ncenter(0,0,0);
    SArray1dC<VertexC>& verts = pointSet.Vertices();
    for(SArray1dIterC<VertexC> it(verts);it;it++)
      ncenter += it->Position();
    ncenter /= (RealT) verts.Size();
    
    RealT dist = 0;
    for(SArray1dIterC<VertexC> it(verts);it;it++)
      dist = Max(dist,Sqrt((ncenter - it->Position()).SumOfSqr()));
    
    return dist;
  }

}

