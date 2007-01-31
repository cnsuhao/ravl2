#include "Ravl/CPUID.hh"
#include "Ravl/Option.hh"
#include <iostream>


using namespace RavlN;


int main(int argc, char **argv) {

  CPUIDC cpuid;

  cpuid.Info();

  //test non class functions
  cout << "Non class functions test\n";
  cout << "MMX: " << MMX()  << endl;
  cout << "SSE: " << SSE()  << endl;
  cout << "SSE2:" << SSE2() << endl;
  cout << "HTT: " << HTT()  << endl;
}

