// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImageProc
//! file="ActiveAppearanceModels/aamTestApp.cc"

#include "Ravl/Image/ImgIO.hh"
#include "Ravl/Option.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/IO.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Affine2d.hh"
#include "Ravl/OS/Directory.hh"
#include "Ravl/StringList.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/PatternRec/FuncMeanProjection.hh"
#include "Ravl/PatternRec/DistanceEuclidean.hh"
#include "Ravl/Array2dIter3.hh"
#include "Ravl/Text/TextFile.hh"
#include "Ravl/Image/DrawCross.hh"
#include "Ravl/Image/DrawCircle.hh"
#include "Ravl/Image/ImageRectangle.hh"
#include "Ravl/Image/WarpScale.hh"
#include "Ravl/Sums1d2.hh"
#include "Ravl/Vector.hh"

#include "Ravl/Image/ImagePointFeatureSet.hh"
#include "Ravl/Image/AAMAppearance.hh"
#include "Ravl/Image/AAMAppearanceUtil.hh"
#include "Ravl/Image/AAMShapeModel.hh"
#include "Ravl/Image/AAMAppearanceModel.hh"
#include "Ravl/Image/AAMActiveAppearanceModel.hh"

#define PROJECT_TEXTURE 0

using namespace RavlN;
using namespace RavlImageN;

int main (int argc, char** argv)
{
  OptionC cmd(argc,argv);
  FilenameC appDir = cmd.String("d","/vol/vssp/vampire/people/jean-yves/appmodel/markup/", "input marked-up images directory");
  FilenameC appList = cmd.String("l","/vol/vssp/vampire/people/jean-yves/appmodel/lists/frontal.list", "input marked-up images list");
  StringC ext = cmd.String("e","xml","Extention to expect on markup files. ");
  StringC aamFile1 = cmd.String("aam1","/vol/vssp/vampire/people/jean-yves/appmodel/models/aam_all_30x26m25_80_60.abs" ,"AAM file 1 (low res)");
  StringC aamFile2 = cmd.String("aam2","/vol/vssp/vampire/people/jean-yves/appmodel/models/aam_all_60x52m25_120_80.abs" ,"AAM file 2 (medium res)");
  StringC aamFile3 = cmd.String("aam3","/vol/vssp/vampire/people/jean-yves/appmodel/models/aam_all_120x104m25_140_90.abs" ,"AAM file 3 (high res)");
  FilenameC OutDir = cmd.String("out", "/vol/vssp/vampire/people/jean-yves/appmodel/test/", "Segmentation map");
  bool ignoreSuspect = cmd.Boolean("is",true,"Ignore suspect markups.");

  cmd.Check();
  
  AAMActiveAppearanceModelC aam1;
  
  if(!Load(aamFile1,aam1)) {
    cerr << "Failed to load model from '" << aamFile1 << "' \n";
    return 1;
  }
  AAMAppearanceModelC am1 = aam1.AppearanceModel();
  cerr << am1.MaskArea() << endl;
  AAMShapeModelC sm1 = am1.ShapeModel();

  AAMActiveAppearanceModelC aam2;
  if(!Load(aamFile2,aam2)) {
    cerr << "Failed to load model from '" << aamFile2 << "' \n";
    return 1;
  }
  AAMAppearanceModelC am2 = aam2.AppearanceModel();
  cerr << am2.MaskArea() << endl;
  AAMShapeModelC sm2 = am2.ShapeModel();

  AAMActiveAppearanceModelC aam3;
  if(!Load(aamFile3,aam3)) {
    cerr << "Failed to load model from '" << aamFile3 << "' \n";
    return 1;
  }
  AAMAppearanceModelC am3 = aam3.AppearanceModel();
  cerr << am3.MaskArea() << endl;
  AAMShapeModelC sm3 = am3.ShapeModel();

  SampleC<AAMAppearanceC> appearanceSet;
  if(!appList.IsEmpty())
  {
    //: load list from file
    DListC<StringC> fileList;
    TextFileC fl(appList);
    for(UIntT i=1;i<=fl.NoLines();i++)  fileList.InsLast(fl[i].TopAndTail());
    appearanceSet = LoadFeatureSet(fileList,appDir,ignoreSuspect,true);
  }
  else
  {
    appearanceSet = LoadFeatureSet(appDir,ext,ignoreSuspect,true);
  }

  for(SampleIterC<AAMAppearanceC> ait(appearanceSet);ait;ait++) {

    VectorC aParam = am1.Parameters(*ait);

#if 1
    VectorC iParam(am1.Dimensions());
    iParam.Fill(0);
    iParam[3] = 0;
    iParam[4] = am1.FixedMean()[4];
    iParam[5] = am1.FixedMean()[5];

    if(rand()<0.5) {
      iParam[0] = aParam[0]-15;
    } else {
      iParam[0] = aParam[0]+15;
    }
    if(rand()<0.5) {
      iParam[1] = aParam[1]-15;
    } else {
      iParam[1] = aParam[1]+15;
    }
    if(rand()<0.5) {
      iParam[2] = aParam[2]*0.9;
    } else {
      iParam[2] = aParam[2]*0.9;
    }
    if(rand()<0.5) {
      iParam[3] = aParam[3]*0.9;
    } else {
      iParam[3] = aParam[3]*0.9;
    }
#else
    // Generate vector corresponding to appearance with converged shape parameters and mean texture values
    VectorC iParam = am1.ShapeParameters(aParam).From(0,sm1.NoFixedParameters());
    iParam.Append((am1.FixedMean()).Copy().From(sm1.NoFixedParameters()));
    VectorC rawp1 = am1.ShapeParameters(aParam).From(sm1.NoFixedParameters());
    VectorC p01(am1.Dimensions()-am1.NoFixedParameters());
    p01.Fill(0);
    rawp1.Append((am1.InvAppearanceModel().Apply(p01)).From(sm1.Dimensions()-sm1.NoFixedParameters()));
    iParam.Append(am1.AppearanceModel().Apply(rawp1));
#endif

    // initialise level 1
    AAMAppearanceC initAM1s = AAMAppearanceC(sm1.Synthesize(am1.ShapeParameters(iParam)),ait->Image());
    initAM1s.Draw("@X:Initialised shape model");
    AAMAppearanceC initAM1 = am1.Synthesize(iParam, 1.0);
    Save("@X:Initial appearance model 1", initAM1.Image(), "", true);

    // solution of level 1
    VectorC resParam1 = aam1.RefinePose(ait->Image(),iParam);
    am1.MakePlausible(resParam1);
    AAMAppearanceC resAM1s = AAMAppearanceC(sm1.Synthesize(am1.ShapeParameters(resParam1)),ait->Image());
    resAM1s.Draw("@X:Converged shape model 1");
    AAMAppearanceC resAM1 = am1.Synthesize(resParam1, 1.0);
    Save("@X:Converged appearance model 1", resAM1.Image(), "", true);

cerr << 1 << endl;
    
    // project solution of level 1 to next level
#if PROJECT_TEXTURE
      // Get shape free image of level 1
      ImageC<RealT> im1(am1.Mask().Frame());
      am1.TextureImage(resParam1,im1);
      
      // Project (scale) to level 2
      WarpScaleC<RealT,RealT> warpS(ImageRectangleC(am2.MaskSize()));
      ImageC<RealT> im2 = warpS.Apply(im1);

      // Get texture values
      VectorC ret(am2.MaskArea()+am2.NoFixedParameters()-sm2.NoFixedParameters());
      am2.TextureParameters(im2, ret);

      // Generate vector of parameters
      VectorC initParam2 = am1.ShapeParameters(resParam1).From(0,sm2.NoFixedParameters());
      initParam2.Append(ret.From(0,am2.NoFixedParameters()-sm2.NoFixedParameters()));
      VectorC rawp = am1.ShapeParameters(resParam1).From(sm2.NoFixedParameters());
      rawp.Append(ret.From(am2.NoFixedParameters()-sm2.NoFixedParameters()));
      initParam2.Append(am2.AppearanceModel().Apply(rawp));
#else
      // Generate vector corresponding to appearance with converged shape parameters and mean texture values
      VectorC initParam2 = am1.ShapeParameters(resParam1).From(0,sm2.NoFixedParameters());
      initParam2.Append((am2.FixedMean()).Copy().From(sm2.NoFixedParameters()));
      VectorC rawp = am1.ShapeParameters(resParam1).From(sm2.NoFixedParameters());
      VectorC p0(am2.Dimensions()-am2.NoFixedParameters());
      p0.Fill(0);
      rawp.Append((am2.InvAppearanceModel().Apply(p0)).From(sm2.Dimensions()-sm2.NoFixedParameters()));
      initParam2.Append(am2.AppearanceModel().Apply(rawp));
#endif

    AAMAppearanceC initAM2 = am2.Synthesize(initParam2, 1.0);
    Save("@X:Initial appearance model 2 init", initAM2.Image(), "", true);

    // solution of level 2
    VectorC resParam2 = aam2.RefinePose(ait->Image(),initParam2);
    AAMAppearanceC resAM2s = AAMAppearanceC(sm2.Synthesize(am2.ShapeParameters(resParam2)),ait->Image());
    resAM2s.Draw("@X:Converged shape model 2");
    AAMAppearanceC resAM2 = am2.Synthesize(resParam2, 1.0);
    Save("@X:Converged appearance model 2", resAM2.Image(), "", true);

    // project solution of level 2 to next level
#if PROJECT_TEXTURE
      // Get shape free image of level 2
      ImageC<RealT> im2(am2.Mask().Frame());
      am2.TextureImage(resParam2,im2);
      
      // Project (scale) to level 3
      WarpScaleC<RealT,RealT> warpS(ImageRectangleC(am3.MaskSize()));
      ImageC<RealT> im3 = warpS.Apply(im1);

      // Get texture values
      VectorC ret(am3.MaskArea()+am3.NoFixedParameters()-sm3.NoFixedParameters());
      am3.TextureParameters(im3, ret);

      // Generate vector of parameters
      VectorC initParam3 = am2.ShapeParameters(resParam2).From(0,sm3.NoFixedParameters());
      initParam3.Append(ret.From(0,am3.NoFixedParameters()-sm3.NoFixedParameters()));
      VectorC rawp = am2.ShapeParameters(resParam2).From(sm3.NoFixedParameters());
      rawp.Append(ret.From(am3.NoFixedParameters()-sm3.NoFixedParameters()));
      initParam3.Append(am3.AppearanceModel().Apply(rawp));
#else
      // Generate vector corresponding to appearance with converged shape parameters and mean texture values
      VectorC initParam3 = am2.ShapeParameters(resParam2).From(0,sm3.NoFixedParameters());
      initParam3.Append((am3.FixedMean()).Copy().From(sm3.NoFixedParameters()));
      VectorC rawp2 = am2.ShapeParameters(resParam2).From(sm3.NoFixedParameters());
      VectorC p02(am3.Dimensions()-am3.NoFixedParameters());
      p02.Fill(0);
      rawp2.Append((am3.InvAppearanceModel().Apply(p02)).From(sm3.Dimensions()-sm3.NoFixedParameters()));
      initParam3.Append(am3.AppearanceModel().Apply(rawp2));
#endif

    AAMAppearanceC initAM3 = am3.Synthesize(initParam3, 1.0);
    Save("@X:Initial appearance model 3 init", initAM3.Image(), "", true);

    // solution of level 3
    VectorC resParam3 = aam3.RefinePose(ait->Image(),initParam3);
    AAMAppearanceC resAM3s = AAMAppearanceC(sm3.Synthesize(am3.ShapeParameters(resParam3)),ait->Image());
    resAM3s.Draw("@X:Converged shape model 3");
    AAMAppearanceC resAM3 = am3.Synthesize(resParam3, 1.0);
    Save("@X:Converged appearance model 3", resAM3.Image(), "", true);

    // reproject solution
    VectorC sParam3 = am3.ShapeParameters(resParam3);
    SArray1dC<Point2dC> points3 = sm3.Synthesize(sParam3);
    AAMAppearanceC convergedAM3 = AAMAppearanceC(points3,ait->Image());
    VectorC resConvParam3 = am3.Parameters(convergedAM3);
    am3.MakePlausible(resConvParam3);
    AAMAppearanceC resConvAM3 = am3.Synthesize(resConvParam3, 1.0);    
    Save("@X:Reprojected appearance model 3", resConvAM3.Image(), "", true);

    // wait for signal to process next model
    char tmp;
    cin >> tmp;
    cin.ignore(100,'\n');
  }

  return 0;
}
