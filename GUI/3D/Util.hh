// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_DUTIL3D_HEADER
#define RAVLGUI_DUTIL3D_HEADER 1
/////////////////////////////////////////////////
//! docentry="Ravl.GUI.3D"
//! rcsid="$Id$"
//! file="Ravl/GUI/3D/Util.hh"
//! lib=RavlGUI3D
//! author="Charles Galambos"
//! date="12/04/1999"

#include "Ravl/GUI/DObject3D.hh"
#include "Ravl/Image/RealRGBValue.hh"

namespace RavlGUIN {
  using namespace RavlImageN;
  
  ///////////////////////////////////////////////////////
  //! userlevel=Develop
  //: Rotate objects
  
  class DTransform3DBodyC
    : public DObjectSet3DBodyC
  {
  public:
    DTransform3DBodyC(RealT nAngle,const Vector3dC &nAxis)
      : doRot(true),
	angle(nAngle),
	axis(nAxis),
	doTrans(false)
    {}
    //: Rotation Constructor.
    
    DTransform3DBodyC(RealT nAngle,const Vector3dC &nAxis,const Vector3dC &nTrans)
      : doRot(true),
	angle(nAngle),
	axis(nAxis),
	doTrans(true),
	trans(nTrans)
    {}
    //: Rotation/Translation Constructor.
    
    DTransform3DBodyC(const Vector3dC &nTrans)
      : doRot(false),
	doTrans(true),
	trans(nTrans)
    {}
    //: Translation Constructor.
    
    virtual bool Render(Canvas3DC &c3d);
    //: Render object.
    
  protected:
    bool doRot;
    RealT angle;
    Vector3dC axis;
    bool doTrans;
    Vector3dC trans;
  };
  
  //! userlevel=Normal
  //: Transform objects
  
  class DTransform3DC
    : public DObjectSet3DC
  {
  public:
    DTransform3DC(RealT nAngle,const Vector3dC &nAxis)
      : DObjectSet3DC(*new DTransform3DBodyC(nAngle,nAxis))
    {}
    //: Rotation Constructor.
    
    DTransform3DC(RealT nAngle,const Vector3dC &nAxis,const Vector3dC &nTrans)
      : DObjectSet3DC(*new DTransform3DBodyC(nAngle,nAxis,nTrans))
    {}
    //: Rotation/Translation Constructor.
    
    DTransform3DC(RealT nAngle,const Vector3dC &nAxis,const Vector3dC &nTrans,const DObject3DC &obj)
      : DObjectSet3DC(*new DTransform3DBodyC(nAngle,nAxis,nTrans))
    { (*this) += obj;  }
    //: Rotation/Translation Constructor.
    
    DTransform3DC(const Vector3dC &nTrans)
      : DObjectSet3DC(*new DTransform3DBodyC(nTrans))
    {}
    //: Translation Constructor.
    
    DTransform3DC(RealT nAngle,const Vector3dC &nAxis,const DObject3DC &obj)
      : DObjectSet3DC(*new DTransform3DBodyC(nAngle,nAxis))
    { (*this) += obj; }
    //: Constructor.
    
  protected:
    DTransform3DBodyC &Body() 
    { return dynamic_cast<DTransform3DBodyC &>(DObject3DC::Body()); }
    
    const DTransform3DBodyC &Body() const
    { return dynamic_cast<const DTransform3DBodyC &>(DObject3DC::Body()); }
  };

}

#endif
