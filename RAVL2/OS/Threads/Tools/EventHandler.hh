#ifndef RAVLEVENTHANDLER_HEADER
#define RAVLEVENTHANDLER_HEADER 1
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="amma/StdType/System/PThreads/Tools/EventHandler.hh"
//! lib=PThreadTools
//! userlevel=Normal
//! docentry="default.Charles Galambos"
//! author="Charles Galambos"
//! date="02/07/99"

#include "amma/PThread/MsgPipe.hh"
#include "amma/RCHandleA.hh"

namespace PThread
{
  //////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Signal Event handle
  
  class SignalEventBodyC
    : public BodyRefCounterVC
  {
  public:
    SignalEventBodyC()
      {}
    //: Default constructor.
    
    virtual void Invoke();
    //: Invoke event.
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  
  class SignalEventC
    : public RCHandleC<SignalEventBodyC>
  {
  public:
    SignalEventC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    SignalEventC(SignalEventBodyC &bod) 
      : RCHandleC<SignalEventBodyC>(bod)
      {}
    //: Body constructor.x
    
  public:
    void Invoke()
      { Body().Invoke(); }
    //: Invoke signal.
  };

  //////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Event handler.
  // Small object.
  
  class SignalEventHandlerC
  {
  public:
    SignalEventHandlerC(IntT qSize = 100)
      : events(qSize)
      {}
    //: Constructor.
    
    void Queue(const SignalEventC &se)
      { events.Put(se); }
    //: Queue an event.
    
    BooleanT TryQueue(const SignalEventC &se)
      { return events.TryPut(se); }
    //: Try and put an event in the queue.
    // Returns false if failed.
    
    int Process(int maxHandle = -1);
    //: Process event queue.
    // A maximum of maxHandle events are processed. (-1=Unlimited.)
    // returns the number of events handled.
    
  protected:
    MsgPipeC<SignalEventC> events;
  };

  //////////////////////////////////////////////////////

  
  //! userlevel=Normal
  //: Signal Event handle
  
  class SignalEventFunc0BodyC
    : public SignalEventBodyC
  {
  public:
    SignalEventFunc0BodyC(void (*nfunc)())
      : func(nfunc)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (*func)(); }
    //: Invoke event.
    
  protected:
    void (*func)();
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  
  class SignalEventFunc0C
    : public SignalEventC
  {
  public:
    SignalEventFunc0C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SignalEventFunc0C(void (*nfunc)())
      : SignalEventC(*new SignalEventFunc0BodyC(nfunc))
      {}
    //: Default constructor.
    // Creates an invalid handle.
  };

  //////////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class DataT>
  class SignalEventFunc1BodyC
    : public SignalEventBodyC
  {
  public:
    SignalEventFunc1BodyC(void (*nfunc)(DataT &),const DataT &ndat)
      : func(nfunc),
	dat(ndat)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (*func)(dat); }
    //: Invoke event.
    
  protected:
    void (*func)(DataT &);
    DataT dat;
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class DataT>
  class SignalEventFunc1C
    : public SignalEventC
  {
  public:
    SignalEventFunc1C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SignalEventFunc1C(void (*nfunc)(DataT &),const DataT &dat)
      : SignalEventC(*new SignalEventFunc1BodyC<DataT>(nfunc,dat))
      {}
    //: Default constructor.
    // Creates an invalid handle.
  };

  //////////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class Data1T,class Data2T>
  class SignalEventFunc2BodyC
    : public SignalEventBodyC
  {
  public:
    SignalEventFunc2BodyC(void (*nfunc)(Data1T &,Data2T &),const Data1T &ndat1,const Data2T &ndat2)
      : func(nfunc),
	dat1(ndat1),
	dat2(ndat2)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (*func)(dat1,dat2); }
    //: Invoke event.
    
  protected:
    void (*func)(Data1T &,Data2T &);
    Data1T dat1;
    Data2T dat2;
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class Data1T,class Data2T>
  class SignalEventFunc2C
    : public SignalEventC
  {
  public:
    SignalEventFunc2C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SignalEventFunc2C(void (*nfunc)(Data1T &,Data2T &),const Data1T &dat1,const Data2T &dat2)
      : SignalEventC(*new SignalEventFunc2BodyC<Data1T,Data2T>(nfunc,dat1,dat2))
      {}
    //: Default constructor.
    // Creates an invalid handle.
  };

  //////////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class Data1T,class Data2T,class Data3T>
  class SignalEventFunc3BodyC
    : public SignalEventBodyC
  {
  public:
    SignalEventFunc3BodyC(void (*nfunc)(Data1T &,Data2T &),const Data1T &ndat1,const Data2T &ndat2,const Data2T &ndat3)
      : func(nfunc),
	dat1(ndat1),
	dat2(ndat2),
	dat3(ndat3)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (*func)(dat1,dat2,dat3); }
    //: Invoke event.
    
  protected:
    void (*func)(Data1T &,Data2T &,Data3T &);
    Data1T dat1;
    Data2T dat2;
    Data3T dat3;
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class Data1T,class Data2T,class Data3T>
  class SignalEventFunc3C
    : public SignalEventC
  {
  public:
    SignalEventFunc3C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SignalEventFunc3C(void (*nfunc)(Data1T &,Data2T &),const Data1T &dat1,const Data2T &dat2,const Data3T &dat3)
      : SignalEventC(*new SignalEventFunc2BodyC<Data1T,Data2T>(nfunc,dat1,dat2,dat3))
      {}
    //: Default constructor.
    // Creates an invalid handle.
  };

  //////////////////////////////////////////////////////

  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class ObjT>
  class SignalEventMethod0BodyC
    : public SignalEventBodyC
  {
  public:
    SignalEventMethod0BodyC(const ObjT &nobj,void (ObjT::*nfunc)())
      : func(nfunc),
	obj(nobj)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (obj.*func)(); }
    //: Invoke event.
    
  protected:
    void (ObjT::*func)();
    ObjT obj;
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class ObjT>
  class SignalEventMethod0C
    : public SignalEventC
  {
  public:
    SignalEventMethod0C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SignalEventMethod0C(const ObjT &nobj,void (ObjT::*nfunc)())
      : SignalEventC(*new SignalEventMethod0BodyC<ObjT>(nobj,nfunc))
      {}
    //: Default constructor.
    // Creates an invalid handle.
  };

  /////////////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class ObjT,class DataT>
  class SignalEventMethod1BodyC
    : public SignalEventBodyC
  {
  public:
    SignalEventMethod1BodyC(const ObjT &nobj,void (ObjT::*nfunc)(DataT &),const DataT &ndat)
      : func(nfunc),
	obj(nobj),
	dat(ndat)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (obj.*func)(dat); }
    //: Invoke event.
    
  protected:
    void (ObjT::*func)(DataT &dat);
    ObjT obj;
    DataT dat;
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class ObjT,class DataT>
  class SignalEventMethod1C
    : public SignalEventC
  {
  public:
    SignalEventMethod1C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SignalEventMethod1C(const ObjT &nobj,void (ObjT::*nfunc)(DataT &), const DataT &dat)
      : SignalEventC(*new SignalEventMethod1BodyC<ObjT,DataT>(nobj,nfunc,dat))
      {}
    //: Default constructor.
    // Creates an invalid handle.
  };

  /////////////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T>
  class SignalEventMethod2BodyC
    : public SignalEventBodyC
  {
  public:
    SignalEventMethod2BodyC(const ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &),const Data1T &ndat1,const Data2T &ndat2)
      : func(nfunc),
	obj(nobj),
	dat1(ndat1),
	dat2(ndat2)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (obj.*func)(dat1,dat2); }
    //: Invoke event.
    
  protected:
    void (ObjT::*func)(Data1T &,Data2T &);
    ObjT obj;
    Data1T dat1;
    Data2T dat2;
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T>
  class SignalEventMethod2C
    : public SignalEventC
  {
  public:
    SignalEventMethod2C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SignalEventMethod2C(const ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &),const Data1T &ndat1,const Data2T &ndat2)
      : SignalEventC(*new SignalEventMethod2BodyC<ObjT,Data1T,Data2T>(nobj,nfunc,ndat1,ndat2))
      {}
    //: Default constructor.
    // Creates an invalid handle.
  };
  
  /////////////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T,class Data3T>
  class SignalEventMethod3BodyC
    : public SignalEventBodyC
  {
  public:
    SignalEventMethod3BodyC(const ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &,Data3T &),const Data1T &ndat1,const Data2T &ndat2,const Data3T &ndat3)
      : func(nfunc),
	obj(nobj),
	dat1(ndat1),
	dat2(ndat2),
	dat3(ndat3)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (obj.*func)(dat1,dat2,dat3); }
    //: Invoke event.
    
  protected:
    void (ObjT::*func)(Data1T &,Data2T &,Data3T &);
    ObjT obj;
    Data1T dat1;
    Data2T dat2;
    Data3T dat3;
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T,class Data3T>
  class SignalEventMethod3C
    : public SignalEventC
  {
  public:
    SignalEventMethod3C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SignalEventMethod3C(const ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &,Data3T &),const Data1T &ndat1,const Data2T &ndat2,const Data3T &ndat3)
      : SignalEventC(*new SignalEventMethod3BodyC<ObjT,Data1T,Data2T,Data3T>(nobj,nfunc,ndat1,ndat2,ndat3))
      {}
    //: Default constructor.
    // Creates an invalid handle.
  };
  
  /////////////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T>
  class SignalEventMethod4BodyC
    : public SignalEventBodyC
  {
  public:
    SignalEventMethod4BodyC(const ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &,Data3T &,Data4T &),const Data1T &ndat1,const Data2T &ndat2,const Data3T &ndat3,const Data4T &ndat4)
      : func(nfunc),
	obj(nobj),
	dat1(ndat1),
	dat2(ndat2),
	dat3(ndat3),
	dat4(ndat4)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (obj.*func)(dat1,dat2,dat3,dat4); }
    //: Invoke event.
    
  protected:
    void (ObjT::*func)(Data1T &,Data2T &,Data3T &,Data4T &);
    ObjT obj;
    Data1T dat1;
    Data2T dat2;
    Data3T dat3;
    Data4T dat4;
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T>
  class SignalEventMethod4C
    : public SignalEventC
  {
  public:
    SignalEventMethod4C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SignalEventMethod4C(const ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &,Data3T &,Data4T &),const Data1T &ndat1,const Data2T &ndat2,const Data3T &ndat3,const Data4T &ndat4)
      : SignalEventC(*new SignalEventMethod4BodyC<ObjT,Data1T,Data2T,Data3T,Data4T>(nobj,nfunc,ndat1,ndat2,ndat3,ndat4))
      {}
    //: Default constructor.
    // Creates an invalid handle.
  };
  
  /////////////////////////////////////////////////////////

  //! userlevel=Normal
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T,class Data5T>
  class SignalEventMethod5BodyC
    : public SignalEventBodyC
  {
  public:
    SignalEventMethod5BodyC(const ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &,Data3T &,Data4T &,Data5T &),const Data1T &ndat1,const Data2T &ndat2,const Data3T &ndat3,const Data4T &ndat4,const Data5T &ndat5)
      : func(nfunc),
	obj(nobj),
	dat1(ndat1),
	dat2(ndat2),
	dat3(ndat3),
	dat4(ndat4),
	dat5(ndat5)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (obj.*func)(dat1,dat2,dat3,dat4,dat5); }
    //: Invoke event.
    
  protected:
    void (ObjT::*func)(Data1T &,Data2T &,Data3T &,Data4T &,Data5T &);
    ObjT obj;
    Data1T dat1;
    Data2T dat2;
    Data3T dat3;
    Data4T dat4;
    Data4T dat5;
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T,class Data5T>
  class SignalEventMethod5C
    : public SignalEventC
  {
  public:
    SignalEventMethod5C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SignalEventMethod5C(const ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &,Data3T &,Data4T &,Data5T &),const Data1T &ndat1,const Data2T &ndat2,const Data3T &ndat3,const Data4T &ndat4,const Data5T &ndat5)
      : SignalEventC(*new SignalEventMethod5BodyC<ObjT,Data1T,Data2T,Data3T,Data4T,Data5T>(nobj,nfunc,ndat1,ndat2,ndat3,ndat4,ndat5))
      {}
    //: Default constructor.
    // Creates an invalid handle.
  };

  /////////////////////////////////////////////////////////
  
  inline
  SignalEventC SignalEvent(void (*nfunc)())
  { return SignalEventFunc0C(nfunc); }
  
  template<class DataT>
  SignalEventC SignalEvent(void (*nfunc)(DataT &dat),const DataT &dat)
  { return SignalEventFunc1C<DataT>(nfunc,dat); }
  
  template<class ObjT>
  SignalEventC SignalEvent(const ObjT &nobj,void (ObjT::*nfunc)())
  { return SignalEventMethod0C<ObjT>(nobj,nfunc); }

  template<class ObjT,class DataT>
  SignalEventC SignalEvent(const ObjT &nobj,void (ObjT::*nfunc)(DataT &),const DataT &dat)
  { return SignalEventMethod1C<ObjT,DataT>(nobj,nfunc,dat); }

  template<class ObjT,class Data1T,class Data2T>
  SignalEventC SignalEvent(const ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &),const Data1T &dat1,const Data2T &dat2)
  { return SignalEventMethod2C<ObjT,Data1T,Data2T>(nobj,nfunc,dat1,dat2); }
  
  template<class ObjT,class Data1T,class Data2T,class Data3T>
  SignalEventC SignalEvent(const ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &,Data3T &),const Data1T &dat1,const Data2T &dat2,const Data3T &dat3)
  { return SignalEventMethod3C<ObjT,Data1T,Data2T,Data3T>(nobj,nfunc,dat1,dat2,dat3); }
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T>
  SignalEventC SignalEvent(const ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &,Data3T &,Data4T &),const Data1T &dat1,const Data2T &dat2,const Data3T &dat3,const Data4T &dat4)
  { return SignalEventMethod4C<ObjT,Data1T,Data2T,Data3T,Data4T>(nobj,nfunc,dat1,dat2,dat3,dat4); }

  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T,class Data5T>
  SignalEventC SignalEvent(const ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &,Data3T &,Data4T &,Data5T &),const Data1T &dat1,const Data2T &dat2,const Data3T &dat3,const Data4T &dat4,const Data5T &dat5)
  { return SignalEventMethod5C<ObjT,Data1T,Data2T,Data3T,Data4T,Data5T>(nobj,nfunc,dat1,dat2,dat3,dat4,dat5); }
  
}


#endif
