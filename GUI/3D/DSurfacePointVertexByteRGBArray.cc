
#include "Ravl/GUI/DSurfacePointVertexByteRGBArray.hh"
#include "Ravl/SArray1dIter.hh"

namespace RavlGUIN
{
  void DSurfacePointVertexByteRGBArray(const SurfacePoint3dArrayC<VertexColourByteRGBC>& s)
  {
    glBegin(GL_POINTS);
    for (SArray1dIterC<VertexColourByteRGBC> i(s); i; i++)
    {
      glColor3ubv(&(*i).Colour()[0]);
      glNormal3dv(&(*i).Normal()[0]);
      glVertex3dv(&(*i).Position()[0]);
    }
    glEnd();
  }
}
