// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlThreads
//! author="Charles Galambos"

#include "Ravl/Threads/Signal.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/Threads/Signal2.hh"
#include "Ravl/Threads/Signal3.hh"
#include "Ravl/Option.hh"

//#include "Ravl/Threads/LaunchThread.hh"

using namespace RavlN;

int count = 0;

bool test1() {
  count++;
  return true;
}

bool test2() {
  count += 2;
  return true;
}

int main(int argc,char **argv)
{
  OptionC option(argc,argv);
  option.Check();

#if 0
  Signal1C<bool> ts1;
  Signal2C<bool,int> ts2;
#endif

  Signal0C sig1(true);
  
  SignalConnectorC c1 = Connect(sig1,&test1);
  SignalConnectorC c2 = Connect(sig1,&test2);

  sig1();
  if(count != 3) {
    cerr<< "Signal test failed \n";
    return 1;
  }
  c1.Disconnect();
  sig1();
  if(count != 5) {
    cerr<< "Signal test failed \n";
    return 1;
  }
  SignalConnectorC c3 = Connect(sig1,&test2);
  sig1();
  if(count != 9) {
    cerr<< "Signal test failed \n";
    return 1;
  }
  Signal0C sig2(true);
  Connect(sig1,sig2);
  Connect(sig2,&test2);
  sig1();
  if(count != 15) {
    cerr<< "Signal test failed  " << count << "\n";
    return 1;
  }
  
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
