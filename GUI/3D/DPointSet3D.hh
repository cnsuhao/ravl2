// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef _DPOINTSET3D_
#define _DPOINTSET3D_ 1
///////////////////////////////////////////////////
//! docentry="Ravl.GUI.3D"
//! rcsid="$Id$"
//! file="Ravl/GUI/3D/DTriMesh3D.hh"
//! lib=RavlGUI3D
//! author="James Smith"
//! date="2/4/2001"

#include "Ravl/GUI/DObject3D.hh"
#include "Ravl/3D/PointSet.hh"

namespace RavlGUIN 
{
  using namespace Ravl3DN;
  
  // Draw a Point Set

  class DPointSet3DBodyC
    : public DObject3DBodyC
  {
  public:
    DPointSet3DBodyC(const PointSetC& oPointSet)
      : pointSet(oPointSet)
    {}
    // Constructor.
    
    virtual bool Render(Canvas3DC &c3d);
    //: Render object.
    
  protected:
    PointSetC pointSet;
  };
  
    
  class DPointSet3DC
    : public DObject3DC
  {
  public:
    DPointSet3DC()
    {}
    // Default constructor, creates an invalid handle.
    
    DPointSet3DC(const PointSetC& oPointSet)
      : DObject3DC(*new DPointSet3DBodyC(oPointSet))
    {}
    // Constructor.
    
  protected:
    DPointSet3DBodyC& Body() 
    { return dynamic_cast<DPointSet3DBodyC &>(DObject3DC::Body()); }
    
    const DPointSet3DBodyC &Body() const
    { return dynamic_cast<const DPointSet3DBodyC &>(DObject3DC::Body()); }  
    
  public:  
  };
  
}

#endif //_DPOINTSET3D_
