#include "Ravl/GUI/DebugAssertDialog.hh"
#include "Ravl/Threads/Signal3.hh"
#include "Ravl/GUI/Label.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/ToggleButton.hh"
#include <gdk/gdktypes.h>
#include <gtk/gtk.h>


namespace RavlGUIN {
  
  //Static member declarations
  bool DebugAssertDialogC::m_sbShowDialog(true);

  //: Constructor.   
  DebugAssertDialogBodyC::DebugAssertDialogBodyC(StringC message, const char *title, const WindowC* parent)
    : WindowBodyC(200,100,title,GTK_WINDOW_DIALOG,0,false, false),
      m_strMessage(message)
  {
     m_rootWindow = const_cast<WindowC*>(parent);
  }
  
  
  bool DebugAssertDialogBodyC::Create() 
  { 
    m_continueButton = ButtonR("Continue",*this,&DebugAssertDialogBodyC::OnContinue); 
    Add(VBox(Label(m_strMessage) +
	       HBox( m_continueButton +
		    ButtonR("Core Dump",*this,&DebugAssertDialogBodyC::OnBombOut)) +
		    CheckButtonR("Do not show this dialog again this session (NOT ADVISED)",false,*this,&DebugAssertDialogBodyC::OnDisableDialog)
	       ,40,false,20));
    // Connect the window kill signal
    ConnectRef(Signal("delete_event"), *this, &DebugAssertDialogBodyC::OnQuit);
    ConnectRef(Signal("destroy"), *this, &DebugAssertDialogBodyC::OnContinue);

    // Set positioning
    GtkWindowPosition pos(GTK_WIN_POS_CENTER);
    GUISetPositioning(pos);

    // Create window
    return WindowBodyC::Create();
  }
  
  bool DebugAssertDialogBodyC::OnContinue() 
  {
    gtk_main_quit();
    return true;
  }
  
  bool DebugAssertDialogBodyC::OnBombOut()
  {
    RavlAssert(0);
    gtk_main_quit();	//Just in case it doesn't bomb out
    return true;
  }
  
  bool DebugAssertDialogBodyC::OnQuit(GdkEvent*& event, WidgetC& myWidge, bool& bRef)
  { 
    bRef = false;	//Setting this to false means that the destroy event is triggered and hence the ObDestroy function is called
    return false;
  }
  
  bool DebugAssertDialogBodyC::OnDisableDialog(bool &bStatus)
  {
    if(bStatus)
      DebugAssertDialogC::m_sbShowDialog = false;
    return true;
  }
  
  //Wrapper class
   DebugDialogWrapperC::DebugDialogWrapperC(StringC message, const char *title, const WindowC* parent)
   {
#ifdef QMAKE_PARANOID
     if(DebugAssertDialogC::m_sbShowDialog)
     {
       DebugAssertDialogC warnUserDlg(message, "Debug Warning", parent);
       warnUserDlg.GUIShow();
       gtk_main();	//Used to make the warning dialog modal. gtk_main_quit called when the warning dialog is closed so execution continues
       warnUserDlg.Destroy(); //Don't replace this with gtk_widget_destroy because it doesn't work
     }
#endif
   }
}
