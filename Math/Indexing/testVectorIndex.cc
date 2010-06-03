// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: testVectorIndex.cc 4130 2004-03-20 15:08:03Z craftit $"
//! lib=RavlMath
//! file="Ravl/Math/Indexing/testVectorIndex.cc"

#include "Ravl/EntryPnt.hh"
#include "Ravl/VectorIndex.hh"
#include "Ravl/DList.hh"
#include "Ravl/Vector.hh"
#include "Ravl/Option.hh"
#include "Ravl/Stream.hh"
#include <stdlib.h>

//////////////////////////////////

using namespace RavlN;
  
typedef Tuple2C<VectorC, int> DataC;

//////////////////////////////////
  
RealT Distance(const VectorC & one, const VectorC & two) {
  return one.SqrEuclidDistance(two);
}
  
//////////////////////////////////
  
DListC<DataC> find_closest_by_brute_force(const DListC<VectorC> & test, const DListC<DataC> & data){
  DListC<DataC> result;
  for(DLIterC<VectorC> test_it(test); test_it.IsElm(); test_it.Next()) {
    RealT cur_dis;
    DataC closest = data.First(); 
    RealT shortest_dist = Distance(test_it.Data(), data.First().Data1());
    for(DLIterC<DataC> data_it(data); data_it.IsElm(); data_it.Next()){ 
      if ((cur_dis = Distance(test_it.Data(), data_it.Data().Data1())) < shortest_dist) {
	shortest_dist = cur_dis;
	closest = data_it.Data();
      }
    }
    result.InsLast(closest);
  }
  return result;
}
  
//////////////////////////////////
  
DListC<DataC> find_closest(const DListC<VectorC> & test, const DListC<DataC> & data,int inddim,RealT maxSearch,RealT binSize){
  VectorIndexC<int> searcher(data, Distance,inddim,binSize,maxSearch); 
  DLIterC<VectorC> it(test);
  DListC<DataC> result;
  for(;it;it++) { 
    result.InsLast(searcher.Closest(it.Data())); 
  }
  return result;
}

  
void check_closest(const DListC<VectorC> & test, const DListC<DataC> & data,int inddim,RealT maxSearch,RealT binSize) {
  VectorIndexC<int> searcher(data, Distance,inddim,binSize,maxSearch); 
  DLIterC<VectorC> it(test);
  int count = 0;
  for(;it;it++) { 
    RealT cur_dis, shortest_dist;
    DataC closest = data.First();
    shortest_dist = Distance(it.Data(), closest.Data1());
    for(DLIterC<DataC> data_it(data); data_it.IsElm(); data_it.Next()) { 
      if ((cur_dis = Distance(it.Data(), data_it.Data().Data1())) < shortest_dist) {
	shortest_dist = cur_dis;
	closest = data_it.Data();
      }
    }
    
    DataC res = searcher.Closest(it.Data());
    if(closest.Data2() != res.Data2() && (shortest_dist < maxSearch || maxSearch <= 0)) {
      cerr << "Res=" << res << "\n";
      cerr << "Brute:" << shortest_dist;
      if(res.Data1().Size() == (UIntT) inddim)
	cerr << " Clever:" << Distance(it.Data(),res.Data1()) << " \n";
      else
	cerr << " Clever:None \n";	
      cerr << "Mismatch in result " << count << " :" << closest.Data2()  << " " << res.Data2() << "\n";
      return ;
    }
    count++;
  }
}


//////////////////////////////////

int Main(int argc, char* argv[])
{
  OptionC option(argc,argv,true);
  IntT datap = option.Int("dp",100000,"Number of data points.");
  IntT dim = option.Int("n",5,"Number of dimensions to data points.");
  bool useBrute = option.Boolean("b",false,"Use brute force. ");
  bool check = option.Boolean("chk",false,"Check results of VectorIndex.");
  RealT maxSearch = option.Real("ms",10,"Maximum search size ");
  RealT binSize = option.Real("bs",maxSearch,"Bin size factor. ");
  IntT npoints = option.Int("tp",100,"Number of test points.");
  option.Check();
  
  // Make up some training data
  DListC<DataC> data;
  for (IntT i=0; i < datap; i++) {
    VectorC point = RandomVector(dim,100);
    data.InsLast(DataC(point,i));
  }
  
  // Make up as many test points as the user wants.
  DListC<VectorC> testpoints;
  for (IntT i=0; i < npoints; i++) {
    VectorC test_p = RandomVector(dim,100);
    testpoints.InsLast(test_p);
  }
  
  if(check) {
    check_closest(testpoints, data,dim,maxSearch,binSize);
  } else {
    if(useBrute) {
      cerr << "Using Brute force. \n";
      // Function to profile
      find_closest_by_brute_force(testpoints, data);
    } else {
      cerr << "Using VectorIndex. \n";
      // Function to profile
      find_closest(testpoints, data,dim,maxSearch,binSize);
    }
  }
  return 0;
}

//////////////////////////////////

RAVL_ENTRY_POINT(Main)
