// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Tools/Signal.cc"

#include "Ravl/Threads/Signal.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/Threads/Signal2.hh"
#include "Ravl/Threads/Signal3.hh"
#include "Ravl/SArr1Iter2.hh"
#include "Ravl/InDLIter.hh"
#include "Ravl/Assert.hh"

namespace RavlN {
  //// Signal0BodyC //////////////////////////////////////////////
  
  Signal0BodyC::~Signal0BodyC()
  { DisconnectAll(); };
  
  //: Connect new output.
  
  void Signal0BodyC::Connect(SignalConnector0BodyC &con) {
    RWLockHoldC hold(access,false); //
    // Make new array 1 bigger than old.
    SArray1dC<SignalConnectorC> newouts(outputs.Size() + 1);
    for(SArray1dIter2C<SignalConnectorC,SignalConnectorC> it(outputs,newouts);it;it++)
      it.Data2() = it.Data1();   // Copy existing...
    con.ind = outputs.Size();  // Put in new index.
    con.sigbod = this;          // Make sure we've got the right signal.
    newouts[con.ind] = SignalConnectorC(con);
    outputs = newouts;
  }
  
  //: Disonnect old output.
  
  void Signal0BodyC::Disconnect(SignalConnector0BodyC &con) {
    RWLockHoldC hold(access,false); //
    int ind = con.ind;
    if(ind < 0)
      return ; // Disconnected already.
    // Make new array 1 bigger than old.
    SArray1dC<SignalConnectorC> newouts(outputs.Size() - 1);
    for(int i = 0;i < ind;i++)
      newouts[i] = outputs[i];
    for(int i = ind;i < ((IntT) newouts.Size());i++) {
      SignalConnectorC &sc = outputs[i+1];
      sc.Body().ind = i; // Update id.
      newouts[i] = sc;
    }
    con.ind = -1; // Flag as disconnected.
    outputs = newouts; // Replace outputs.
  }
  
  //: Disconnect an input.
  
  void Signal0BodyC::DisconnectInput(SignalInterConnect0BodyC &in) {
    RWLockHoldC hold(access,false);
    if(in.IsSelfPointing())
      return ; // Done already.
    in.Unlink(); 
    in.SetSelfPointing(); // Flag as deleted.
    hold.Unlock();
  }
  
  //: Connect an input.
  
  void Signal0BodyC::ConnectInput(SignalInterConnect0BodyC &in) {
    RWLockHoldC hold(access,false);
    inputs.InsFirst(in);
  }
  
  
  //: Send default signal.
  
  bool Signal0BodyC::Invoke() {
    RWLockHoldC hold(access,true); //
    SArray1dIterC<SignalConnectorC> it(outputs);
    hold.Unlock();
    bool ret = true;
    for(;it;it++) 
      ret &= it.Data().Invoke();
    return ret;
  }
  
  //: Find interconnection between this and 'targ'.
  // Assumes there's only one connect!!
  
  SignalInterConnect0C Signal0BodyC::FindInterConnect(const Signal0C &targ)  {
    if(!targ.IsValid())
      return SignalInterConnect0C();
    RWLockHoldC hold(access,true); //
    SArray1dIterC<SignalConnectorC> it(outputs);
    hold.Unlock();
    for(;it;it++) {
      SignalInterConnect0BodyC *inter = dynamic_cast<SignalInterConnect0BodyC *>(&it.Data().Body());
      if(inter == 0)
	continue; // Not an interconnector.
      if(&inter->Target() == &targ.Body())
	return SignalInterConnect0C(*inter); // Found !
    }
    return SignalInterConnect0C();
  }
  
  //: Disconnect other signal from this one.
  // 'targ' must be the target of the signal.
  
  bool Signal0BodyC::Disconnect(Signal0C &targ) {
    SignalInterConnect0C  inter = FindInterConnect(targ);
    if(!inter.IsValid())
      return false; // Not found.
    inter.Disconnect();
    return true;
  }
  
  //: Disconnect all signals.
  
  void Signal0BodyC::DisconnectAll() {
    RWLockHoldC hold(access,false); 
    while(!inputs.IsEmpty()) {
      SignalInterConnect0C con(inputs.First());
      hold.Unlock();
      con.Disconnect();
      con.Invalidate(); // Make sure its released here..
      hold.LockWr();
    }
    // Disconnect all outputs.
    hold.Unlock();
    do {
      hold.LockRd();
      SArray1dIterC<SignalConnectorC> it(outputs);
      hold.Unlock();
      for(;it;it++) 
	it.Data().Disconnect();
    } while(outputs.Size() > 0) ;
  }
  
  //// SignalIterConnect0 ////////////////////////////////////////////////
  
  SignalInterConnect0C::SignalInterConnect0C(Signal0C &from,Signal0C &targ)
    : SignalConnectorC(*new SignalInterConnect0BodyC(from.Body(),targ.Body()))
  {}
  
  
  SignalConnector0BodyC::~SignalConnector0BodyC() {
    if(ind >= 0 && sigbod != 0) // Disconnect.
      sigbod->Disconnect(*this);
  }
  
  //: Pass signal on.
  
  bool SignalConnector0BodyC::Invoke() {
    cerr << "SignalConnector0BodyC::Invoke(), ABSTRACT method Called. \n";
    RavlAssert(0);
    return true;
  }
  
  //: Disconnect from input list.
  
  void SignalConnector0BodyC::Disconnect() { 
    sigbod->Disconnect(*this); 
  }
  
  ostream &operator<<(ostream &os,const SignalConnectorC &sc) {
    RavlAssert(0);
    return os;
  }
  
  ///////// SignalInterConnect0BodyC //////////////////////////////////////////////////
  
  //: Constructor.
  
  SignalInterConnect0BodyC::SignalInterConnect0BodyC(Signal0C &from,Signal0C &targ)
    :  SignalConnector0BodyC(from.Body()),
       target(&targ.Body())
  { targ.Body().ConnectInput(*this); }
  
  SignalInterConnect0BodyC::SignalInterConnect0BodyC(Signal0BodyC &from,Signal0BodyC &targ)
    :  SignalConnector0BodyC(from),
       target(&targ)
  { targ.ConnectInput(*this); }
  
  
  //: Destructor.
  
  SignalInterConnect0BodyC::~SignalInterConnect0BodyC() { 
    Disconnect(); 
  }
  
  //: Invoke signal.
  
  bool SignalInterConnect0BodyC::Invoke() {
    RavlAssert(target != 0);
    return target->Invoke();
  }
  
  void SignalInterConnect0BodyC::Disconnect()  { 
    if(target != 0)
      target->DisconnectInput(*this);
    SignalConnector0BodyC::Disconnect(); 
  }
}

