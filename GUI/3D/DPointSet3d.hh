// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_DPOINTSET3D_HEADER
#define RAVLGUI_DPOINTSET3D_HEADER 1
///////////////////////////////////////////////////
//! docentry="Ravl.API.GUI.3D"
//! rcsid="$Id$"
//! file="Ravl/GUI/3D/DPointSet3D.hh"
//! lib=RavlGUI3D
//! author="Joel Mitchelson"
//! date="31/1/2002"

#include "Ravl/GUI/DObject3D.hh"
#include "Ravl/PointSet3d.hh"

namespace RavlGUIN 
{
  
  //! userlevel=Develop
  //: Body to draw a Point Set

  class DPointSet3dBodyC
    : public DObject3DBodyC
  {
  public:
    DPointSet3dBodyC(const PointSet3dC& oPointSet)
      : pointSet(oPointSet)
    {}
    // Constructor.
    
    virtual bool Render(Canvas3DC &c3d);
    //: Render object.
    
    virtual Vector3dC Center();
    //: Get center of object.
    // defaults to 0,0,0
    
    virtual RealT Extent();
    //: Get extent of object.
    // defaults to 1
    
  protected:
    PointSet3dC pointSet;
  };
  
    
  //! userlevel=Normal
  //: Draw a Point Set

  class DPointSet3dC
    : public DObject3DC
  {
  public:
    DPointSet3dC()
    {}
    // Default constructor, creates an invalid handle.
    
    DPointSet3dC(const PointSet3dC& oPointSet)
      : DObject3DC(*new DPointSet3dBodyC(oPointSet))
    {}
    // Constructor.
    
  protected:
    DPointSet3dBodyC& Body() 
    { return dynamic_cast<DPointSet3dBodyC &>(DObject3DC::Body()); }
    
    const DPointSet3dBodyC &Body() const
    { return dynamic_cast<const DPointSet3dBodyC &>(DObject3DC::Body()); }  
    
  public:  
  };
  
}

#endif 
