#ifndef DPEVENTHANDLERREF_HEADER
#define DPEVENTHANDLERREF_HEADER 1
/////////////////////////////////////////////////////////////
//! file="amma/StdType/System/PThreads/Tools/EventHandlerRef.hh"
//! lib=PThreadTools
//! userlevel=Normal
//! docentry="default.Charles Galambos"
//! rcsid="$Id: EventHandlerRef.hh 1466 2002-07-29 11:58:25Z craftit $"
//! author="Charles Galambos"
//! date="25/05/2000"

#include "amma/PThread/EventHandler.hh"

namespace PThread
{
  
  //! userlevel=Normal
  //: Signal Event handle
  // Use a reference (&) to the target object.
  // NB. Will not keep a reference to big objects.
   
  template<class ObjT>
  class SignalEventMethodRef0BodyC
    : public SignalEventBodyC
  {
  public:
    SignalEventMethodRef0BodyC(ObjT &nobj,void (ObjT::*nfunc)())
      : func(nfunc),
	obj(nobj)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (obj.*func)(); }
    //: Invoke event.
    
  protected:
    void (ObjT::*func)();
    ObjT &obj;
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class ObjT>
  class SignalEventMethodRef0C
    : public SignalEventC
  {
  public:
    SignalEventMethodRef0C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SignalEventMethodRef0C(ObjT &nobj,void (ObjT::*nfunc)())
      : SignalEventC(*new SignalEventMethodRef0BodyC<ObjT>(nobj,nfunc))
      {}
    //: Default constructor.
    // Creates an invalid handle.
  };

  /////////////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Signal Event handle
  // Use a reference (&) to the target object.
  // NB. Will not keep a reference to big objects.
  
  template<class ObjT,class DataT>
  class SignalEventMethodRef1BodyC
    : public SignalEventBodyC
  {
  public:
    SignalEventMethodRef1BodyC(ObjT &nobj,void (ObjT::*nfunc)(DataT &),const DataT &ndat)
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
    ObjT &obj;
    DataT dat;
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  
  template<class ObjT,class DataT>
  class SignalEventMethodRef1C
    : public SignalEventC
  {
  public:
    SignalEventMethodRef1C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SignalEventMethodRef1C(ObjT &nobj,void (ObjT::*nfunc)(DataT &), const DataT &dat)
      : SignalEventC(*new SignalEventMethodRef1BodyC<ObjT,DataT>(nobj,nfunc,dat))
      {}
    //: Default constructor.
    // Creates an invalid handle.
  };

  /////////////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Signal Event handle
  // Use a reference (&) to the target object.
  // NB. Will not keep a reference to big objects.
  
  template<class ObjT,class Data1T,class Data2T>
  class SignalEventMethodRef2BodyC
    : public SignalEventBodyC
  {
  public:
    SignalEventMethodRef2BodyC(ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &),const Data1T &ndat1,const Data2T &ndat2)
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
    ObjT &obj;
    Data1T dat1;
    Data2T dat2;
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  // Use a reference (&) to the target object.
  // NB. Will not keep a reference to big objects.
  
  template<class ObjT,class Data1T,class Data2T>
  class SignalEventMethodRef2C
    : public SignalEventC
  {
  public:
    SignalEventMethodRef2C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SignalEventMethodRef2C(ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &),const Data1T &ndat1,const Data2T &ndat2)
      : SignalEventC(*new SignalEventMethodRef2BodyC<ObjT,Data1T,Data2T>(nobj,nfunc,ndat1,ndat2))
      {}
    //: Default constructor.
    // Creates an invalid handle.
  };
  
  /////////////////////////////////////////////////////////
  
  //! userlevel=Normal
  //: Signal Event handle
  // Use a reference (&) to the target object.
  // NB. Will not keep a reference to big objects.
  
  template<class ObjT,class Data1T,class Data2T,class Data3T>
  class SignalEventMethodRef3BodyC
    : public SignalEventBodyC
  {
  public:
    SignalEventMethodRef3BodyC(ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &,Data3T &),const Data1T &ndat1,const Data2T &ndat2,const Data3T &ndat3)
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
    ObjT &obj;
    Data1T dat1;
    Data2T dat2;
    Data3T dat3;
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  // Use a reference (&) to the target object.
  // NB. Will not keep a reference to big objects.
  
  template<class ObjT,class Data1T,class Data2T,class Data3T>
  class SignalEventMethodRef3C
    : public SignalEventC
  {
  public:
    SignalEventMethodRef3C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SignalEventMethodRef3C(ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &,Data3T &),const Data1T &ndat1,const Data2T &ndat2,const Data3T &ndat3)
      : SignalEventC(*new SignalEventMethodRef3BodyC<ObjT,Data1T,Data2T,Data3T>(nobj,nfunc,ndat1,ndat2,ndat3))
      {}
    //: Default constructor.
    // Creates an invalid handle.
  };
  
  /////////////////////////////////////////////////////////

  template<class ObjT>
  SignalEventC SignalEventRef(ObjT &nobj,void (ObjT::*nfunc)())
  { return SignalEventMethodRef0C<ObjT>(nobj,nfunc); }
  
  template<class ObjT,class DataT>
  SignalEventC SignalEventRef(ObjT &nobj,void (ObjT::*nfunc)(DataT &),const DataT &dat)
  { return SignalEventMethodRef1C<ObjT,DataT>(nobj,nfunc,dat); }

  template<class ObjT,class Data1T,class Data2T>
  SignalEventC SignalEventRef(ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &),const Data1T &dat1,const Data2T &dat2)
  { return SignalEventMethodRef2C<ObjT,Data1T,Data2T>(nobj,nfunc,dat1,dat2); }
  
  template<class ObjT,class Data1T,class Data2T,class Data3T>
  SignalEventC SignalEventRef(ObjT &nobj,void (ObjT::*nfunc)(Data1T &,Data2T &,Data3T &),const Data1T &dat1,const Data2T &dat2,const Data3T &dat3)
  { return SignalEventMethodRef3C<ObjT,Data1T,Data2T,Data3T>(nobj,nfunc,dat1,dat2,dat3); }
  
}

#endif
