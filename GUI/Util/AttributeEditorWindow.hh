// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_ATTRIBUTEEDITORWINDOW_HEADER
#define RAVLGUI_ATTRIBUTEEDITORWINDOW_HEADER 1
//! rcsid="$Id$"
//! lib=RavlGUIUtil
//! file="Ravl/GUI/Util/AttributeEditorWindow.hh"
//! example=exAttributeEditor.cc
//! author="Charles Galambos"
//! docentry="Ravl.GUI.Util"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/AttributeEditor.hh"

namespace RavlGUIN {

  //! userlevel=Develop
  //: Window for editing attribute.
  
  class AttributeEditorWindowBodyC
    : public WindowBodyC
  {
  public:
    AttributeEditorWindowBodyC(const StringC &name,const AttributeCtrlC &ctrl);
    //: Constructor.
    
    
  protected:
    AttributeEditorC editor;
  };

  //! userlevel=Normal
  //: Window for editing attribute.
  
  class AttributeEditorWindowC
    : public WindowC
  {
  public:
    AttributeEditorWindowC(const StringC &name,const AttributeCtrlC &ctrl)
      : WindowC(*new AttributeEditorWindowBodyC(name,ctrl))
    {}
  };
}


#endif
