// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_THREADMSGQUEUE_HEADER 
#define RAVL_THREADMSGQUEUE_HEADER 1
/////////////////////////////////////////////////////////////////////
//! author="Charles Galambos"
//! date="25/11/1995"
//! docentry="Ravl.OS.Threads"
//! rcsid="$Id$"
//! file="Ravl/OS/Threads/Tools/MessageQueue.hh"
//! lib=RavlThreads

#include "Ravl/Threads/Mutex.hh"
#include "Ravl/Threads/Semaphore.hh"

#if RAVL_HAVE_ANSICPPHEADERS
#include <new>
#else
#include <new.h>
#endif


namespace RavlN
{
  
  //////////////////////
  //! userlevel=Develop
  //: MessageQueue base class.
  // SMALL OBJECT. <p>
  
  class MessageQueueBaseC {
  public:
    MessageQueueBaseC(int nMaxSize = 10) 
      : putSema(nMaxSize), 
        ready(0),
        maxSize(nMaxSize + 2),
        head(0),
        tail(0)
    { RavlAssert(nMaxSize > 0); }
    //: Default constructor.
    
    MessageQueueBaseC(const MessageQueueBaseC &) 
      : putSema(0),
	ready(0),
	maxSize(0)
    { RavlAssert(0); } 
    // Not supported !
    
    void Dump(void) const; 
    //: Dump contents to stdout.
    
    IntT MaxSize() const { return maxSize; }
    //: Get size of pipe.
    
  protected:
    inline bool IsSpace() const;
    // Is space to data into ring ?
    
    inline bool IsEmptyBase() const;
    // Is space to data into ring ?
    
    MutexC access;      // Access control.
    SemaphoreC putSema; // Used to limit the size of the queue.
    SemaphoreC ready;   // Used to signal queue is not empty.
    const IntT maxSize;
    volatile IntT head;
    volatile IntT tail;
  };
  
  //////////////////////
  //! userlevel=Normal
  //: Thread safe queue.
  // This is designed to be used in inter-thread communication.
  // And number of threads can get and put from the queue. The queue is
  // of a fixed length to provide some flow control in the program. 
  // SMALL OBJECT.
  
  template<class T>
  class MessageQueueC 
    : public MessageQueueBaseC
  {
  public:
    MessageQueueC(int nMaxSize = 10);
    //: Default constructor.
    
    MessageQueueC(const MessageQueueC<T> &) { RavlAssert(0); }// Not supported !
    //: Copy constructor.
    
    ~MessageQueueC();
    //: Destructor.
    
    inline void Put(const T &Data);
    //: Put data into queue.
    
    inline bool TryPut(const T &Data);
    //: Try an put data in queue if there's space.
    // Ret:true = Data in queue. Ret:false = data not in queue.
    
    inline T Get();
    //: Get data from queue.
    
    inline bool TryGet(T &Data);
    //: Try and get data from queue.
    // Ret:false = No data available.
    
    inline bool IsElm();
    //: Is there data in the queue ?

    bool IsEmpty()
    { return !IsElm(); }
    //: Is the queue empty ?
    
    inline int Size();
    //: How much data is there in the queue.
    
    void Empty();
    //: Empty pipe of all its contents.
    
  private:
    T *data;
  };
  
  //////////////////////////////////////////////////////////////
  
  inline 
  bool MessageQueueBaseC::IsSpace() const {
    IntT nHead = head + 1;
    if(nHead >= MaxSize())
      nHead = 0;
    return (nHead != tail);
  }
  
  inline 
  bool MessageQueueBaseC::IsEmptyBase() const  
  { return head == tail; }

  //////////////////////////////////////////////////////////////
  
  template<class T>
  MessageQueueC<T>::MessageQueueC(int nMaxSize)  
    : MessageQueueBaseC(nMaxSize),
      data((T *) new char[(nMaxSize + 2) * sizeof(T)])
  {}
  
  template<class T>
  MessageQueueC<T>::~MessageQueueC() { 
    Empty();
    delete [] (char *) data; 
  }
  
  // Put data into queue.
  
  template<class T>
  inline void MessageQueueC<T>::Put(const T &Data)  {
    putSema.Wait();
    MutexLockC lock(access);
    new((void *) &(data[head])) T(Data); // Possible exception.
    // If exception constructing object following code won't be called.
    head++;
    if(head >= MaxSize())
      head = 0;
    lock.Unlock();
    ready.Post();
  }
  
  /////////////////////////
  // Try an put data in queue if there's space.
  // Ret:true = Data in queue. Ret:false = data not in queue.
  
  template<class T>
  inline bool MessageQueueC<T>::TryPut(const T &Data)  {
    if(!putSema.TryWait()) 
      return false;
    MutexLockC lock(access);
    new((void *) &(data[head])) T(Data); // Possible exception.
    // If exception constructing object following code won't be called.
    head++;
    if(head >= MaxSize())
      head = 0;  
    lock.Unlock();
    ready.Post();
    return true;
  }

  /////////////////////////
  // Get data from queue.
  
  template<class T>
  inline T MessageQueueC<T>::Get()  {
    ready.Wait();
    MutexLockC lock(access);
    RavlAssert(!IsEmptyBase());
    T Ret = data[tail]; // Possible exception.
    // If copy failed we're in trouble anyway.
    data[tail].~T(); // Possible exception.
    tail++;
    if(tail >= MaxSize())
      tail = 0;  
    lock.Unlock();
    putSema.Post();
    return Ret;
  }
  
  ///////////////////////////
  // Try and get data from queue.
  // Ret:false = No data available.
  
  template<class T>
  inline 
  bool MessageQueueC<T>::TryGet(T &Data)  {
    if(!ready.TryWait())
      return false;
    MutexLockC lock(access);
    // If copy failed we're in trouble anyway.
    Data = data[tail]; // Possible exception.
    data[tail].~T();   // Possible exception.
    tail++;
    if(tail >= MaxSize())
      tail = 0;  
    lock.Unlock();
    putSema.Post();
    return true;
  }
  
  //: Empty pipe of all its contents.
  template<class T>
  void MessageQueueC<T>::Empty() {
    while(IsElm())
      Get();
  }
  
  
  /////////////////////////
  // Is there data in the queue ?
  
  template<class T>
  inline 
  bool MessageQueueC<T>::IsElm()  { 
    MutexLockC lock(access);
    return !IsEmptyBase();
    // Unlock here.
  }
  
  /////////////////////////
  // How much data is there in the queue.
  
  template<class T>
  inline 
  int MessageQueueC<T>::Size()  {
    MutexLockC lock(access);
    if(head >= tail)
      return head-tail;
    return (MaxSize() - tail) + head;
    // Unlock here.
  }
  
};
#endif
