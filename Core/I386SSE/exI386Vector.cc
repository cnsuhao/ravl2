
#include "Ravl/Vector.hh"

// Small program usefull for checking SSE usage

int main () {

  using namespace RavlN;
#if 0
  VectorC a(1024); a.Fill(0.96);
  RealT s = 0;
  for (IntT i=0; i<100000; ++i) s += a.Dot(a);
#else
  TVectorC<float> a(1024);
  a.Fill(0.96);
  double s = 0;
  for (IntT i=0; i<100000; ++i) s += a.Dot(a);
#endif
  cout << s << endl;
}
