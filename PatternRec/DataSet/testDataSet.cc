// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/testDataSet.cc"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! userlevel=Develop

#include "Ravl/PatternRec/DataSet1.hh"
#include "Ravl/PatternRec/DataSet2.hh"
#include "Ravl/PatternRec/DataSet3.hh"
#include "Ravl/PatternRec/DataSet1Iter.hh"
#include "Ravl/PatternRec/DataSet2Iter.hh"
#include "Ravl/PatternRec/DataSet3Iter.hh"
#include "Ravl/PatternRec/SampleIO.hh"
#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/PatternRec/SampleStreamVector.hh"
#include "Ravl/PatternRec/Function1.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/Stream.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/MatrixRUT.hh"
#include "Ravl/MeanCovariance.hh"
#include "Ravl/DP/ListIO.hh"

using namespace RavlN;

#define USE_SPEEDTEST 0

int testSample();
int testSampleIO();
int testDataSet1();
int testDataSet2();
int testDataSet3();
int testSampleVector();
int testSampleStreamVector();

#if USE_SPEEDTEST
#include "Ravl/DList.hh"
int testSpeed();
#endif

#ifndef __sgi__
template DataSet1C<SampleC<IntT> >;
template DataSet2C<SampleC<IntT>,SampleC<RealT> >;
template DataSet3C<SampleC<IntT>,SampleC<RealT>,SampleC<bool> >;
#endif

int main() {
  int ln;
  if((ln = testSample()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  if((ln = testSampleIO()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  if((ln = testDataSet1()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  if((ln = testDataSet2()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  if((ln = testDataSet3()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  if((ln = testSampleVector()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  if((ln = testSampleStreamVector()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
#if USE_SPEEDTEST
  if((ln = testSpeed()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
#endif
  cout << "Test passed ok. \n";
  return 0;
}

int testSample() {
  SampleC<IntT> sample;
  int i = 0;
  for(;i < 10;i++)
    sample.Append(i);
  i = 0;
  for(DArray1dIterC<IntT> it(sample.DArray());it;it++,i++)
    if(*it != i) return __LINE__;
  if(sample.Size() != 10) return __LINE__;
  return 0;
}

int testSampleIO() {
  SampleC<IntT> sample;
  sample.Append(10);
  sample.Append(11);
  sample.Append(12);
  FilenameC tmpFile("/tmp/test.strm");
  if(!SaveSample(tmpFile,sample,"",true))
    return __LINE__;
  SampleC<IntT> sample2;
  if(!LoadSample(tmpFile,sample2,((UIntT) -1),"",true))
    return __LINE__;
  if(sample.Size() != sample2.Size())
    return __LINE__;
  // Should check the loaded set.
  tmpFile.Remove();
  
  StringC dataStr;
  {
    StrOStreamC ostr;
    ostr << sample;
    dataStr = ostr.String();
  }
  SampleC<IntT> sample3;
  StrIStreamC istr(dataStr);
  istr >> sample3;
  //cerr << "DataStr=" << dataStr << "\n";
  if(sample.Size() != sample3.Size()) {
    cerr << "Size1=" << sample.Size() << " Size3=" << sample3.Size() << "\n";
    return __LINE__;
  }
  
  return 0;
}

int testDataSet1() {
  DataSet1C<SampleC<IntT> > dataset(true);
  dataset.Append(10);
  dataset.Append(11);
  dataset.Append(12);
  dataset.Append(13);
  UIntT count = 0;
  for(DataSet1IterC<SampleC<IntT> > it(dataset);it;it++)
    count++;
  if(count != 4) return __LINE__;
  return 0;
}

int testDataSet2() {
  DataSet2C<SampleC<IntT>,SampleC<RealT> > dataset(true);
  dataset.Append(10,0.3);
  dataset.Append(11,0.4);
  UIntT count = 0;
  for(DataSet2IterC<SampleC<IntT>,SampleC<RealT> > it(dataset);it;it++)
    count++;
  if(count != 2) return __LINE__;
  return 0;
}

int testDataSet3() {
  DataSet3C<SampleC<IntT>,SampleC<RealT>,SampleC<bool> > dataset(true);
  dataset.Append(10,0.3,true);
  dataset.Append(11,0.4,false);
  dataset.Append(12,0.5,false);
  UIntT count = 0;
  for(DataSet3IterC<SampleC<IntT>,SampleC<RealT>,SampleC<bool> > it(dataset);it;it++)
    count++;
  if(count != 3) return __LINE__;
  return 0;
}

int testSampleVector() {
  SampleVectorC sv;
  sv += VectorC(1,2,3);
  sv += VectorC(1,1,1);
  if(sv.Size() != 2) return __LINE__;
  MatrixRUTC sop = sv.SumOuterProducts();
  sop.MakeSymmetric();
  MatrixC t(3,3);
  t.Fill(0);
  t += VectorC(1,2,3).OuterProduct();
  t += VectorC(1,1,1).OuterProduct();
  if((sop - t).SumOfSqr() > 0.0000001) return __LINE__;
  //cerr << "SOP=" << sop << "\n";;
  
  // Check mean covariance computation.
  MeanCovarianceC mc = sv.MeanCovariance();
  MeanCovarianceC cmc(3);
  cmc += VectorC(1,2,3);
  cmc += VectorC(1,1,1);
  if((mc.Covariance() - cmc.Covariance()).SumOfSqr() > 0.00001) return __LINE__;
  if((mc.Mean() - cmc.Mean()).SumOfSqr() > 0.00001) return __LINE__;
  if(mc.Number() != cmc.Number()) return __LINE__;

  StringC dataStr;
  {
    StrOStreamC ostr;
    ostr << sv;
    dataStr = ostr.String();
  }
  StrIStreamC istr(dataStr);
  SampleVectorC sv2;
  istr >> sv2;
  if(sv2.Size() != sv.Size()) return __LINE__;
  return 0;
}

int testSampleStreamVector() {
  cerr << "testSampleStreamVector(), Called. \n";
  DListC<VectorC> lst;
  MatrixRUTC accum(4);
  accum.Fill(0);
  MeanCovarianceC mc(4);
  for(int i = 0;i < 100000;i++) {
    VectorC vec = RandomVector(4,1000);
    accum.AddOuterProduct(vec);
    lst.InsLast(vec);
    mc += vec;
  }
  DPISListC<VectorC> vecs(lst);
  SampleStreamVectorC ssv(vecs);
  accum.MakeSymmetric();
  MatrixRUTC accum2 = ssv.SumOuterProducts();
  //cerr << "Accum=" << accum << "\n";
  //cerr << "Accum2=" << accum2 << "\n";
  //cerr << "Diff=" << (accum - accum2) << "\n";
  if((accum - accum2).SumOfSqr() > 0.01) return __LINE__;
  MeanCovarianceC mcn = ssv.MeanCovariance();
  //cerr << "mc=" << mc << "\n";
  //cerr << "mnc=" << mcn << "\n";
  MeanCovarianceC lmc(lst);
  //cerr << "lmc=" << mcn << "\n";
  if((mc.Mean() - mc.Mean()).SumOfSqr() > 0.0001) return __LINE__;
  if((mc.Covariance() - mc.Covariance()).SumOfSqr() > 0.0001) return __LINE__;
  return 0;
}

#if USE_SPEEDTEST
const int testSize = 1000000;
int testSpeed() {
  DataSet1C<SampleC<IntT> > dataset1(true);
  DateC start(true);
  for(int i = 0;i < testSize;i++) 
    dataset1.Append(i);
  DateC end(true);
  cerr << "Create Time1 = " << (end.Double() - start.Double()) << "\n";
  
  DataSet2C<SampleC<IntT>,SampleC<RealT> > dataset2(true);
  start.SetToNow();
  for(int i = 0;i < testSize;i++) 
    dataset2.Append(i,0.3);
  end.SetToNow();
  cerr << "Create Time2 = " << (end.Double() - start.Double()) << "\n";
  
  DataSet3C<SampleC<IntT>,SampleC<RealT>,SampleC<bool> > dataset3(true);
  start.SetToNow();
  for(int i = 0;i < testSize;i++) 
    dataset3.Append(i,0.3,true);
  end.SetToNow();
  cerr << "Create Time3 = " << (end.Double() - start.Double()) << "\n";

  start.SetToNow();
  DListC<int> aList;
  for(int i = 0;i < testSize;i++) 
    aList.InsLast(i);
  end.SetToNow();
  cerr << "DList Create Time = " << (end.Double() - start.Double()) << "\n";
  
  UIntT val = 0;
  start.SetToNow();
  for(DataSet1IterC<SampleC<IntT> > it1(dataset1);it1;it1++)
    val += it1.Data();
  end.SetToNow();
  cerr << "Iter Time1 = " << (end.Double() - start.Double()) << "\n";
  
  start.SetToNow();
  for(DataSet2IterC<SampleC<IntT>,SampleC<RealT> > it2(dataset2);it2;it2++) {
    val += it2.Data1() + it2.Data2();
  }
  end.SetToNow();
  cerr << "Iter Time2 = " << (end.Double() - start.Double()) << "\n";

  start.SetToNow();
  for(DataSet3IterC<SampleC<IntT>,SampleC<RealT>,SampleC<bool> > it3(dataset3);it3;it3++) {
    val += it3.Data1() + it3.Data2() + ((int) it3.Data3());
  }
  end.SetToNow();
  cerr << "Iter Time3 = " << (end.Double() - start.Double()) << "\n";
  start.SetToNow();
  for(DLIterC<int > itl(aList);itl;itl++)
    val += itl.Data();
  end.SetToNow();

  cerr << "DList Iter Time = " << (end.Double() - start.Double()) << "\n";
  
  return 0;
}


#endif
