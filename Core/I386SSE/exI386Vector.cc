
#include "Ravl/Vector.hh"

// Small program usefull for checking SSE usage

int main () {

  using namespace RavlN;

  VectorC a(1024); a.Fill(1);
  RealT s = 0;
  for (IntT i=0; i<100000; ++i) s += a.Dot(a);
  cout << s << endl;
}
