// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! file="Ravl/Applications/VisualDataFlow/DFProcess.cc"

#include "Ravl/DF/DFProcess.hh"
#include "Ravl/DF/GUIView.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlDFN {
  
  DFProcessBodyC::DFProcessBodyC(const StringC &nname)
    : DFObjectBodyC(nname)
  {}
  
  //: Render object to view.
  
  bool DFProcessBodyC::Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode) {
    ONDEBUG(cerr << "DFProcessBodyC::Render(), Called. At=" << at << " Mode=" << (int)mode << "\n");
    
    Index2dC size = view.TextSize(view.DrawFont(),name) + Index2dC(5,0);
    GdkGC *fggc = view.DrawModeFG(mode);
    IndexRange2dC rect(at,at + size);
    view.DrawRectangle(view.DrawModeBG(mode),rect,true);
    view.DrawRectangle(fggc,rect,false);
    view.DrawText(fggc,view.DrawFont(),at + Index2dC(5,15),name);
    RenderSize(rect.Size());

    return true;
  }
  
  //: Get list of attachment points.
  
  DListC<DFAttachC> DFProcessBodyC::Parts() const {
    return parts;
  }

}
