// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_DVIEWPOINT3D_HEADER
#define RAVLGUI_DVIEWPOINT3D_HEADER 1
////////////////////////////////////////////
//! docentry="Ravl.API.GUI.3D"
//! rcsid="$Id$"
//! file="Ravl/GUI/3D/DViewPoint3D.hh"
//! lib=RavlGUI3D
//! author="Charles Galambos"
//! date="12/04/99"

#include "Ravl/GUI/DObject3D.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/Point3d.hh"

namespace RavlGUIN {
  
  //! userlevel=Develop
  //: Setup a view point in the 3D world.
  // See handles description for more information.
  
  class DViewPoint3DBodyC
    : public DObject3DBodyC
  {
  public:
    DViewPoint3DBodyC(RealT nFov,
		      Point3dC nEye,    // Position of eye.
		      Point3dC nCentre, // Center of object to look at.
		      Vector3dC nUp,   // Up direction.
		      RealT dNear,
		      RealT dFar
		      )
      : fov(nFov),
	eye(nEye),
	centre(nCentre),
	up(nUp),
	m_dNear(dNear),
	m_dFar(dFar)
    {}
    //: Default constructor.
    
    virtual bool Render(Canvas3DC &c3d);
    //: Render object.
    
  protected:
    RealT fov;       // Field of view angle.
    Point3dC eye;    // Position of eye.
    Point3dC centre; // Center of object to look at.
    Vector3dC up;    // Up direction.
    RealT m_dNear, m_dFar; // Clipping planes
  };
  
  //! userlevel=Normal
  //: Setup a view point in the 3D world.
  // This also does some default setup of depth buffers, and shape
  // models.  If you wish to configures these aspects yours self you
  // should do so after using this class. (Or not use it at all.)
  
  class DViewPoint3DC
    : public DObject3DC
  {
  public:
    DViewPoint3DC(RealT fov = 90,
		  Point3dC nEye = Point3dC(0,0,5),
		  Point3dC nCentre  = Point3dC(0,0,0), 
		  Vector3dC nUp = Vector3dC(0,1,0),
		  RealT dNear = 0.2,RealT dFar =100
		  )
    : DObject3DC(*new DViewPoint3DBodyC(fov,nEye,nCentre,nUp,dNear,dFar))
      {}
    //: Constructor.
    // Position of eye. (0,0,-1)
    // Center of object (0,0,0)
    // Up direction.  (Y Axis.)
    
  protected:
    DViewPoint3DBodyC &Body() 
      { return dynamic_cast<DViewPoint3DBodyC &>(DObject3DC::Body()); }
    
    const DViewPoint3DBodyC &Body() const
      { return dynamic_cast<const DViewPoint3DBodyC &>(DObject3DC::Body()); }
    
  public:
    
    
  };
  
}

#endif
