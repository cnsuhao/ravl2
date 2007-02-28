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
#include "Ravl/PatternRec/DataSet1Iter.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SumsNd2.hh"
#include "Ravl/Exception.hh"

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
    CollectionC<Tuple2C<VectorC,UIntT> > means(10);
    DataSet2IterC<SampleVectorC,SampleLabelC> it(Sample1(),Sample2());
    if(!it) return SArray1dC<VectorC>(); // No samples.
    UIntT dim = it.Data1().Size();
    for(;it;it++) {
      while(means.Size() <= it.Data2()) {
	VectorC vec(dim);
	vec.Fill(0);
	means.Insert(Tuple2C<VectorC,UIntT>(vec,0));
      }
      means[it.Data2()].Data1() += it.Data1();
      means[it.Data2()].Data2()++;
    }
    SArray1dC<VectorC> ret(means.Size());
    for(SArray1dIter2C<Tuple2C<VectorC,UIntT>,VectorC > it(means.Array(),ret);it;it++)
      it.Data2() = it.Data1().Data1() / static_cast<RealT>(it.Data1().Data2());
    return ret;
  }

  DataSetVectorLabelC DataSetVectorLabelBodyC::ClassMeansLabels() const {
    SampleVectorC means(Sample2().MaxValue()+1);
    SampleLabelC  labels(Sample2().MaxValue()+1);
    SArray1dC<VectorC> smeans = ClassMeans();
    means.Append(smeans);
    for (UIntT i = 0;i < smeans.Size();i++)
      labels.Append(i);
    return DataSetVectorLabelC(means, labels);
  }

  SArray1dC<UIntT> DataSetVectorLabelBodyC::ClassNums ()  const {
    CollectionC<UIntT> num(10);
    for(DataSet1IterC<SampleLabelC> it(Sample2());it;it++) {
      while(num.Size() <= *it)
	num.Insert(0);
      num[*it]++;
    }
    return num.Array();
  }
  
  SArray1dC<MeanCovarianceC> DataSetVectorLabelBodyC::ClassStats (bool sampleStatistics) const {
    CollectionC<SumsNd2C> stats(10);
    DataSet2IterC<SampleVectorC,SampleLabelC> it(Sample1(),Sample2());
    if(!it) return SArray1dC<MeanCovarianceC>();
    UIntT dim = it.Data1().Size();
    for(;it;it++) {
      while(stats.Size() <= it.Data2())	
	stats.Insert(SumsNd2C(dim));
      stats[it.Data2()] += it.Data1();
    }
    SArray1dC<MeanCovarianceC> meancovs(stats.Size());
    for(SArray1dIter2C<MeanCovarianceC,SumsNd2C > it(meancovs,stats.Array());it;it++)
      it.Data1() = it.Data2().MeanCovariance(sampleStatistics);
    return meancovs;
  }
  
  MatrixC DataSetVectorLabelBodyC::BetweenClassScatter () const {
    CollectionC<Tuple2C<VectorC,UIntT> > means(1024);
    DataSet2IterC<SampleVectorC,SampleLabelC> it(Sample1(),Sample2());
    if(!it) return MatrixC(); // No samples.
    UIntT dim = it.Data1().Size();
    for(;it;it++) {
      while(means.Size() <= it.Data2()) {
	VectorC vec(dim);
	vec.Fill(0);
	means.Insert(Tuple2C<VectorC,UIntT>(vec,0));
      }
      means[it.Data2()].Data1() += it.Data1();
      means[it.Data2()].Data2()++;
    }
    SArray1dIterC<Tuple2C<VectorC,UIntT> > mit(means.Array());
    VectorC globalMean = mit->Data1().Copy();
    RealT total = mit->Data2();
    for(mit++;mit;mit++) {
      globalMean += mit->Data1();
      total += mit->Data2();
    }
    globalMean /= total;
    MatrixC Sb(globalMean.Size(),globalMean.Size(),0.0);
    for(mit.First();mit;mit++) {
      if(mit->Data2() > 0) {
        VectorC diff = (mit->Data1() / mit->Data2()) - globalMean;
        Sb.AddOuterProduct(diff,diff);
      }
    }
    return Sb;
  }
  
  MatrixC DataSetVectorLabelBodyC::WithinClassScatter (bool sampleStatistics)  const {
    SArray1dC<MeanCovarianceC> stats = ClassStats(sampleStatistics);
    SArray1dIterC<MeanCovarianceC> it (stats);
    while(it && it->Number() < 2)
      it++;
    if(!it) throw ExceptionNumericalC("DataSetVectorLabelBodyC::WithinClassScatter, No enough data to compute inclass scatter. ");
    MatrixC Sw = it->Covariance() * it->Number();
    RealT total = it->Number();
    for (it++; it; it++) {
      if(it->Number() < 2)
        continue;
      total += it->Number();
      Sw.MulAdd(it->Covariance(),it->Number());
    }
    if(total < 1) throw ExceptionNumericalC("DataSetVectorLabelBodyC::WithinClassScatter, Not enough data to compute inclass scatter. ");
    Sw /= total;
    return Sw;
  }
  
  DataSetVectorLabelC DataSetVectorLabelBodyC::ExtractPerLabel(UIntT numSamples)  const {
    cerr << "numSample: " << numSamples << endl;
    SArray1dC<SampleVectorC> arr = SeperateLabels();
    UIntT noClasses = arr.Size();
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

