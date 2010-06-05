#ifndef PCHILDTHREAD_HEADER
#define PCHILDTHREAD_HEADER
///////////////////////////////////////////////////
//! rcsid="$Id: ChildThread.hh 4 2001-04-11 12:45:55Z craftit $"

namespace PThread {

  template<class RetT,class DataT>
  class ChildThreadBodyC
    : public ThreadBodyC
  {
  public:
    ThreadBodyC(RetT (*func)(DataT dat))
    
  protected:
    virtual int Start();
    //: Called on startup.
    
    RetT (*func)(DataT dat);
    DataT param; // Paramiter.
    RetT ret;    // Returned value.
  };
  
  template<class RetT,class DataT>
  class ChildThreadC 
    : public ThreadC
  {
  public:
    ChildThreadC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    ChildThreadC(RetT (*func)(DataT dat))
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
  };

}

#endif
