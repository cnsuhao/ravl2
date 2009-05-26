// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! file="Ravl/Applications/VisualDataFlow/FactorySet.cc"

#include "Ravl/DF/FactorySet.hh"
#include "Ravl/Text/ConfigFile.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/DF/DFStreamOp.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/DP/TypeConverter.hh"
#include "Ravl/TypeName.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlDFN {
  
  ////////////////////////////////////////////////////////////////////////////////////
  
  static TypeNameC type1(typeid(DFObjectC),"DFObjectC");  
  static TypeNameC type2(typeid(DFStreamOpC),"DFStreamOpC");  
  static TypeNameC type3(typeid(DPStreamOpC),"DPStreamOpC");
  
  // Setup a convertsion from a DPStreamOpC to DFObjectC.
  
  static DFObjectC DPStreamOp2DFObject(const DPStreamOpC &streamOp) {
    return DFStreamOpC(streamOp.OpName(),streamOp);
  }
  
  DP_REGISTER_CONVERSION_NAMED(DPStreamOp2DFObject,1,"DFObjectC RavlDFN::Convert(const DPStreamOpC &)");
  
  
  /////////////////////////////////////////////////////////////////////////////////////
  
  static DFObjectC Converter2DFObject(DPConverterBaseC &conv) {
    DPIPortBaseC ip;
    DPIPortBaseC iport = conv.CreateIStream(ip);
    return DFStreamOpC(StringC("Converter"),DPStreamOpC(iport));
  }
  
  /////////////////////////////////////////////////////////////////////////////////////
  
  //: Load from a file.
  
  FactorySetBodyC::FactorySetBodyC(const StringC &fn) {
    LoadDefault();
    Load(fn);
  }
  
  //: Load default converters.
  
  bool FactorySetBodyC::LoadDefault() {
    ONDEBUG(cerr << "FactorySetBodyC::LoadDefault(), Called. \n");
    TypeConverterC typeConv = SystemTypeConverter();
    PixmapC pm((char **) xpmData_OpenFile);
    for(GraphEdgeIterC<StringC,DPConverterBaseC> it(typeConv.Graph());it;it++) {
      StringC nname = StringC(TypeName(it.Data().ArgType(0))) + " => " + StringC(TypeName(it.Data().Output()));
      //ONDEBUG(cerr <<"FactorySetBodyC::LoadDefault(), Got converter. " << nname << "\n");
      FactoryC nfac(nname,pm,Trigger(&Converter2DFObject,it.Data()));
      StringC sec("converter.");
      nfac.Section(sec + nname);
      if(!Register(nfac))
	cerr << "Failed to register new factory. '" << nname << "'\n";
    }
    return true;
  }

  
  //: Load a factory descriptor file.
  
  bool FactorySetBodyC::Load(const StringC &afn) {
    FilenameC fn(afn);
    if(!fn.Exists())
      return false;
    ConfigFileC config(fn);
    DListC<StringC> sections = config.ListSections();
    for(DLIterC<StringC> it(sections);it;it++) {
      ConfigFileC cfac = config.Section(*it);
      if(!cfac.IsValid())
	continue;
      FactoryC nfac(cfac);
      if(!Register(nfac))
	cerr << "Failed to register new factory. '" << *it << "'\n";
    }
    return false;
  }

  //: Create an object of type 'tag'
  // If the tag is not found an invalid handle is returned.
  
  DFObjectC FactorySetBodyC::Create(const StringC &tag) {
    FactoryC fac;
    if(!LookupFactory(tag,fac))
      return DFObjectC(); // Unknown tag.
    return fac.Create();
  }

  //: Create a list of factories.
  
  DListC<FactoryC> FactorySetBodyC::List() const {
    DListC<FactoryC> ret;
    for(HashIterC<StringC,FactoryC> it(tag2factory);it;it++)
      ret.InsLast(it.Data());
    return ret;
  }
  
}
