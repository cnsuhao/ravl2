// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI3D

#include "Ravl/GUI/DCube3D.hh"
#include <GL/gl.h>

namespace RavlGUIN {

  //: Render object.
  
  bool DCube3DBodyC::Render(Canvas3DC &c3d) {
    //cerr << "DCube3DBodyC::Render(), Called. \n";
    
    GLColour(colour);
    Vector3dC d1 = diag/2;
    Vector3dC d2 = -diag/2;
    
#if 0
    glBegin(GL_QUAD_STRIP);
    {	       
      glNormal3d(0,0,-1);
      glVertex3d(d1.X(),d1.Y(),d1.Y());
      glVertex3d(d2.X(),d1.Y(),d1.Y());
      
      glNormal3d(0,1,0);
      glVertex3d(d1.X(),d2.Y(),d1.Y());
      glVertex3d(d2.X(),d2.Y(),d1.Y());
      
      glNormal3d(0,0,1);
      glVertex3d(d1.X(),d2.Y(),d2.Y());
      glVertex3d(d2.X(),d2.Y(),d2.Y());
      
      glNormal3d(0,-1,0);
      glVertex3d(d1.X(),d1.Y(),d2.Y());
      glVertex3d(d2.X(),d1.Y(),d2.Y());
      
      glNormal3d(0,0,-1);
      glVertex3d(d1.X(),d1.Y(),d1.Y());
      glVertex3d(d2.X(),d1.Y(),d1.Y());
    }
    glEnd();
#endif  
    
#if 1
    glBegin(GL_QUAD_STRIP);
    {
      glNormal3d(1,0,0);
      
      glVertex3d(d1.X(),d1.Y(),d1.Y());
      glVertex3d(d1.X(),d2.Y(),d1.Y());
      
      glVertex3d(d1.X(),d1.Y(),d2.Y());
      glVertex3d(d1.X(),d2.Y(),d2.Y());
    }
    glEnd();
    
    
    glBegin(GL_QUAD_STRIP);
    {
      glNormal3d(-1,0,0);
      
      glVertex3d(d2.X(),d1.Y(),d1.Y());
      glVertex3d(d2.X(),d2.Y(),d1.Y());
      
      glVertex3d(d2.X(),d1.Y(),d2.Y());
      glVertex3d(d2.X(),d2.Y(),d2.Y());
    }
    glEnd();
#endif  
    return true;
  }
}
