// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlLibGlade
//! file="Ravl/GUI/LibGlade/GladeWidget.cc"

#include "Ravl/GUI/GladeWidget.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/OS/SysLog.hh"
#include "Ravl/XMLFactoryRegister.hh"
#include <gtk/gtk.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  using RavlN::SmartPtrC;
  
  //: Constructor
  
  GladeWidgetBodyC::GladeWidgetBodyC(const GladeXMLC &gladeXml,
                                     const StringC &widgetName,
                                     bool aCustomWidget,
                                     const StringC prefix) 
    : xml(gladeXml),
      name(widgetName),
      customWidget(aCustomWidget),
      m_widgetPrefix(prefix)
  {
    ONDEBUG(cerr << "GladeWidgetBodyC::GladeWidgetBodyC(name=" << widgetName << ", customWidget=" << aCustomWidget << ", prefix = " << prefix << ")" << endl);
    if(!m_widgetPrefix.IsEmpty() && m_widgetPrefix.lastchar() != '.')
      m_widgetPrefix += ".";
    
    if(customWidget)
      xml = GladeXMLC(gladeXml.Filename(),name,gladeXml.ModuleName());
  }
  
  //: Constructor
  
  GladeWidgetBodyC::GladeWidgetBodyC(const StringC &widgetName,bool aCustomWidget) 
    : name(widgetName),
      customWidget(aCustomWidget)
  {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "GladeWidgetBodyC::GladeWidgetBodyC(name=" << widgetName << ", customWidget=" << aCustomWidget << ")" << endl);
  }
  
  GladeWidgetBodyC::GladeWidgetBodyC(const XMLFactoryContextC &factory)
   : WidgetBodyC(factory),
     name(factory.AttributeString("widgetName",factory.Name())),
     customWidget(factory.AttributeBool("customWidget",false)),
     m_widgetPrefix(factory.AttributeString("widgetPrefix",""))
  {
    if(!factory.UseComponent("GladeXML",xml,false,typeid(GladeXMLC))) {
      SysLog(SYSLOG_ERR) << "Failed to find glade xml file. \n";
    }
    if(!m_widgetPrefix.IsEmpty() && m_widgetPrefix.lastchar() != '.')
      m_widgetPrefix += ".";
    if(customWidget) {
      xml = GladeXMLC(xml.Filename(),name,xml.ModuleName());
    }
    ONDEBUG(cerr << "GladeWidgetBodyC::GladeWidgetBodyC(name=" << name << ", customWidget=" << customWidget << ", prefix = " << m_widgetPrefix << ")" << endl);
    for(RavlN::DLIterC<RavlN::XMLTreeC> it(factory.Children());it;it++) {
      if(it->Name() == "GladeXML" || it->AttributeString("typename","").IsEmpty())
        continue;
      WidgetC widget;
      if(!factory.UseComponent(it->Name(),widget)) {
        SysLog(SYSLOG_ERR) << "Failed to load component " << it->Name() << "\n";
        continue;
      }
      StringC widgetName = it->AttributeString("widgetName",it->Name());
      AddObject(widgetName,widget,it->AttributeBool("optional",false));
    }
  }
  
  bool GladeWidgetBodyC::SetXML(const GladeXMLC &gladeXml)
  {
    if (xml.IsValid())
    {
      ONDEBUG(cerr << "GladeWidgetBodyC::SetXML already set" << endl;)
      return true;
    }
    
    if(customWidget)
      xml = GladeXMLC(gladeXml.Filename(),name,gladeXml.ModuleName());
    else
      xml = gladeXml;
    
    return xml.IsValid();
  }


  
  bool GladeWidgetBodyC::CommonCreate(GtkWidget *newWidget) {
    ONDEBUG(cerr << "GladeWidgetBodyC::CommonCreate(GtkWidget *), Called. Name=" << name << " \n");

    if (!xml.IsValid())
    {
      cerr << "GladeWidgetBodyC::CommonCreate called with no XML set" << endl;
      return false;
    }

    if(widget != NULL)
      return true;
    
    if (newWidget == NULL)
      widget = xml.Widget(name);
    else
    {
      widget = newWidget;

      if (customWidget)
      {
        if (!GTK_IS_CONTAINER(widget))
        {
          cerr << "ERROR: Custom widget for " << name << " isn't a container. (Try putting an event box here.) \n";
          RavlAssert(0);
          return false;
        }
        
        ONDEBUG(cerr << "Adding custom child widget '" << name << "' into parent. \n");  
        GtkWidget *childWidget = xml.Widget(name);
        if (childWidget == 0)
        {
          cerr << "ERROR: No child widget found for '" << name << "' \n";
          return false;
        }
        
        gtk_widget_show(childWidget);
        gtk_container_add(GTK_CONTAINER(widget), childWidget);
      }
    }
    
    if (widget == NULL)
    {
      cerr << "ERROR: Failed to find widget '" << name << "' in '" << xml.Filename() << "'\n";
      RavlAssertMsg(false,"Failed to find widget.");
      return false;
    }
    
    for (HashIterC<StringC, Tuple2C<SmartPtrC<WidgetBodyC>, bool> > it(children); it; it++)
    {
      GtkWidget *childWidget = xml.Widget(it.Key());
      if (childWidget == NULL)
      {
        if (!it.Data().Data2())
          cerr << "WARNING: Can't find widget for '" << it.Key() << "'\n";
        continue;
      }
      if (it->Data1().IsValid())
        it->Data1()->Create(childWidget);
      else
        cerr << "WARNING: Invalid handle for widget '" << it.Key() << "' \n";
    }
    
    ConnectSignals();    
    
    ONDEBUG(cerr << "GladeWidgetBodyC::CommonCreate(GtkWidget *), Done. Name=" << name << "\n");
    return true;
  }

  //: Add named widget.
  
  bool GladeWidgetBodyC::AddObject(const StringC &name,const WidgetC &newWidget, bool optional) {
    StringC useName = name;
    if(!m_widgetPrefix.IsEmpty())
      useName = m_widgetPrefix + name;
    children[useName] = Tuple2C<SmartPtrC<WidgetBodyC>, bool>(newWidget, optional);
    return true;
  }


  
  bool GladeWidgetBodyC::AddObject(const StringC &name, const SmartPtrC<WidgetBodyC> &newWidget, bool optional)
  {
    StringC useName = name;
    if(!m_widgetPrefix.IsEmpty())
      useName = m_widgetPrefix + name;
    children[name] = Tuple2C<SmartPtrC<WidgetBodyC>, bool>(newWidget, optional);
    return true;
  }


  
  extern "C" {
    static int StopDeleteEvent(GtkWidget *widget,GdkEvent *event,GladeWidgetBodyC *bod) {
      bod->GUIHide(); // Hide the window.
      return 1; // Return true so window isn't really destroyed
    }
  }
  
  //: Intercept the "delete-event", and just hide the widget.
  // Useful on windows where you just want to make them dissapear.
  
  bool GladeWidgetBodyC::InterceptDeleteEvent() {
    RavlAssert(widget != 0);
    gtk_signal_connect (GTK_OBJECT (widget),
                        "delete_event",         
                        GTK_SIGNAL_FUNC (StopDeleteEvent),
                        this);
    return true;
  }
  
  //: Called when gtk widget is destroyed.
  
  void GladeWidgetBodyC::WidgetDestroy() {
    // Just call back to parent.
    WidgetBodyC::WidgetDestroy();
  }

  static XMLFactoryRegisterHandleConvertC<GladeWidgetC,WidgetC> g_registerXMLFactoryGladeWidget("RavlGUIN::GladeWidgetC");

  void LinkGladeWidget()
  {}

}
