// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/DataSetVectorLabel.cc"

#include "Ravl/PatternRec/DataSetVectorLabel.hh"
#include "Ravl/PatternRec/DataSet2Iter.hh"

namespace RavlN {

  //: Create a seperate sample for each label.
  
  SArray1dC<SampleVectorC> DataSetVectorLabelBodyC::SeperateLabels() const {
    SArray1dC<SampleVectorC> ret(Sample2().MaxValue()+1);
    for(DataSet2IterC<SampleVectorC,SampleLabelC> it(Sample1(),Sample2());it;it++)
      ret[it.Data2()].Append(it.Data1());
    return ret;
  }

  VectorC DataSetVectorLabelBodyC::GlobalMean() const {
    return Sample1().Mean();
  }

  SArray1dC<VectorC> DataSetVectorLabelBodyC::ClassMeans () const {
    SArray1dC<VectorC> means(Sample2().MaxValue()+1);
    SArray1dC<SampleVectorC> samps = SeperateLabels();
    IndexC counter = 0;
    for (SArray1dIterC<SampleVectorC> it (samps); it; it++) 
      means[counter++] = it.Data().Mean();

    return means;
  }

  SArray1dC<UIntT> DataSetVectorLabelBodyC::ClassNums ()  const {
    SArray1dC<UIntT> nums(Sample2().MaxValue()+1);
    SArray1dC<SampleVectorC> samps = SeperateLabels();
    IndexC counter = 0;
    for (SArray1dIterC<SampleVectorC> it (samps); it; it++) 
      nums[counter++] = it.Data().Size();
    return nums;
  }

  SArray1dC<MeanCovarianceC> DataSetVectorLabelBodyC::ClassStats () const {
    SArray1dC<MeanCovarianceC> meancovs(Sample2().MaxValue()+1);
    SArray1dC<SampleVectorC> samps = SeperateLabels();
    IndexC counter = 0;
    for (SArray1dIterC<SampleVectorC> it (samps); it; it++) 
      meancovs[counter++] = it.Data().MeanCovariance();
    return meancovs;
  }
    
  MatrixC DataSetVectorLabelBodyC::BetweenClassScatter () const {
    VectorC setMean = GlobalMean();
    SArray1dC<VectorC> classMeans = ClassMeans ();
    SArray1dC<UIntT> nums = ClassNums();
    MatrixC Sb (setMean.Size(), setMean.Size(), 0.0);
    RealT total = (RealT) Sample1().Size();
    IndexC i = 0;
    for (SArray1dIterC<VectorC> it (classMeans); it; it++) {
      VectorC diff = classMeans[i] - setMean;
      RealT p = (RealT) nums[i] / total;
      Sb += diff.OuterProduct (diff, p);
      i ++;
    }
    return Sb;
  }

  MatrixC DataSetVectorLabelBodyC::WithinClassScatter ()  const {
    SArray1dC<MeanCovarianceC> meanCovs = ClassStats();
    SArray1dC<UIntT> nums = ClassNums();
    IntT n = meanCovs[0].Mean().Size();
    MatrixC Sw (n, n, 0.0);
    RealT total = (RealT) Sample1().Size();
    IndexC i = 0;
    for (SArray1dIterC<MeanCovarianceC> it (meanCovs); it; it++) {
      RealT p = (RealT) nums[i] / total;
      Sw += it.Data().Covariance() * p;
      i ++;
    }
    return Sw;
  }

  DataSetVectorLabelC
  DataSetVectorLabelBodyC::ExtractPerLabel(UIntT numSamples)  const {
    cerr << "numSample: " << numSamples << endl;
    SArray1dC<SampleVectorC> arr = SeperateLabels();
    UIntT noClasses = Sample2().MaxValue()+1;
    cerr << "classes: " << noClasses << endl;
    SampleVectorC input(numSamples * noClasses);
    SampleLabelC output(numSamples * noClasses);
    for(SArray1dIterC<SampleVectorC>it(arr);it;it++) {
      for(UIntT i=0;i<numSamples;i++) {
	input.Append(it.Data().Pick());
	output.Append(it.Index().V());
      }
    }
    DataSetVectorLabelC ret(input, output);
    return ret;
  }

    

}

