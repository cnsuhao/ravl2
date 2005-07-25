// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_APPEARANCEUTIL_HEADER
#define RAVLIMAGE_APPEARANCEUTIL_HEADER 1
//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMAppearanceUtil.hh"

#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/String.hh"
#include "Ravl/DList.hh"
#include "Ravl/Image/AAMAppearanceModel.hh"

namespace RavlImageN {

  using namespace RavlN;

  SampleC<AAMAppearanceC> LoadFeatureSet(const StringC &dir,const StringC &ext,bool ignoreSuspect,bool loadImages);
  //: Load a feature set.

  SampleC<AAMAppearanceC> LoadFeatureSet(const DListC<StringC> &files,const StringC &dir,bool ignoreSuspect,bool loadImages);
  //: Load a feature set.

  AAMAppearanceC LoadFeatureFile(const StringC &file,const StringC &dir,bool ignoreSuspect = true,bool loadImages = true);
  //: Load a feature set from one file.

}


#endif
