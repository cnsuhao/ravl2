//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/ProgressBar.hh"
#include "Ravl/GUI/Manager.hh"

#include <gtk/gtkprogressbar.h>

namespace RavlGUIN {

  //: Create the widget.
  
  bool ProgressBarBodyC::Create() {
    if(widget != 0)
      return true;
    widget = gtk_progress_bar_new();
    
    switch(type) 
      {
      case GUIPROGBAR_CONTINUOUS_WITH_TEXT:
	gtk_progress_set_show_text (GTK_PROGRESS(widget),true);
      case GUIPROGBAR_CONTINUOUS:
	gtk_progress_bar_set_bar_style (GTK_PROGRESS_BAR(widget),GTK_PROGRESS_CONTINUOUS);
	break;
      case GUIPROGBAR_DISCRETE:
	gtk_progress_bar_set_bar_style (GTK_PROGRESS_BAR(widget),GTK_PROGRESS_DISCRETE);
	gtk_progress_bar_set_discrete_blocks(GTK_PROGRESS_BAR(widget),blocks);
	break;
      case GUIPROGBAR_ACTIVITY:
	gtk_progress_set_activity_mode (GTK_PROGRESS(widget),true);
	gtk_progress_bar_set_activity_blocks(GTK_PROGRESS_BAR(widget),blocks);
	break;
      default:
	cerr << "ProgressBarBodyC::Create(), WARNING: Unknow style : " << ((int) type) << "\n";
      }
    
    GtkProgressBarOrientation orientmap[] = {
      GTK_PROGRESS_LEFT_TO_RIGHT,
      GTK_PROGRESS_RIGHT_TO_LEFT,
      GTK_PROGRESS_BOTTOM_TO_TOP,
      GTK_PROGRESS_TOP_TO_BOTTOM
    };
    if(((int) orient) < 0 && ((int) orient) > 3)
      cerr << "ProgressBarBodyC::Create(), WARNING: Unknow orientation : " << ((int) orient) << "\n";
    else
      gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(widget),orientmap[(int) orient]);
    ConnectSignals();
    return true;
  }
  
  //: Update percentage done on bar.
  
  void ProgressBarBodyC::Update(float percentage) {
    Manager.Queue(Trigger(ProgressBarC(*this),&ProgressBarC::GUIUpdate,percentage));
  }
  
  
  //: Update percentage done on bar.
  
  bool ProgressBarBodyC::GUIUpdate(float &percentage) {
    if(widget == 0)
      return true;
    gtk_progress_bar_update(GTK_PROGRESS_BAR(widget),percentage);
    return true;
  }

}
