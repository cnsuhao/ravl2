// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! file="Ravl/Applications/VisualDataFlow/Factory.cc"

#include "Ravl/DF/Factory.hh"
#include "Ravl/DF/DFPump.hh"
#include "Ravl/DF/DFStreamOp.hh"
#include "Ravl/IO.hh"
#include "Ravl/StringList.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/DF/DFPort.hh"
#include "Ravl/DP/MTIOConnect.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/GUI/DPDisplayObj.hh"
#include "Ravl/Image/EdgeDeriche.hh"
#include "Ravl/DP/Method2Proc.hh"
#include "Ravl/DP/ProcIStream.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlDFN {
  using namespace RavlImageN;
  using namespace RavlGUIN;
  
  static DFObjectC DFObjectFromFile(StringC &file,StringC &format) {
    DFObjectC ret;
    if(format == "meta_in") {
      DPIPortBaseC ip;
      DPSeekCtrlC sc;
      if(!OpenISequenceBase(ip,sc,file,"",typeid(void))) {
	cerr << "DFObjectFromFile(), Failed to open '" << file << "' Format=" << format << "\n";
	return ret;
      }
      if(ip.IsValid())
	ip.SetAttr("id",file);
      return DFIPortC(ip,file);
    }
    if(format == "meta_out") {
      DPOPortBaseC ip;
      DPSeekCtrlC sc;
      if(!OpenOSequenceBase(ip,sc,file,"",typeid(void))) {
	cerr << "DFObjectFromFile(), Failed to open '" << file << "' Format=" << format << "\n";
	return ret;
      }
      if(ip.IsValid())
	ip.SetAttr("id",file);
      return DFOPortC(ip,file);
    }
    if(format == "pump") {
      if(file == "ImageC<ByteRGBValueC>") {
	DPMTIOConnectC<ImageC<ByteRGBValueC> > pump(true);
	return DFPumpC("Pump",pump);
      }
      if(file == "DPDisplayObjC") {
	DPMTIOConnectC<DPDisplayObjC> pump(true);
	return DFPumpC("Pump",pump);
      }
      return DFObjectC();
    }
    if(format == "proc") {
      if(file == "EdgeDericheC") {
	EdgeDericheC edgeDet;
	DPProcIStreamC<ImageC<RealT>,ImageC<RealT> > proc(Process(edgeDet,&EdgeDericheC::EdgeMagnitude));
	return DFStreamOpC("EdgeDericheC",proc);
      }
    }
    Load(file,ret,format);
    return ret;
  }
  
  //: Constructor.
  
  FactoryBodyC::FactoryBodyC(const StringC &nName)
    : name(nName),
      icon((char **) xpmData_OpenFile)
  {}

  //: Constructor.
  
  FactoryBodyC::FactoryBodyC(const StringC &nName,const PixmapC &pm) 
    : name(nName),
      icon(pm)
  {}
  
  //: Constructor.
  
  FactoryBodyC::FactoryBodyC(const StringC &nName,const PixmapC &pm,const CallFunc0C<DFObjectC> &nfunc)
    : name(nName),
      icon(pm),
      func(nfunc)
  {}

  //: Constructor.
  
  FactoryBodyC::FactoryBodyC(ConfigFileC &cfg)
  { Load(cfg); }
  
  //: Load configuration from a file.
  
  bool FactoryBodyC::Load(ConfigFileC &cfg) {
    if(cfg.IsDefined("name"))
      name = cfg["name"];
    else 
      name = cfg.Name();
    if(cfg.IsDefined("icon")) {
      StringC iconFile = cfg["icon"];
      if(!iconFile.IsEmpty())
	icon = PixmapC(iconFile);
    }
    if(!icon.IsValid()) // Setup default icon ?
      icon = PixmapC((char **) xpmData_OpenFile);
    if(cfg.IsDefined("source")) {
      StringC loadFile = cfg["source"];
      StringC format = cfg["format"];
      func = Trigger(&DFObjectFromFile,loadFile,format);
    } else {
      cerr << "WARNING: No source for object '" << name << "'\n";
    }
    if(cfg.IsDefined("section"))
      Section(cfg["section"]);
    ONDEBUG(cerr << "FactoryBodyC::Load(), Name=" << name << " Section=" << cfg["section"] << "\n");
    return true;
  }
  
  //: Get an icon for the object.
  
  PixmapC FactoryBodyC::Icon() const {
    return icon;
  }
  
  //: Create a new object.
  
  DFObjectC FactoryBodyC::Create() {
    DFObjectC ret;
    if(!func.IsValid())
      return ret;
    ret = const_cast<CallFunc0C<DFObjectC> &>(func)();
    FactoryC me(*this);
    ret.Init(me);
    return ret;
  }

  //: Set section.
  // Expects a . seperated string.
  
  const DListC<StringC> FactoryBodyC::Section(const StringC &sectionName) {
    section = StringListC(sectionName,".");
    return section;
  }
  
}
