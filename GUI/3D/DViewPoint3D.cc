// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI3D

#include "Ravl/GUI/DViewPoint3D.hh"
#include "Ravl/GUI/Canvas3D.hh"
#include <GL/gl.h>
#include <GL/glu.h>

namespace RavlGUIN {

  //: Render object.
  
  bool DViewPoint3DBodyC::Render(Canvas3DC &canvas) { 
    //cerr << "DViewPoint3DBodyC::Render(), Called. \n";
    // Setup GL stuff.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    RealT dAspect = 1;//canvas.Size()[0]/canvas.Size()[1];
    gluPerspective(fov,dAspect,m_dNear,m_dFar);
    gluLookAt(eye.X(),eye.Y(),eye.Z(),centre.X(),centre.Y(),centre.Z(),up.X(),up.Y(),up.Z());
    
    //glDepthRange(1,5);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //glTranslatef(0,0,-15);
    
    return true;
  }
  
}
