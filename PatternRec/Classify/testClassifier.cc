// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: testClassifier.cc 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Classify/testClassifier.cc"
//! docentry="Ravl.API.Pattern Recognition.Classifier"
//! userlevel=Develop

#include "Ravl/PatternRec/ClassifierKNearestNeighbour.hh"
#include "Ravl/PatternRec/ClassifierAverageNearestNeighbour.hh"
#include "Ravl/PatternRec/DesignClassifierGaussianMixture.hh"
#include "Ravl/PatternRec/DesignKMeans.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/HSet.hh"

using namespace RavlN;

int GenerateDataSet();
int testKNearestNeighbour();
int testAverageNearestNeighbour();
int testDesignKMeans();
int testDesignClassifierGaussianMixture();

int main() {
  int ln;
  if((ln = GenerateDataSet()) != 0) {
    cerr << "Error line " << ln << "\n";
    return 1;
  }
  if((ln = testKNearestNeighbour()) != 0) {
    cerr << "Error line " << ln << "\n";
    return 1;
  }
  if((ln = testAverageNearestNeighbour()) != 0) {
    cerr << "Error line " << ln << "\n";
    return 1;
  }
  if((ln = testDesignKMeans()) != 0) {
    cerr << "Error line " << ln << "\n";
    return 1;
  }
  if((ln = testDesignClassifierGaussianMixture()) != 0) {
    cerr << "Error line " << ln << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";
  return 0;
}

DataSet2C<SampleVectorC,SampleLabelC> dataset(true);

int GenerateDataSet() {
  
  dataset.Append(VectorC(0.10,0.10),1);
  dataset.Append(VectorC(0.11,0.11),1);
  dataset.Append(VectorC(0.30,0.20),1);
  dataset.Append(VectorC(0.20,0.10),1);
  dataset.Append(VectorC(0.23,0.12),1);
  dataset.Append(VectorC(0.40,0.90),2);
  dataset.Append(VectorC(0.30,0.80),2);
  dataset.Append(VectorC(0.32,0.81),2);
  dataset.Append(VectorC(0.50,0.90),2);
  dataset.Append(VectorC(0.51,0.92),2);
  dataset.Append(VectorC(0.90,0.30),3);
  dataset.Append(VectorC(0.90,0.20),3);
  dataset.Append(VectorC(0.93,0.24),3);
  dataset.Append(VectorC(0.90,0.40),3);
  dataset.Append(VectorC(0.95,0.42),3);
  if(dataset.Size() != 15) return __LINE__;
  return 0;
}


int testKNearestNeighbour() {
  cerr << "testKNearestNeighbour(), Called. \n";
  ClassifierKNearestNeighbourC knn(dataset,3);
  int c = knn.Classify(VectorC(0.3,0.2));
  if(c != 1) return __LINE__;
  VectorC vec =  knn.Confidence(VectorC(0.3,0.2));
  if(vec.Size() != 4) return __LINE__;
  return 0;
}

int testAverageNearestNeighbour() {
  cerr << "testAverageNearestNeighbour(), Called. \n";
  ClassifierAverageNearestNeighbourC knn(dataset,3);
  int c = knn.Classify(VectorC(0.3,0.2));
  if(c != 1) return __LINE__;
  VectorC vec =  knn.Confidence(VectorC(0.3,0.2));
  if(vec.Size() != 4) return __LINE__;
  return 0;
}

int testDesignKMeans() {
  cerr << "testDesignKMeans(), Called. \n";
  DesignKMeansC kmeans(3);
  ClassifierC cv = kmeans.Apply(dataset.Sample1());
  HSetC<UIntT> labels;
  for(SampleIterC<VectorC> it(dataset.Sample1());it;it++) {
    UIntT label = cv.Classify(*it);
    labels += label;
    //cerr << "Label=" << label << "\n";
  }
  if(labels.Size() != 3) return __LINE__;
  return 0;
}

int testDesignClassifierGaussianMixture() {
  cerr << "testDesignClassifierGaussianMixture(), Called. \n";  
  DesignClassifierGaussianMixtureC gm(1);
  ClassifierC cv = gm.Apply(dataset.Sample1(),dataset.Sample2());
  HSetC<UIntT> labels;
  for(SampleIterC<VectorC> it(dataset.Sample1());it;it++) {
    UIntT label = cv.Classify(*it);
    labels += label;
    //cerr << "Label=" << label << "\n";
  }
  if(labels.Size() != 3) return __LINE__;
  return 0;
}
