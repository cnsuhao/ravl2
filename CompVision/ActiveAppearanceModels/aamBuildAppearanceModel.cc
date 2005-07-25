// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/aamBuildAppearanceModel.cc"

#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/OS/Directory.hh"
#include "Ravl/IO.hh"
#include "Ravl/Option.hh"
#include "Ravl/Collection.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/SArray1dIter3.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/Random.hh"
#include "Ravl/Text/TextFile.hh"
#include "Ravl/String.hh"

#include "Ravl/Image/ImagePointFeatureSet.hh"
#include "Ravl/Image/AAMAppearance.hh"
#include "Ravl/Image/AAMAppearanceModel.hh"
#include "Ravl/Image/AAMActiveAppearanceModel.hh"
#include "Ravl/Image/AAMAppearanceUtil.hh"

using namespace RavlN;
using namespace RavlImageN;


int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  StringC dir = opt.String("d","/vol/vssp/vampire/people/jean-yves/appmodel/markup/","Directory to search for examples. ");
  StringC list = opt.String("l","/vol/vssp/vampire/people/jean-yves/appmodel/lists/all.list","file list. ");
  RealT varS = opt.Real("vs",0.98,"Preserved variation in shape. ");
  RealT varT = opt.Real("vt",0.98,"Preserved variation in texture. ");
  RealT varC = opt.Real("vc",0.98,"Preserved variation in combined model. ");
  UIntT maxS = opt.Int("maxs",25,"Maximum number of shape parameters. ");
  UIntT maxT = opt.Int("maxt",120,"Maximum number of texture parameters. ");
  UIntT maxC = opt.Int("maxc",80,"Maximum number of combined parameters. ");
  StringC ext = opt.String("e","xml","Extention to expect on markup files. ");
  bool evaluate = opt.Boolean("ev",false,"Evaluate appearance model. ");
  bool loadOld = opt.Boolean("lam",false,"Load existing appearance model. ");
  RealT sigma = opt.Real("s",2,"Warping sigma. ");
  Index2dC maskSize = opt.Index2d("ms",55,51,"Mask Size. ");
  StringC op = opt.String("o","am.abs","File to save model into. ");
  StringC mirrorFile = opt.String("m","/vol/vssp/vampire/people/jean-yves/appmodel/mirror.txt","Mirror file. ");
  bool ignoreSuspect = opt.Boolean("is",true,"Ignore suspect feature sets.");
  opt.Check();
  
  cout << "Creating list of marked-up files in '" << dir << "'\n"; 
  DListC<StringC> fileList;
  if(!list.IsEmpty())
  {
    //: load list from file
    TextFileC fl(list);
    for(UIntT i=1;i<=fl.NoLines();i++) {

      StringC fileName = fl[i].TopAndTail();
      
      // check it is a valid appearance and eliminate suspect files if required
      AAMAppearanceC appear = LoadFeatureFile(fileName,dir,ignoreSuspect,true);
      if (!appear.IsValid()) {
        continue;
      }      

      fileList.InsLast(fileName);
    }
  }
  else
  {
    DirectoryC md(dir);
    if(!md.IsValid()) {
      cerr << "Can't find directory '" << dir << "'\n";
      return 1;
    }
    DListC<StringC> fileList = md.List("",StringC(".") + ext);
  }
 
  if(!fileList.IsValid() || fileList.Size() == 0) {
    cerr << "Failed to create list of marked-up files from '" << dir << "' \n";
    return 1;
  }

  // build appearance model
  AAMAppearanceModelC am(sigma);

  if(loadOld) {
    // Load a model.
    cerr << "Loading model appearance model '" << op << "' \n";
    if(!Load(op,am)) {
      cerr << "Failed to save model to '" << op << "' \n";
      return 1;
    }
  }
  else {
    // Build from scratch
    am.Design(fileList,dir,mirrorFile,maskSize,varS,varT,varC,maxS,maxT,maxC);
    cout << "Dimensions in appearance model = " << am.Dimensions() << "\n";
    if(!Save(op,am)) {
      cerr << "Failed to save model to '" << op << "' \n";
      return 1;
    }
  }

  if(evaluate) {
    cerr << "Evaluating fit of appearance model. \n";
    IntT NoPerFile;
    AAMAppearanceMirrorC mirror;
    if (mirrorFile.IsEmpty()) {
      NoPerFile = 1;
    }
    else {
      mirror = AAMAppearanceMirrorC(mirrorFile);
      if(!mirror.IsValid()) {
        cerr << "ERROR: Failed to read mirror file. \n";
        return 1;
      }
      NoPerFile = 2;
    }
    for(DLIterC<StringC> it(fileList);it;it++) {
    for (IntT k=1;k<=NoPerFile;k++) {

      AAMAppearanceC appear = LoadFeatureFile(*it,dir);
      if (k == 2) {
        appear = mirror.Reflect(appear);      
      }
      VectorC trueVec = am.Parameters(appear);
      VectorC errVec;
      am.ErrorVector(trueVec,appear.Image(),errVec);
      RealT diff = errVec.SumOfSqr() / am.MaskArea();
      StringC fileName = appear.SourceFile();
      cerr << ":\t" << diff << endl;
    }
    }
  }
  
  return 0;
}
