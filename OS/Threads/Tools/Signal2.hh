// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SIGNAL2_HEADER
#define RAVL_SIGNAL2_HEADER 1
/////////////////////////////////////////////////////
//! docentry="Ravl.OS.Signals"
//! rcsid="$Id$"
//! file="Ravl/OS/Threads/Tools/Signal2.hh"
//! lib=RavlThreads
//! author="Charles Galambos"
//! date="23/09/1999"
//! example=exSignal1.cc

#include "Ravl/Threads/Signal1.hh"
#include "Ravl/IntrDLIter.hh"

// Fix for Visual C++ which doesn't like default values for
// some templated arguments. 
#ifndef VISUAL_CPP
#define VCPPARGFIX(x) x
#else
#define VCPPARGFIX(x)
#endif

namespace RavlN {
  
  template<class Data1T,class Data2T> class Signal2C;
  
  ////////////////////////////////////////////////////
  //! userlevel=Develop
  //: Signal 1 connector.
  
  template<class Data1T,class Data2T>
  class SignalConnector2BodyC
    : virtual public SignalConnector1BodyC<Data1T>
  {
  public:    
    inline SignalConnector2BodyC(const Data1T &def1,const Data2T &def2)
      : SignalConnector1BodyC<Data1T>(def1),
	defaultVal2(def2)
      {}
    //: Constructor.
    
    inline SignalConnector2BodyC(Signal0C &from)
      : SignalConnector0BodyC(from),
	SignalConnector1BodyC<Data1T>(from)
      {}
    //: Constructor.
    
    inline SignalConnector2BodyC(Signal0C &from,const Data1T &def1,const Data2T &def2)
      : SignalConnector0BodyC(from),
	SignalConnector1BodyC<Data1T>(from,def1),
	defaultVal2(def2)
    {}
    //: Constructor.
    
    virtual bool Invoke(Data1T &,Data2T &) = 0;
    //: Pass signal on.
    
    virtual bool Invoke(Data1T &d1)
    { return Invoke(d1,defaultVal2); }
    //: Pass signal on, use default value.
    
    virtual bool Invoke()
    { return Invoke(defaultVal,defaultVal2); }
    //: Pass signal on, use default value.
    
  protected:
    Data2T defaultVal2;
  };
  
  //! userlevel=Develop
  //: Signal 2 inter connector.
  
  template<class Data1T,class Data2T>
  class SignalInterConnect2BodyC
    : virtual public SignalConnector2BodyC<Data1T,Data2T>,
      virtual public SignalInterConnect0BodyC
  {
  public:
    SignalInterConnect2BodyC()
    {}
    //: Constructor.
    
    SignalInterConnect2BodyC(Signal0C &from,Signal2C<Data1T,Data2T> &targ);
    //: Constructor.
    
    inline virtual bool Invoke(Data1T &,Data2T &);
    //: Invoke signal, with value.
    
    inline virtual bool Invoke(Data1T &);
    //: Invoke signal, with value.
    
    inline virtual bool Invoke();
    //: Invoke signal, with default value.
  };
  
  ///////////////////////////
  //! userlevel=Advanced
  //: class for signal interconnector with 1 arg.
  
  template<class Data1T,class Data2T>
  class SignalInterConnect2C
    : public SignalConnectorC
  {
  public:
    SignalInterConnect2C(Signal0C &from,Signal2C<Data1T,Data2T> &targ)
      : SignalConnectorC(*new SignalInterConnect2BodyC<Data1T,Data2T>(from,targ))
    {}
    //: Constructor.
  };
  
  ///////////////////////////////////////////////////
  //! userlevel=Develop
  //: Signal 1 function connector.
  
  template<class Data1T,class Data2T>
  class Signal2FuncBodyC
    : public SignalConnector2BodyC<typename TraitsC<Data1T>::BaseTypeT,typename TraitsC<Data2T>::BaseTypeT>
  {
  public:
    typedef typename TraitsC<Data1T>::BaseTypeT Arg1T; //: Type of arguments without const's and refs.
    typedef typename TraitsC<Data2T>::BaseTypeT Arg2T; //: Type of arguments without const's and refs.
    typedef bool (*Func2T)(Data1T,Data2T);
    
    Signal2FuncBodyC(Signal0C &from,Func2T nFunc,const Arg1T &def1,const Arg2T &def2)
      : SignalConnector0BodyC(from),
	SignalConnector1BodyC<typename TraitsC<Data1T>::BaseTypeT>(from,def1),
	SignalConnector2BodyC<typename TraitsC<Data1T>::BaseTypeT,typename TraitsC<Data2T>::BaseTypeT>(from,def1,def2),
	func(nFunc)
    {}
    //: Constructor.
    
    virtual bool Invoke()
    { return func(defaultVal,defaultVal2); }
    //: Call function.
    // Use default value.
    
    virtual bool Invoke(Arg1T &val)
    { return func(val,defaultVal2); }
    //: Call function.
    
    virtual bool Invoke(Arg1T &val1,Arg2T &val2)
    { return func(val1,val2); }
    //: Call function.
    
  protected:
    Func2T func;
  };
  
  //! userlevel=Advanced
  //: Signal a function
  
  template<class Data1T,class Data2T>
  class Signal2FuncC 
    : public SignalConnectorC
  {
  public:
    typedef typename TraitsC<Data1T>::BaseTypeT Arg1T; //: Type of arguments without const's and refs.
    typedef typename TraitsC<Data2T>::BaseTypeT Arg2T; //: Type of arguments without const's and refs.
    
    Signal2FuncC(Signal0C &from,typename Signal2FuncBodyC<Data1T,Data2T>::Func2T nFunc,const Arg1T &def1 = Arg1T(),const Arg2T &def2 = Arg2T())
      : SignalConnectorC(*new Signal2FuncBodyC<Data1T,Data2T>(from,nFunc,def1,def2))
      {}
    //: Constructor.
  };
  
  ///////////////////////////////////////////////////
  //! userlevel=Develop
  //: Signal 2 method connector.
  
  template<class Data1T,class Data2T,class ObjT>
  class Signal2MethodBodyC
    : public SignalConnector2BodyC<typename TraitsC<Data1T>::BaseTypeT,typename TraitsC<Data2T>::BaseTypeT>
  {
  public:
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Type of object without const's and refs.
    typedef typename TraitsC<Data1T>::BaseTypeT Arg1T; //: Type of arguments without const's and refs.
    typedef typename TraitsC<Data2T>::BaseTypeT Arg2T; //: Type of arguments without const's and refs.
#if !RAVL_COMPILER_VISUALCPP 
    typedef bool (BaseObjT::*Func2T)(Data1T,Data2T);
#else
    typedef bool (ObjT::*Func2T)(Data1T,Data2T);
#endif
    
    Signal2MethodBodyC(Signal0C &from,
		       BaseObjT &nobj,
		       typename Signal2MethodBodyC<Data1T,Data2T,ObjT>::Func2T nFunc,
		       const Arg1T &dat1 = Arg1T(),
		       const Arg2T &dat2 = Arg2T())
      : SignalConnector0BodyC(from),
	SignalConnector1BodyC<typename TraitsC<Data1T>::BaseTypeT>(from,dat1),
	SignalConnector2BodyC<typename TraitsC<Data1T>::BaseTypeT,typename TraitsC<Data2T>::BaseTypeT>(from,dat1,dat2),
	obj(nobj),
	func(nFunc)
    {}
    //: Constructor.
    
    virtual bool Invoke()
    { return (obj.*func)(defaultVal,defaultVal2); }
    //: Call function.
    
    virtual bool Invoke(Arg1T &val)
      { return (obj.*func)(val,defaultVal2); }
    //: Call function.
    
    virtual bool Invoke(Arg1T &val1,Arg2T &val2)
      { return (obj.*func)(val1,val2); }
    //: Call function.
    
  protected:
    ObjT obj;
    Func2T func;
  };
  
  //! userlevel=Advanced
  //: Signal a method.
  
  template<class Data1T,class Data2T,class ObjT>
  class Signal2MethodC
    : public SignalConnectorC
  {
  public:
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Type of object without const's and refs.
    typedef typename TraitsC<Data1T>::BaseTypeT Arg1T; //: Type of arguments without const's and refs.
    typedef typename TraitsC<Data2T>::BaseTypeT Arg2T; //: Type of arguments without const's and refs.
    
    Signal2MethodC(Signal0C &from,
		   BaseObjT &nobj,
		   typename Signal2MethodBodyC<Data1T,Data2T,ObjT>::Func2T nFunc,
		   const Arg1T &dat1 = Arg1T(),
		   const Arg2T &dat2 = Arg2T())
      : SignalConnectorC(*new Signal2MethodBodyC<Data1T,Data2T,ObjT>(from,nobj,nFunc,dat1,dat2))
      {}
    //: Constructor.
  };
  
  ////////////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Signal 1 body.
  
  template<class Data1T,class Data2T>
  class Signal2BodyC
    : public Signal1BodyC<Data1T>
  {
  public:
    Signal2BodyC(const Data1T &def1,const Data2T &def2)
      : Signal1BodyC<Data1T>(def1), 
	defaultVal2(def2)     
      {}
    //: Constructor.
    
    virtual bool Invoke(Data1T &v1,Data2T &v2) {
      RWLockHoldC hold(access,true);
      SArray1dIterC<SignalConnectorC> it(outputs);
      hold.Unlock();
      // Flag that we're executing signal code.
      // This is used to ensure all threads have left the signal handlers
      // before they are disconnected.
      RWLockHoldC holdExec(execLock,RWLOCK_READONLY);
      bool ret = true;
      for(;it;it++) {
	SignalConnector2BodyC<Data1T,Data2T> *sc2 = dynamic_cast<SignalConnector2BodyC<Data1T,Data2T> *>(&it.Data().Body());
	if(sc2 != 0) {
	  ret &= sc2->Invoke(v1,v2);
	  continue;
	}
	SignalConnector1BodyC<Data1T> *sc1 = dynamic_cast<SignalConnector1BodyC<Data1T> *>(&it.Data().Body());
	if(sc1 != 0) {
	  ret &= sc1->Invoke(v1);
	  continue;
	}
	// Must be a 0.
	ret &= it.Data().Invoke();
      }
      return ret;
    }
    //: Send signal with value.
    
    virtual bool Invoke(Data1T &v1)
      { return Signal2BodyC<Data1T,Data2T>::Invoke(v1,defaultVal2); }
    //: Send signal with value.
    
    virtual bool Invoke()
      { return Signal2BodyC<Data1T,Data2T>::Invoke(defaultVal,defaultVal2); }
    //: Send signal with default value where needed.
    
  protected:
    Data2T defaultVal2; // Default data value.
  };
  
  //! userlevel=Normal
  //: Signal with 2 arguments
  
  template<class Data1T,class Data2T>
  class Signal2C
    : public Signal1C<Data1T>
  {
  public:
    typedef bool (*Func2T)(Data1T &dat1,Data2T &dat2);
    
    Signal2C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    Signal2C(const Data1T &def1,const Data2T &def2 = Data2T())
      : Signal1C<Data1T>(*new Signal2BodyC<Data1T,Data2T>(def1,def2))
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    Signal2C(const Signal0C &base)
      : Signal1C<Data1T>(base)
      {
	if(dynamic_cast<const Signal2BodyC<Data1T,Data2T> *>(&Signal0C::Body()) == 0)
	  Invalidate();
      }
    //: Base constructor.
    // Creates an invalid handle if body type
    // is correct.
    
  protected:
    Signal2C(Signal2BodyC<Data1T,Data2T> &sig)
      : Signal1C<Data1T>(sig)
      {}
    //: Body constructor.
    
    inline 
      Signal2BodyC<Data1T,Data2T> &Body() 
      { return static_cast<Signal2BodyC<Data1T,Data2T> &>(Signal0C::Body()); }
  //: Access body.
    
    inline 
      const Signal2BodyC<Data1T,Data2T> &Body() const 
      { return static_cast<const Signal2BodyC<Data1T,Data2T> &>(Signal0C::Body()); }
    //: Access body.
    
  public:
    inline bool Invoke(Data1T &dat1,Data2T &dat2)
      { return Body().Invoke(dat1,dat2); }
    //: Send default signal.
    
    inline bool operator()(Data1T &dat1,Data2T &dat2)
      { return Body().Invoke(dat1,dat2); }
    //: Simple invokation.
    
    inline bool operator()(const Data1T &dat1,const Data2T &dat2) { 
      Data1T tmp1(dat1);
      Data2T tmp2(dat2);
      return Body().Invoke(tmp1,tmp2); 
    }
    //: Simple invokation.  
  };
  
  template<class Data1T,class Data2T>
  ostream &operator<<(ostream &out,const Signal2C<Data1T,Data2T> &) { 
    RavlAssert(0); // Not implemented.
    return out;
  }
  //! userlevel=Normal
  //: IO Operator.
  // Not implemented
  
  ////////////////////////////
  
  template<class Data1T,class Data2T>
  SignalInterConnect2BodyC<Data1T,Data2T>::SignalInterConnect2BodyC(Signal0C &from,Signal2C<Data1T,Data2T> &targ)
    : SignalConnector0BodyC(from),
      SignalConnector1BodyC<Data1T>(from),
      SignalConnector2BodyC<Data1T,Data2T>(from),
      SignalInterConnect0BodyC(from,targ)
  {}
    
  template<class Data1T,class Data2T>
  inline 
  bool SignalInterConnect2BodyC<Data1T,Data2T>::Invoke(Data1T &dat1,Data2T &dat2) {
    //RavlAssert(dynamic_cast<Signal2BodyC<Data1T,Data2T> *>(&Target()) != 0);
    return dynamic_cast<Signal2BodyC<Data1T,Data2T> &>(Target()).Invoke(dat1,dat2);
  }
  
  template<class Data1T,class Data2T>
  inline
  bool SignalInterConnect2BodyC<Data1T,Data2T>::Invoke(Data1T &dat1) { 
    //RavlAssert(dynamic_cast<Signal2BodyC<Data1T,Data2T> *>(&Target()) != 0);
    return dynamic_cast<Signal2BodyC<Data1T,Data2T> &>(Target()).Invoke(dat1,defaultVal2);
  }
  
  template<class Data1T,class Data2T>
  inline
  bool SignalInterConnect2BodyC<Data1T,Data2T>::Invoke()
  { return Invoke(defaultVal,defaultVal2); }
  
  ///////////////////////
  
  template<class Data1T,class Data2T>
  inline SignalConnectorC Connect(Signal0C &from,Signal2C<Data1T,Data2T> &oth) { 
    RavlAssertMsg(from.IsValid(),"Source signal not valid.");
    RavlAssertMsg(oth.IsValid(),"Destination signal not valid.");
    return SignalInterConnect2C<Data1T,Data2T>(from,oth);
  }
  //! userlevel=Normal
  //: Connect a signal to another signal.
  
  template<class Data1T,class Data2T>  
  inline 
  SignalConnectorC Connect(Signal0C &from,bool (*func)(Data1T,Data2T),
			   const typename TraitsC<Data1T>::BaseTypeT &def1 VCPPARGFIX(=typename TraitsC<Data1T>::BaseTypeT()),
			   const typename TraitsC<Data2T>::BaseTypeT &def2 VCPPARGFIX(=typename TraitsC<Data2T>::BaseTypeT())
			   ) { 
    RavlAssertMsg(from.IsValid(),"Source signal not valid.");
    return Signal2FuncC<Data1T,Data2T>(from,func,def1,def2);  
  }
  //! userlevel=Normal
  //: Connect a signal to a function.

  template<class Data1T,class Data2T,class ObjT>
  inline
  SignalConnectorC Connect(Signal0C &from,const ObjT &obj,bool (ObjT::* func)(Data1T,Data2T),
			   const typename TraitsC<Data1T>::BaseTypeT &def1 VCPPARGFIX(=typename TraitsC<Data1T>::BaseTypeT()),
			   const typename TraitsC<Data2T>::BaseTypeT &def2 VCPPARGFIX(=typename TraitsC<Data2T>::BaseTypeT())) {
    RavlAssertMsg(from.IsValid(),"Source signal not valid.");
    return Signal2MethodC<Data1T,Data2T,ObjT>(from,const_cast<typename TraitsC<ObjT>::BaseTypeT &>(obj),func,def1,def2); 
  }
  //! userlevel=Normal
  //: Connect a signal to a method.
  
  template<class Data1T,class Data2T,class ObjT>
  inline
  SignalConnectorC ConnectRef(Signal0C &from,ObjT &obj,bool (ObjT::* func)(Data1T,Data2T),
			      const typename TraitsC<Data1T>::BaseTypeT &def1 VCPPARGFIX(=typename TraitsC<Data1T>::BaseTypeT()),
			      const typename TraitsC<Data2T>::BaseTypeT &def2 VCPPARGFIX(=typename TraitsC<Data2T>::BaseTypeT())) {
    RavlAssertMsg(from.IsValid(),"Source signal not valid.");
    return Signal2MethodC<Data1T,Data2T,ObjT &>(from,obj,func,def1,def2); 
  }
  //! userlevel=Normal
  //: Connect to a method.
  // Uses reference to object not instance. <p>
  // NB. It is the users responsibility to ensure the object
  // remains valid while being used.

  template<class Data1T,class Data2T,class ObjT>
  inline
  SignalConnectorC ConnectR(Signal0C &from,ObjT &obj,bool (ObjT::* func)(Data1T,Data2T),
			    const typename TraitsC<Data1T>::BaseTypeT &def1 VCPPARGFIX(=typename TraitsC<Data1T>::BaseTypeT()),
			    const typename TraitsC<Data2T>::BaseTypeT &def2 VCPPARGFIX(=typename TraitsC<Data2T>::BaseTypeT())) {
    RavlAssertMsg(from.IsValid(),"Source signal not valid.");
    return Signal2MethodC<Data1T,Data2T,ObjT &>(from,obj,func,def1,def2); 
  }
  //! userlevel=Normal
  //: Connect to a method.
  // Uses reference to object not instance. <p>
  // NB. It is the users responsibility to ensure the object
  // remains valid while being used.

};

#undef VCPPARGFIX
#endif
