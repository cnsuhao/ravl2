

#include "Ravl/Logic/DecisionTreeBase.hh"

using namespace RavlLogicN;

int testBasic();

int main() {
  int ln;
  if((ln = testBasic()) == 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }

  return 0;
}

int testBasic() {
  DecisionTreeBaseC dl;
  //(const DiscriminatorC &desc)
  
  return 0;
}


