// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLSIGNAL2_HEADER
#define RAVLSIGNAL2_HEADER 1
/////////////////////////////////////////////////////
//! docentry="Ravl.OS.Signals"
//! rcsid="$Id$"
//! file="amma/StdType/MTDataProc/Signal2.hh"
//! lib=RavlThreads
//! author="Charles Galambos"
//! date="23/09/99"

#include "Ravl/Threads/Signal1.hh"
#include "Ravl/InDLIter.hh"

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
    //: Default constructor.
    
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
    
    virtual void Invoke(Data1T &,Data2T &) = 0;
    //: Pass signal on.
    
    virtual void Invoke(Data1T &d1)
      { Invoke(d1,defaultVal2); }
    //: Pass signal on, use default value.
    
    virtual void Invoke()
      { Invoke(defaultVal,defaultVal2); }
    //: Pass signal on, use default value.
    
  protected:
    Data2T defaultVal2;
  };
  
  //! userlevel=Develop
  //: Signal 1 inter connector.
  
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
    
    inline virtual void Invoke(Data1T &,Data2T &);
    //: Invoke signal, with value.
    
    inline virtual void Invoke(Data1T &);
    //: Invoke signal, with value.
    
    inline virtual void Invoke();
    //: Invoke signal, with default value.
  };
  
  ///////////////////////////
  //! userlevel=Normal
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
    : public SignalConnector2BodyC<Data1T,Data2T>
  {
  public:
    typedef void (*Func2T)(Data1T &val1,Data2T &val2);
    
    Signal2FuncBodyC(Signal0C &from,Func2T nFunc,const Data1T &def1,const Data2T &def2)
      : SignalConnector0BodyC(from),
      SignalConnector1BodyC<Data1T>(from,def1),
      SignalConnector2BodyC<Data1T,Data2T>(from,def1,def2),
      func(nFunc)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { func(defaultVal,defaultVal2); }
    //: Call function.
    // Use default value.
    
    virtual void Invoke(Data1T &val)
      { func(val,defaultVal2); }
    //: Call function.
    
    virtual void Invoke(Data1T &val1,Data2T &val2)
      { func(val1,val2); }
  //: Call function.
    
  protected:
    Func2T func;
  };
  
  //! userlevel=Normal
  //: Signal a function
  
  template<class Data1T,class Data2T>
  class Signal2FuncC 
    : public SignalConnectorC
  {
  public:
    Signal2FuncC(Signal0C &from,Signal2FuncBodyC<Data1T,Data2T>::Func2T nFunc,const Data1T &def1 = Data1T(),const Data2T &def2 = Data2T())
      : SignalConnectorC(*new Signal2FuncBodyC<Data1T,Data2T>(from,nFunc,def1,def2))
      {}
    //: Constructor.
  };
  
  ///////////////////////////////////////////////////
  //! userlevel=Develop
  //: Signal 2 method connector.
  
  template<class Data1T,class Data2T,class ObjT>
  class Signal2MethodBodyC
    : public SignalConnector2BodyC<Data1T,Data2T>
  {
  public:
    typedef void (ObjT::*Func2T)(Data1T &dat1,Data2T &dat2);
    
    Signal2MethodBodyC(Signal0C &from,
		       const ObjT &nobj,
		       Func2T nFunc,
		       const Data1T &dat1 = Data1T(),
		       const Data2T &dat2 = Data2T())
      : SignalConnector0BodyC(from),
      SignalConnector1BodyC<Data1T>(from,dat1),
      SignalConnector2BodyC<Data1T,Data2T>(from,dat1,dat2),
      obj(nobj),
      func(nFunc)
      {}
    //: Constructor.
  
    virtual void Invoke()
      { (obj.*func)(defaultVal,defaultVal2); }
    //: Call function.
    
    virtual void Invoke(Data1T &val)
      { (obj.*func)(val,defaultVal2); }
    //: Call function.

    virtual void Invoke(Data1T &val1,Data2T &val2)
      { (obj.*func)(val1,val2); }
    //: Call function.
    
  protected:
    ObjT obj;
    Func2T func;
  };
  
  //! userlevel=Normal
  //: Signal a method.
  
  template<class Data1T,class Data2T,class ObjT>
  class Signal2MethodC
    : public SignalConnectorC
  {
  public:
    Signal2MethodC(Signal0C &from,
		   const ObjT &nobj,
		   Signal2MethodBodyC<Data1T,Data2T,ObjT>::Func2T nFunc,
		   const Data1T &dat1 = Data1T(),
		   const Data2T &dat2 = Data2T())
      : SignalConnectorC(*new Signal2MethodBodyC<Data1T,Data2T,ObjT>(from,nobj,nFunc,dat1,dat2))
      {}
    //: Constructor.
  };
  
  ///////////////////////////////////////////////////
  //! userlevel=Develop
  //: Signal 2 method connector.
  // Uses refrence to object not instance. <p>
  // NB. It is the users responsibility to ensure the object
  // remains valid while being used.
  
  template<class Data1T,class Data2T,class ObjT>
  class Signal2MethodRefBodyC
    : public SignalConnector2BodyC<Data1T,Data2T>
  {
  public:
    typedef void (ObjT::*Func2T)(Data1T &dat1,Data2T &dat2);
    
    Signal2MethodRefBodyC(Signal0C &from,
			  ObjT &nobj,
			  Func2T nFunc,
			  const Data1T &dat1 = Data1T(),
			  const Data2T &dat2 = Data2T())
      : SignalConnector0BodyC(from),
      SignalConnector1BodyC<Data1T>(from,dat1),
      SignalConnector2BodyC<Data1T,Data2T>(from,dat1,dat2),
      obj(nobj),
      func(nFunc)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (obj.*func)(defaultVal,defaultVal2); }
    //: Call function.
    
    virtual void Invoke(Data1T &val)
      { (obj.*func)(val,defaultVal2); }
    //: Call function.
    
    virtual void Invoke(Data1T &val1,Data2T &val2)
      { (obj.*func)(val1,val2); }
    //: Call function.
    
  protected:
    ObjT &obj;
    Func2T func;
  };
  
  //! userlevel=Normal
  //: Signal a method.
  // Uses refrence to object not instance. <p>
  // NB. It is the users responsibility to ensure the object
  // remains valid while being used.
  
  template<class Data1T,class Data2T,class ObjT>
  class Signal2MethodRefC
    : public SignalConnectorC
  {
  public:
    Signal2MethodRefC(Signal0C &from,
		      ObjT &nobj,
		      Signal2MethodRefBodyC<Data1T,Data2T,ObjT>::Func2T nFunc,
		      const Data1T &dat1 = Data1T(),
		      const Data2T &dat2 = Data2T())
      : SignalConnectorC(*new Signal2MethodRefBodyC<Data1T,Data2T,ObjT>(from,nobj,nFunc,dat1,dat2))
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
    
    virtual void Invoke(Data1T &v1,Data2T &v2) {
      RWLockHoldC hold(access,true);
      SArray1dIterC<SignalConnectorC> it(outputs);
      hold.Unlock();
      for(;it;it++) {
	SignalConnector2BodyC<Data1T,Data2T> *sc2 = dynamic_cast<SignalConnector2BodyC<Data1T,Data2T> *>(&it.Data().Body());
	if(sc2 != 0) {
	  sc2->Invoke(v1,v2);
	  continue;
	}
	SignalConnector1BodyC<Data1T> *sc1 = dynamic_cast<SignalConnector1BodyC<Data1T> *>(&it.Data().Body());
	if(sc1 != 0) {
	  sc1->Invoke(v1);
	  continue;
	}
	// Must be a 0.
	it.Data().Invoke();
      }
    }
    //: Send signal with value.
    
    virtual void Invoke(Data1T &v1)
      { Signal2BodyC<Data1T,Data2T>::Invoke(v1,defaultVal2); }
    //: Send signal with value.
    
    virtual void Invoke()
      { Signal2BodyC<Data1T,Data2T>::Invoke(defaultVal,defaultVal2); }
    //: Send signal with default value where needed.
    
  protected:
    Data2T defaultVal2; // Default data value.
  };
  
  //! userlevel=Normal
  //: Signal 1 handle.
  
  template<class Data1T,class Data2T>
  class Signal2C
    : public Signal1C<Data1T>
  {
  public:
    typedef void (*Func2T)(Data1T &dat1,Data2T &dat2);
    
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
    inline void Invoke(Data1T &dat1,Data2T &dat2)
      { Body().Invoke(dat1,dat2); }
    //: Send default signal.
    
    inline void operator()(Data1T &dat1,Data2T &dat2)
      { Body().Invoke(dat1,dat2); }
    //: Simple invokation.
    
    inline void operator()(const Data1T &dat1,const Data2T &dat2) { 
      Data1T tmp1(dat1);
      Data2T tmp2(dat2);
      Body().Invoke(tmp1,tmp2); 
    }
    //: Simple invokation.  
  };
  
  template<class Data1T,class Data2T>
  ostream &operator<<(ostream &out,const Signal2C<Data1T,Data2T> &) { 
    assert(0); // Not implemented.
    return out;
  }
  //: IO Operator.
  // Not implemented
  
  ////////////////////////////
  
  template<class Data1T,class Data2T>
  SignalInterConnect2BodyC<Data1T,Data2T>::SignalInterConnect2BodyC(Signal0C &from,Signal2C<Data1T,Data2T> &targ)
    : SignalConnector0BodyC(from),
      SignalConnector1BodyC<Data1T>(from),
      SignalInterConnect0BodyC(from,targ)
  {}
  
  
  //: Invoke signal, with value.
  
  template<class Data1T,class Data2T>
  inline 
  void SignalInterConnect2BodyC<Data1T,Data2T>::Invoke(Data1T &dat1,Data2T &dat2) {
    //assert(dynamic_cast<Signal2BodyC<Data1T,Data2T> *>(&Target()) != 0);
    dynamic_cast<Signal2BodyC<Data1T,Data2T> &>(Target()).Invoke(dat1,dat2);
  }
  
  template<class Data1T,class Data2T>
  inline
  void SignalInterConnect2BodyC<Data1T,Data2T>::Invoke(Data1T &dat1) { 
    //assert(dynamic_cast<Signal2BodyC<Data1T,Data2T> *>(&Target()) != 0);
    dynamic_cast<Signal2BodyC<Data1T,Data2T> &>(Target()).Invoke(dat1,defaultVal2);
  }
  
  template<class Data1T,class Data2T>
  inline
  void SignalInterConnect2BodyC<Data1T,Data2T>::Invoke()
  { Invoke(defaultVal1,defaultVal2); }
  
  ///////////////////////
  
  template<class Data1T,class Data2T>
  inline 
  SignalConnectorC Connect(Signal0C &from,Signal2C<Data1T,Data2T> &oth) { 
    assert(from.IsValid());
    assert(oth.IsValid());
    return SignalInterConnect2C<Data1T,Data2T>(from,oth);
  }
  //: Connect to another signal.
  
  template<class Data1T,class Data2T>  
  inline 
  SignalConnectorC Connect(Signal0C &from,void (*func)(Data1T &,Data2T &),const Data1T &def1 =Data1T(),const Data2T &def2 = Data2T()) { 
    assert(from.IsValid());
    return Signal2FuncC<Data1T,Data2T>(from,func,def1,def2);  
  }
  //: Connect to a function.

  template<class Data1T,class Data2T,class ObjT>
  inline
  SignalConnectorC Connect(Signal0C &from,const ObjT &obj,void (ObjT::* func)(Data1T &arg1,Data2T &arg2),const Data1T &def1 = Data1T(),const Data2T &def2 = Data2T()) {
    assert(from.IsValid());
    return Signal2MethodC<Data1T,Data2T,ObjT>(from,obj,func,def1,def2); 
  }
  //: Connect to a method.

  template<class Data1T,class Data2T,class ObjT>
  inline
  SignalConnectorC ConnectRef(Signal0C &from,ObjT &obj,void (ObjT::* func)(Data1T &arg1,Data2T &arg2),const Data1T &def1 = Data1T(),const Data2T &def2 = Data2T()) {
    assert(from.IsValid());
    return Signal2MethodRefC<Data1T,Data2T,ObjT>(from,obj,func,def1,def2); 
  }
  //: Connect to a method.
  // Uses refrence to object not instance. <p>
  // NB. It is the users responsibility to ensure the object
  // remains valid while being used.

};
#endif
