
#include "Ravl/Image/ConnectedComponents.hh"


using namespace RavlImageN;

int testConnectComp();

int main(int nargs,char **argv)
{
  int ln;
  if((ln = testConnectComp()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
    
  return 0;
}


int testConnectComp() {
  ImageC<UIntT> test(8,8);
  test.Fill(0);

  test[1][1] = 1;
  test[1][2] = 1;
  test[2][1] = 1;
  test[6][6] = 1;
  test[5][6] = 1;
  //cerr << test;
  ConnectedComponentsC<UIntT> conComp(false);
  Tuple2C<ImageC<UIntT>,UIntT> result = conComp.Apply(test);
  ImageC<UIntT> segMap = result.Data1();
  //cerr << "Regions=" << result.Data2() << "\n";
  //cerr << segMap;
  if(result.Data2() != 4) return __LINE__;
  if(segMap[1][1] != segMap[1][2]) return __LINE__;
  if(segMap[1][2] != segMap[2][1]) return __LINE__;
  if(segMap[6][6] != segMap[5][6]) return __LINE__;
  if(segMap[6][6] == segMap[1][1]) return __LINE__;
  if(segMap[6][6] == segMap[0][0]) return __LINE__;
  if(segMap[1][2] == segMap[0][0]) return __LINE__;
  return 0;
}
