
//! author="Alexey Kostin"

namespace RavlN {
  extern void InitRavlSVMIO2();
  extern void InitRavlSVMIO();
  extern void linkCommonKernels();
  extern void linkDesignSvm();
  extern void linkDesignOneClass();
  extern void linkDesignOneClassLarge();
  extern void linkDesignSvmSmo();
  extern void linkDesignSvmSmoLarge();
  
  void linkRavlSVM() {
    InitRavlSVMIO2();
    InitRavlSVMIO();
    linkCommonKernels();
    linkDesignSvm();
    linkDesignOneClass();
    linkDesignOneClassLarge();
    linkDesignSvmSmo();
    linkDesignSvmSmoLarge();
  }
}
