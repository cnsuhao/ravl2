
#include "Ravl/Histogram.hh"
#include "Ravl/StdMath.hh"

using namespace RavlN;

int main() {
    
  HistogramC<int> hist;
  
  hist.Vote(1);
  hist.Vote(2);
  hist.Vote(2);
  hist.Vote(2);
  hist.Vote(3);
  hist.Vote(4);
  
  cout << "Votes:" << hist.Total() << "\n";
  cout << "Information:" << hist.Information() << "\n";
  return 0;
}
