// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DTRISET3D_HEADER
#define RAVL_DTRISET3D_HEADER 1
///////////////////////////////////////////////////
//! docentry="Ravl.GUI.3D"
//! rcsid="$Id$"
//! file="Ravl/GUI/3D/DTriMesh3D.hh"
//! lib=RavlGUI3D
//! author="James Smith"
//! date="2/4/2001"

#include "Ravl/GUI/DObject3D.hh"
#include "Ravl/3D/TriMesh.hh"

namespace RavlGUIN {
  using namespace Ravl3DN;
  
  //! userlevel=Develop
  //: Draw a TriMesh
  
  class DTriMesh3DBodyC
    : public DObject3DBodyC
  {
  public:
    DTriMesh3DBodyC(const TriMeshC &oTriMesh)
      : model(oTriMesh)
    {}
    //: Constructor.
    
    virtual bool Render(Canvas3DC &c3d);
    //: Render object.
    
  protected:
    TriMeshC model;
  };
  
  //! userlevel=Normal
  //: Draw a TriMesh
  
  class DTriMesh3DC
    : public DObject3DC
  {
  public:
    DTriMesh3DC()
    {}
    //: Default constructor.
    // creat an invalid handle.
    
    DTriMesh3DC(const TriMeshC &oTriMesh)
      : DObject3DC(*new DTriMesh3DBodyC(oTriMesh))
    {}
    //: Constructor.
    
  protected:
    DTriMesh3DBodyC &Body() 
    { return dynamic_cast<DTriMesh3DBodyC &>(DObject3DC::Body()); }
    
    const DTriMesh3DBodyC &Body() const
    { return dynamic_cast<const DTriMesh3DBodyC &>(DObject3DC::Body()); }  
    
  public:  
  };
  
  ostream &operator<<(ostream &strm,const DTriMesh3DC &);
  istream &operator>>(istream &strm,DTriMesh3DC &);
}
#endif
