

#include "Ravl/DP/ThreadPipe.hh"
#include "Ravl/DP/MTIOConnect.hh"

using namespace RavlN;

template class DPThreadPipeC<IntT,IntT>;
template class DPMTIOConnectC<IntT>;

int testThreadPipe();

int main() {
  int ln;
  if((ln = testThreadPipe()) != 0) {
    cerr << "Error on line " << ln << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

int testThreadPipe() {
  //...
  return 0;
}
