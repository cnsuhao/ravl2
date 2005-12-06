// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Container/Queue/testPriQ.cc"
//! userlevel=Develop
//! author="Charles Galambos"
//! docentry="Ravl.API.Core.Queues"

#include "Ravl/BinStream.hh"
#include "Ravl/PriQueueL.hh"
#include "Ravl/Random.hh"
#include "Ravl/Stream.hh"

using namespace RavlN;

void SeqTest(void);
void InterTest(void);

int main() {
  cerr << "Starting test. \n";
  SeqTest();
  InterTest();
  return 0;
}

void SeqTest(void) {
  PriQueueLC<int,int> Queue;
  int i;
  for(i = 2;i < 10000;i++) {
    Queue.Insert(RandomInt(),i+1);
    //Queue.Dump();
  }
  int Last = Queue.TopKey();
  while(Queue.IsElm()) {
    Tuple2C<int,int> &KP =Queue.GetTopPair();
    const int Val = KP.Data2();
    const int Key = KP.Data1();
    if(Key < Last) {
      cerr << "\n ERROR !!! " << KP.Data1() << " " << Val << " \n";
      break;
    }
    Last = Key;
    //printf("(%d %d) ",KP.Data1(),Val);
  }
  
  cerr << "Sequence test passed. \n";
  return ;
}  

void InterTest(void) {
  PriQueueLC<int,int> Queue;
  int i,Last;
  
  for(i = 1;i < 10000;i++)
    Queue.Insert(RandomInt(),i+1);
  cerr << "Starting Interleave. \n";
  for(int k = 0;k < 1000;k++) {
    // Remove
    Last = Queue.TopKey();
    for(i = 1;i < 10;i++) {
      Tuple2C<int,int> &KP =Queue.GetTopPair();
      const int Val = KP.Data2();
      const int Key = KP.Data1();
      if(Key < Last) {
	cerr << "\n ERROR !!! " << KP.Data1() << " " << Val << " \n";
	break;
      }
      Last = Key;
    }
    // Insert.
    for(i = 1;i < 10;i++) {
      Queue.Insert(RandomInt(),i+1);
    }
  }
  cerr << "Checking remaining queue. \n";
  Last = Queue.TopKey();
  while(Queue.IsElm()) {
    Tuple2C<int,int> &KP =Queue.GetTopPair();
    const int Val = KP.Data2();
    const int Key = KP.Data1();
    if(Key < Last) {
      cerr << "\n ERROR !!! " << KP.Data1() << "  " <<Val << " \n";
      break;
    }
    Last = Key;
  }
  
  cerr << "Interleave test passed. \n";
  return ;
}

template class  PriQueueLC<int,UIntT>;

