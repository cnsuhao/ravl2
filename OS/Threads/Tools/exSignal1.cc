// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlThreads

#include "Ravl/Threads/Signal1.hh"

using namespace RavlN;

bool PrintNumberA(int &i) {
  cout << "PrintNumberA called with value " << i << "\n";
  return true;
}

bool PrintNumberB(int &i) {
  cout << "PrintNumberB called with value " << i << "\n";
  return true;
}

int main() {
  
  // Create two signals with a single integer argument.
  
  Signal1C<int> sig1(0);
  Signal1C<int> sig2(0);

  // Connect sig1 to a function which prints the signal value.
    
  Connect(sig1,PrintNumberA); 

  // Connect sig2 to a function which prints the signal value.
  
  Connect(sig2,PrintNumberB); 

  // Connect signal 1 to signal 2.  
  // If sig1 is invoked, sig2 will also be triggered
  
  Connect(sig1,sig2);

  // Trigger signal 1.  Both PrintNumberA and PrintNumberB will be called.
  
  cout << "Triggering signal 'sig1' with value 1 \n";
  sig1(1); // Send a signal.
  
  // Trigger signal 2.  Only PrintNumberB will be called.
  
  cout << "Triggering signal 'sig2' with value 2 \n";
  sig2(2);
  
  return 0;
}
