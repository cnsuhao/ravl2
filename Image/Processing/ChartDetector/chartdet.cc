// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlChartDetector

#include "Ravl/Image/ChartDetector.hh"
#include "Ravl/IO.hh"
#include "Ravl/Option.hh"

using namespace RavlN;
using namespace RavlImageN;

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  RealT inlierThreshold = opt.Real("id",10,"Inlier distance threshold. ");
  UIntT ransacIterations = (UIntT) opt.Int("ri",10000,"RANSAC iterations to use in search.");
  RealT acceptThreshold = opt.Real("at",0.7,"Threshold at which to just accept hypothesis ");
  StringC chartName = opt.String("c","chart.pgm","Image of chart to search for. ");
  StringC sceneName = opt.String("","image.pgm","Image in which to search for chart. ");
  
  UIntT minRegionSize = 40;
  UIntT minRegionMargin = 10;
  opt.Check();
  
  ImageC<ByteT> chartImage;
  if(!Load(chartName,chartImage)) {
    cerr << "Failed to load image of chart. \n";
    return 1;
  }
  
  ImageC<ByteT> sceneImage;
  if(!Load(sceneName,sceneImage)) {
    cerr << "Failed to load image to search. \n";
    return 1;
  }
  
  ChartDetectorC chartDetector(chartImage,minRegionSize,minRegionMargin);
  chartDetector.SetInlierThreshold(inlierThreshold);
  chartDetector.SetRANSACIterations(ransacIterations);
  chartDetector.SetAcceptThreshold(acceptThreshold);
  
  Projection2dC transform;  
  if(!chartDetector.Apply(sceneImage,transform)) {
    cerr << "Failed to find the chart in the image. ";
    return 2;
  }
  
  cerr << "Transform =" << transform << "\n";
  
  return 0;
}
