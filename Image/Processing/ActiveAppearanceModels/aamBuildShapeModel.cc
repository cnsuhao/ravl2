// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImageProc
//! file="ActiveAppearanceModels/aamBuildShapeModel.cc"

#include "Ravl/OS/Filename.hh"
#include "Ravl/OS/Directory.hh"
#include "Ravl/IO.hh"
#include "Ravl/Option.hh"
#include "Ravl/Collection.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/Stream.hh"
#include "Ravl/DList.hh"
#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/Text/TextFile.hh"

#include "Ravl/Image/AAMShapeModel.hh"
#include "Ravl/Image/AAMScaleRotationShapeModel.hh"
#include "Ravl/Image/AAMAffineShapeModel.hh"
#include "Ravl/Image/ImagePointFeatureSet.hh"
#include "Ravl/Image/AAMAppearanceUtil.hh"

using namespace RavlN;
using namespace RavlImageN;

bool ReadSection(IStreamC &is,const char *name,Array1dC<Point2dC> &array) {
  if(!is.SkipTo(name)) {
    cerr << "Failed to find '" << name << "' \n";
    return false;
  }
  if(!is.SkipTo('('))
    return false;
  int nc;
  is >> nc;
  if(!is.SkipTo(')'))
    return false;
  array = Array1dC<Point2dC>(nc);
  for(Array1dIterC<Point2dC> it(array);it;it++) {
    is >> *it;
    //Swap((*it)[0],(*it)[1]);
  }
  return true;
}

CollectionC<Point2dC> LoadPointSet(IStreamC &is) {
  CollectionC<Point2dC> points(200);
  Array1dC<Point2dC> array;
  ReadSection(is,"Face Border",array);
  points.Insert(array);
  ReadSection(is,"Outer Lip",array);
  points.Insert(array);
  ReadSection(is,"Inner Lip",array);
  points.Insert(array);
  ReadSection(is,"Nose",array);
  points.Insert(array);
  ReadSection(is,"Left Outer Eye",array);
  points.Insert(array);
  ReadSection(is,"Left Inner Eye",array);
  points.Insert(array);
  ReadSection(is,"Right Outer Eye",array);
  points.Insert(array);
  ReadSection(is,"Right Inner Eye",array);
  points.Insert(array);
  ReadSection(is,"Left Eyebrow",array);
  points.Insert(array);
  ReadSection(is,"Right Eyebrow",array);  
  return points;
}


SampleC<AAMAppearanceC> LoadOtherSet(const StringC &dir,const StringC &ext) {
  SampleC<AAMAppearanceC> appearanceSet;
  
  for(int i = 0;;i++) {    
    StringC curFile = dir + i + ".txt";
    IStreamC is(curFile);
    if(!is)
      break;
    CollectionC<Point2dC> points = LoadPointSet(is);
    AAMAppearanceC app(points.Array());
#if 0
    // Sanity check.
    for(SArray1dIterC<Point2dC> it(points.Array());it;it++) {
      RavlAssert(Abs((*it)[0]) < 300);
      RavlAssert(Abs((*it)[1]) < 300);
    }
#endif
    appearanceSet.Append(app);
    
  }
  
  return appearanceSet;
}

void AddFeatures(IStreamC &is,const StringC &sec,int &id,ImagePointFeatureSetC &fs) {
  Array1dC<Point2dC> array;
  ReadSection(is,sec,array);
  StringC aName = sec + "-";
#if 0
  Array1dIterC<Point2dC> it(array);
  int lastId = id;
  fs.AddFeature(ImagePointFeatureC(id++,aName + StringC(it.Index().V()),(*it)[1],(*it)[0]));
  for(it++;it;it++) {
    fs.AddFeature(ImagePointFeatureC(id,aName + StringC(it.Index().V()),(*it)[1],(*it)[0]));
    fs.AddLine(lastId,id);
    lastId = id++;
  }
#else
  DListC<IntT> ints;
  for(Array1dIterC<Point2dC> it(array);it;it++) {
    fs.AddFeature(ImagePointFeatureC(id,aName + StringC(it.Index().V()),(*it)[1],(*it)[0]));
    ints.InsLast(id);
    id++;
  }
  fs.AddSubset(sec,ints);
#endif
}

int SaveModel(const StringC &pos,const StringC &sm) {
  
  IStreamC is(pos);
  ImagePointFeatureSetC fs(true);
  
  int id = 0;
  
  AddFeatures(is,"Face Border",id,fs);
  AddFeatures(is,"Outer Lip",id,fs);
  AddFeatures(is,"Inner Lip",id,fs);
  AddFeatures(is,"Nose",id,fs);
  AddFeatures(is,"Left Outer Eye",id,fs);
  AddFeatures(is,"Left Inner Eye",id,fs);
  AddFeatures(is,"Right Outer Eye",id,fs);
  AddFeatures(is,"Right Inner Eye",id,fs);
  AddFeatures(is,"Left Eyebrow",id,fs);
  AddFeatures(is,"Right Eyebrow",id,fs);
  
  Save(sm,fs);
  return 0;
}

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  StringC dir = opt.String("d","/vol/vssp/vampire/people/jean-yves/appmodel/markup/","Directory to search for examples. ");
  StringC list = opt.String("l","/vol/vssp/vampire/people/jean-yves/appmodel/lists/all.list","file list. ");
  RealT var = opt.Real("vs",0.98,"Preserved variation in appearence. ");
  UIntT maxP = opt.Int("maxs",25,"Maximum number of shape parameters ");
  StringC ext = opt.String("e","xml","Extention to expect on markup files. ");
  bool os = opt.Boolean("os",false,"Other types of sets. ");
  bool st = opt.Boolean("st",false,"Save template model. ");
  bool ignoreSuspect = opt.Boolean("is",true,"Ignore suspect markups.");
  StringC op = opt.String("o","sm.abs","File to save model into.");
  StringC mirrorFile = opt.String("m","/vol/vssp/vampire/people/jean-yves/appmodel/mirror.txt","Mirror file. ");
  StringC meanPnts = opt.String("om","","Save position of mean points to a seperate file. ");
  opt.Check();

#if 0  
  AAMShapeModelC sm(true); // Shape model.
#else
  AAMScaleRotationShapeModelC sm(true); // Shape model.
#endif
  
  SampleC<AAMAppearanceC> appearanceSet;
  
  if(st) {
    SaveModel(dir,"model.xml");
    return 0;
  }
  
  if(!os)
    if(!list.IsEmpty())
    {
      //: load list from file
      DListC<StringC> fileList;
      TextFileC fl(list);
      for(UIntT i=1;i<=fl.NoLines();i++)  fileList.InsLast(fl[i].TopAndTail());
      appearanceSet = LoadFeatureSet(fileList,dir,ignoreSuspect,false);
    }
    else
    {
      appearanceSet = LoadFeatureSet(dir,ext,ignoreSuspect,false);
    }
  else
    appearanceSet = LoadOtherSet(dir,ext);
  
  if(!mirrorFile.IsEmpty()) {
    AAMAppearanceMirrorC mirror(mirrorFile);
    if(!mirror.IsValid()) {
      cerr << "ERROR: Failed to read mirror file. \n";
      return 1;
    }
    mirror.Reflect(appearanceSet);
  }
  
  cerr << "Got " << appearanceSet.Size() << " samples. \n";
  
  sm.Design(appearanceSet,var,maxP);
  
  cerr << "Dimensions in shape model = " << sm.Dimensions() << "\n";
    
  if(!meanPnts.IsEmpty()) {
    if(!Save(meanPnts,sm.MeanPoints())) {
      cerr << "Failed to save position of mean points to '" << meanPnts << "'\n";
      return 1;
    }
  }

  cout << sm << endl;

  if(!op.IsEmpty()) {
    if(!Save(op,sm)) {
      cerr << "Failed to save model to '" << op << "'\n";
      return 1;
    }
  }
  
  return 0;
}
