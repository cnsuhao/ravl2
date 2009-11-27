
//! author="Alexey Kostin"

namespace RavlN {
  extern void InitRavlSVMIO2();
  extern void InitRavlSVMIO();
  
  void linkRavlSVM() {
    InitRavlSVMIO2();
    InitRavlSVMIO();
  }
}
