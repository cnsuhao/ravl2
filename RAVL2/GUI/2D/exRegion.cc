///////////////////////////////////////////
//! rcsid="$Id: exRegion.cc 152 2001-05-29 09:59:23Z craftit $"

#include "amma/GUI/Window.hh"
#include "amma/GUI/CanvasF.hh"
#include "amma/GUI/Manager.hh"
#include "amma/GUI/LBox.hh"
#include "amma/GUI/RenderTools.hh"
#include "amma/DP/FileFormatIO.hh"
#include "amma/Option.hh"
#include "amma/EntryPnt.hh"
#include "amma/Filename.hh"
#include "amma/RGBImage.hh"

#define GTKDEBUG 0

#if GTKDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

#define USEMT 0

void canvas_event(GUICanvasC &cv,const GUIMouseEventC &me,int &)
{
  if(me.IsPressed(0)) {
    cv.Put(GUIRenderPointC(me.X(),me.Y(),1));
    
  }
  //cerr << "X:" << me.X() << " y:" << me.Y() << "\n";
}

int exRegion(int nargs,char *args[]) 
{
  GUIManager.Init(nargs,args); // Initalise GUI manager, let it read args.
  
  // Do normal option processing ....
  
  OptionC option(nargs,args,TRUE);
  FilenameC infile = option.String("","","Name of input image file. ");
  StringC ifmt = option.String("if","","Input format. ");
  FilenameC outfile = option.String("","","Name of output image file. ");
  StringC ofmt = option.String("of","","Output format. ");
  BooleanT verbose = option.Boolean("v",false,"Verbose mode. ");
  option.Check();
  
  ImageC<ByteRGBValueC> image;
  
  if(!StdIO::Load(infile,image,ifmt,verbose)) {
    cerr << "Failed to load image "<< infile <<". \n";
    return 1;
  }
  
  // Setup GUI...
  
  using namespace StdGUI;
  
  GUICanvasC draw;
  draw = Canvas(200,200,canvas_event,1); // Make a canvas to draw into.  
  draw.SetMouseEventMask(TRUE,TRUE,TRUE);
  
  GUIWindowC win(300,300,infile); // Make a new window called hello.
  win.Add(GUILBoxC(draw,FALSE));   // Put draw area inside a window.
  win.Show();                    // Display this lot on the screen.
  
#if USEMT  
  GUIManager.Execute();            // Start X thread.
#endif
  
  // Do some work with the gui...
  
  ONDEBUG(cerr << "Drawing stuff... \n");
  
  draw.RGB().Put(image);
  
  ONDEBUG(cerr << "Executing manager... \n");
  
#if USEMT  
  GUIManager.Wait();              // Wait for GUI to finish.
#else
  GUIManager.Start();              // Wait for GUI to finish.
#endif
  //cerr << "Terminating.!\n";
  exit(0);
  
  return 0;
}


AMMA_ENTRY_POINT(exRegion);
