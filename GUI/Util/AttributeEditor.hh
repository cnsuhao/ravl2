// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_ATTRIBUTEEDITOR_HEADER
#define RAVLGUI_ATTRIBUTEEDITOR_HEADER 1
//! rcsid="$Id$"
//! lib=RavlGUIUtil
//! file="Ravl/GUI/Util/AttributeEditor.hh"
//! docentry="Ravl.GUI.Util"
//! author="Charles Galambos"
//! example=exAttributeEditor.cc

#include "Ravl/DP/AttributeCtrl.hh"
#include "Ravl/DP/AttributeType.hh"
#include "Ravl/GUI/Table.hh"

namespace RavlGUIN {
  
  //! userlevel=Develop
  //: Attribute editor widget.
  
  class AttributeEditorBodyC
    : public TableBodyC
  {
  public:
    AttributeEditorBodyC(const AttributeCtrlC &ctrl);
    //: Construct on attribute control
    
    void BuildWidgets();
    //: Build widgets needed for the current attribute control.
    
    bool SetAttribBool(bool &val,StringC &name);
    //: Set a bool attribute.
    
    bool SetAttribString(StringC &val,StringC &name);
    //: Set a string attribute.
    
    bool SetAttribReal(RealT &val,StringC &name);
    //: Set a string attribute.

    bool SetAttribInt(RealT &val,StringC &name);
    //: Set a string attribute.
    
  protected:
    virtual bool Create();
    //: Create widget.
    
    HashC<StringC,WidgetC> controls;
    AttributeCtrlC attribCtrl;
  };
  
  //! userlevel=Normal
  //: Attribute editor widget.
  
  class AttributeEditorC
    : public TableC
  {
  public:
    AttributeEditorC(const AttributeCtrlC &ctrl)
      : TableC(*new AttributeEditorBodyC(ctrl))
    {}
    //: Construct on attribute control    
  };
  
}

#endif
