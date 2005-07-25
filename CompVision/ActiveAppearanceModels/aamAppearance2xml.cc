// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImageProc
//! file="ActiveAppearanceModels/aamAppearance2xml.cc"

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
#include "Ravl/Image/ImagePointFeatureSet.hh"

using namespace RavlN;
using namespace RavlImageN;

namespace RavlImageN {
  
    bool GenerateTypeMap2(HashIterC<IntT, ImagePointFeatureC> fit,bool &useTypeId,HashC<IntT,IntT> &typeMap,HashC<StringC,IntT> &namedTypeMap) {
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

}

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  StringC smfile = opt.String("d","sm.abs","Shape model file");
  StringC xmlin = opt.String("e","","Example xml file");
  StringC xmlout = opt.String("o","","output xml file");
  opt.Check();

  AAMShapeModelC sm;
  if(!Load(smfile,sm)) {
    cerr << "Failed to load file " << smfile << "\n";
    return 1;
  }
  
  ImagePointFeatureSetC fs;
  if(!Load(xmlin,fs)) {
    cerr << "WARNING: Failed to load file '" << xmlin << "' \n";
    return 1;
  }

  SArray1dC<Point2dC> pnts(fs.Size());
  pnts = sm.MeanPoints();

  HashC<IntT,IntT> typeMap;
  HashC<StringC,IntT> namedTypeMap;
  bool useTypeId = false;
  GenerateTypeMap2(fs.FeatureIterator(),useTypeId,typeMap,namedTypeMap);

  for(HashIterC<IntT, ImagePointFeatureC> fit(fs.FeatureIterator());fit;fit++) {
    if(useTypeId) {
      IntT id = fit->TypeID();
      if(id < 0)
        fit->Location()=pnts[namedTypeMap[fit->Description()]]; 
      else
        fit->Location()=pnts[typeMap[id]];
    }
    else {
      // Use description, its more reliable.;
      fit->Location()=pnts[namedTypeMap[fit->Description()]]; 
    }
  }

  fs.ImageFile() = "";

  if(!Save(xmlout,fs)) {
    cerr << "WARNING: Failed to load file '" << xmlout << "' \n";
    return 1;
  }
  
  return 0;
}
