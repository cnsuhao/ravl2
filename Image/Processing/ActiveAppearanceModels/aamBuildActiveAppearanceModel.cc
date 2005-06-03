// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImageProc
//! file="ActiveAppearanceModels/aamBuildActiveAppearanceModel.cc"

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
#include "Ravl/Types.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/DList.hh"
#include "Ravl/StringList.hh"

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
  StringC ext = opt.String("e","xml","Extention to expect on markup files. ");
  bool evaluate = opt.Boolean("ev",false,"Evaluate active appearance model. ");
  bool loadOld = opt.Boolean("lam",false,"Load existing active appearance model. ");
  StringC op = opt.String("o","aam.abs","File to save model into. ");
  StringC ip = opt.String("am","am.abs","File to load model from. ");
  StringC mirrorFile = opt.String("m","/vol/vssp/vampire/people/jean-yves/appmodel/mirror.txt","Mirror file. ");
  UIntT incrSize = opt.Int("i", 1, "Number of perturbation values. ");
  bool ignoreSuspect = opt.Boolean("is",true,"Ignore suspect feature sets.");
  bool precompute = opt.Boolean("pre",false,"Precompute matrix.");
  opt.Check();

  StringC outFile = StringListC(op,"/").Last();
  StringC outName = StringListC(outFile,".").First();
  UIntT noFiles = (StringListC(outName,"_").Nth(-1)).UIntValue();
  UIntT startNo = (StringListC(outName,"_").Nth(-2)).UIntValue();

  cout << "Creating list of marked-up files in '" << dir << "'\n"; 
  DListC<StringC> fileList;
  
  //: load list from file
  TextFileC fl(list);
  if (startNo<=fl.NoLines()) {
    for(UIntT i=1;i<startNo;i++) {
      StringC fileName = fl[i].TopAndTail();
    }
    for(UIntT i=startNo;i<Min(startNo+noFiles,fl.NoLines()+1);i++) {
      StringC fileName = fl[i].TopAndTail();
      // check it is a valid appearance and eliminate suspect files if required
      AAMAppearanceC appear = LoadFeatureFile(fileName,dir,ignoreSuspect,true);
      if (!appear.IsValid()) {  
        continue;
      }      
      fileList.InsLast(fileName);
    }
  }
  if(!fileList.IsValid() || fileList.Size() == 0) {
    cerr << "Failed to create list of marked-up files from '" << dir << "' \n";
    return 1;
  }

  AAMAppearanceModelC am;
  AAMActiveAppearanceModelC aam;
  
  if(loadOld) {
    if(!ip.IsEmpty()) {
      cerr << "Warning: appearance parameter specified in -am is not necessary, parameter will be ignored." << endl;
    }

    // Load a model.
    cerr << "Loading active appearance model '" << op << "' \n";
    if(!Load(op,aam)) {
      cerr << "Failed to load model to '" << op << "' \n";
      return 1;
    }
    am = aam.AppearanceModel();
  }
  else {
    // start by loading appearance model
    cerr << "Loading appearance model '" << ip << "' \n";
    if(!Load(ip,am)) {
      cerr << "Failed to load model from '" << ip << "' \n";
      return 1;
    }

    if(precompute) {
      if(!aam.PreDesign(am,fileList,dir,mirrorFile,incrSize,op)) {
        cerr << "Failed to precompute results \n";
        return 1;
      }
    } else {
      aam.Design(am,fileList,dir,mirrorFile,incrSize);
      if(!Save(op,aam)) {
        cerr << "Failed to save model to '" << op << "' \n";
        return 1;
      }
    }
  }

  if(evaluate) {
    cerr << "Evaluating fit of active appearance model. \n";
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

      VectorC trueVec = aam.AppearanceModel().Parameters(appear);
      VectorC deltaVec(trueVec.Size());
      for(SArray1dIter3C<RealT,RealT,RealT> xit(deltaVec,trueVec,am.EigenValues());xit;xit++)
	xit.Data1() = xit.Data2() + RandomGauss() * Sqrt(xit.Data3());
      VectorC vec = aam.RefinePose(appear.Image(),deltaVec);
      cerr << "Error=" << (vec - trueVec).SumOfSqr() << "\n";
    }
    }
  }
  
  return 0;
}
