// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImageProc
//! file="ActiveAppearanceModels/AAMActiveAppearanceModelsIO.cc"

#include "Ravl/BinStream.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/AAMActiveAppearanceModel.hh"
#include "Ravl/Image/AAMAffineShapeModel.hh"
#include "Ravl/Image/AAMScaleRotationShapeModel.hh"

namespace RavlImageN {

  void ActiveAppearanceModelsIO() 
  {}
  
  static TypeNameC t1(typeid(AAMAppearanceC),"RavlImageN::AAMAppearanceC");
  static TypeNameC t2(typeid(AAMAppearanceModelC),"RavlImageN::AAMAppearanceModelC");
  static TypeNameC t3(typeid(AAMShapeModelC),"RavlImageN::AAMShapeModelC");
  static TypeNameC t4(typeid(AAMActiveAppearanceModelC),"RavlImageN::AAMActiveAppearanceModelC"); 
  static TypeNameC t5(typeid(AAMAffineShapeModelC),"RavlImageN::AAMAffineShapeModelC");
  static TypeNameC t6(typeid(AAMScaleRotationShapeModelC),"RavlImageN::AAMScaleRotationShapeModelC");
  
  FileFormatStreamC <AAMActiveAppearanceModelC> FileFormatStream_ActiveAppearanceModel;
  FileFormatBinStreamC <AAMActiveAppearanceModelC> FileFormatBinStream_ActiveAppearanceModel;  
  
  FileFormatStreamC <AAMShapeModelC> FileFormatStream_ShapeModel;
  FileFormatBinStreamC <AAMShapeModelC> FileFormatBinStream_ShapeModel;  
  
  FileFormatStreamC <AAMAffineShapeModelC> FileFormatStream_AffineShapeModel;
  FileFormatBinStreamC <AAMAffineShapeModelC> FileFormatBinStream_AffineShapeModel;  
  
  FileFormatStreamC <AAMScaleRotationShapeModelC> FileFormatStream_ScaleRotationShapeModel;
  FileFormatBinStreamC <AAMScaleRotationShapeModelC> FileFormatBinStream_ScaleRotationShapeModel;  
  
  FileFormatStreamC <AAMAppearanceModelC> FileFormatStream_AppearanceModel;
  FileFormatBinStreamC <AAMAppearanceModelC> FileFormatBinStream_AppearanceModel;  

  FileFormatStreamC <AAMAppearanceC> FileFormatStream_Appearance;
  FileFormatBinStreamC <AAMAppearanceC> FileFormatBinStream_Appearance;  
  
  AAMShapeModelC AffineShapeModel2ShapeModel(const AAMAffineShapeModelC &anasm) 
  { return anasm; }
  
  AAMShapeModelC ScaleRotationShapeModel2ShapeModel(const AAMScaleRotationShapeModelC &anasm) 
  { return anasm; }
  
  DP_REGISTER_CONVERSION_NAMED(AffineShapeModel2ShapeModel,1,"AAMShapeModelC RavlImageN::AffineShapeModel2ShapeModel(const AAMAffineShapeModelC &)");
  
  DP_REGISTER_CONVERSION_NAMED(ScaleRotationShapeModel2ShapeModel,1,"AAMShapeModelC RavlImageN::ScaleRotationShapeModel2ShapeModel(const AAMAffineShapeModelC &)");
}
