// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////
//! author="Lee Gregory"
//! userlevel=Normal
//! docentry="Ravl.API.OS.Threads"
//! rcsid="$Id: exLaunchThread.cc 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Tools/exLaunchThread.cc"

#include "Ravl/Stream.hh"
#include "Ravl/Calls.hh"
#include "Ravl/CallMethodRefs.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/Threads/LaunchThread.hh"
using namespace RavlN ; 



// Some Test Functions 
// --------------------
 
bool Func1 (void) 
{
  for (UIntT i = 1 ; i <= 10 ; ++i ) 
    {
      Sleep(1) ; 
      cout << "\n Func1 counting:" << i ; 
    }
  return true ; 
}


bool Func2 (IntT & dummy) 
{
  for ( UIntT i = 1 ; i <= 15 ; i++ ) 
    { 
      Sleep(1) ; 
      cout << "\n Func2 counting:" << i ; 
    }
  return true ;
}





// Main Program - demonstrate simple use of Launchthread

int main (void) 
{
  
  TriggerC 
    trig1 = Trigger (&Func1),
    trig2 = Trigger (&Func2, 0) ;   
  
  LaunchThreadC thread1 = LaunchThread ( trig1 ) ; 
  LaunchThreadC thread2 = LaunchThread ( trig2 ) ; 
  
  for ( UIntT i = 1 ; i <= 5 ; ++i ) 
    { Sleep(1) ; cout << "\n Main counting " ; } 

  thread1.WaitForExit() ; 
  cout << "\n\n **** Thread 1 Finished " ; 
  thread2.WaitForExit() ; 
  cout << "\n\n **** Thread 2 Finished \n\n" ; 

}
