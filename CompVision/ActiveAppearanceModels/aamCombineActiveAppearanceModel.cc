// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/aamCombineActiveAppearanceModel.cc"

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
  StringC ext = opt.String("e","abs","Extention to expect on markup files. ");
  StringC op = opt.String("o","aam.abs","File to save model into. ");
  StringC ip = opt.String("am","am.abs","File to load model from. ");
  opt.Check();

  
  cout << "Creating list of marked-up files in '" << dir << "'\n"; 
  DListC<StringC> fileList;
  if(!list.IsEmpty())
  {
    //: load list from file
    TextFileC fl(list);
    for(UIntT i=1;i<=fl.NoLines();i++) {
      StringC fileName = fl[i].TopAndTail();
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
    cerr << StringC(".") + ext << endl;
    fileList = md.List("",StringC(".") + ext);
    cerr << fileList << endl;
  }
  
  if(!fileList.IsValid() || fileList.Size() == 0) {
    cerr << "Failed to create list of marked-up files from '" << dir << "' \n";
    return 1;
  }

cerr << fileList << endl;

  AAMAppearanceModelC am;
  AAMActiveAppearanceModelC aam;
  
  // start by loading appearance model
  cerr << "Loading appearance model '" << ip << "' \n";
  if(!Load(ip,am)) {
    cerr << "Failed to load model from '" << ip << "' \n";
    return 1;
  }

  if(!aam.PostDesign(am,fileList,dir,op)) {
    cerr << "Failed to precompute results \n";
    return 1;
  }

  if(!Save(op,aam)) {
    cerr << "Failed to save AAM to file '" << op << "' \n";
    return 1;
  }

  
  return 0;
}
