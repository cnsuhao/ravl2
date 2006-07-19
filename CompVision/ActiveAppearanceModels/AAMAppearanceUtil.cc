// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMAppearanceUtil.cc"

#include "Ravl/DLIter.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/String.hh"
#include "Ravl/DList.hh"
#include "Ravl/OS/Directory.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/IO.hh"
#include "Ravl/Image/ImagePointFeatureSet.hh"
#include "Ravl/Image/AAMAppearance.hh"
#include "Ravl/Image/AAMAppearanceUtil.hh"
#include "Ravl/OS/Filename.hh"

namespace RavlImageN {

  bool GenerateTypeMap(HashIterC<IntT, ImagePointFeatureC> fit,bool &useTypeId,HashC<IntT,IntT> &typeMap,HashC<StringC,IntT> &namedTypeMap) {
    // Check if we have feature type id's.
    if(fit.Data().TypeID() >= 0)
      useTypeId = true;
    // Go through and setup typemap.
    IntT allocId = 0;
    for(;fit;fit++) {
      UIntT idVal;
      //if(useTypeId) idVal = fit->TypeID();
      if(useTypeId) idVal =  allocId + 1;
      else idVal = fit.Key();
      typeMap[idVal] = allocId;
      namedTypeMap[fit->Description()] = allocId;
      allocId++;
    }
    //cout << "typeMap: " << typeMap << endl << "namedTypeMap: " << namedTypeMap << endl;
    return true;
  }


  //: Convert appearance to ImagePointFeatureSetC .
  bool SaveFeatureSet(const AAMAppearanceC &appear, const ImagePointFeatureSetC &ModelFeatureSet, ImagePointFeatureSetC &featureSet, const FilenameC Name) {

    featureSet = ModelFeatureSet.Copy();

    HashC<IntT,IntT> typeMap;
    HashC<StringC,IntT> namedTypeMap;

    bool useTypeId = false;

    SArray1dC<Point2dC> pnts = appear.Points();
    if(typeMap.IsEmpty()) { // Do we need to build a type map ?
      GenerateTypeMap(ModelFeatureSet.FeatureIterator(),useTypeId,typeMap,namedTypeMap);
    }
    for(HashIterC<IntT, ImagePointFeatureC> fit(ModelFeatureSet.FeatureIterator());fit;fit++) {
      if(useTypeId) {
        IntT id = fit->TypeID();
        if(id < 0) {
          featureSet.Set(fit->Description(),pnts[namedTypeMap[fit->Description()]]);
          featureSet.Set(fit->ID(),pnts[namedTypeMap[fit->Description()]]);
        } else {
          featureSet.Set(fit->Description(),pnts[typeMap[id]]);
          featureSet.Set(fit->ID(),pnts[typeMap[id]]);
        }
      } else {
        // Use description, its more reliable.;
        featureSet.Set(fit->Description(),pnts[namedTypeMap[fit->Description()]]);
        featureSet.Set(fit->ID(),pnts[namedTypeMap[fit->Description()]]);
      }
    }
    featureSet.ImageFile() = Name;

    return true;
  }

  //: Load ImagePointFeatureSetC object from XML file and store as an appearance.
  //!param: file - names of XML file.
  //!param: dir - Name of directory containing appearance files.
  //!param: ignoreSuspect - Ignore XML files marked as "Suspect"? True = yes.
  //!param: loadImages - Load image in memory? True = yes.
  // Note that if 'loadImages' is set to false, only the shape of the model instance will be loaded.
  AAMAppearanceC LoadFeatureFile(const StringC &file,const StringC & dir,bool ignoreSuspect,bool loadImages) {
    AAMAppearanceC appear;

    HashC<IntT,IntT> typeMap;
    HashC<StringC,IntT> namedTypeMap;

    bool useTypeId = false;

    ImagePointFeatureSetC fs;
    StringC featureSetFile = dir + '/' + file;
    if(!Load(featureSetFile,fs)) {
      cerr << "WARNING: Failed to load file '" << featureSetFile << "' \n";
      return appear;
    }
    if(ignoreSuspect && fs.IsSuspect())
      return appear;
    SArray1dC<Point2dC> pnts(fs.Size());
    if(typeMap.IsEmpty()) { // Do we need to build a type map ?
      GenerateTypeMap(fs.FeatureIterator(),useTypeId,typeMap,namedTypeMap);
    }
    for(HashIterC<IntT, ImagePointFeatureC> fit(fs.FeatureIterator());fit;fit++) {
      if(useTypeId) {
        IntT id = fit->TypeID();
        if(id < 0) {
          pnts[namedTypeMap[fit->Description()]] = fit.Data(); 
        } else {
          pnts[typeMap[id]] = fit.Data();
        }
      } else {
        // Use description, its more reliable.;
        pnts[namedTypeMap[fit->Description()]] = fit.Data(); 
      }
    }
    ImageC<ByteT> img;
    if(loadImages) {
      if(!Load(fs.ImageFile(),img)) {
        cerr << "Failed to load image '" << fs.ImageFile() << "' \n";
        return appear;
      }
    }
    appear = AAMAppearanceC(pnts,img);
    appear.SourceFile() = file;
    cout  << file << " " << flush;

    return appear;
  }


  //: Load ImagePointFeatureSetC objects from a set of XML files and store as set of appearances.
  //!param: files - list of names of XML files.
  //!param: dir - Name of directory containing XML files.
  //!param: ignoreSuspect - Ignore XML files marked as "Suspect"? True = yes.
  //!param: loadImages - Load image in memory? True = yes.
  // Note that if 'loadImages' is set to false, only the shape of the model instance will be loaded.
  SampleC<AAMAppearanceC> LoadFeatureSet(const DListC<StringC> &files,const StringC & dir,bool ignoreSuspect,bool loadImages) {
    SampleC<AAMAppearanceC> appearanceSet;

    DirectoryC md(dir);
    if(!md.IsValid()) {
      cerr << "Can't find directory '" << dir << "'\n";
      return appearanceSet;
    }
    cerr << "Got " << files.Size() << " files in the list. \n";
    appearanceSet = SampleC<AAMAppearanceC>(files.Size());
    cout << "Loading " << flush;

    for(DLIterC<StringC> it(files);it;it++) {
      AAMAppearanceC appear;
      appear = LoadFeatureFile(*it,dir,ignoreSuspect,loadImages);
      if (appear.IsValid()) {
        appearanceSet.Append(appear);
      }
    }
    cout  << "\n";

    return appearanceSet;
  }


  //: Load ImagePointFeatureSetC objects from all XML files located in a directory.
  //!param: dir - Name of directory containing XML files.
  //!param: ext - Extension of XML files.
  //!param: ignoreSuspect - Ignore XML files marked as "Suspect"? True = yes.
  //!param: loadImages - Load image in memory? True = yes.
  // Note that if 'loadImages' is set to false, only the shape of the model instance will be loaded.
  SampleC<AAMAppearanceC> LoadFeatureSet(const StringC &dir,const StringC &ext,bool ignoreSuspect,bool loadImages) {
    SampleC<AAMAppearanceC> appearanceSet;
    DirectoryC md(dir);
    if(!md.IsValid()) {
      cerr << "Can't find directory '" << dir << "'\n";
      return appearanceSet;
    }

    DListC<StringC> files = md.List("",StringC(".") + ext);
    appearanceSet = LoadFeatureSet(files,dir,ignoreSuspect,loadImages);

    return appearanceSet;
  }

}

