
#include "Ravl/Histogram.hh"

using namespace RavlN;

int testBasic();
int testCompair();

int main() {
  int ln;
  
  if((ln = testBasic()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testCompair()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  
  cerr << "Test passed. \n";
  return 0;
}

int testBasic() {
  HistogramC<int> h1;
  if(h1.Size() != 0) return __LINE__;
  if(h1.Vote(1) != 1) return __LINE__;
  if(h1.Vote(2) != 1) return __LINE__;
  if(h1.Vote(2) != 2) return __LINE__;
  if(h1.Vote(3) != 1) return __LINE__;
  if(h1.Size() != 3) return __LINE__;
  if(h1.Total() != 4) return __LINE__;
  if(Abs(h1.Information() - 1.5) > 0.00000001) return __LINE__;
  if(Abs(h1.Energy() - 0.375) > 0.00000001) return __LINE__;  
  return 0;
}

int testCompair() {
  HistogramC<int> h1,h2;
  h1.Vote(1,2);
  h1.Vote(2,3);
  h1.Vote(3,1);
  if(h1.Total() != 6) return __LINE__;
  h2.Vote(2,1);
  h2.Vote(3,4);
  h2.Vote(4,2);
  if(h2.Total() != 7) return __LINE__;
  if(h1.SumIntersection(h2) != 2) return __LINE__;
  if(h2.SumIntersection(h1) != 2) return __LINE__;
  
  int key = -2;
  int ldiff = -2;
  UIntT c = h1.LargestDifference(h2,key,ldiff);
  if(c != 1) return __LINE__;
  if(key != 3) return __LINE__;
  if(ldiff != 3) return __LINE__;
  c = h2.LargestDifference(h1,key,ldiff);
  if(c != 1) return __LINE__;
  if(key != 3) return __LINE__;
  if(ldiff != 3) return __LINE__;
  return 0;
}
