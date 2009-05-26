// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/aamViewShapeModel.hh"
//! docentry="Ravl.API.Images.AAM"
//! userlevel="Normal"
//! author="Jean-Yves Guillemaut"

#include "Ravl/Image/AAMShapeModel.hh"
#include "Ravl/Image/AAMScaleRotationShapeModel.hh"
#include "Ravl/Image/AAMAppearanceModel.hh"
#include "Ravl/IO.hh"
#include "Ravl/Option.hh"
#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Canvas.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/Slider.hh"
#include "Ravl/GUI/SpinButton.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/Math.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/WarpThinPlateSpline.hh"
#include "Ravl/EntryPnt.hh"


using namespace RavlN;
using namespace RavlGUIN;
using namespace RavlImageN;

CanvasC canvas;
SliderC slider;

AAMShapeModelC sm; // Shape model.
AAMAppearanceModelC am; // appearance model.

VectorC params(3);
VectorC variance(3);
VectorC fixedMeans(3);
IntT currentParam = 0;
//IntT counter = 0;

RealT scale = 1;

void RenderModel() {
  bool x = false;
  canvas.GUIAutoRefresh(x);

  if(sm.IsValid()) {
    SArray1dC<Point2dC> points = sm.Synthesize(params);
    Index2dC off(2,2);
    IntT col = 0;
    canvas.GUIClear();
    for(SArray1dIterC<Point2dC> it(points);it;it++) {
      Index2dC mid(*it);
      Index2dC tr(mid - off);
      Index2dC bl(mid + off);

      IntT tr1 = tr[1].V(); IntT tr0 = tr[0].V();
      IntT bl1 = bl[1].V(); IntT bl0 = bl[0].V();
      canvas.GUIDrawLine(tr1, tr0, bl1, bl0, col);
      canvas.GUIDrawLine(tr1, tr0, bl1, bl0, col);
      canvas.GUIDrawLine(tr1, bl0, bl1, tr0, col);
      canvas.GUIDrawLine(bl1, tr0, tr1, bl0, col);
    }
  }
  if(am.IsValid()) {
    //cerr << "Synthesising appearance. ";
    AAMAppearanceC appear = am.Synthesize(params,scale);
    //cerr << "Image =  " << appear.Image().Frame() << "\n";
    Index2dC off(0,0);
    //cout << currentParam << endl;
    //Save ("/vol/vssp/vampiredb/people/mohammad/appmodel//all/xm_turntable/xm_turntable_noglasses/tmp/app_"+StringC(counter)+".pgm", appear.Image());
    //counter++;
    canvas.GUIDrawImage(appear.Image(),off);
  }

  canvas.GUIRefresh();
}

bool ChangeParameter(RealT &parm) {
  currentParam = Round(parm);
  if((UIntT) currentParam >= params.Size())
    return true;
  if(currentParam < (IntT) fixedMeans.Size()) {
    slider.UpdateValue(((params[currentParam] - fixedMeans[currentParam]) * 20) / Sqrt(variance[currentParam]));
  } else {
    slider.UpdateValue((params[currentParam] * 20) / Sqrt(variance[currentParam]));
  }
  return true;
}

bool ChangeValue(RealT &parm) {
  if((UIntT) currentParam >= params.Size())
    return true;
  RealT value;
  if(currentParam >= (IntT) fixedMeans.Size()) {
    value = (parm / 20) * Sqrt(variance[currentParam]);
  } else {
    value = fixedMeans[currentParam] + (parm / 20) * Sqrt(variance[currentParam]);
  }
  //cerr << "Setting " << currentParam << " to " << value << "\n";
  params[currentParam] = value;
  RenderModel();
  return true;
}

//: Visualise shape or appearance model.
//  This programs allows to visualise interactively the effects of varying the parameters 
// controling the main modes of variation of the shape or appearance model. For more information type "aamViewShapeModel -help".
int viewShapeModel(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  bool appear = opt.Boolean("a",false,"Load appearance? true=yes. Load only shape if set to false.");
  StringC fileName = opt.String("f",appear ? "am.abs" : "sm.abs","Input model.");
  IntT varRange = opt.Int("vr",40,"Range to put on the slider. ");
  scale = opt.Real("sc",1,"Scale image. ");
  opt.Check();

  if(appear) {
    if(!Load(fileName,am)) {
      cerr << "Failed to load file " << fileName << "\n";
      return 1;
    }
  } else {
    if(!Load(fileName,sm)) {
      cerr << "Failed to load file " << fileName << "\n";
      return 1;
    }
    // out << sm << "\n";
  }
  if(sm.IsValid()) {
    params = VectorC(sm.Dimensions());
    params.Fill(0);
    for(UIntT i = 0;i < sm.FixedMean().Size();i++)
      params[i] = sm.FixedMean()[i];
    variance = sm.EigenValues();
    fixedMeans = sm.FixedMean();
    cerr << "Means=" << fixedMeans << "\n";
  }
  if(am.IsValid()) {
    params = VectorC(am.Dimensions());
    params.Fill(0);
    for(UIntT i = 0;i < am.FixedMean().Size();i++)
      params[i] = am.FixedMean()[i];
    variance = am.EigenValues();
    fixedMeans = am.FixedMean();
  }
  cout << "Dimentions in model=" << params.Size() << "\n";

  WindowC win(100,100,"Shape Model Viewer");
  canvas = CanvasC(600,600);
  canvas.AutoRefresh(false);
  SpinButtonC spinButton(0,1,0.0,0.0,params.Size()-1,1.0);

  slider = SliderC(false,0,(RealT) -varRange,(RealT) varRange,0.1);
  Connect(spinButton.SigChanged(),ChangeParameter);
  Connect(slider.SigChanged(),ChangeValue);
  win.Add(VBox(canvas + HBox(spinButton + slider)));

  win.Show();
  RenderModel();
  Manager.Execute();

  Manager.Wait();

  return 0;
}


RAVL_ENTRY_POINT(viewShapeModel);
