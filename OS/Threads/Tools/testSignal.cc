// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Tools/testSignal.cc"
//! author="Charles Galambos"
//! docentry="Ravl.OS.Signals"
//! userlevel=Develop

#include "Ravl/Threads/Signal.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/Threads/Signal2.hh"
#include "Ravl/Threads/Signal3.hh"
#include "Ravl/Option.hh"

//#include "Ravl/Threads/LaunchThread.hh"

using namespace RavlN;

int callcount = 0;

bool test1() {
  callcount++;
  return true;
}

bool test2(int x) {
  callcount += 2;
  return true;
}

bool test3(bool x) {
  callcount += 2;
  return true;
}

class TestClassC {
public:
  bool test1() {
    callcount++;
    return true;
  }
  
  bool test2(int x) {
    callcount += 2;
    return true;
  }
  
  bool test3(bool x) {
    callcount += 2;
    return true;
  }

  bool test_2(bool x,int n) {
    callcount += 2;
    return true;
  }

  bool test_3(bool x,int n,RealT y) {
    callcount += 2;
    return true;
  }

}; 

int main(int argc,char **argv)
{
  OptionC option(argc,argv);
  option.Check();
  
  Signal0C sig1(true);
  
  SignalConnectorC c1 = Connect(sig1,&test1);
  SignalConnectorC c2 = Connect(sig1,&test2);


  sig1();
  if(callcount != 3) {
    cerr<< "Signal test failed \n";
    return 1;
  }
  c1.Disconnect();
  sig1();
  if(callcount != 5) {
    cerr<< "Signal test failed \n";
    return 1;
  }
  SignalConnectorC c3 = Connect(sig1,&test2);
  sig1();
  if(callcount != 9) {
    cerr<< "Signal test failed \n";
    return 1;
  }
  Signal0C sig2(true);
  Connect(sig1,sig2);
  Connect(sig2,&test2);
  sig1();
  if(callcount != 15) {
    cerr<< "Signal test failed  " << callcount << "\n";
    return 1;
  }

#if 1
  // Some extra checks.
  Signal1C<bool> sig3(true);
  Signal2C<bool,int> sig4(true,1);
  Signal3C<bool,int,RealT> sig5(true,1,2.2);
  SignalConnectorC c4 = Connect(sig3,&test3);
  SignalConnectorC c5 = Connect(sig4,&test3);

  TestClassC aclass;
  SignalConnectorC c4a = Connect(sig3,aclass,&TestClassC::test3);
  SignalConnectorC c5a = Connect(sig4,aclass,&TestClassC::test_2);
  SignalConnectorC c6a = Connect(sig5,aclass,&TestClassC::test_3);

#if 0
  SignalConnectorC c4b = ConnectR(sig3,aclass,&TestClassC::test3);
  SignalConnectorC c5b = ConnectR(sig4,aclass,&TestClassC::test_2);
  SignalConnectorC c6b = ConnectR(sig5,aclass,&TestClassC::test_3);
#endif
#endif
  
  //  Launch(ae,&ExampleC::DoItArg,1);
  cerr << "testSignal(): Passed. \n";
  return 0;
}


template class Signal1C<IntT>;
template class Signal1BodyC<IntT>;

template class Signal2C<IntT,RealT>;
template class Signal2BodyC<IntT,RealT>;
template class Signal2FuncBodyC<IntT,RealT>;
template class Signal2FuncC<IntT,RealT>;
template class SignalConnector2BodyC<IntT,RealT>;
template class Signal2MethodC<IntT,RealT,Signal0C>;
template class SignalInterConnect2C<IntT,RealT>;

template class Signal3C<IntT,RealT,UIntT>;
template class Signal3BodyC<IntT,RealT,UIntT>;
template class Signal3FuncBodyC<IntT,RealT,UIntT>;
template class Signal3FuncC<IntT,RealT,UIntT>;
template class SignalConnector3BodyC<IntT,RealT,UIntT>;
template class Signal3MethodC<IntT,RealT,UIntT,Signal0C>;
template class SignalInterConnect3C<IntT,RealT,UIntT>;
