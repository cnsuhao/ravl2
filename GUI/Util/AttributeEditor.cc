// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUIUtil
//! file="Ravl/GUI/Util/AttributeEditor.cc"


#include "Ravl/GUI/AttributeEditor.hh"
#include "Ravl/GUI/ToggleButton.hh"
#include "Ravl/GUI/Label.hh"
#include "Ravl/GUI/TextEntry.hh"
#include "Ravl/GUI/Slider.hh"
#include "Ravl/GUI/Combo.hh"
#include "Ravl/GUI/SpinButton.hh"
#include "Ravl/GUI/Table.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/DP/AttributeValueTypes.hh"
#include "Ravl/HSet.hh"

#define DODEBUG 0
#if DODEBUG 
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif


namespace RavlGUIN {
  
  //: Construct on attribute control
  
  AttributeEditorBodyC::AttributeEditorBodyC(const AttributeCtrlC &ctrl) 
    : TableBodyC(1,1,false),
      attribCtrl(ctrl)
  {}
  
  //: Create widget.
  
  bool AttributeEditorBodyC::Create() {
    BuildWidgets();
    return TableBodyC::Create();
  }
  
  //: Build widgets needed for the current attribute control.
  
  void AttributeEditorBodyC::BuildWidgets() {
    DListC<AttributeTypeC> list;
    if(!attribCtrl.IsValid())
      return ;
    attribCtrl.GetAttrTypes(list);
    
    // Count the number of attributes to display and
    // remove duplicates.
    
    HSetC<StringC> done;
    int noAttribs = 0;
    for(DLIterC<AttributeTypeC> it(list);it;it++) {
      if(done[it->Name()]) { // Ignore duplicate entries.
	it.Del();
	continue;
      }
      done += it->Name();
      noAttribs++;
    }
    
    sx = 3;
    sy = noAttribs;
    
    // Go through the list creating controls for each attribute.

    int lineNo = 0;
    for(DLIterC<AttributeTypeC> it(list);it;it++,lineNo++) {      
      WidgetC widge;
      if(it->CanWrite() || it->CanRead()) {
	switch(it->ValueType()) {
	case AVT_Bool: {
	  bool initState;
	  if(it->CanRead())
	    attribCtrl.GetAttr(it->Name(),initState);
	  else
	    initState = false;
	  if(it->CanWrite()) {
	    CheckButtonC cb = CheckButtonR(StringC(" "),(bool)initState,*this,&AttributeEditorBodyC::SetAttribBool,it->Name());
	    widge = cb;
	  } else {
	    StringC s;
	    if(initState)
	      s = "true";
	    else 
	      s = "false";
	    LabelC label(s);
	    widge = label;
	  }
	} break;
	case AVT_String:{
	  StringC initValue;
	  attribCtrl.GetAttr(it->Name(),initValue);
	  if(it->CanWrite()) {
	    TextEntryC te = TextEntryR(initValue,*this,&AttributeEditorBodyC::SetAttribString,it->Name());
	    widge = te;
	  } else {
	    LabelC label(initValue);
	    widge = label;
	  }
	} break;
	case AVT_Int: {
	  IntT val;
	  attribCtrl.GetAttr(it->Name(),val);
	  AttributeTypeNumC<IntT> attr(*it);
	  RavlAssert(attr.IsValid());
	  if(attr.CanWrite()) {
	    SliderC sl((RealT) val,(RealT) attr.Min(),(RealT) attr.Max(),(RealT) attr.Step());
	    ConnectRef(sl.SigChanged(),*this,&AttributeEditorBodyC::SetAttribInt,val,it->Name());
	    widge = sl;
	  } else {
	    StringC str(val);
	    LabelC label(str);
	    widge = label;
	  }
	} break;
	case AVT_Real: {
	  RealT val;
	  attribCtrl.GetAttr(it->Name(),val);
	  AttributeTypeNumC<RealT> attr(*it);
	  RavlAssert(attr.IsValid());
	  if(attr.CanWrite()) {
	    SpinButtonC sl(4,attr.Step(),val,attr.Min(),attr.Max(),attr.Step() * 2);
	    ConnectRef(sl.SigChanged(),*this,&AttributeEditorBodyC::SetAttribReal,val,it->Name());
	    widge = sl;
	  } else {
	    StringC str(val);
	    LabelC label(str);
	    widge = label;
	  }
	} break;
	case AVT_Enum: {
	  StringC val;
	  attribCtrl.GetAttr(it->Name(),val);
	  AttributeTypeEnumC attr(*it);
	  RavlAssert(attr.IsValid());
	  if(attr.CanWrite()) {
	    ComboC cb(attr.Values());
	    cb.SetSelection(val);	
	    ConnectRef(cb.SigSelected(),*this,&AttributeEditorBodyC::SetAttribString,val,it->Name());
	    widge = cb;
	  } else {
	    StringC str(val);
	    LabelC label(str);
	    widge = label;
	  }
	} break;
	default:
	  cerr << "WARNING: Unhandled attribute type. ";
	  break;
	}
      } else
	widge = LabelC("?"); // Can't write or read the attribute ?!?
      
      // Add widget and its label to the layout.
      if(widge.IsValid()) {
	controls[it->Name()] = widge;
	StringC name = it->Name();
	//cerr << "Name='" << name << "'\n";
	//AddObject(CheckButtonC(name,it->CanRead()),0,1,lineNo,lineNo+1);
	StringC rwtype;
	if(it->CanRead()) {
	  if(it->CanWrite())
	    rwtype="RW ";
	  else
	    rwtype="RO ";
	} else {
	  if(it->CanWrite())
	    rwtype="WO ";
	  else
	    rwtype="NA ";
	}
	AddObject(LabelC(rwtype),0,1,lineNo,lineNo+1,(GtkAttachOptions) (GTK_FILL | GTK_EXPAND),(GtkAttachOptions) (GTK_FILL | GTK_EXPAND),2,3);	  
	AddObject(LabelC(name)  ,1,2,lineNo,lineNo+1,(GtkAttachOptions) (GTK_FILL | GTK_EXPAND),(GtkAttachOptions) (GTK_FILL | GTK_EXPAND),2,5);
	AddObject(widge         ,2,3,lineNo,lineNo+1);
      }
    }
    //Add(table);
  }

  //: Set a string attribute.
  
  bool AttributeEditorBodyC::SetAttribString(StringC &val,StringC &name) {
    ONDEBUG(cerr << "AttributeEditorBodyC::SetAttribString(), Called. Name=" << name << " Value=" << val << " \n");
    attribCtrl.SetAttr(name,val);
    return true;
  }
  
  //: Set a bool attribute.
  
  bool AttributeEditorBodyC::SetAttribBool(bool &val,StringC &name) {
    ONDEBUG(cerr << "AttributeEditorBodyC::SetAttribBool(), Called. Name=" << name << " Value=" << val << " \n");
    attribCtrl.SetAttr(name,val);
    return true;
  }
  
  //: Set a string attribute.
  
  bool AttributeEditorBodyC::SetAttribReal(RealT &val,StringC &name) {
    ONDEBUG(cerr << "AttributeEditorBodyC::SetAttribReal(), Called. Name=" << name << " Value=" << val << " \n");    
    attribCtrl.SetAttr(name,val);
    return true;
  }

  //: Set a string attribute.
  
  bool AttributeEditorBodyC::SetAttribInt(RealT &val,StringC &name) {
    ONDEBUG(cerr << "AttributeEditorBodyC::SetAttribInt(), Called. Name=" << name << " Value=" << val << " \n");    
    attribCtrl.SetAttr(name,Round(val));
    return true;
  }

  
  
}
