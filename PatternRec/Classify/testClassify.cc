// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec


#include "Ravl/PatternRec/KNearestNeighbour.hh"
#include "Ravl/PatternRec/AverageNearestNeighbour.hh"

using namespace RavlN;

int GenerateDataSet();
int testKNearestNeighbour();
int testAverageNearestNeighbour();

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
  cerr << "Test passed ok. \n";
  return 0;
}

DataSet2C<SampleVectorC,SampleLabelC> dataset(true);

int GenerateDataSet() {
  
  dataset.Append(VectorC(0.1,0.1),1);
  dataset.Append(VectorC(0.3,0.2),1);
  dataset.Append(VectorC(0.2,0.1),1);
  dataset.Append(VectorC(0.4,0.9),2);
  dataset.Append(VectorC(0.3,0.8),2);
  dataset.Append(VectorC(0.5,0.9),2);
  dataset.Append(VectorC(0.9,0.3),3);
  dataset.Append(VectorC(0.9,0.2),3);
  dataset.Append(VectorC(0.9,0.4),3);
  if(dataset.Size() != 9) return __LINE__;
  return 0;
}

int testKNearestNeighbour() {
  cerr << "testKNearestNeighbour(), Called. \n";
  KNearestNeighbourC knn(dataset,3);
  int c = knn.Classify(VectorC(0.3,0.2));
  if(c != 1) return __LINE__;
  VectorC vec =  knn.Confidence(VectorC(0.3,0.2));
  if(vec.Size() != 4) return __LINE__;
  return 0;
}

int testAverageNearestNeighbour() {
  cerr << "testAverageNearestNeighbour(), Called. \n";
  AverageNearestNeighbourC knn(dataset,3);
  int c = knn.Classify(VectorC(0.3,0.2));
  if(c != 1) return __LINE__;
  VectorC vec =  knn.Confidence(VectorC(0.3,0.2));
  if(vec.Size() != 4) return __LINE__;
  return 0;
}
