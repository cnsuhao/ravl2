
#include "Ravl/GUI/DPinholeCamera03D.hh"

namespace RavlGUIN
{
  using namespace Ravl3DN;
  
  bool DPinholeCamera03DBodyC::Render(Canvas3DC &c3d)
  {
    // get camera
    PinholeCamera0C& cam = camera;

    // virtual image size
    RealT sx = canvas_region.Cols();
    RealT sy = canvas_region.Rows();

    // create camera projection matrix
    double matrixProject[16] =
    {
      2.0*cam.fx()/sx, 0.0, 0.0, 0.0,
      0.0, -2.0*cam.fy()/sy, 0.0,  0.0,
      (2.0*cam.cx()/sx)-1.0, 1.0-(2.0*cam.cy()/sy), 1.01,  1.0,
      0.0, 0.0, -1.0, 0.0
    };
    
    // create homogeneous transform matrix
    double matrixModelView[16] =
    {
      cam.R()[0][0],  cam.R()[1][0],  cam.R()[2][0], 0.0,
      cam.R()[0][1],  cam.R()[1][1],  cam.R()[2][1], 0.0,
      cam.R()[0][2],  cam.R()[1][2],  cam.R()[2][2], 0.0,
      cam.t()[0],     cam.t()[1],     cam.t()[2],    1.0
    };
    
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrixProject);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(matrixModelView);    

    return true;
  }

}
