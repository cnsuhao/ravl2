// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Applications/VPlay/VPlay.cc"
//! docentry="Ravl.Applications.VPlay"
//! author="Charles Galambos"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteYUVValue.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Tuple2.hh"

#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Image/DeinterlaceStream.hh"

#include "Ravl/DP/Compose.hh"
#include "Ravl/DP/MTIOConnect.hh"
#include "Ravl/DP/Governor.hh"
#include "Ravl/DP/EventSet.hh"

#include "Ravl/EntryPnt.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/Option.hh"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Canvas.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/Menu.hh"
#include "Ravl/GUI/PackInfo.hh"
#include "Ravl/GUI/FileSelector.hh"

#include "Ravl/VPlay/PlayControl.hh"

#include "Ravl/Image/ImgIOCif.hh"

#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/DP/MethodIO.hh"

#include <stdlib.h>

#define DODEBUG 1

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

using namespace RavlN;
using namespace RavlGUIN;
using namespace RavlImageN;

static bool gui_quit(DPIPlayControlC<ImageC<ByteRGBValueC> > &pc) 
{
  pc.Continue();
  Manager.Quit(); // Initate shutdown.
  return true;
}

static bool file_selector(StringC &filename,FileSelectorC &fs,Tuple2C<DPIPlayControlC<ImageC<ByteRGBValueC> > ,CanvasC>  &pc) 
{
  if(filename == "") {
    fs.Hide();
    return true;
  }
  DPISPortC<ImageC<ByteRGBValueC> > vidIn;
  if(!OpenISequence(vidIn,filename)) {
    cerr << "ERROR: Failed to open '" << filename << "'\n";
    return true;
  }
  ImageC<ByteRGBValueC> tmp;
  if(!vidIn.Get(tmp)) {
    cerr << "ERROR: Failed to find image size '" << filename << "'\n";
    return true;
  }
  vidIn.DSeek(-1); // Back up.
  ImageRectangleC rect = tmp.Rectangle();
  pc.Data2().Resize(rect.Cols(),rect.Rows());
  pc.Data1().Open(vidIn);
  return true;
}


int doVPlay(int nargs,char *args[]) 
{
  bool noDisplay = false;
  // Make sure you can list options even when you don't have a display.
  if(getenv("DISPLAY") != 0) { 
    Manager.Init(nargs,args);
  } else {
    noDisplay = true;
  }
    
  OptionC option(nargs,args,true);
  IntT N(option.Int("nf",-1, "Max no. of frames read"));
  IntT start(option.Int("sf", -1, " Start at nth frame"));
  //IntT digits = option.Int("d",3,"Digits in filename. ");
  //IntT scale = option.Int("s",1,"Scale image. ");
  RealT delay = option.Real("t",0.04,"Delay between frames. ");
  bool directDraw = option.Boolean("dd",false,"Direct draw. (For realtime playback of large images) ");
  bool deinterlace = option.Boolean("di",false,"Deinterlace incoming images. ");
  bool verb = option.Boolean("v",false,"Verbose mode. ");
  //bool deInterlace = option.Boolean("di",false,"De-interlace. (Subsample by 2) ");
  DListC<StringC> attribs = option.List("a","List of attributes to set. ");
  StringC formatIn = option.String("if","","Input format. ");
  StringC infile = option.String("","","Input filename");  
  if(infile.IsEmpty())
    infile = option.String("","in.pgm","Input filename");
  
  option.Check();

  if(noDisplay) {
    cerr << "ERROR: No DISPLAY enviroment set. \n";
    return 1;
  }
  
  ONDEBUG(cerr << "VPlay: Setting up input stream ... \n");
  // Setup video source.
  // Put in vpCtrl early, else we may not get a seekable port.
  
  DPISPortC<ImageC<ByteRGBValueC> > vidIn;
  
  if(!OpenISequence(vidIn,infile,formatIn,verb)) {
    cerr << "VPlay: Failed to open '" << infile << "'\n";
    exit(1);
  }
  for(DLIterC<StringC> it(attribs);it;it++) {
    StringC attrName = it->before('=').TopAndTail();
    StringC attrValue = it->after('=').TopAndTail();
    if(!vidIn.SetAttr(attrName,attrValue))
      cerr << "WARNING: Failed to set attribute '" << attrName << "' to '" << attrValue <<  "'\n";
  }
  
  ONDEBUG(cerr << "VPlay: Sequence opened.\n");
  if(start < 0) {
    start = vidIn.Tell();
    if(start < 0)
      start = 0;
  }
  UIntT endFrame = N;
  if(N != -1)
    endFrame += start;

  if(deinterlace) 
    vidIn = DeinterlaceStreamC<ByteRGBValueC>(vidIn);
  
  DPIPlayControlC<ImageC<ByteRGBValueC> > vpCtrl(vidIn,false,start,endFrame);  
  
  ONDEBUG(cerr << "VPlay: Play control built.\n");
  
  DPIPortC<ImageC<ByteRGBValueC> > src =  vpCtrl;// >> YUVImageCT2RGBImageCT;
  
  ONDEBUG(cerr << "VPlay: Conversion stream built.\n");
  // Try and establish size of images.
  
  int sx = 300,sy = 300;
  
  ImageRectangleC rect;
  {
    ImageC<ByteRGBValueC> tmp(vidIn.Get());
    ONDEBUG(cerr << "VPlay: Got inital frame. \n");
    vidIn.DSeek(-1);
    rect = tmp.Rectangle();
  }
  
  ONDEBUG(cerr << "VPlay: Image size found..\n");
  sy = rect.Rows();
  sx = rect.Cols();
  if(sx < 1 || sy < 1) {
    cerr << "ERROR: Image size too small opening : '" << infile << "'.\n";
    sy = 100;
    sx = 100;
  }

  vidIn.Invalidate(); // Finished with vidIn handle.
  
  // Setup GUI stuff.
  
  ONDEBUG(cerr << "Setting up GUI ... \n");
  
  WindowC win(sx,sy,infile);
  CanvasC vidout(sx,sy,directDraw);  
  
  StringC strinfile(infile);
  Tuple2C<DPIPlayControlC<ImageC<ByteRGBValueC> > ,CanvasC> guiData(vpCtrl,vidout);

  //void file_selector(StringC &filename,FileSelectorC &fs,Tuple2C<DPIPlayControlC<ImageC<ByteRGBValueC> > ,CanvasC>  &pc)   
  // Setup file selector.
  FileSelectorC inFileSelect = RavlGUIN::FileSelector(StringC("Open Video File"),
						      strinfile,
						      &file_selector,
						      guiData
						      );
  
  // Setup menu.
  MenuBarC menuBar(MenuC("File",
			 MenuItemShow("Open",inFileSelect) +
			 MenuItem("Quit",gui_quit,vpCtrl) 
			 )
		   );
  
  win.Add(VBox(PackInfoC(menuBar,false,true) + 
	       PackInfoC(Box(vidout,5,true),false,false) + 
	       PackInfoC(PlayControlC(vpCtrl),false,true)
	       )
	  );
  win.Show();
  
  // Get GUI going ...
  
  ONDEBUG(cerr << "Executing manager... \n");
  Manager.Execute();
  Sleep(0.1); // Give it a chance to setup the display before starting the video.
  
  ONDEBUG(cerr << "Starting video... \n");
  DPEventSetC es;  
  
  // Setup play stream.
  
  es += src >> DPGovernorC<ImageC<ByteRGBValueC> >(delay) >>= OMethod(vidout,&CanvasC::DrawRGBImage);
  
  es.Wait();
  Manager.Shutdown();
  
  ONDEBUG(cerr << "Terminating... \n");
  exit(0);
  return 0;
}


RAVL_ENTRY_POINT(doVPlay);
