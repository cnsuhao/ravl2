
#include "amma/SobelSeq.hh"

int main()
{
  int k;
  for(SobelSeqC ss(1);ss.IsElm() && k < 10;ss.Next(),k++) {
    cerr << ss.Data()[0] << " ";
  }
  cerr << "\n";
  return 0;
}
