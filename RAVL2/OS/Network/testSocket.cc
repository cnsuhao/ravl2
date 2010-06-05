// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: testSocket.cc 5570 2006-06-09 15:12:15Z craftit $"
//! lib=RavlNet
//! file="Ravl/OS/Network/testSocket.cc"

#include "Ravl/Option.hh"
#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/OS/NetStream.hh"
#include "Ravl/Stream.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/Random.hh"
#include "Ravl/Threads/Semaphore.hh"

#include <signal.h>

using namespace RavlN;

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x) 
#endif

StringC address;
bool buffer;
int totalSize = 100000;
bool testFreeze = false;
SemaphoreC serverReady(0);
int timeout = 15;
volatile bool error = false;

bool TransmitThread() {
  SocketC os(address,true);
  if(!os.IsOpen()) {
    error = true;
    return true;
  }
  serverReady.Post(); 
  os = os.Listen();
  os.SetNonBlocking(true);
  os.SetWriteTimeout(timeout);
  cerr << "Transmit started. \n";
  for(int i = 0;i < totalSize && ! error;) {
    int a[257],b[257],c[257];
    int b1s = Round(Random1() * 255) + 1;
    for(int k = 0;k < b1s;k++)
      a[k] = i++;
    int b2s = Round(Random1() * 255) + 1;
    for(int k = 0;k < b2s;k++)
      b[k] = i++;
    int b3s = Round(Random1() * 255) + 1;
    for(int k = 0;k < b3s;k++)
      c[k] = i++;
    char *bufs[3];
    int lens[3];
    bufs[0] = (char *) a;
    lens[0] = sizeof(int) * b1s;
    bufs[1] = (char *) b;
    lens[1] = sizeof(int) * b2s;
    bufs[2] = (char *) c;
    lens[2] = sizeof(int) * b3s;
    int total = lens[0] + lens[1] + lens[2];
    int n = os.WriteV((const char **) bufs,lens,3);
    if(n != total) {
      cerr << "WriteV(), ERROR: Total=" << total << " n=" << n << "\n";
      error = true;
      break;
    }
    //if(Random1() < 0.3)
    // Sleep(0.1);
  }
  cerr << "Transmit done. \n";
  Sleep(5);
  cerr << "Transmit exited. \n";
  
  return 0;
}

int RecieveThread() {
  SocketC is(address,false);
  int n = 10;
  while(!is.IsOpen() && n-- > 0) {
    cerr << "RecieveThread(), Failed to open socket. Retrying. \n";
    Sleep(0.02);
    is = SocketC(address,false);
  }
  if(!is.IsOpen()) {
    error = true;
    return __LINE__;
  }
  serverReady.Wait(); 
  is.SetNonBlocking(true);
  bool error = false;
  for(int i = 0;i < totalSize && !error;) {
    int a[257],b[257],c[257];
    int b1s = Round(Random1() * 256) + 1;
    int b2s = Round(Random1() * 256) + 1;
    int b3s = Round(Random1() * 256) + 1;
    char *bufs[3];
    int lens[3];
    bufs[0] = (char *) a;
    lens[0] = sizeof(int) * b1s;
    bufs[1] = (char *) b;
    lens[1] = sizeof(int) * b2s;
    int total = lens[0] + lens[1];
    int n = is.ReadV(bufs,lens,2);
    if(n < total) {
      cerr << "ReadV(), Total=" << total << " n=" << n << " i=" << i << "\n";
      if(i > (totalSize - 256)) // Just end of stream ?
	return 0;
      if(n != total) {
	error = true;
	break;
      }
    }
    for(int k = 0;k < b1s;k++)
      if(a[k] != i++) { error = true; break; }
    for(int k = 0;k < b2s;k++)
      if(b[k] != i++) { error = true; break; }
    total = sizeof(int) * b3s;
    n = is.Read((char *) c,total);
    if(n < total) {
      ONDEBUG(cerr << "Read(), Total=" << total << " n=" << n << " i=" << i << "\n");
      if(i > (totalSize - 64)) // Just end of stream ?
	return 0;
      error = true;
      break;
    }
    
    for(int k = 0;k < b3s;k++)
      if(c[k] != i++) { error = true; break; }
    cerr << "." << flush;
    if(Random1() < 0.4)
      Sleep(0.1);
    if(testFreeze)
      break;
  }
  if(testFreeze) {
    cerr << "Freezing reader thread. \n";
    while(testFreeze)
      Sleep(10);
  }
  if(error) {
    cerr << "Test failed. \n";
    return __LINE__;
  }
  cerr << "Recieve done. \n";
  return 0;
}

int main(int nargs,char **argv)
{
  OptionC opts(nargs,argv);
  address = opts.String("h","localhost:4248","Network address to use. ");
  buffer = opts.Boolean("b",false,"Buffer. ");
  totalSize = opts.Int("s",100000,"Test size. ");
  testFreeze = opts.Boolean("f",false,"Test reader freeze. ");
  timeout = opts.Int("to",30,"Set write timeout. ");;
  opts.Check();
  
  // Ignore broken pipe signals
  signal(SIGPIPE,SIG_IGN);
  
  LaunchThread(&TransmitThread);
  if(RecieveThread() != 0)
    return 1;
  if(error) {
    cerr << "Test failed. \n";
    return 1;
  }
  return 0;
}
