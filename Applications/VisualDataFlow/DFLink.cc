// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! file="Ravl/Applications/VisualDataFlow/DFLink.cc"

#include "Ravl/DF/DFLink.hh"
#include "Ravl/DF/DFPort.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlDFN {

  //: Create link.
  
  DFLinkBodyC::DFLinkBodyC(const DFObjectC &nsrc,
			   const DFObjectC &ndst)
    : src(nsrc),
      dst(ndst),
      connected(false)
  { Connect(); }
  
  //: Destructor.
  
  DFLinkBodyC::~DFLinkBodyC() {
    if(connected)
      Disconnect();
  }
  
  //: Read from istream.
  
  DFLinkBodyC::DFLinkBodyC(XMLIStreamC &strm,DFSystemC &context) 
    : DFObjectBodyC(strm,context)
  {
    strm >> XMLAttribute("connected",connected);
  }
  
  //: Save ostream.
  
  bool DFLinkBodyC::Save(XMLOStreamC &strm,bool inCharge) const {
    if(inCharge)
      strm << XMLStartTag("DFLink");
    strm << XMLAttribute("connected",connected);
    if(!DFObjectBodyC::Save(strm,false))
      return false;
    if(inCharge)
      strm << XMLEndTag;
    return true;
  }
  
  //: Render object to view.
  
  bool DFLinkBodyC::Render(GUIViewBodyC &view,const Index2dC &at) {
    //cerr << "DFLinkBodyC::Render() Can't render link directly. ";
    return true;
  }
  
  //: Connect link.
  
  bool DFLinkBodyC::Connect() {
    ONDEBUG(cerr << "DFLinkBodyC::Connect(), Called. \n");
    DFPortC sp(src);
    DFPortC dp(dst);
    if(sp.IsValid() && dp.IsValid())
      connected = sp.Connect(dp);
    ONDEBUG(cerr << "DFLinkBodyC::Connect(), Connect=" << connected << ". \n");
    return connected;
  }
  
  //: Disconnect link.
  
  bool DFLinkBodyC::Disconnect() {
    ONDEBUG(cerr << "DFLinkBodyC::Disconnect() \n");
    if(!connected)
      return false;
    DFPortC sp(src);
    DFPortC dp(dst);
    RavlAssert(sp.IsValid() && dp.IsValid());
    sp.Disconnect(dp);
    return true;
  }

}
