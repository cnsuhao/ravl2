// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SIGNAL1_HEADER
#define RAVL_SIGNAL1_HEADER 1
/////////////////////////////////////////////////////
//! docentry="Ravl.OS.Signals"
//! rcsid="$Id$"
//! lib=RavlThreads
//! author="Charles Galambos"
//! date="23/09/1999"
//! file="Ravl/OS/Threads/Tools/Signal1.hh"
//! example=exSignal1.cc

#include "Ravl/Threads/Signal.hh"
#include "Ravl/Traits.hh"
#include "Ravl/IntrDLIter.hh"
#include "Ravl/Types.hh"

namespace RavlN {

  template<class DataT> class Signal1C;
  
  ////////////////////////////////////////////////////
  //! userlevel=Develop
  //: Signal 1 connector.
  
  template<class DataT>
  class SignalConnector1BodyC
    : virtual public SignalConnector0BodyC
  {
  public:
    inline SignalConnector1BodyC(const DataT &def)
      : defaultVal(def)
    {}
    //: Default constructor.
    
    inline SignalConnector1BodyC(Signal0C &from)
      : SignalConnector0BodyC(from)
    {}
    //: Constructor.
    
    inline SignalConnector1BodyC(Signal0C &from,const DataT &def)
      : SignalConnector0BodyC(from),
	defaultVal(def)
    {}
    //: Constructor.
    
    virtual bool Invoke(DataT &) = 0;
    //: Pass signal on.
    
    virtual bool Invoke()
    { return Invoke(defaultVal); }
    //: Pass signal on, use default value.
    
  protected:
    DataT defaultVal;
  };
  
  //! userlevel=Develop
  //: Signal 1 inter connector.
  
  template<class DataT>
  class SignalInterConnect1BodyC
    : virtual public SignalConnector1BodyC<DataT>,
      virtual public SignalInterConnect0BodyC
  {
  public:
    SignalInterConnect1BodyC()
    {}
    //: Constructor.
    
    SignalInterConnect1BodyC(Signal0C &from,Signal1C<DataT> &targ);
    //: Constructor.
    
    inline virtual bool Invoke(DataT &);
    //: Invoke signal, with value.
    
    inline virtual bool Invoke();
    //: Invoke signal, with default value.
  };

  ///////////////////////////
  //! userlevel=Advanced
  //: class for signal interconnector with 1 arg.
  
  template<class DataT>
  class SignalInterConnect1C
    : public SignalConnectorC
  {
  public:
    SignalInterConnect1C(Signal0C &from,Signal1C<DataT> &targ)
      : SignalConnectorC(*new SignalInterConnect1BodyC<DataT>(from,targ))
    {}
    //: Constructor.
  };
  
  ///////////////////////////////////////////////////
  //! userlevel=Develop
  //: Signal 1 function connector.
  
  template<class DataT>
  class Signal1FuncBodyC
    : public SignalConnector1BodyC<typename TraitsC<DataT>::BaseTypeT>
  {
  public:
    typedef typename TraitsC<DataT>::BaseTypeT Arg1T; //: Type of arguments without const's and refs.
    typedef bool (*Func1T)(DataT val);
    
    Signal1FuncBodyC(Signal0C &from,Func1T nFunc,const Arg1T &def)
      : SignalConnector0BodyC(from),
	SignalConnector1BodyC<typename TraitsC<DataT>::BaseTypeT>(from,def),
	func(nFunc)
    {}
    //: Constructor.
    
    virtual bool Invoke()
    { return func(defaultVal); }
    //: Call function.
    // Use default value.
    
    virtual bool Invoke(Arg1T &val)
    { return func(val); }
    //: Call function.
    
  protected:
    Func1T func;
  };
  
  //! userlevel=Advanced
  //: Signal a function
  
  template<class DataT>
  class Signal1FuncC 
    : public SignalConnectorC
  {
  public:
    typedef typename TraitsC<DataT>::BaseTypeT Arg1T; //: Type of arguments without const's and refs.
    
    Signal1FuncC(Signal0C &from,typename Signal1FuncBodyC<DataT>::Func1T nFunc,const Arg1T &def = Arg1T())
      : SignalConnectorC(*new Signal1FuncBodyC<DataT>(from,nFunc,def))
    {}
    //: Constructor.
  };
  
  ///////////////////////////////////////////////////
  //! userlevel=Develop
  //: Signal 1 method connector.
  
  template<class DataT,class ObjT>
  class Signal1MethodBodyC
    : public SignalConnector1BodyC<typename TraitsC<DataT>::BaseTypeT>
  {
  public:
    typedef typename TraitsC<DataT>::BaseTypeT Arg1T; //: Type of arguments without const's and refs.
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Type of object without const's and refs.
#if !RAVL_COMPILER_VISUALCPP 
    typedef bool (BaseObjT::*Func1T)(DataT dat);
#else
    typedef bool (ObjT::*Func1T)(DataT dat);
#endif
    
    Signal1MethodBodyC(Signal0C &from,
		       BaseObjT &nobj,
		       Func1T nFunc,
		       const Arg1T &dat = Arg1T())
      : SignalConnector0BodyC(from),
	SignalConnector1BodyC<typename TraitsC<DataT>::BaseTypeT>(from,dat),
	obj(nobj),
	func(nFunc)
    {}
    //: Constructor.
    
    virtual bool Invoke()
    { return (obj.*func)(defaultVal); }
    //: Call function.
    
    virtual bool Invoke(Arg1T &val)
    { return (obj.*func)(val); }
    //: Call function.
    
    inline bool operator()(Arg1T &val)
    { return Invoke(val); }
    //: Simple invokation.
    
  protected:
    ObjT obj;
    Func1T func;
  };
  
  //! userlevel=Advanced
  //: Signal a method.
  
  template<class DataT,class ObjT>
  class Signal1MethodC
    : public SignalConnectorC
  {
  public:
    typedef typename TraitsC<DataT>::BaseTypeT Arg1T; //: Type of arguments without const's and refs.
#if !RAVL_COMPILER_VISUALCPP 
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Type of object without const's and refs.
#else
    typedef ObjT BaseObjT; //: Type of object without const's and refs.
#endif
    
    Signal1MethodC(Signal0C &from,
		   BaseObjT &nobj,
		   typename Signal1MethodBodyC<DataT,ObjT>::Func1T nFunc,
		   const Arg1T &dat = Arg1T())
      : SignalConnectorC(*new Signal1MethodBodyC<DataT,ObjT>(from,nobj,nFunc,dat))
    {}
    //: Constructor.
  };
  
#if RAVL_COMPILER_VISUALCPP 
  ///////////////////////////////////////////////////
  //! userlevel=Develop
  //: Signal 1 method connector.
  
  template<class DataT,class ObjT>
  class Signal1MethodRefBodyC
    : public SignalConnector1BodyC<typename TraitsC<DataT>::BaseTypeT>
  {
  public:
    typedef typename TraitsC<DataT>::BaseTypeT Arg1T; //: Type of arguments without const's and refs.
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Type of object without const's and refs.
    typedef bool (ObjT::*Func1T)(DataT dat);
    
    Signal1MethodRefBodyC(Signal0C &from,
			  BaseObjT &nobj,
			  Func1T nFunc,
			  const Arg1T &dat = Arg1T())
      : SignalConnector0BodyC(from),
	SignalConnector1BodyC<typename TraitsC<DataT>::BaseTypeT>(from,dat),
	obj(nobj),
	func(nFunc)
    {}
    //: Constructor.
    
    virtual bool Invoke()
    { return (obj.*func)(defaultVal); }
    //: Call function.
    
    virtual bool Invoke(Arg1T &val)
    { return (obj.*func)(val); }
    //: Call function.
    
    inline bool operator()(Arg1T &val)
    { return Invoke(val); }
    //: Simple invokation.
    
  protected:
    ObjT &obj;
    Func1T func;
  };
  
  //! userlevel=Advanced
  //: Signal a method from a refrence to a class.
  
  template<class DataT,class ObjT>
  class Signal1MethodRefC
    : public SignalConnectorC
  {
  public:
    typedef typename TraitsC<DataT>::BaseTypeT Arg1T; //: Type of arguments without const's and refs.
    typedef ObjT BaseObjT; //: Type of object without const's and refs.
    
    Signal1MethodRefC(Signal0C &from,
		      BaseObjT &nobj,
		      typename Signal1MethodRefBodyC<DataT,ObjT>::Func1T nFunc,
		      const Arg1T &dat = Arg1T())
      : SignalConnectorC(*new Signal1MethodRefBodyC<DataT,ObjT>(from,nobj,nFunc,dat))
    {}
    //: Constructor.
  };

#endif
  
  ////////////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Signal 1 body.
  
  template<class DataT>
  class Signal1BodyC
    : public Signal0BodyC
  {
  public:
    Signal1BodyC(const DataT &def)
      : defaultVal(def)
    {}
    //: Constructor.
    
    virtual bool Invoke(DataT &v) {
      RWLockHoldC hold(access,true);
      SArray1dIterC<SignalConnectorC> it(outputs);
      hold.Unlock();
      // Flag that we're executing signal code.
      // This is used to ensure all threads have left the signal handlers
      // before they are disconnected.
      RWLockHoldC holdExec(execLock,RWLOCK_READONLY);
      bool ret = true;
      for(;it;it++) {
	SignalConnector1BodyC<DataT> *sc1 = dynamic_cast<SignalConnector1BodyC<DataT> *>(&it.Data().Body());
	if(sc1 != 0)
	  ret &= sc1->Invoke(v);
	else
	  ret &= it.Data().Invoke();
      }
      return ret;
    }
    //: Send signal with value.
    
    virtual bool Invoke() { 
      RWLockHoldC hold(access,true); 
      SArray1dIterC<SignalConnectorC> it(outputs);
      hold.Unlock();
      // Flag that we're executing signal code.
      // This is used to ensure all threads have left the signal handlers
      // before they are disconnected.
      RWLockHoldC holdExec(execLock,RWLOCK_READONLY);
      bool ret = true;
      for(;it;it++) {
	SignalConnector1BodyC<DataT> *sc1 = dynamic_cast<SignalConnector1BodyC<DataT> *>(&it.Data().Body());
	if(sc1 != 0)
	  ret &= sc1->Invoke(defaultVal);
	else
	  ret &= it.Data().Invoke();
      }
      return ret;
    }
    //: Send signal with default value where needed.
  
  protected:
    DataT defaultVal; // Default data value.
  };
  
  //! userlevel=Normal
  //: Signal with 1 argument
  
  template<class DataT>
  class Signal1C
    : public Signal0C
  {
  public:
    typedef bool (*Func1T)(DataT &dat);
    
    Signal1C()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    Signal1C(const Signal0C &base)
      : Signal0C(base)
    {
      if(dynamic_cast<const Signal1BodyC<DataT> *>(&Signal0C::Body()) == 0)
	Invalidate();
    }
    //: Base constructor.
    // Creates an invalid handle if body type
    // is correct.
    
    Signal1C(const DataT &defV)
      : Signal0C(*new Signal1BodyC<DataT>(defV))
    {}
    //: Constructor.
    // Creates a valid signal
    
  protected:
    Signal1C(Signal1BodyC<DataT> &sig)
      : Signal0C(sig)
    {}
    //: Body constructor.
    
    inline Signal1BodyC<DataT> &Body() 
    { return static_cast<Signal1BodyC<DataT> &>(Signal0C::Body()); }
    //: Access body.
    
    inline const Signal1BodyC<DataT> &Body() const 
    { return static_cast<const Signal1BodyC<DataT> &>(Signal0C::Body()); }
    //: Access body.
    
  public:
    inline bool Invoke(DataT &dat)
    { return Body().Invoke(dat); }
    //: Send default signal.
    
    inline bool operator()(DataT &dat)
    { return Body().Invoke(dat); }
    //: Simple invokation.
    
    inline bool operator()(const DataT &dat)
    { 
      DataT tmp(dat);
      return Body().Invoke(tmp); 
    }
    //: Simple invokation.  
  };
  
  
  template<class DataT>
  ostream &operator<<(ostream &out,const Signal1C<DataT> &) { 
    RavlAssert(0); // Not implemented.
    return out;
  }
  //: IO Operator.
  // Not implemented
  
  ////////////////////////////
  
  template<class DataT>
  SignalInterConnect1BodyC<DataT>::SignalInterConnect1BodyC(Signal0C &from,Signal1C<DataT> &targ)
    : SignalConnector0BodyC(from),
      SignalConnector1BodyC<DataT>(from),
      SignalInterConnect0BodyC(from,targ)
  {}
  
  template<class DataT>
  inline
  bool SignalInterConnect1BodyC<DataT>::Invoke(DataT &dat) { 
    RavlAssert(dynamic_cast<Signal1BodyC<DataT> *>(&Target()) != 0);
    return dynamic_cast<Signal1BodyC<DataT> &>(Target()).Invoke(dat);
  }
  
  template<class DataT>
  inline
  bool SignalInterConnect1BodyC<DataT>::Invoke()
  { return Invoke(defaultVal); }
  
  template<class DataT>
  inline 
  SignalConnectorC Connect(Signal0C &from,Signal1C<DataT> &oth) { 
    RavlAssert(from.IsValid());
    RavlAssert(oth.IsValid());
    return SignalInterConnect1C<DataT>(from,oth);  
  }
  //! userlevel=Normal  
  //: Connect two signals together.
  
  template<class DataT>  
  inline SignalConnectorC Connect(Signal0C &from,bool (*func)(DataT),
				  const typename TraitsC<DataT>::BaseTypeT &def = TraitsC<DataT>::BaseTypeT()) {
    RavlAssert(from.IsValid());
    return Signal1FuncC<DataT>(from,func,def);  
  }
  //! userlevel=Normal  
  //: Connect a signal to a function.
  
  template<class ObjT,class DataT>
  inline
  SignalConnectorC Connect(Signal0C &from,const ObjT &obj,bool (ObjT::* func)(DataT),
			   const typename TraitsC<DataT>::BaseTypeT &def = TraitsC<DataT>::BaseTypeT()) { 
    RavlAssert(from.IsValid());
    return Signal1MethodC<DataT,ObjT>(from,const_cast<ObjT &>(obj),func,def);
  } 
  //! userlevel=Normal  
  //: Connect a signal to a method.
  
  template<class ObjT,class DataT>
  inline
  SignalConnectorC ConnectRef(Signal0C &from,ObjT &obj,bool (ObjT::* func)(DataT),
			      const typename TraitsC<DataT>::BaseTypeT &def = TraitsC<DataT>::BaseTypeT()) { 
    RavlAssert(from.IsValid());
#if RAVL_COMPILER_VISUALCPP 
    return Signal1MethodRefC<DataT,ObjT>(from,obj,func,def);
#else
    return Signal1MethodC<DataT,ObjT &>(from,obj,func,def);
#endif
  }
  //! userlevel=Normal  
  //: Connect a signal to a method.
  // Uses reference to object not instance. <p>
  // NB. It is the users responsibility to ensure the object
  // remains valid while being used.
  
  template<class ObjT,class DataT>
  inline
  SignalConnectorC ConnectR(Signal0C &from,ObjT &obj,bool (ObjT::* func)(DataT),
			    const typename TraitsC<DataT>::BaseTypeT &def = TraitsC<DataT>::BaseTypeT()) { 
    RavlAssert(from.IsValid());
#if RAVL_COMPILER_VISUALCPP 
    return Signal1MethodRefC<DataT,ObjT>(from,obj,func,def);
#else
    return Signal1MethodC<DataT,ObjT &>(from,obj,func,def);    
#endif
  }
  //! userlevel=Normal  
  //: Connect a signal to a method.
  // Uses reference to object not instance. <p>
  // NB. It is the users responsibility to ensure the object
  // remains valid while being used.
}
#endif
