// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! file="Ravl/Applications/VisualDataFlow/DFData.cc"

#include "Ravl/DF/DFData.hh"
#include "Ravl/DF/GUIView.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlDFN {
  
  DFDataBodyC::DFDataBodyC(const StringC &nname,const RCWrapAbstractC &ndata)
    : DFObjectBodyC(nname),
      data(ndata)
  {}
  
  //: Render object to view.
  
  bool DFDataBodyC::Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode) {
    //ONDEBUG(cerr << "DFDataBodyC::Render(), Called. At=" << at << " \n");
    
    Index2dC size = view.TextSize(view.DrawFont(),name) + Index2dC(5,0);
    GdkGC *fggc = view.DrawModeFG(mode);
    IndexRange2dC rect(at,at + size + Index2dC(5,10));
    view.DrawRectangle(view.DrawModeBG(mode),rect,true);
    view.DrawRectangle(fggc,rect,false);
    view.DrawText(fggc,view.DrawFont(),at + Index2dC(5,size[1] + 5),name);
    PackingSize(size);
    RenderSize(size);
    return true;
  }
  
  //: Load from stream.
  
  DFDataBodyC::DFDataBodyC(istream &strm)
    : DFObjectBodyC(strm)
  {}
  
  //: Load from binary stream.
  
  DFDataBodyC::DFDataBodyC(BinIStreamC &strm)
    : DFObjectBodyC(strm)
  {}
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DFDataBodyC::Save (ostream &out) const {
    if(!DFObjectBodyC::Save(out))
      return false;
    
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DFDataBodyC::Save (BinOStreamC &out) const {
    if(!DFObjectBodyC::Save(out))
      return false;
    return true;
  }
  
}
