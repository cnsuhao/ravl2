
#include "Ravl/RefCounter.hh"
#include "Ravl/RCWrap.hh"
#include "Ravl/IndexRange1d.hh"

using namespace RavlN;

class TestBodyC
  : public RCBodyVC
{
public:
  TestBodyC()
  {}
};

int testIndex();

int main()
{
  int ln;
  if((ln = testIndex()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  
  cerr << "Test passed ok. \n";
  return 0;
}

int testIndex()
{
  IndexRangeC r1(0,3);
  IndexRangeC r2(1,2);
  IndexRangeC r3(r1);
  r3.ClipBy(r2);
  if(!r1.Contains(r3)) {
    cerr << "IndexRange test 1 failed " << r1 << " does not contain " << r3 << "\n";
    return __LINE__;
  }
  if(!r2.Contains(r3)) {
    cerr << "IndexRange test 2 failed. " << r2 << " does not contain " << r3 << "\n";
    return __LINE__;
  }
  return 0;
}

template class RCHandleC<TestBodyC>;
template class RCWrapC<IntT>;
