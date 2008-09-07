// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlLibGlade
//! file="Ravl/GUI/LibGlade/GladeXML.cc"

#include "Ravl/GUI/GladeXML.hh"
#include "Ravl/TypeName.hh"

#include <gtk/gtk.h>
#include <glade/glade.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  static bool gladeInitDone = false;
  
  static void CheckGladeInit() {
    if(gladeInitDone)
      return ;
    ONDEBUG(cerr << "CheckGladeInit(), Called. \n");
    gladeInitDone = true;
    glade_init();
    ONDEBUG(cerr << "CheckGladeInit(), Done. \n");
  }
  
  //: Default constructor.
  
  GladeXMLBodyC::GladeXMLBodyC()
    : xml(0)
  {}
  
  //: Create from a file.
  
  GladeXMLBodyC::GladeXMLBodyC(const StringC &nfilename) 
    : xml(0),
      filename(nfilename)
      
  {}
  
  //: Create part of interface from a file.
  
  GladeXMLBodyC::GladeXMLBodyC(const StringC &nfilename,const StringC &nwidgetName) 
    : xml(0),
      filename(nfilename),
      rootWidgetName(nwidgetName)
  {}
  
  //: Create interface.
  
  bool GladeXMLBodyC::Create() {
    if(xml != 0) 
      return true;
    CheckGladeInit();
    if(rootWidgetName.IsEmpty())
      xml = glade_xml_new(filename.chars(), NULL,0);
    else
      xml = glade_xml_new(filename.chars(), rootWidgetName.chars(),0);
    if(xml == 0) return false;
    glade_xml_signal_autoconnect(xml);    
    return true;
  }
  
  //: Access xml info for whole interface.
  
  GladeXML *GladeXMLBodyC::XML() {
    if(xml == 0) Create();
    return xml;
  }

  //: Find named widget.
  
  GtkWidget *GladeXMLBodyC::Widget(const StringC &widgetName) {
    ONDEBUG(cerr << "GladeXMLBodyC::Widget(), Called for '" << widgetName << "' in file " << filename <<  "\n");
    if(xml == 0) Create();
    return glade_xml_get_widget(xml, widgetName.chars());
  }
  
  static TypeNameC type0(typeid(GladeXMLC),"RavlGUIN::GladeXMLC");
}
