//! author="Charles Galambos"
//! docentry="Ravl.Logic.Agent"

#include "Ravl/Option.hh"
#include "Ravl/Logic/ActiveBlackboard.hh"

using namespace RavlLogicN;
using namespace RavlN;

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  StringC file = opt.String("","rules.rl","Input file. ");
  opt.Check();
  
  ActiveBlackboardC abb(true);
  if(!abb.LoadRules(file)) {
    cerr << "Failed to load '" << file << "'\n";
    return 1;
  }
  cout << "Done. \n";
  return 0;
}
