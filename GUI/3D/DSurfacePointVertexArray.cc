
#include "Ravl/GUI/DSurfacePointVertexArray.hh"
#include "Ravl/SArray1dIter.hh"

namespace RavlGUIN
{
  void DSurfacePointVertexArray(const SurfacePoint3dArrayC<VertexC>& s)
  {
    glBegin(GL_POINTS);
    for (SArray1dIterC<VertexC> i(s); i; i++)
    {
      glNormal3dv(&(*i).Normal()[0]);
      glVertex3dv(&(*i).Position()[0]);
    }
    glEnd();
  }
}
