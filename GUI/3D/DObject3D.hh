// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDOBJECT3D_HEADER
#define RAVLDOBJECT3D_HEADER 1
//////////////////////////////////////////////////////////
//! docentry="Ravl.GUI.3D"
//! rcsid="$Id$"
//! file="Ravl/GUI/3D/DObject3D.hh"
//! lib=RavlGUI3D
//! author="Charles Galambos"
//! date="12/04/99"

#include "Ravl/RefCounter.hh"
#include "Ravl/Trigger.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/Point3d.hh"
#include "Ravl/DList.hh"
#include <GL/gl.h>
#include "Ravl/Assert.hh"


namespace RavlGUIN {
  using namespace RavlN;
  using namespace RavlImageN;
  
  class Canvas3DC;
  
  //! userlevel=Develop
  //: Body of a basic display object in a 3d world.
  
  class DObject3DBodyC
    : public RCBodyVC
  {
  public:
    DObject3DBodyC()
      : id(-1)
      {}
    //: Default constructor.
    
    ~DObject3DBodyC();
    //: Destructor.
    // Make sure display list is free'd
    
    virtual bool Render(Canvas3DC &c3d);
    //: Render object.
    
    bool RenderDL(Canvas3DC &c3d);
    //: Render, checking for display lists.
    
    inline
    void GLColour(const RealRGBValueC &colour)
      { glColor3d(colour.Red(),colour.Green(),colour.Blue()); }
    //: Set current colour.
    
    inline
      void GLVertex(const Point3dC &v)
      { glVertex3d(v.X(),v.Y(),v.Z()); }
    //: Set a vertex.
    
    inline
      void GLNormal(const Vector3dC &v)
      { glNormal3d(v.X(),v.Y(),v.Z()); }
    //: Set a vertex.
    
    inline
      void GLTexCoord(const Point2dC &p)
      { glTexCoord2d(p.X(),p.Y()); }
    //: Set a texture coordinate
  
    virtual Vector3dC Center()
      { return Vector3dC(0,0,0); }
    //: Get center of object.
    // defaults to 0,0,0
    
    virtual RealT Extent()
    { return 1; }
    //: Get extent of object.
    // defaults to 1
    
    void EnableDisplayList() 
      { id = -2; }
    //: Enable generation of a display list.
    
    IntT DisplayListID() const
      { return id; }
    //: Access display list ID.
    
    IntT &DisplayListID()
      { return id; }
    //: Access display list ID.
    
  protected:
    IntT id; // Display list id. -1=None. -2=To be generated...
    
  };
  
  //! userlevel=Normal
  //: Handle to basic object in a 3d world.
  
  class DObject3DC
    : public RCHandleC<DObject3DBodyC>
  {
  public:
    DObject3DC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DObject3DC(DObject3DBodyC &bod)
      : RCHandleC<DObject3DBodyC>(bod)
      {}
    //: Body constructor.
    
  protected:
    DObject3DBodyC &Body() { return RCHandleC<DObject3DBodyC>::Body(); }
    //: Access body.
    
    const DObject3DBodyC &Body() const { return RCHandleC<DObject3DBodyC>::Body(); }
    //: Access body.
    
  public:
    bool Render(Canvas3DC &c3d)
      { return Body().Render(c3d); }
    //: Render object.
    
    bool RenderDL(Canvas3DC &c3d)
      { return Body().RenderDL(c3d); }
    //: Render object, checking for display list.
    
    void EnableDisplayList() 
      { Body().EnableDisplayList(); }
    //: Enable generation of a display list.
    
    IntT DisplayListID() const
      { return Body().DisplayListID(); }
    //: Access display list ID.
    
    IntT &DisplayListID()
      { return Body().DisplayListID(); }
    //: Access display list ID.
  
    Vector3dC Center()
      { return Body().Center(); }
    //: Get center of object.
    // defaults to 0,0,0
    
    RealT Extent()
      { return Body().Extent(); }
    //: Get extent of object.
    // defaults to 1
    
  };


  ostream &operator<<(ostream &strm,const DObject3DC &);
  istream &operator>>(istream &strm,DObject3DC &);

  ////////////////////////////////////
  
  //! userlevel=Develop
  //: Body for OpenGL code invokation class.
  
  class DOpenGLBodyC
    : public DObject3DBodyC
  {
  public:
    DOpenGLBodyC(const TriggerC &se,const Vector3dC &ncenter = Vector3dC(0,0,0),RealT nextent = 1)
      : sigEvent(se),
      center(ncenter),
      extent(nextent)
      {}
    //: Constructor.
    
    virtual Vector3dC Center() 
      { return center; }
    //: Get center of object.
    // defaults to 0,0,0
    
    virtual RealT Extent() 
      { return extent; }
    //: Get extent of object.
    // defaults to 1
    
  protected:
    virtual bool Render(Canvas3DC &c3d);
    //: Render object.
    
    TriggerC sigEvent;
    Vector3dC center;
    RealT extent;
  };
  
  //! userlevel=Develop
  //: OpenGL code invokation class.
  
  class DOpenGLC
    : public DObject3DC
  {
  public:
    DOpenGLC()
      {}
    //: Default constructor.
    // NB. Creates an invalid handle.
    
    DOpenGLC(const TriggerC &se,const Vector3dC &ncenter = Vector3dC(0,0,0),RealT nextent = 1)
      : DObject3DC(*new DOpenGLBodyC(se,ncenter,nextent))
      {}
    //: Constructor.
  };
  
  ostream &operator<<(ostream &strm,const DOpenGLC &);
  istream &operator>>(istream &strm,DOpenGLC &);
  
  ////////////////////////////////////
  
  //! userlevel=Develop
  //: Body of a  object set in a 3d world.
  
  class DObjectSet3DBodyC
    : public DObject3DBodyC
  {
  public:
    DObjectSet3DBodyC();
    //: Default constructor.
    
    virtual bool Render(Canvas3DC &c3d);
    //: Render object.
    
    inline void Add(const DObject3DC &obj)
      { parts.InsLast(obj); }
    //: Add object into list.
    
    virtual Vector3dC Center();
    //: Get center of object.
    // defaults to 0,0,0
    
    virtual RealT Extent();
    //: Get extent of object.
    // defaults to 1
    
  protected:
    DListC<DObject3DC> parts;
    bool done;
    bool gotCenter;
    Vector3dC center;
    bool gotExtent;
    RealT extent;
  };
  
  //! userlevel=Normal
  //: Handle to basic object in a 3d world.
  
  class DObjectSet3DC
    : public DObject3DC
  {
  public:
    DObjectSet3DC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DObjectSet3DC(bool withBod)
      : DObject3DC(*new DObjectSet3DBodyC())
      {}
    //:  Constructor.
    
    DObjectSet3DC(DObjectSet3DBodyC &bod)
      : DObject3DC(bod)
      {}
    //: Body Constructor.
    
  protected:
    DObjectSet3DBodyC &Body() 
      { return dynamic_cast<DObjectSet3DBodyC &>(DObject3DC::Body()); }
    
    const DObjectSet3DBodyC &Body() const
      { return dynamic_cast<const DObjectSet3DBodyC &>(DObject3DC::Body()); }
    
  public:
    const DObjectSet3DC &operator+=(const DObject3DC &obj)
      { Body().Add(obj); return *this; }
    //: Add object into list.
  };
  
  ostream &operator<<(ostream &strm,const DObjectSet3DC &);
  istream &operator>>(istream &strm,DObjectSet3DC &);

}
#endif

