
#include "Ravl/DP/SPortAttach.hh"

using namespace RavlN;

int main()
{
  DPSeekCtrlC sc(TRUE);
  DPISPortAttachC<int> sp(in,sc);
  DPISPortC<int> x(sp);
  DPSeekCtrlC asc(x);
  asc.Seek(0);
  return 0;
}
