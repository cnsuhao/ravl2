// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI3D

#include "Ravl/GUI/Util.hh"
#include "Ravl/GUI/Canvas3D.hh"

namespace RavlGUIN {

  //////////////////////////////////////////////
  //: Render object.
  
  bool DSwapBuff3DBodyC::Render(Canvas3DC &c3d) {
    c3d.GUISwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
    
    return true;
  }
  
  //////////////////////////////////////////////
  //: Render object.
  
  bool DTransform3DBodyC::Render(Canvas3DC &c3d) {
    glPushMatrix();
    if(doRot)
      glRotated(angle,axis.X(),axis.Y(),axis.Z());
    if(doTrans)
      glTranslated(trans.X(),trans.Y(),trans.Z());
    for(DLIterC<DObject3DC> it(parts);it.IsElm();it.Next())
      it.Data().RenderDL(c3d);
    glPopMatrix();
    return true;
  }
}
