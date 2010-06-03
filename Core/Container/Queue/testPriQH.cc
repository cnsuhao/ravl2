// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////////
//! rcsid="$Id: testPriQH.cc 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlCore
//! file="Ravl/Core/Container/Queue/testPriQH.cc"
//! author="Charles Galambos"
//! docentry="Ravl.API.Core.Queues"
//! userlevel=Develop

#include "Ravl/BinStream.hh"
#include "Ravl/PriQueue.hh"
#include "Ravl/Random.hh"
#include "Ravl/Stream.hh"
#include <stdlib.h>

using namespace RavlN;

bool SeqTest(void);
bool InterTest(void);

#ifndef __sgi__
template class RCWrapBodyC<SDArray1dC<Tuple2C<int, int> > >;
#endif

int main() {
  cerr << "Starting test. \n";
  SeqTest();
  InterTest();
  return 0;
}

bool SeqTest(void) {
  PriQueueC<int,int> Queue(10000);
  int i;
  for(i = 2;i < 10000;i++) {
    Queue.Insert(rand(),i+1);
    //Queue.Dump();
  }
  int Last = Queue.TopKey();
  bool ok(true);
  while(Queue.IsElm()) {
    Tuple2C<int,int> KP =Queue.GetTopPair();
    //Queue.Check();
    const int Val = KP.Data2();
    const int Key = KP.Data1();
    if(Key < Last) {
      cerr << "\n ERROR !!! " << Key << " " << Val << " (Last: " << Last << ") \n";
      ok = false;
      break;
    }
    Last = Key;
    //cerr << "(%d %d) ",KP.Data1(),Val);
  }
  if(ok)
    cerr << "Sequence test passed. \n";
  else
    cerr << "Sequence test failed. \n";
  return ok;
}  

bool InterTest(void) {
  PriQueueC<int,int> Queue(10000);
  int i,Last;
  bool ok = true;
  for(i = 1;i < 10000;i++) {
    Queue.Insert(rand(),i+1);
  }
  cerr << "Starting Interleave. \n";
  for(int k = 0;k < 1000;k++) {
    // Remove
    Last = Queue.TopKey();
    for(i = 1;i < 10;i++) {
      Tuple2C<int,int> KP =Queue.GetTopPair();
      const int Val = KP.Data2();
      const int Key = KP.Data1();
      if(Key < Last) {
	cerr << "\n ERROR !!! " << KP.Data1() << " " << Val << " \n";
	ok = false;
	break;
      }
      Last = Key;
    }
    // Insert.
    for(i = 1;i < 10;i++) {
      Queue.Insert(rand(),i+1);
    }
  }
  cerr << "Checking remaining queue. \n";
  Last = Queue.TopKey();
  while(Queue.IsElm()) {
    Tuple2C<int,int> KP =Queue.GetTopPair();
    const int Val = KP.Data2();
    const int Key = KP.Data1();
    if(Key < Last) {
      cerr << "\n ERROR !!! " << KP.Data1() << " " << Val << " \n";
      ok = false;
      break;
    }
    Last = Key;
  }
  
  cerr << "Interleave test passed. \n";
  return ok;
}

template class PriQueueC<int,int>;
