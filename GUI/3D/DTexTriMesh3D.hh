// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DTEXTRIMESH3D_HEADER
#define RAVL_DTEXTRIMESH3D_HEADER 1
///////////////////////////////////////////////////
//! docentry="Ravl.GUI.3D"
//! rcsid="$Id$"
//! file="Ravl/GUI/3D/DTexTriMesh3D.hh"
//! lib=RavlGUI3D
//! author="James Smith"
//! date="2/4/2001"

#include "Ravl/GUI/DTriMesh3D.hh"
#include "Ravl/3D/TexTriMesh.hh"

namespace RavlGUIN {
  using namespace Ravl3DN;
  
  //! userlevel=Develop
  //: Draw a TexTriMesh
  
  class DTexTriMesh3DBodyC
    : public DTriMesh3DBodyC
  {
  public:
    DTexTriMesh3DBodyC(const TexTriMeshC &oTexTriMesh);
    //: Constructor.
    
    ~DTexTriMesh3DBodyC();
    
    virtual bool Render(Canvas3DC &c3d);
    //: Render object.
    
  protected:
    TexTriMeshC tmodel;
    GLuint* texNames;
  };
  
  //! userlevel=Normal
  //: Draw a TexTriMesh
  
  class DTexTriMesh3DC
    : public DTriMesh3DC
  {
  public:
    DTexTriMesh3DC()
    {}
    //: Default constructor.
    // creat an invalid handle.
    
    DTexTriMesh3DC(const TexTriMeshC &oTexTriMesh)
      : DTriMesh3DC(*new DTexTriMesh3DBodyC(oTexTriMesh))
    {}
    //: Constructor.
    
  protected:
    DTexTriMesh3DBodyC &Body() 
    { return dynamic_cast<DTexTriMesh3DBodyC &>(DObject3DC::Body()); }
    
    const DTexTriMesh3DBodyC &Body() const
    { return dynamic_cast<const DTexTriMesh3DBodyC &>(DObject3DC::Body()); }  
    
  public:  
  };
  
  ostream &operator<<(ostream &strm,const DTexTriMesh3DC &);
  istream &operator>>(istream &strm,DTexTriMesh3DC &);
}
#endif
