// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUICANVAS3D_HEADER
#define RAVLGUICANVAS3D_HEADER 1
/////////////////////////////////////////////////////
//! docentry="Ravl.GUI.3D"
//! rcsid="$Id$"
//! file="Ravl/GUI/3D/3DCanvas.hh"
//! lib=RavlGUI3D
//! example=exCanvas3D.cc
//! author="Charles Galambos"
//! date="12/04/99"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/DP/Port.hh"
#include "Ravl/GUI/DObject3D.hh"
#include "Ravl/GUI/Util.hh"
#include "Ravl/GUI/DViewPoint3D.hh"
#include "Ravl/GUI/DLight3D.hh"
#include "Ravl/CallMethods.hh"
#include "Ravl/CallMethodRefs.hh"

//#include "Ravl/Threads/EventHandlerRef.hh"

typedef struct _GdkGLContext GdkGLContext;
typedef struct _GdkVisual GdkVisual;

namespace RavlGUIN {

  
  //! userlevel=Default
  //: 3D Canvas Rendering modes
  
  enum Canvas3DRenderMode {
    C3D_POINT,
    C3D_WIRE,
    C3D_FLAT,
    C3D_SMOOTH
  };
  
  
  //! userlevel=Develop
  //: 3D Canvas body.
  
  class Canvas3DBodyC
    : public WidgetBodyC 
  {
  public:
    Canvas3DBodyC(int x,int y,int *nglattrlist = 0);
    //: Create a 3D canvas
    
    virtual bool Create();
    //: Create the widget.
    
    bool BeginGL();
    //: Call before using any GL commands.
    // Should only be called by GUI thread.
    
    bool EndGL();
    //: Call aftern finished with GL
    // Should only be called by GUI thread.
    
    bool Put(const DObject3DC &r);
    //: Put render instructon into pipe.
    
    bool SwapBuffers();
    //: swap buffers.
    
    void SetTextureMode(bool& bTexture) {m_bTexture = bTexture;}
    //: Enable or disable texturing
    
    void SetLightingMode(bool& bLighting); 
    //: Enable or disable lighting
    
    void SetRenderMode(Canvas3DRenderMode eRenderMode) {m_eRenderMode = eRenderMode;}
    //: Set rendering mode
    
    bool GetTextureMode(void) {return m_bTexture;}
    //: Is texturing enabled?
    
    bool GetLightingMode(void) {return m_bLighting;}
    //: Is lighting enabled?
    
    Canvas3DRenderMode GetRenderMode(void) {return m_eRenderMode;}
    //: Get rendering mode
    
  protected:
    bool ProcessReq(DObject3DC &obj);
    //: Process OpenGL requests.
    
    bool InitGL();
    //: Initalise GL info
    // Returns false if GL is not available.
    
    bool DoLighting() {
      if (m_bLighting) glEnable(GL_LIGHTING);
      else glDisable(GL_LIGHTING);
      return true;
    }
    
    int *glattrlist;
    //: Attribute list. 
    // see GUI/3D/gdkgl.h for a list of attributes.
    // the attribute list should be terminated with
    // GDK_GL_NONE.  
    
    int sx,sy; // Size of view port.
    friend class Canvas3DC;
    
    Canvas3DRenderMode m_eRenderMode;
    //: Rendering mode

    bool m_bTexture;
    //: Texture mode
    // true = use texture when rendering.
    bool m_bLighting;
    //: Lighting mode
    // true = Use lighting when rendering.
    
  private:
    Canvas3DBodyC(const Canvas3DBodyC &);
    //: Don't do this.
    
  };
  
  //! userlevel=Normal
  //: 3D Canvas Widget.
  
  class Canvas3DC
    : public WidgetC 
  {
  public:
    Canvas3DC()
      {}
    //: Default constructor.
    // Creates an invalid handle.

    Canvas3DC(int x,int y,int *nglattrlist = 0)
      : WidgetC(*new Canvas3DBodyC(x,y,nglattrlist))
      {}
    //: Constructor.
    // see GUI/3D/gdkgl.h for a list of attributes for nglattrlist,
    // the attribute list should be terminated with
    // GDK_GL_NONE.
    
    Canvas3DC(Canvas3DBodyC &bod)
      : WidgetC(bod)
      {}
    //: Body constructor
    
  protected:
    Canvas3DBodyC &Body() 
      { return static_cast<Canvas3DBodyC &>(WidgetC::Body()); }
    
    const Canvas3DBodyC &Body() const
      { return static_cast<const Canvas3DBodyC &>(WidgetC::Body()); }
    
    bool ProcessReq(DObject3DC &obj)
      { return Body().ProcessReq(obj); }
    //: Process OpenGL requests.
    
    bool DoLighting()
      { return Body().DoLighting(); }
    //: Enable or disable lighting
    
  public:
    
    bool GUISwapBuffers() 
      { return Body().SwapBuffers(); }
    //: swap buffers.
    // NB. Only call from the GUI thread.
    
    bool Put(const DObject3DC &r)
      { return Body().Put(r); }
    //: Put render object on canvas.
    
    void SwapBuffers()
      { Body().Put(DSwapBuff3DC()); }
    //: Swap display buffers.
    // Thread safe.
    
    void ViewPoint(RealT fov = 90,
		   Point3dC nEye = Point3dC(0,0,5),
		   Point3dC nCentre  = Point3dC(0,0,0), 
		   Vector3dC nUp = Vector3dC(0,1,0))
      { Put(DViewPoint3DC(fov,nEye,nCentre,nUp)); }
    //: Set the view point.
    // Thread safe.
    
    void Light(const RealRGBValueC &colour,const Point3dC &position,int nn = 0)
      { Put(DLight3DC(colour,position,nn)); }
    //: Setup a light nn.
    // Thread safe
    
    void Transform(RealT nAngle,const Vector3dC &nAxis)
      { Put(DTransform3DC(nAngle,nAxis)); }
    //: Rotation Constructor.
    
    void Transform(RealT nAngle,const Vector3dC &nAxis,const Vector3dC &nTrans)
      { Put(DTransform3DC(nAngle,nAxis,nTrans)); }
    //: Rotation/Translation Constructor.
    
    void Transform(RealT nAngle,const Vector3dC &nAxis,const Vector3dC &nTrans,const DObject3DC &obj)
      { Put(DTransform3DC(nAngle,nAxis,nTrans,obj)); }
    //: Rotation/Translation Constructor.
  
    void Transform(const Vector3dC &nTrans)
      { Put(DTransform3DC(nTrans)); }
    //: Translation Constructor.
    
    void Transform(RealT nAngle,const Vector3dC &nAxis,const DObject3DC &obj)
      { Put(DTransform3DC(nAngle,nAxis,obj)); }
    //: Constructor.
    
    void Render(bool (*nfunc)())
      { Put(DOpenGLC(CallFunc0C<bool>(nfunc))); }
    //: Call OpenGL rendering function.
    
    template<class DataT>
    void Render(bool (*nfunc)(DataT &dat),const DataT &dat)
      { Put(DOpenGLC(CallFunc1C<DataT>(nfunc,dat))); }
    //: Call OpenGL rendering function.
    
    template<class Data1T,class Data2T>
    void Render(bool (*nfunc)(Data1T &dat1,Data2T &dat2),const Data1T &dat1,const Data2T &dat2)
      { Put(DOpenGLC(CallFunc2C<Data1T,Data2T>(nfunc,dat1,dat2))); }
    //: Call OpenGL rendering function.
    
    template<class ObjT>
    void Render(const ObjT &nobj,bool (ObjT::*nfunc)())
      { Put(DOpenGLC(CallMethod0C<ObjT>(nobj,nfunc))); }
    //: Call OpenGL rendering function.
    
    template<class ObjT,class DataT>
    void Render(const ObjT &nobj,bool (ObjT::*nfunc)(DataT &),const DataT &dat)
      { Put(DOpenGLC(CallMethod1C<ObjT,DataT>(nobj,nfunc,dat))); }
    //: Call OpenGL rendering function.
    
    template<class ObjT,class Data1T,class Data2T>
    void Render(const ObjT &nobj,bool (ObjT::*nfunc)(Data1T &,Data2T &),const Data1T &dat1,const Data2T &dat2)
      { Put(DOpenGLC(CallMethod2C<ObjT,Data1T,Data2T>(nobj,nfunc,dat1,dat2))); }
    //: Call OpenGL rendering function.
    
    template<class ObjT>
    void RenderRef(ObjT &nobj,bool (ObjT::*nfunc)())
      { Put(DOpenGLC(CallMethodRef0C<ObjT>(nobj,nfunc))); }
    //: Call OpenGL rendering function.
    // Use only a refrence to 'nobj', not a copy.
    // NB. This means the refrence counter will NOT be incremented.
    
    template<class ObjT,class DataT>
    void RenderRef(ObjT &nobj,bool (ObjT::*nfunc)(DataT &),const DataT &dat)
      { Put(DOpenGLC(CallMethodRef1C<ObjT,DataT>(nobj,nfunc,dat))); }
    //: Call OpenGL rendering function.
    // Use only a refrence to 'nobj', not a copy.
    // NB. This means the refrence counter will NOT be incremented.
    
    template<class ObjT,class Data1T,class Data2T>
    void RenderRef(ObjT &nobj,bool (ObjT::*nfunc)(Data1T &,Data2T &),const Data1T &dat1,const Data2T &dat2)
      { Put(DOpenGLC(CallMethodRef2C<ObjT,Data1T,Data2T>(nobj,nfunc,dat1,dat2))); }
    //: Call OpenGL rendering function.
    // Use only a refrence to 'nobj', not a copy.
    // NB. This means the refrence counter will NOT be incremented.
    
    void SetTextureMode(bool& bTexture) {Body().SetTextureMode(bTexture);}
    //: Enable or disable texturing
    
    void SetLightingMode(bool& bLighting) {Body().SetLightingMode(bLighting);}
    //: Enable or disable lighting
    
    void SetRenderMode(Canvas3DRenderMode eRenderMode) {Body().SetRenderMode(eRenderMode);}
    //: Set rendering mode
    
    bool GetTextureMode(void) {return Body().GetTextureMode();}
    //: Is texturing enabled?
    
    bool GetLightingMode(void) {return Body().GetLightingMode();}
    //: Is lighting enabled?
    
    Canvas3DRenderMode GetRenderMode(void) {return Body().GetRenderMode();}
    //: Get rendering mode
    
    friend class Canvas3DBodyC;
  };
  
}

#endif
