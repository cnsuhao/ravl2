// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI3D
//! file="Ravl/GUI/3D/DObject3D.cc"

#include "Ravl/GUI/DObject3D.hh"
#include "Ravl/DLIter.hh"

namespace RavlGUIN {

  //: Destructor.
  // Make sure display list is free'd
  
  DObject3DBodyC::~DObject3DBodyC() {
    // Well we should.............
  }
  
  //: Render object.
  
  bool DObject3DBodyC::Render(Canvas3DC &c3d) {
    RavlAssert(0); // Abstract method.
    return true;
  }
  
  //: Render, checking for display lists.

  bool DObject3DBodyC::RenderDL(Canvas3DC &c3d) {
    bool ret = true;
    //cerr << "Calling Genlist. " << id << "\n";
    if(id >= 0) {
      //cerr << "Calling Genlist. " << id << "\n";
      glCallList(id);
    } else {
      if(id == -2) { // Generate display list.
	id = glGenLists(1);
	//cerr << "New Genlist. " << id << "\n";
	glNewList(id,GL_COMPILE);
	Render(c3d);
	glEndList();
	glCallList(id);
      } else  // Don't use a display list...
	ret = Render(c3d);
    }
    return ret;
  }
  
  //////////////////////////////////////////////////
  
  ostream &operator<<(ostream &strm,const DObject3DC &) {
    RavlAssert(0);
    return strm;
  }
  
  istream &operator>>(istream &strm,DObject3DC &) {
    RavlAssert(0);
    return strm;
  }
  
  /// DObjectSet3DBodyC ///////////////////////////////////////////////
  
  //: Default constructor.
  
  DObjectSet3DBodyC::DObjectSet3DBodyC()
    : done(false),
      gotCenter(false),
      center(0,0,0),
      gotExtent(false),
      extent(1)
  {}
  
  //: Render object.
  
  bool DObjectSet3DBodyC::Render(Canvas3DC &c3d) {
    for(DLIterC<DObject3DC> it(parts);it.IsElm();it.Next())
      it.Data().Render(c3d);
    gotExtent = false;
    gotCenter = false;
    return true;
  }
  
  //: Get center of object.
  // defaults to 0,0,0
  
  Vector3dC DObjectSet3DBodyC::Center() { 
    Vector3dC cent(0,0,0);
    if (parts.Size() == 0) return cent;
    RealT count = 0;
    for(DLIterC<DObject3DC> it(parts);it.IsElm();it.Next()) {
      cent += it.Data().Center();
      count++;
    }
    center = cent / count;
    gotCenter = true;
    return center; 
  }
  
  //: Get extent of object.
  // defaults to 1

  RealT DObjectSet3DBodyC::Extent() { 
    if (parts.Size() == 0) return 1;
    Vector3dC at = Center();
    RealT maxDist = 0;
    for(DLIterC<DObject3DC> it(parts);it.IsElm();it.Next()) {
      RealT dist = at.EuclidDistance(it.Data().Center()) + it.Data().Extent();
      if(dist > maxDist)
	maxDist = dist;
    }
    extent = maxDist;
    gotExtent = true;
    return extent; 
  }
  
  ostream &operator<<(ostream &strm,const DObjectSet3DC &) {
    RavlAssert(0);
    return strm;
  }
  
  istream &operator>>(istream &strm,DObjectSet3DC &) {
    RavlAssert(0);
    return strm;
  }
  
  //// DOpenGLBodyC ////////////////////////////////////////////////////////
  
  //: Render object.
  
  bool DOpenGLBodyC::Render(Canvas3DC &c3d) {
    if(sigEvent.IsValid())
      sigEvent.Invoke();
    return true;
  }

  ostream &operator<<(ostream &strm,const DOpenGLC &) {
    RavlAssert(0);
    return strm;
  }
  
  istream &operator>>(istream &strm,DOpenGLC &) {
    RavlAssert(0);
    return strm;
  }
}

