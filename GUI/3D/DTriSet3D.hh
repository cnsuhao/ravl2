#ifndef RAVL_DTRISET3D_HEADER
#define RAVL_DTRISET3D_HEADER 1
///////////////////////////////////////////////////
//! docentry="Ravl.GUI.3D"
//! rcsid="$Id$"
//! file="Ravl/GUI/3D/DTriSet3D.hh"
//! lib=GUI3D
//! author="James Smith"
//! date="2/4/2001"

#include "Ravl/GUI/DObject3D.hh"
#include "Ravl/3D/TriSet.hh"

namespace RavlGUIN {
  using namespace Ravl3DN;
  
  //! userlevel=Develop
  //: Draw a TriSet
  
  class DTriSet3DBodyC
    : public DObject3DBodyC
  {
  public:
    DTriSet3DBodyC(const TriSetC &oTriSet)
      : model(oTriSet)
    {}
    //: Constructor.
    
    virtual bool Render(Canvas3DC &c3d);
    //: Render object.
    
  protected:
    TriSetC model;
  };
  
  //! userlevel=Normal
  //: Draw a TriSet
  
  class DTriSet3DC
    : public DObject3DC
  {
  public:
    DTriSet3DC()
    {}
    //: Default constructor.
    // creat an invalid handle.
    
    DTriSet3DC(const TriSetC &oTriSet)
      : DObject3DC(*new DTriSet3DBodyC(oTriSet))
    {}
    //: Constructor.
    
  protected:
    DTriSet3DBodyC &Body() 
    { return dynamic_cast<DTriSet3DBodyC &>(DObject3DC::Body()); }
    
    const DTriSet3DBodyC &Body() const
    { return dynamic_cast<const DTriSet3DBodyC &>(DObject3DC::Body()); }  
    
  public:  
  };
  
  ostream &operator<<(ostream &strm,const DTriSet3DC &);
  istream &operator>>(istream &strm,DTriSet3DC &);
}
#endif
