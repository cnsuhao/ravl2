
#include "amma/GUI/Image.hh"

//: Constructor.

GUIImageBodyC::GUIImageBodyC(const ImageC<ByteRGBValueC> &nimg)
  : GUIWidgetBodyC(TRUE),
    img(nimg)
{}

//: Create the widget.

BooleanT GUIImageBodyC::Create()
{
  widget =  gtk_drawing_area_new ();  

  gtk_signal_connect (GTK_OBJECT (widget), "expose_event",
		      (GtkSignalFunc) win_expose_event,(gpointer) this);
  
  return TRUE;
}


//: Service request.
// Used to send signals from other
// threads to the program.  

BooleanT GUIImageBodyC::Service()
{
  if(widget == 0)
    return TRUE;

  return TRUE;
}
