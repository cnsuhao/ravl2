
#include "Ravl/AMutex.hh"

namespace RavlN {

  //: Default constructor.
  
  AMutexBodyC::AMutexBodyC()
  {}
  
  //: Lock mutex.
  // Returns true if lock is obtained succesfully.
  
  bool AMutexBodyC::Lock() {
    RavlAssertMsg(0,"Abstract method");
    return false;
  }
    
  //: Try and obtain lock without blocking.
  // Return true if lock is obtained, false otherwise.
  
  bool AMutexBodyC::TryLock() {
    RavlAssertMsg(0,"Abstract method");
    return false;
  }
  
  //: Lock mutex.
  // Returns true if lock is released succesfully. 
  
  bool AMutexBodyC::Unlock() {
    RavlAssertMsg(0,"Abstract method");
    return false;
  }

  //========================================================================
  
  //: Stub AMutexBodyC.
  // With some basic sanity checks.
  
  class AMutexStubBodyC 
    : public AMutexBodyC
  {
  public:        
    AMutexStubBodyC(bool doRecursive)
      : recursive(doRecursive)
    {}
    //: Constructor.
    
    bool Lock() {
      RavlAssert(recursive || !locked);
      locked = true;
      return true;
    }
    //: Lock mutex.
    // Returns true if lock is obtained succesfully.
    
    bool TryLock() {
      bool ret = !locked || recursive;
      locked = true;
      return ret;
    }
    //: Try and obtain lock without blocking.
    // Return true if lock is obtained, false otherwise.
    
    bool Unlock() {
      RavlAssert(locked || recursive);
      return true;
    }
    //: Lock mutex.
    // Returns true if lock is released succesfully.
    
  protected:
    bool recursive;
    bool locked;
  };
  

  //========================================================================
  
  
  static AMutexBodyC *DefaultLockFunc(bool recursive)
  { return new AMutexStubBodyC(recursive); }
  
  static AMutexLockFactoryT AMutexLockFactory = DefaultLockFunc;
  
  //: Register constructor func for AMutexC's
  
  void RegisterAMutexFactory(AMutexLockFactoryT newFunc) {
    AMutexLockFactory = newFunc;
  }
  
  //========================================================================
  
  //: Constructor.
  // If 'recursive' is false a 'fast' mutex is created otherise
  // a recursive version is used.
  
  AMutexC::AMutexC(bool recursive) 
    : RCHandleVC<AMutexBodyC>(AMutexLockFactory(recursive))
  {}
  

}
