////////////////////////////////////////////
//! rcsid="$Id$"


#include "Ravl/Threads/Signal.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/Threads/Signal2.hh"
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

