#ifndef RAVL_INITAUTORELEASEPOOL_HEADER
#define RAVL_INITAUTORELEASEPOOL_HEADER 1

namespace RavlN {

  //! Make sure release pool is initialised for the current thread.
  bool AutoReleasepoolInit();

  //! Call release for the current pool
  bool AutoReleasepoolRelase();

}

#endif
