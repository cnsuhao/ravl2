// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd. 
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlLibGlade

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Button.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/Menu.hh"
#include "Ravl/GUI/GladeWidget.hh"
#include "Ravl/Threads/Signal.hh"

using namespace RavlGUIN;

//#===--- Custom widget class

class CustomWidgetBodyC :
  public GladeWidgetBodyC
{
public:
  CustomWidgetBodyC(const GladeXMLC &gladeXml) :
    GladeWidgetBodyC(gladeXml, "vbox1", true),
    m_signal(true)    
  {}
  //: Constructor.
  
  virtual bool Create()
  {
    AddObject("button1", ButtonR("custom", *this, &CustomWidgetBodyC::OnClicked));
    return GladeWidgetBodyC::Create();
  }
  //: Create the widget.
  
  virtual bool Create(GtkWidget *widget)
  {
    AddObject("button1", ButtonR("custom", *this, &CustomWidgetBodyC::OnClicked));
    return GladeWidgetBodyC::Create(widget);
  }
  //: Create with a widget supplied from elsewhere.
  
  bool OnClicked()
  {
    m_signal();
    return true;
  }
  
  Signal0C &SigClicked()
  { return m_signal; }
  
protected:
  Signal0C m_signal;
};

class CustomWidgetC :
  public GladeWidgetC
{
public:
  CustomWidgetC()
  {}
  //: Default constructor.
  // Creates an invalid handle.

  CustomWidgetC(const GladeXMLC &gladeXml) :
    GladeWidgetC(*new CustomWidgetBodyC(gladeXml))
  {}
  //: Constructor.
  
  Signal0C &SigClicked()
  { return Body().SigClicked(); }
  
protected:    
  CustomWidgetC(CustomWidgetBodyC &body) :
    GladeWidgetC(body)
  {}
  //: Body constructor.
  
  CustomWidgetBodyC &Body()
  { return static_cast<CustomWidgetBodyC &>(WidgetC::Body()); }
  //: Access body.
  
  const CustomWidgetBodyC &Body() const
  { return static_cast<const CustomWidgetBodyC &>(WidgetC::Body()); }
  //: Access body.
};
  
//#===--- Application callbacks

bool OnPress1() {
  cerr << "Pressed 1. \n";
  return true;
}

bool OnPressC1() {
  cerr << "Pressed custom1. \n";
  return true;
}

bool OnPressC2() {
  cerr << "Pressed custom2. \n";
  return true;
}

bool OnQuit() 
{
  Manager.Quit(); // Initate shutdown.
  return true;
}

//#===--- Main application

int main(int nargs,char **argv) {
  Manager.Init(nargs,argv);
  
  cerr << "Create widgets." << endl;

  // Create the main window
  GladeXMLC glade("exlibgladecustommain.glade");
  GladeWidgetC mainWindow(glade, "window1");
  Connect(mainWindow.Signal("delete_event"), &OnQuit);

  // Create the custom widgets
  GladeXMLC gladeCustom("exlibgladecustomwidget.glade");
  CustomWidgetC custom1(gladeCustom);
  CustomWidgetC custom2(gladeCustom);
  Connect(custom1.SigClicked(), &OnPressC1);
  Connect(custom2.SigClicked(), &OnPressC2);
  
  // Add the widgets
  mainWindow.AddObject("button1",Button("Test",&OnPress1));
  mainWindow.AddObject("quit1",MenuItem("Quit",&OnQuit));
  mainWindow.AddObject("custom1",custom1);
  mainWindow.AddObject("custom2",custom2);
  
  cerr << "Show widgets. \n";
  
  mainWindow.Show();
  
  cerr << "Start GUI. \n";
  
  Manager.Start();

  cerr << "Done. \n";
  
  return 0;
}
