

#include "Ravl/Logic/DecisionTreeBase.hh"

int TestBasic();

int main() {
  int ln;
  if((ln = testBasic()) == 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }

  return 0;
}

int TestBasic() {
  DecisionTreeBaseC dl;
  //(const DiscriminatorC &desc)
  
  return 0;
}


