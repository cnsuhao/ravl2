// This file is part of CxxDoc, The RAVL C++ Documentation tool 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
// defchk.cc
// $Id$
//! rcsid="$Id$"
//! lib=RavlSourceTools
//! file="Ravl/SourceTools/CodeManager/amma2ravl.cc"

#include "Ravl/Option.hh"
#include "Ravl/SourceTools/DefsFile.hh"
#include "Ravl/SourceTools/SourceCodeManager.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/SourceTools/SourceFile.hh"

using namespace RavlN;

bool verb = false;
bool dryRun = false;
bool guiUpdates = false;
bool guiSrc = false;

static bool CheckDirectory(StringC &dir,DefsMkFileC &defs) {
  if(verb)
    cerr << "Checking '" << dir << "' \n";
  StringListC source = defs.AllSources();
  for(DLIterC<StringC> it(source);it;it++) {
    FilenameC fn(dir + filenameSeperator + *it);
    if(!fn.Exists()) {
      cerr << "ERROR: Source file '" << fn << "' does not exist. \n";
      return false;
    }
    if(!fn.IsReadable()) {
      cerr << "ERROR: Source file '" << fn << "' is not readable \n";
      return false;
    }
    SourceFileC theFile;
    if(!theFile.Load(fn)) {
      cerr << "Failed to load file '" << fn << "'\n";
      continue;
    }
    theFile.GlobalSubst("\"amma/PThread/","\"Ravl/Threads/");
    theFile.GlobalSubst("\"amma/DeadLine.hh\"","\"Ravl/OS/DeadLineTimer.hh\"");
    theFile.GlobalSubst("\"amma/RCHandle.hh\"","\"Ravl/RefCounter.hh\"");
    theFile.GlobalSubst("\"amma/Filename.hh\"","\"Ravl/OS/Filename.hh\"");
    theFile.GlobalSubst("\"amma/HashAR.hh\"","\"Ravl/Hash.hh\"");
    theFile.GlobalSubst("<assert.h>","\"Ravl/Assert.hh\"");
    theFile.GlobalSubst("\"amma/DP/Signal.hh\"","\"Ravl/Threads/Signal.hh\"");
    theFile.GlobalSubst("\"amma/DP/Signal1.hh\"","\"Ravl/Threads/Signal1.hh\"");
    theFile.GlobalSubst("\"amma/DP/Signal2.hh\"","\"Ravl/Threads/Signal2.hh\"");
    theFile.GlobalSubst("\"amma/DP/Signal3.hh\"","\"Ravl/Threads/Signal3.hh\"");
    theFile.GlobalSubst("\"amma/StrList.hh\"","\"Ravl/StringList.hh\"");
    theFile.GlobalSubst("\"amma/Date.hh\"","\"Ravl/OS/Date.hh\"");
    theFile.GlobalSubst("\"amma/StdTypes.hh\"","\"Ravl/Types.hh\"");
    theFile.GlobalSubst("\"amma/PThread/MsgPipe.hh\"","\"Ravl/Threads/MessageQueue.hh\"");
    theFile.GlobalSubst("\"amma/PThread/MsgPipe.hh\"","\"Ravl/Threads/MessageQueue.hh\"");
    theFile.GlobalSubst("\"amma/Date.hh\"","\"Ravl/OS/Date.hh\"");
    theFile.GlobalSubst("\"amma/ImageIter.hh\"","\"Ravl/Array2dIter.hh\"");
    theFile.GlobalSubst("\"amma/Image2Iter.hh\"","\"Ravl/Array2dIter2.hh\"");
    theFile.GlobalSubst("\"amma/Image3Iter.hh\"","\"Ravl/Array2dIter3.hh\"");
    
    
    if(guiUpdates) {
      theFile.GlobalSubst("GUIDEBUG","DODEBUG");
      
      theFile.GlobalSubst("PixelC","Index2dC");
      theFile.GlobalSubst("GUIManager","Manager");
      theFile.GlobalSubst("GUIWidget","Widget");
      theFile.GlobalSubst("GUIMouseEvent","MouseEvent");
      theFile.GlobalSubst("GUICListEvent","CListEvent");
      theFile.GlobalSubst("GUICursor","Cursor");
      theFile.GlobalSubst("GUIWindow","Window");
      theFile.GlobalSubst("GUIToolTips","ToolTips");
      theFile.GlobalSubst("GUIContainerWidget","ContainerWidget");
      theFile.GlobalSubst("GUIButton","Button");
      theFile.GlobalSubst("GUIToggleButton","ToggleButton");
      theFile.GlobalSubst("GUICheckButton","CheckButton");
      theFile.GlobalSubst("GUICanvas","Canvas");
      theFile.GlobalSubst("GUIMenu","Menu");
      theFile.GlobalSubst("GUILabel","Label");
      theFile.GlobalSubst("GUIPixmap","Pixmap");
      theFile.GlobalSubst("GUIFileSelector","FileSelector");
      theFile.GlobalSubst("GUITextEntry","TextEntry");
      theFile.GlobalSubst("GUISlider","Slider");
      theFile.GlobalSubst("GUIOneChild","OneChild");
      theFile.GlobalSubst("GUIScrolledArea","ScrolledArea");
      theFile.GlobalSubst("GUIFixed","Fixed");
      theFile.GlobalSubst("GUIStatusBar","StatusBar");
      theFile.GlobalSubst("GUICombo","Combo");
      theFile.GlobalSubst("GUIList","List");
      theFile.GlobalSubst("GUIRawCanvas","RawCanvas");
      theFile.GlobalSubst("GUITable","Table");
      theFile.GlobalSubst("GUIRuler","Ruler");
      theFile.GlobalSubst("GUISpinButton","SpinButton");
      theFile.GlobalSubst("GUITree","Tree");
      theFile.GlobalSubst("GUIPackInfo","PackInfo");
      theFile.GlobalSubst("GUISeparator","Separator");
      theFile.GlobalSubst("GUIBitmap","Bitmap");
      theFile.GlobalSubst("GUINotebook","Notebook");
      theFile.GlobalSubst("GUICList","CList");
      theFile.GlobalSubst("GUIVLabel","VLabel");
      theFile.GlobalSubst("GUIGraph1d","Graph1d");
      theFile.GlobalSubst("GUIRadioButton","RadioButton");
      theFile.GlobalSubst("GUILBox","LBox");
      theFile.GlobalSubst("GUIEventBox","EventBox");
      theFile.GlobalSubst("GUIFrame","Frame");
      theFile.GlobalSubst("GUIProgressBar","ProgressBar");

      // Other stuff.
      theFile.GlobalSubst("StdGUI","RavlGUIN");
      theFile.GlobalSubst("#define GUI","#define RAVLGUI");
      theFile.GlobalSubst("#ifndef GUI","#ifndef RAVLGUI");

      // Helper functions.
      theFile.GlobalSubst("MenuCheckItemRef(","MenuCheckItemR(");
      
    }
    if(guiSrc) {
      theFile.GlobalSubst("DPEntityC::Body()","WidgetC::Body()");
      theFile.GlobalSubst("return dynamic_cast<","return static_cast<");
    }
    theFile.GlobalSubst("BodyRefCounterC","RCBodyC");
    theFile.GlobalSubst("BodyRefCounterVC","RCBodyVC");
    theFile.GlobalSubst("ImageIterC","Array2dIterC");
    theFile.GlobalSubst("Image2IterC","Array2dIter2C");
    theFile.GlobalSubst("Image3IterC","Array2dIter3C");
    theFile.GlobalSubst("Launch(","ThreadLaunch(");
    theFile.GlobalSubst("MsgPipeC<","MessageQueueC<");
    theFile.GlobalSubst("SignalEvent(","Trigger(");
    theFile.GlobalSubst("PThread::","");
    theFile.GlobalSubst("StdDP::","");
    theFile.GlobalSubst("StdIO::","");
    theFile.GlobalSubst("BooleanT","bool");
    theFile.GlobalSubst("assert(","RavlAssert(");
    theFile.GlobalSubst("IndexT","IndexC");
    theFile.GlobalSubst("aTRUE","true");
    theFile.GlobalSubst("aFALSE","false");
    theFile.GlobalSubst("TRUE","true");
    theFile.GlobalSubst("FALSE","false");
    theFile.GlobalSubst("amma","Ravl");
    theFile.GlobalSubst("AMMA","RAVL");
    theFile.GlobalSubst("HashARC<","HashC<");
    theFile.GlobalSubst("AMMA_CHECK","QMAKE_CHECK");
    
    if(theFile.IsModified()) {
      cerr << "Updated file :" << fn << "\n";
      if(!dryRun)
	theFile.Save();
    }
  }
  return true;
}

int main(int nargs,char **argv) {
  OptionC option(nargs,argv);
  StringC fn = option.String("i",".","Input filename. ");
  bool all = option.Boolean("a",false,"Go into inactive directories as well. ");
  dryRun = option.Boolean("d",false,"Do a dry run.");
  guiSrc = option.Boolean("guis",false,"do gui renaming's");
  guiUpdates = option.Boolean("gui",guiSrc,"do gui renaming's");
  verb = option.Boolean("v",false,"Verbose mode.");
  option.Check();
  
  SourceCodeManagerC chkit(fn);
  if(verb)
    chkit.SetVerbose(true);  
  chkit.ForAllDirs(CallFunc2C<StringC,DefsMkFileC,bool>(&CheckDirectory),all);
  
  return 0;
}
