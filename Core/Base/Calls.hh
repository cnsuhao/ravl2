// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLCALLS_HEADER
#define RAVLCALLS_HEADER 1
//////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Base/Calls.hh"
//! lib=RavlCore
//! docentry="Ravl.Core.Misc.Calls"
//! userlevel=Advanced
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/Trigger.hh"
#include "Ravl/Assert.hh"

namespace RavlN {
  
  //////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Signal Event handle
  
  template<class RetT = bool>
  class CallFunc0BodyC
    : public TriggerBodyC
  {
  public:
    typedef RetT (*VoidFuncPtrT)();
    
    CallFunc0BodyC(VoidFuncPtrT nfunc)
      : func(nfunc)
      {}
    //: Constructor.
    
    CallFunc0BodyC(bool issueErrorOnCall) {
      cerr << "CallFunc0BodyC(bool issueErrorOnCall), Called. \n";
      if(issueErrorOnCall)
	func = (VoidFuncPtrT) &CallFunc0BodyC<RetT>::IssueError;
      else
	func = (VoidFuncPtrT) &CallFunc0BodyC<RetT>::NoOp;
    }
    //: Constructor.
    // if issueErrorOnCall a function which causes the
    // equivelent of a assertion failure is called. Otherwise
    // the call returns silently.
    
    CallFunc0BodyC()
      : func((VoidFuncPtrT) &CallFunc0BodyC<RetT>::IssueError)
      {}
    //: Default constructor.
    
    virtual void Invoke()
    { (*FuncPtr())(); }
    //: Invoke event.

    virtual RetT Call()
      {  return (*FuncPtr())(); }
    //: Call signal

    virtual RCBodyVC &Copy() const
      { return *new CallFunc0BodyC<RetT>(func); }
    //: Copy call.
    
  protected:
    VoidFuncPtrT func; // Function ptr.
    
    typedef RetT (*FuncT)();
    //: Function ptr type.
    
    static RetT NoOp() { 
      return RetT(); 
    }
    //: NoOp function.
    
    static RetT IssueError() { 
      RavlN::IssueError(__FILE__,__LINE__,"NoOp CallFunc0 Called. ");
      return RetT(); 
    }
    //: Error function.
    
    inline
      FuncT FuncPtr() const
      { return (FuncT)(func); }
    //: Function.
    
  };
  
  //! userlevel=Advanced
  //: Signal Event handle
  
  template<class RetT = bool>
  class CallFunc0C
    : public TriggerC
  {
  public:
    CallFunc0C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    CallFunc0C(const TriggerC &trig)
      : TriggerC(trig)
      {
	if(dynamic_cast<CallFunc0BodyC<RetT> *>(&Body()) == 0)
	  Invalidate();
      }
    //: Convert from a base handle.
    // If the base handle is of another type, and invalid handle
    // is generated.
    
    CallFunc0C(bool issueErrorOnCall)
      : TriggerC(*new CallFunc0BodyC<RetT>(issueErrorOnCall))
      {}
    //: NoOp constructor.
    // if issueErrorOnCall a function which causes the
    // equivelent of a assertion failure is called. Otherwise
    // the call returns silently.
    
    CallFunc0C(RetT (*nfunc)())
      : TriggerC(*new CallFunc0BodyC<RetT>(nfunc))
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    CallFunc0C(CallFunc0BodyC<RetT> &bod)
      : TriggerC(bod)
      {}
    // Body constructor.
    
    CallFunc0BodyC<RetT> &Body()
      { return static_cast<CallFunc0BodyC<RetT> &>(TriggerC::Body()); }
    //: Access body.

    const CallFunc0BodyC<RetT> &Body() const
      { return static_cast<const CallFunc0BodyC<RetT> &>(TriggerC::Body()); }
    //: Constant access to body.

    CallFunc0C<RetT> Copy() const
    { return CallFunc0C<RetT>(static_cast<CallFunc0BodyC<RetT> &>(Body().Copy())); }
    //: Copy func call.

  public:
    RetT Call()
      { return Body().Call(); }
    //: Call function.

    RetT operator()()
      { return Body().Call(); }
    //: Call function.
    
  };

  //////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Signal Event handle
  
  template<class DataT,class RetT = bool>
  class CallFunc1BodyC
    : public CallFunc0BodyC<RetT>
  {
  public:
    CallFunc1BodyC() 
      : CallFunc0BodyC<RetT>((VoidFuncPtrT)&CallFunc1BodyC<DataT,RetT>::IssueError)
    {}
    //: Default constructor.
    
    CallFunc1BodyC(RetT (*nfunc)(DataT &),const DataT &ndat)
      : CallFunc0BodyC<RetT>((VoidFuncPtrT) nfunc),
	dat1(ndat)
      {}
    //: Constructor.

    CallFunc1BodyC(bool issueErrorOnCall) {
      if(issueErrorOnCall)
	func = (VoidFuncPtrT) (&CallFunc1BodyC<DataT,RetT>::IssueError);
      else
	func = (VoidFuncPtrT) &CallFunc1BodyC<DataT,RetT>::NoOp;
    }
    //: Constructor.
    // if issueErrorOnCall a function which causes the
    // equivelent of a assertion failure is called. Otherwise
    // the call returns silently.
    
    virtual void Invoke()
      { (*FuncPtr())(dat1); }
    //: Invoke event.
    
    virtual RetT Call()
      { return (*FuncPtr())(dat1); }
    //: Call an function.
    
    virtual RetT Call(DataT &pd)
      { return (*FuncPtr())(pd); }
    //: Call event, with paramiter.
    
    DataT &Data1()
      { return dat1; }
    //: Access data.
    
    const DataT &Data1() const
      { return dat1; }
    //: Access data.

    virtual RCBodyVC &Copy() const
      { return *new CallFunc1BodyC<DataT,RetT>(func,dat1); }
    //: Copy call.
    
    static RetT NoOp(DataT &) { 
      return RetT();
    }
    //: NoOp function.
    
    static RetT IssueError(DataT &) { 
      RavlN::IssueError(__FILE__,__LINE__,"NoOp CallFunc1 Called. ");
      return RetT(); 
    }
    //: Error function.
    
  protected:
    CallFunc1BodyC(RetT (*nfunc)(),const DataT &ndat)
      : CallFunc0BodyC<RetT>(nfunc),
	dat1(ndat)
      {}
    //: Constructor.
    
    typedef RetT (*FuncT)(DataT &);
    //: Function ptr type.    
    
    inline
    FuncT FuncPtr() const
      { return (FuncT)(func); }
    //: Function.
    
    DataT dat1;
  };
  
  //! userlevel=Advanced
  //: Signal Event handle
  
  template<class DataT,class RetT = bool>
  class CallFunc1C
    : public CallFunc0C<RetT>
  {
  public:
    CallFunc1C()
      {}
    //: Default constructor.
    // Creates an invalid handle.

    CallFunc1C(const TriggerC &trig)
      : CallFunc0C<RetT>(trig)
      {
	if(dynamic_cast<CallFunc1BodyC<DataT,RetT> *>(&Body()) == 0)
	  Invalidate();
      }
    //: Convert from a base handle.
    // If the base handle is of another type, and invalid handle
    // is generated.
    
    CallFunc1C(bool issueErrorOnCall)
      : CallFunc0C<RetT>(*new CallFunc1BodyC<DataT,RetT>(issueErrorOnCall))
      {}
    //: NoOp constructor.
    // if issueErrorOnCall a function which causes the
    // equivelent of a assertion failure is called. Otherwise
    // the call returns silently.
    
    CallFunc1C(RetT (*nfunc)(DataT &),const DataT &dat = DataT())
      : CallFunc0C<RetT>(*new CallFunc1BodyC<DataT,RetT>(nfunc,dat))
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    CallFunc1C(CallFunc1BodyC<DataT,RetT> &body)
      : CallFunc0C<RetT>(body)
      {}
    //: Body constructor.
    
    CallFunc1BodyC<DataT,RetT> &Body()
      { return static_cast<CallFunc1BodyC<DataT,RetT> &>(TriggerC::Body()); }
    //: Access body.
    
    const CallFunc1BodyC<DataT,RetT> &Body() const
      { return static_cast<const CallFunc1BodyC<DataT,RetT> &>(TriggerC::Body()); }
    //: Constant access to body.
    
  public:
    RetT Call()
      { return Body().Call(); }
    //: Invoke event, with paramiter.
    
    RetT Call(DataT &pd)
      { return Body().Call(pd); }
    //: Invoke event, with paramiter.

    RetT operator()(DataT &pd)
      { return Body().Call(pd); }
    //: Call function with patamiter
    
    CallFunc1C<DataT,RetT> Copy() const
      { return CallFunc1C<DataT,RetT>(static_cast<CallFunc1BodyC<DataT,RetT> &>(Body().Copy())); }
    //: Copy func call.
    
    DataT &Data1()
      { return Body().Data1(); }
    //: Access data.
    
    const DataT &Data1() const
      { return Body().Data1(); }
    //: Access data.
    
  };

  //////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Signal Event handle
  
  template<class Data1T,class Data2T,class RetT = bool>
  class CallFunc2BodyC
    : public CallFunc1BodyC<Data1T,RetT>
  {
  public:
    CallFunc2BodyC() 
      : CallFunc1BodyC<Data1T,RetT>((VoidFuncPtrT) &CallFunc2BodyC<Data1T,Data2T,RetT>::IssueError)
    {}
    //: Default constructor.
    
    CallFunc2BodyC(RetT (*nfunc)(Data1T &,Data2T &),const Data1T &ndat1,const Data2T &ndat2)
      : CallFunc1BodyC<Data1T,RetT>((VoidFuncPtrT)nfunc,ndat1),
	dat2(ndat2)
      {}
    //: Constructor.

    CallFunc2BodyC(bool issueErrorOnCall) {
      if(issueErrorOnCall)
	func = (VoidFuncPtrT) &CallFunc2BodyC<Data1T,Data2T,RetT>::IssueError;
      else
	func = (VoidFuncPtrT) &CallFunc2BodyC<Data1T,Data2T,RetT>::NoOp;
    }
    //: Constructor.
    // if issueErrorOnCall a function which causes the
    // equivelent of a assertion failure is called. Otherwise
    // the call returns silently.
    
    virtual void Invoke()
      { (*FuncPtr())(dat1,dat2); }
    //: Invoke event.

    virtual RetT Call()
      { return (*FuncPtr())(dat1,dat2); }
    //: Invoke event.

    virtual RetT Call(Data1T &pd)
      { return (*FuncPtr())(pd,dat2); }
    //: Invoke event, with paramiter.
    
    virtual RetT Call(Data1T &pd1,Data2T &pd2)
      { return (*FuncPtr())(pd1,pd2); }
    //: Invoke event, with paramiters.
    
    Data2T &Data2()
      { return dat2; }
    //: Access data.
    
    const Data2T &Data2() const
      { return dat2; }
    //: Access data.

    virtual RCBodyVC &Copy() const
      { return *new CallFunc2BodyC<Data1T,Data2T,RetT>(func,dat1,dat2); }
    //: Copy call.
    
  protected:
    CallFunc2BodyC(RetT (*nfunc)(),const Data1T &ndat1,const Data2T &ndat2)
      : CallFunc1BodyC<Data1T,RetT>(nfunc,ndat1),
	dat2(ndat2)
      {}
    //: Constructor.
    
    
    Data2T dat2;

    static RetT NoOp(Data1T &,Data2T &) { 
      return RetT(); 
    }
    //: NoOp function.
    
    static RetT IssueError(Data1T &,Data2T &) { 
      RavlN::IssueError(__FILE__,__LINE__,"NoOp CallFunc2 Called. ");
      return RetT(); 
    }
    //: Error function.
    
    typedef RetT (*FuncT)(Data1T &,Data2T &);
    //: Function ptr type.    
    
    inline
    FuncT FuncPtr() const
      { return (FuncT)(func); }
    //: Function.
    
  };
  
  //! userlevel=Advanced
  //: Signal Event handle
  
  template<class Data1T,class Data2T,class RetT = bool>
  class CallFunc2C
    : public CallFunc1C<Data1T,RetT>
 {
  public:
    CallFunc2C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
   
    CallFunc2C(const TriggerC &trig)
      : CallFunc1C<Data1T,RetT>(trig)
      {
	if(dynamic_cast<CallFunc2BodyC<Data1T,Data2T,RetT> *>(&Body()) == 0)
	  Invalidate();
      }
    //: Convert from a base handle.
    // If the base handle is of another type, and invalid handle
    // is generated.

    CallFunc2C(bool issueErrorOnCall)
      : CallFunc1C<Data1T,RetT>(*new CallFunc2BodyC<Data1T,Data2T,RetT>(issueErrorOnCall))
      {}
    //: NoOp constructor.
    // if issueErrorOnCall a function which causes the
    // equivelent of a assertion failure is called. Otherwise
    // the call returns silently.
    
    CallFunc2C(RetT (*nfunc)(Data1T &,Data2T &),const Data1T &dat1 = Data1T(),const Data2T &dat2 = Data2T())
      : CallFunc1C<Data1T,RetT>(*new CallFunc2BodyC<Data1T,Data2T,RetT>(nfunc,dat1,dat2))
      {}
    //: Default constructor.
    // Creates an invalid handle.
   
  protected:
    CallFunc2C(CallFunc2BodyC<Data1T,Data2T,RetT> &bod)
      : CallFunc1C<Data1T,RetT>(bod)
      {}
    //: Body constructor.
    
    CallFunc2BodyC<Data1T,Data2T,RetT> &Body()
      { return static_cast<CallFunc2BodyC<Data1T,Data2T,RetT> &>(TriggerC::Body()); }
    //: Access body.
    
    const CallFunc2BodyC<Data1T,Data2T,RetT> &Body() const
      { return static_cast<const CallFunc2BodyC<Data1T,Data2T,RetT> &>(TriggerC::Body()); }
    //: Constant access to body.
    
  public:
    RetT Call()
      { return Body().Call(); }
    //: Call function.
   
    RetT Call(Data1T &pd1,Data2T &pd2)
      { return Body().Call(pd1,pd2); }
    //: Invoke event, with paramiters.

    RetT operator()(Data1T &pd1,Data2T &pd2)
      { return Body().Call(pd1,pd2); }
    //: Call function with patamiters
   
    CallFunc2C<Data1T,Data2T,RetT> Copy() const
      { return CallFunc2C<Data1T,Data2T,RetT>(static_cast<CallFunc2BodyC<Data1T,Data2T,RetT> &>(Body().Copy())); }
    //: Copy func call.
   
    Data2T &Data2()
      { return Body().Data2(); }
    //: Access data.
   
    const Data2T &Data2() const
      { return Body().Data2(); }
    //: Access data.
  };
  
  //////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Signal Event handle
  
  template<class Data1T,class Data2T,class Data3T,class RetT = bool>
  class CallFunc3BodyC
    : public CallFunc2BodyC<Data1T,Data2T,RetT>
  {
  public:
    CallFunc3BodyC(bool issueErrorOnCall) {
      if(issueErrorOnCall)
	func = (VoidFuncPtrT) &CallFunc3BodyC<Data1T,Data2T,RetT>::IssueError;
      else
	func = (VoidFuncPtrT) &CallFunc3BodyC<Data1T,Data2T,RetT>::NoOp;
    }
    //: Constructor.
    // if issueErrorOnCall a function which causes the
    // equivelent of a assertion failure is called. Otherwise
    // the call returns silently.

    CallFunc3BodyC() 
      : CallFunc2BodyC<Data1T,Data2T,RetT>((VoidFuncPtrT) &CallFunc3BodyC<Data1T,Data2T,Data3T,RetT>::IssueError)
    {}
    //: Default constructor.
    
    CallFunc3BodyC(RetT (*nfunc)(Data1T &,Data2T &,Data3T &),const Data1T &ndat1 = Data1T(),const Data2T &ndat2 = Data2T(),const Data3T &ndat3 = Data3T())
      : CallFunc2BodyC<Data1T,Data2T,RetT>((VoidFuncPtrT) nfunc,ndat1,ndat2),
	dat3(ndat3)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (*FuncPtr())(dat1,dat2,dat3); }
    //: Invoke event.

    virtual RetT Call()
      { return (*FuncPtr())(dat1,dat2,dat3); }
    //: Invoke event.
    
    virtual RetT Call(Data1T &pd)
      { return (*FuncPtr())(pd,dat2,dat3); }
    //: Invoke event, with paramiter.
    
    virtual RetT Call(Data1T &pd1,Data2T &pd2)
      { return (*FuncPtr())(pd1,pd2,dat3); }
    //: Invoke event, with paramiters.
    
    virtual RetT Call(Data1T &pd1,Data2T &pd2,Data3T &pd3)
      { return (*FuncPtr())(pd1,pd2,pd3); }
    //: Invoke event, with paramiters.
    
    Data3T &Data3()
      { return dat3; }
    //: Access data.
    
    const Data3T &Data3() const
      { return dat3; }
    //: Access data.

    virtual RCBodyVC &Copy() const
      { return *new CallFunc3BodyC<Data1T,Data2T,Data3T,RetT>(func,dat1,dat2,dat3); }
    //: Copy call.

    static RetT NoOp(Data1T &,Data2T &,Data3T &) { 
      return RetT(); 
    }
    //: NoOp function.
    
    static RetT IssueError(Data1T &,Data2T &,Data3T &) { 
      RavlN::IssueError(__FILE__,__LINE__,"NoOp CallFunc3 Called. ");
      return RetT(); 
    }
    //: Error function.
    
  protected:
    CallFunc3BodyC(RetT (*nfunc)(),const Data1T &ndat1,const Data2T &ndat2,const Data3T &ndat3)
      : CallFunc2BodyC<Data1T,Data2T,RetT>((VoidFuncPtrT) nfunc,ndat1,ndat2),
	dat3(ndat3)
      {}
    //: Constructor.
    
    Data3T dat3;
        
    typedef RetT (*FuncT)(Data1T &,Data2T &,Data3T &);
    //: Function ptr type.    
    
    inline
    FuncT FuncPtr() const
      { return (FuncT)(func); }
    //: Function.
  };
  
  //! userlevel=Advanced
  //: Signal Event handle
  
  template<class Data1T,class Data2T,class Data3T,class RetT = bool>
  class CallFunc3C
    : public CallFunc2C<Data1T,Data2T,RetT>
  {
  public:
    CallFunc3C()
      {}
    //: Default constructor.
    // Creates an invalid handle.

    CallFunc3C(const TriggerC &trig)
      : CallFunc2C<Data1T,Data2T,RetT>(trig)
      {
	if(dynamic_cast<CallFunc3BodyC<Data1T,Data2T,Data3T,RetT> *>(&Body()) == 0)
	  Invalidate();
      }
    //: Convert from a base handle.
    // If the base handle is of another type, and invalid handle
    // is generated.
    
    CallFunc3C(bool issueErrorOnCall)
      : CallFunc2C<Data1T,Data2T,RetT>(*new CallFunc3BodyC<Data1T,Data2T,Data3T,RetT>(issueErrorOnCall))
      {}
    //: NoOp constructor.
    // if issueErrorOnCall a function which causes the
    // equivelent of a assertion failure is called. Otherwise
    // the call returns silently.
    
    CallFunc3C(RetT (*nfunc)(Data1T &,Data2T &,Data3T &),const Data1T &dat1 = Data1T(),const Data2T &dat2 = Data2T(),const Data3T &dat3 = Data3T())
      : CallFunc2C<Data1T,Data2T,RetT>(*new CallFunc3BodyC<Data1T,Data2T,Data3T,RetT>(nfunc,dat1,dat2,dat3))
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    CallFunc3C(CallFunc3BodyC<Data1T,Data2T,Data3T,RetT> &bod)
      : CallFunc2C<Data1T,Data2T,RetT>(bod)
      {}
    //: Body constructor.
    
    CallFunc3BodyC<Data1T,Data2T,Data3T,RetT> &Body()
      { return static_cast<CallFunc3BodyC<Data1T,Data2T,Data3T,RetT> &>(TriggerC::Body()); }
    //: Access body.
    
    const CallFunc3BodyC<Data1T,Data2T,Data3T,RetT> &Body() const
      { return static_cast<const CallFunc3BodyC<Data1T,Data2T,Data3T,RetT> &>(TriggerC::Body()); }
    //: Constant access to body.
    
  public:
    RetT Call()
      { return Body().Call(); }
    //: Call function.
    
    RetT Call(Data1T &pd1,Data2T &pd2,Data3T &pd3)
      { return Body().Call(pd1,pd2,pd3); }
    //: Invoke event, with paramiters.

    RetT operator()(Data1T &pd1,Data2T &pd2,Data3T &pd3)
      { return Body().Call(pd1,pd2,pd3); }
    //: Call function with patamiters

    CallFunc3C<Data1T,Data2T,Data3T,RetT> Copy() const
      { return CallFunc3C<Data1T,Data2T,Data3T,RetT>(static_cast<CallFunc3BodyC<Data1T,Data2T,Data3T,RetT> &>(Body().Copy())); }
    //: Copy func call.

    Data3T &Data3()
      { return Body().Data3(); }
    //: Access data.
   
    const Data3T &Data3() const
      { return Body().Data3(); }
    //: Access data.
    
  };

  //////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Signal Event handle
  
  template<class Data1T,class Data2T,class Data3T,class Data4T,class RetT = bool>
  class CallFunc4BodyC
    : public CallFunc3BodyC<Data1T,Data2T,Data3T,RetT>
  {
  public:
    CallFunc4BodyC() 
      : CallFunc3BodyC<Data1T,Data2T,Data3T,RetT>((VoidFuncPtrT) &CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT>::IssueError)
    {}
    //: Default constructor.
    
    CallFunc4BodyC(bool issueErrorOnCall) {
      if(issueErrorOnCall)
	func = (VoidFuncPtrT) &CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT>::IssueError;
      else
	func = (VoidFuncPtrT) &CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT>::NoOp;
    }
    //: Constructor.
    // if issueErrorOnCall a function which causes the
    // equivelent of a assertion failure is called. Otherwise
    // the call returns silently.
    
    CallFunc4BodyC(RetT (*nfunc)(Data1T &,Data2T &,Data3T &,Data4T &),const Data1T &ndat1,const Data2T &ndat2,const Data3T &ndat3,const Data4T &ndat4)
      : CallFunc3BodyC<Data1T,Data2T,Data3T,RetT>((VoidFuncPtrT) nfunc,ndat1,ndat2,ndat3),
	dat4(ndat4)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (*FuncPtr())(dat1,dat2,dat3,dat4); }
    //: Invoke event.

    virtual RetT Call()
      { return (*FuncPtr())(dat1,dat2,dat3,dat4); }
    //: Invoke event.
    
    virtual RetT Call(Data1T &pd)
      { return (*FuncPtr())(pd,dat2,dat3,dat4); }
    //: Invoke event, with paramiter.
    
    virtual RetT Call(Data1T &pd1,Data2T &pd2)
      { return (*FuncPtr())(pd1,pd2,dat3,dat4); }
    //: Invoke event, with paramiters.
    
    virtual RetT Call(Data1T &pd1,Data2T &pd2,Data3T &pd3)
      { return (*FuncPtr())(pd1,pd2,pd3,dat4); }
    //: Invoke event, with paramiters.

    virtual RetT Call(Data1T &pd1,Data2T &pd2,Data3T &pd3,Data4T &pd4)
      { return (*FuncPtr())(pd1,pd2,pd3,pd4); }
    //: Invoke event, with paramiters.

    Data4T &Data4()
      { return dat4; }
    //: Access data.
    
    const Data4T &Data4() const
      { return dat4; }
    //: Access data.

    virtual RCBodyVC &Copy() const
      { return *new CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT>(func,dat1,dat2,dat3,dat4); }
    //: Copy call.
    
  protected:
    CallFunc4BodyC(RetT (*nfunc)(),const Data1T &ndat1,const Data2T &ndat2,const Data3T &ndat3,const Data4T &ndat4)
      : CallFunc3BodyC<Data1T,Data2T,Data3T,RetT>((VoidFuncPtrT) nfunc,ndat1,ndat2,ndat3),
	dat4(ndat4)
      {}
    //: Constructor.

    Data4T dat4;

    static RetT NoOp(Data1T &,Data2T &,Data3T &,Data4T &) { 
      return RetT();
    }
    //: NoOp function.
    
    static RetT IssueError(Data1T &,Data2T &,Data3T &,Data4T &) { 
      RavlN::IssueError(__FILE__,__LINE__,"NoOp CallFunc4 Called. ");
      return RetT(); 
    }
    //: Error function.

    typedef RetT (*FuncT)(Data1T &,Data2T &,Data3T &,Data4T &);
    //: Function ptr type.    
    
    inline
    FuncT FuncPtr() const
      { return (FuncT)(func); }
    //: Function.
  };
  
  //! userlevel=Advanced
  //: Signal Event handle
  
  template<class Data1T,class Data2T,class Data3T,class Data4T,class RetT = bool>
  class CallFunc4C
    : public CallFunc3C<Data1T,Data2T,Data3T,RetT>
  {
  public:
    CallFunc4C()
      {}
    //: Default constructor.
    // Creates an invalid handle.

    CallFunc4C(const TriggerC &trig)
      : CallFunc3C<Data1T,Data2T,Data3T,RetT>(trig)
      {
	if(dynamic_cast<CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT> *>(&Body()) == 0)
	  Invalidate();
      }
    //: Convert from a base handle.
    // If the base handle is of another type, and invalid handle
    // is generated.

    CallFunc4C(bool issueErrorOnCall)
      : CallFunc3C<Data1T,Data2T,Data3T,RetT>(*new CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT>(issueErrorOnCall))
      {}
    //: NoOp constructor.
    // if issueErrorOnCall a function which causes the
    // equivelent of a assertion failure is called. Otherwise
    // the call returns silently.
    
    CallFunc4C(RetT (*nfunc)(Data1T &,Data2T &,Data3T &,Data4T &),
	       const Data1T &dat1 = Data1T(),const Data2T &dat2 = Data2T(),const Data3T &dat3 = Data3T(),const Data4T &dat4 = Data4T())
      : CallFunc3C<Data1T,Data2T,Data3T,RetT>(*new CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT>(nfunc,dat1,dat2,dat3,dat4))
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    CallFunc4C(CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT> &bod)
      : CallFunc3C<Data1T,Data2T,Data3T,RetT>(bod)
      {}
    //: Body constructor.
    
    CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT> &Body()
      { return static_cast<CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT> &>(TriggerC::Body()); }
    //: Access body.
    
    const CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT> &Body() const
      { return static_cast<const CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT> &>(TriggerC::Body()); }
    //: Constant access to body.
    
  public:
    RetT Call()
      { return Body().Call(); }
    //: Call function.
    
    RetT Call(Data1T &pd1,Data2T &pd2,Data3T &pd3,Data4T &pd4)
      { return Body().Call(pd1,pd2,pd3,pd4); }
    //: Invoke event, with paramiters.

    RetT operator()(Data1T &pd1,Data2T &pd2,Data3T &pd3,Data4T &pd4)
      { return Body().Call(pd1,pd2,pd3,pd4); }
    //: Call function with patamiters
    
    CallFunc4C<Data1T,Data2T,Data3T,Data4T,RetT> Copy() const
      { return CallFunc4C<Data1T,Data2T,Data3T,Data4T,RetT>(static_cast<CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT> &>(Body().Copy())); }
    //: Copy func call.
    
    Data4T &Data4()
      { return Body().Data4(); }
    //: Access data.
   
    const Data4T &Data4() const
      { return Body().Data4(); }
    //: Access data.
    
  };

  //////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Signal Event handle
  
  template<class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class RetT = bool>
  class CallFunc5BodyC
    : public CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT>
  {
  public:
    CallFunc5BodyC(bool issueErrorOnCall) {
      if(issueErrorOnCall)
	func = (VoidFuncPtrT) &CallFunc5BodyC<Data1T,Data2T,Data3T,Data4T,Data5T,RetT>::IssueError;
      else
	func = (VoidFuncPtrT) &CallFunc5BodyC<Data1T,Data2T,Data3T,Data4T,Data5T,RetT>::NoOp;
    }
    //: Constructor.
    // if issueErrorOnCall a function which causes the
    // equivelent of a assertion failure is called. Otherwise
    // the call returns silently.

    CallFunc5BodyC() 
      : CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT>((VoidFuncPtrT) &CallFunc5BodyC<Data1T,Data2T,Data3T,Data4T,Data5T,RetT>::IssueError)
    {}
    //: Default constructor.
    
    
    CallFunc5BodyC(RetT (*nfunc)(Data1T &,Data2T &,Data3T &,Data4T &,Data5T &),
		   const Data1T &ndat1,
		   const Data2T &ndat2,
		   const Data3T &ndat3,
		   const Data4T &ndat4,
		   const Data5T &ndat5)
      : CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT>((VoidFuncPtrT) nfunc,ndat1,ndat2,ndat3,ndat4),
	dat5(ndat5)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (*FuncPtr())(dat1,dat2,dat3,dat4,dat5); }
    //: Invoke event.

    virtual RetT Call()
      { return (*FuncPtr())(dat1,dat2,dat3,dat4,dat5); }
    //: Invoke event.
    
    virtual RetT Call(Data1T &pd)
      { return (*FuncPtr())(pd,dat2,dat3,dat4,dat5); }
    //: Invoke event, with paramiter.
    
    virtual RetT Call(Data1T &pd1,Data2T &pd2)
      { return (*FuncPtr())(pd1,pd2,dat3,dat4,dat5); }
    //: Invoke event, with paramiters.
    
    virtual RetT Call(Data1T &pd1,Data2T &pd2,Data3T &pd3)
      { return (*FuncPtr())(pd1,pd2,pd3,dat4,dat5); }
    //: Invoke event, with paramiters.

    virtual RetT Call(Data1T &pd1,Data2T &pd2,Data3T &pd3,Data4T &pd4)
      { return (*FuncPtr())(pd1,pd2,pd3,pd4,dat5); }
    //: Invoke event, with paramiters.

    virtual RetT Call(Data1T &pd1,Data2T &pd2,Data3T &pd3,Data4T &pd4,Data5T &pd5)
      { return (*FuncPtr())(pd1,pd2,pd3,pd4,pd5); }
    //: Invoke event, with paramiters.
    
    Data5T &Data5()
      { return dat5; }
    //: Access data.
    
    const Data5T &Data5() const
      { return dat5; }
    //: Access data.
    
    virtual RCBodyVC &Copy() const
      { return *new CallFunc5BodyC<Data1T,Data2T,Data3T,Data4T,Data5T,RetT>(func,dat1,dat2,dat3,dat4,dat5); }
    //: Copy call.
    
  protected:
    CallFunc5BodyC(RetT (*nfunc)(),
		   const Data1T &ndat1,
		   const Data2T &ndat2,
		   const Data3T &ndat3,
		   const Data4T &ndat4,
		   const Data5T &ndat5)
      : CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT>(nfunc,ndat1,ndat2,ndat3,ndat4),
	dat5(ndat5)
      {}
    //: Constructor.
    
    Data5T dat5;

    static RetT NoOp(Data1T &,Data2T &,Data3T &,Data4T &,Data5T &) { 
      return RetT();
    }
    //: NoOp function.
    
    static RetT IssueError(Data1T &,Data2T &,Data3T &,Data4T &,Data5T &) { 
      RavlN::IssueError(__FILE__,__LINE__,"NoOp CallFunc5 Called. ");
      return RetT(); 
    }
    //: Error function.

    typedef RetT (*FuncT)(Data1T &,Data2T &,Data3T &,Data4T &,Data5T &);
    //: Function ptr type.    
    
    inline
    FuncT FuncPtr() const
      { return (FuncT)(func); }
    //: Function.
  };
  
  //! userlevel=Advanced
  //: Signal Event handle
  
  template<class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class RetT = bool>
  class CallFunc5C
    : public CallFunc4C<Data1T,Data2T,Data3T,Data4T,RetT>
  {
  public:
    CallFunc5C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    CallFunc5C(bool issueErrorOnCall)
      : CallFunc4C<Data1T,Data2T,Data3T,Data4T,RetT>(*new CallFunc5BodyC<Data1T,Data2T,Data3T,Data4T,Data5T,RetT>(issueErrorOnCall))
      {}
    //: NoOp constructor.
    // if issueErrorOnCall a function which causes the
    // equivelent of a assertion failure is called. Otherwise
    // the call returns silently.

    CallFunc5C(const TriggerC &trig)
      : CallFunc4C<Data1T,Data2T,Data3T,Data4T,RetT>(trig)
      {
	if(dynamic_cast<CallFunc5BodyC<Data1T,Data2T,Data3T,Data4T,Data5T,RetT> *>(&Body()) == 0)
	  Invalidate();
      }
    //: Convert from a base handle.
    // If the base handle is of another type, and invalid handle
    // is generated.
    
    CallFunc5C(RetT (*nfunc)(Data1T &,Data2T &,Data3T &,Data4T &,Data5T &),
	       const Data1T &dat1 = Data1T(),
	       const Data2T &dat2 = Data2T(),
	       const Data3T &dat3 = Data3T(),
	       const Data4T &dat4 = Data4T(),
	       const Data5T &dat5 = Data5T())
      : CallFunc4C<Data1T,Data2T,Data3T,Data4T,RetT>(*new CallFunc5BodyC<Data1T,Data2T,Data3T,Data4T,Data5T,RetT>(nfunc,dat1,dat2,dat3,dat4,dat5))
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    CallFunc5C(CallFunc5BodyC<Data1T,Data2T,Data3T,Data4T,Data5T,RetT> &bod)
      : CallFunc4C<Data1T,Data2T,Data3T,Data4T,RetT>(bod)
      {}
    //: Body constructor.
    
    CallFunc5BodyC<Data1T,Data2T,Data3T,Data4T,Data5T,RetT> &Body()
      { return static_cast<CallFunc5BodyC<Data1T,Data2T,Data3T,Data4T,Data5T,RetT> &>(TriggerC::Body()); }
    //: Access body.
    
    const CallFunc5BodyC<Data1T,Data2T,Data3T,Data4T,Data5T,RetT> &Body() const
      { return static_cast<const CallFunc5BodyC<Data1T,Data2T,Data3T,Data4T,Data5T,RetT> &>(TriggerC::Body()); }
    //: Constant access to body.
    
  public:
    RetT Call()
      { return Body().Call(); }
    //: Call function.
    
    RetT Call(Data1T &pd1,Data2T &pd2,Data3T &pd3,Data4T &pd4,Data5T &pd5)
      { return Body().Call(pd1,pd2,pd3,pd4,pd5); }
    //: Invoke event, with paramiters.

    RetT operator()(Data1T &pd1,Data2T &pd2,Data3T &pd3,Data4T &pd4,Data5T &pd5)
      { return Body().Call(pd1,pd2,pd3,pd4,pd5); }
    //: Call function with patamiters
    
    CallFunc5C<Data1T,Data2T,Data3T,Data4T,Data5T,RetT> Copy() const
      { return CallFunc5C<Data1T,Data2T,Data3T,Data4T,Data5T,RetT>(static_cast<CallFunc5BodyC<Data1T,Data2T,Data3T,Data4T,Data5T,RetT> &>(Body().Copy())); }
    //: Copy func call.
    
    Data5T &Data5()
      { return Body().Data5(); }
    //: Access data.
   
    const Data5T &Data5() const
      { return Body().Data5(); }
    //: Access data.

  };


  /////////////////////////////////////////////////////////
  //! userlevel=Normal

#if !defined(VISUAL_CPP)
  
  template<class RetT>
  inline
  CallFunc0C<RetT> Trigger(RetT (*nfunc)())
  { return CallFunc0C<RetT>(nfunc); }
  
  template<class DataT,class RetT>
  inline
  CallFunc1C<DataT,RetT> 
  Trigger(RetT (*nfunc)(DataT &dat),const DataT &dat)
  { return CallFunc1C<DataT,RetT>(nfunc,dat); }
  
  template<class Data1T,class Data2T,class RetT>
  inline
  CallFunc2C<Data1T,Data2T,RetT> 
  Trigger(RetT (*nfunc)(Data1T &,Data2T &),const Data1T &dat1,const Data2T &dat2)
  { return CallFunc2C<Data1T,Data2T,RetT>(nfunc,dat1,dat2); }

  template<class Data1T,class Data2T,class Data3T,class RetT>
  inline
  CallFunc3C<Data1T,Data2T,Data3T,RetT> 
  Trigger(RetT (*nfunc)(Data1T &,Data2T &,Data3T &),const Data1T &dat1,const Data2T &dat2,const Data3T &dat3)
  { return CallFunc3C<Data1T,Data2T,Data3T,RetT>(nfunc,dat1,dat2,dat3); }

  template<class Data1T,class Data2T,class Data3T,class Data4T,class RetT>
  inline
  CallFunc4C<Data1T,Data2T,Data3T,Data4T,RetT> 
  Trigger(RetT (*nfunc)(Data1T &,Data2T &,Data3T &,Data4T &),const Data1T &dat1,const Data2T &dat2,const Data3T &dat3,const Data4T &dat4)
  { return CallFunc4C<Data1T,Data2T,Data3T,Data4T,RetT>(nfunc,dat1,dat2,dat3,dat4); }

  template<class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class RetT>
  inline
  CallFunc5C<Data1T,Data2T,Data3T,Data4T,Data5T,RetT> 
  Trigger(RetT (*nfunc)(Data1T &,Data2T &,Data3T &,Data4T &,Data5T &),const Data1T &dat1,const Data2T &dat2,const Data3T &dat3,const Data4T &dat4,const Data5T &dat5)
  { return CallFunc5C<Data1T,Data2T,Data3T,Data4T,Data5T,RetT>(nfunc,dat1,dat2,dat3,dat4,dat5); }
  
#else
  // Labotimized version for Visual C++.
  // Doesn't template on return types.
  
  inline
  CallFunc0C<bool> Trigger(bool (*nfunc)())
  { return CallFunc0C<bool>(nfunc); }
  
  template<class DataT>
  inline
  CallFunc1C<DataT,bool> 
  Trigger(bool (*nfunc)(DataT &dat),const DataT &dat)
  { return CallFunc1C<DataT,bool>(nfunc,dat); }
  
  template<class Data1T,class Data2T>
  inline
  CallFunc2C<Data1T,Data2T,bool> 
  Trigger(bool (*nfunc)(Data1T &,Data2T &),const Data1T &dat1,const Data2T &dat2)
  { return CallFunc2C<Data1T,Data2T,bool>(nfunc,dat1,dat2); }

  template<class Data1T,class Data2T,class Data3T>
  inline
  CallFunc3C<Data1T,Data2T,Data3T,bool> 
  Trigger(bool (*nfunc)(Data1T &,Data2T &,Data3T &),const Data1T &dat1,const Data2T &dat2,const Data3T &dat3)
  { return CallFunc3C<Data1T,Data2T,Data3T,bool>(nfunc,dat1,dat2,dat3); }

  template<class Data1T,class Data2T,class Data3T,class Data4T>
  inline
  CallFunc4C<Data1T,Data2T,Data3T,Data4T,bool> 
  Trigger(bool (*nfunc)(Data1T &,Data2T &,Data3T &,Data4T &),const Data1T &dat1,const Data2T &dat2,const Data3T &dat3,const Data4T &dat4)
  { return CallFunc4C<Data1T,Data2T,Data3T,Data4T,bool>(nfunc,dat1,dat2,dat3,dat4); }

  template<class Data1T,class Data2T,class Data3T,class Data4T,class Data5T>
  inline
  CallFunc5C<Data1T,Data2T,Data3T,Data4T,Data5T,bool> 
  Trigger(bool (*nfunc)(Data1T &,Data2T &,Data3T &,Data4T &,Data5T &),const Data1T &dat1,const Data2T &dat2,const Data3T &dat3,const Data4T &dat4,const Data5T &dat5)
  { return CallFunc5C<Data1T,Data2T,Data3T,Data4T,Data5T,bool>(nfunc,dat1,dat2,dat3,dat4,dat5); }
  
#endif
  
}

#endif
