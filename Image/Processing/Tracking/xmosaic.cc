
#include "Ravl/EntryPnt.hh"
#include "Ravl/Option.hh"
#include "Ravl/GUI/Canvas.hh"
#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Button.hh"
#include "Ravl/Image/MosaicBuilder.hh"

using namespace RavlGUIN;


int xmosaic(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  StringC ifn = opt.String("f","@V4L:/dev/video0","Input image sequence.");
  opt.Check();
  
  // Open an input stream.
  DPIPortC<ImageC<ByteRGBValueC> > inp;
  if(!OpenISequence(inp,ifn)) {
    cerr << "Failed to open input '" << ifn << "'\n";
    return 1;
  }
  
  MosaicBuilderC mbuilder;
  
  CanvasC canvas(400,400);
  
  WindowC win(1,1,"XMosaic");
  
  win.Add(VBox(canvas,Button("Go")));
  
  return 0;
}

RAVL_ENTRY_POINT(xmosaic);
