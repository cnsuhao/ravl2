
#ifndef _RAVL_DSURFACE_POINT_VERTEX_BYTE_RGB_ARRAY_HH_
#define _RAVL_DSURFACE_POINT_VERTEX_BYTE_RGB_ARRAY_HH_ 1

#include "Ravl/GUI/DObject3D.hh"
#include "Ravl/3D/SurfacePoint3dArray.hh"
#include "Ravl/3D/VertexColourByteRGB.hh"

namespace RavlGUIN
{
  using namespace Ravl3DN;
  
  //! userlevel=Normal
  //: Direct OpenGL render of vertex array, using current colour.
  void DSurfacePointVertexByteRGBArray(const SurfacePoint3dArrayC<VertexColourByteRGBC>& s);

  //! userlevel=Develop
  //: Rendering class for vertex array.
  //  Does not set the colour, so will use current OpenGL colour.
  class DSurfacePointVertexByteRGBArrayBodyC
    : public DObject3DBodyC
  {
  public:
    DSurfacePointVertexByteRGBArrayBodyC(const SurfacePoint3dArrayC<VertexColourByteRGBC>& s)
      : surface(s)
    {}
    // constructor
    
    virtual bool Render(Canvas3DC &c3d)
    {  
      DSurfacePointVertexByteRGBArray(surface); 
      return true; 
    }
    //: render object
    
  protected:
    SurfacePoint3dArrayC<VertexColourByteRGBC> surface;
  };
  
  //! userlevel=Normal
  //: Rendering class for vertex array, using current OpenGL colour.
  //  Does not set the colour, so will use current OpenGL colour.
    
  class DSurfacePointVertexByteRGBArrayC
    : public DObject3DC
  {
  public:
    DSurfacePointVertexByteRGBArrayC()
    {}
    //: Default constructor, creates an invalid handle.
    
    DSurfacePointVertexByteRGBArrayC(const SurfacePoint3dArrayC<VertexColourByteRGBC>& s)
      : DObject3DC(*new DSurfacePointVertexByteRGBArrayBodyC(s))
    {}
    //: Construct drawing object from array of coloured vertices.
  };
}
 

#endif
