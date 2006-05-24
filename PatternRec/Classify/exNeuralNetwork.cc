// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id: exKNearestNeighbour.cc,v 1.4 2005/12/06 17:16:50 plugger Exp $"
//! lib=RavlPatternRec
//! docentry="Ravl.API.Pattern Recognition.Classifier"
//! userlevel=Normal
//! file="Ravl/PatternRec/Classify/exKNearestNeighbour.cc"

#include "Ravl/PatternRec/DesignClassifierNeuralNetwork.hh"
#include "Ravl/PatternRec/DataSet2.hh"
#include "Ravl/PatternRec/DataSet2Iter.hh"
#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/PatternRec/SampleLabel.hh"
#include "Ravl/PatternRec/DataSetVectorLabel.hh"
#include "Ravl/IO.hh"

using namespace RavlN;

int main(int nargs,char **argv) {


#if 1
  DataSetVectorLabelC dataset;
  IStreamC istrain("example.dset");
  istrain >> dataset;
  MeanCovarianceC mcov = dataset.Sample1().MeanCovariance();
  dataset.Sample1().Normalise(mcov);
  dataset.Shuffle();
  DataSet2C<SampleVectorC, SampleLabelC> testdataset = dataset.ExtractSample(0.5f);
#endif

#if 0
  DataSet2C<SampleVectorC,SampleLabelC> dataset(true);
  DataSet2C<SampleVectorC,SampleLabelC> testdataset(true);
  dataset.Append(VectorC(0.11,0.13),0);
  dataset.Append(VectorC(0.12,0.11),0);
  dataset.Append(VectorC(0.13,0.12),0);
  dataset.Append(VectorC(0.52,0.51),1);
  dataset.Append(VectorC(0.51,0.515),1);
  dataset.Append(VectorC(0.501,0.52),1);
  dataset.Append(VectorC(0.89,0.91),2);
  dataset.Append(VectorC(0.88,0.92),2);
  dataset.Append(VectorC(0.92,0.89),2);

  testdataset.Append(VectorC(0.09,0.09),0);
  testdataset.Append(VectorC(0.15,0.16),0);
  testdataset.Append(VectorC(0.54,0.55),1);
  testdataset.Append(VectorC(0.51,0.43),1);
  testdataset.Append(VectorC(0.9, 0.76),2);
  testdataset.Append(VectorC(0.67,0.76),2);
#endif

#if 0
  DataSet2C<SampleVectorC,SampleLabelC> dataset(true);
  DataSet2C<SampleVectorC,SampleLabelC> testdataset(true);
  dataset.Append(VectorC(-1, -1),0);
  dataset.Append(VectorC(-1, 1),1);
  dataset.Append(VectorC(1, -1),1);
  dataset.Append(VectorC(1, 1), 0);
  testdataset = dataset;
#endif


#if 1
  // Construct a designer.
  DesignClassifierNeuralNetworkC designer(3u, 2u, 5u, 5u);
  
  // Build a classifier.
  
  ClassifierC classifier = designer.Apply(dataset.Sample1(), dataset.Sample2());
  
  // In which cluster is each vector ?
  for(DataSet2IterC<SampleVectorC,SampleLabelC> it(testdataset);it;it++) {
    UIntT cluster = classifier.Classify(it.Data1());
    cerr << "Vector " << it.Data1() << " is in cluster " << cluster << " (True=" << it.Data2() << ")\n";
    cerr << classifier.Confidence(it.Data1()) << endl;
  }
#endif

#if 0
  IStreamC is("class5.dset");
  UIntT size;
  is >> size;
  DataSetVectorLabelC dset(size);
  for(UIntT i=0;i<size;i++) {
    VectorC vec;
    UIntT label;
    is >> vec >> label;
    dset.Append(vec, label);
  }
  OStreamC os("train.dset");
  os << dset;
  exit(0);
#endif

  return 0;
}
