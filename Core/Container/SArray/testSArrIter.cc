// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Container/SArray/testSArrIter.cc"

#include "Ravl/SArray1dIter.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SArray1dIter3.hh"
#include "Ravl/SArray1dIter4.hh"
//#include "Ravl/SArray2dIter.hh"

using namespace RavlN;

int main() {
  SArray1dC<int> test(100);
  SArray1dC<int> test2(100);
  int x = 10;
  for(SArray1dIterC<int> it(test);it.IsElm();it.Next())
    it.Data() = x++;
  if((x-10) != (int) test.Size()) {
    cerr << "Error. \n";
    return 2;
  }
  x = 10;
  for(int i = 0;i < (int) test.Size();i++) {
    if(test[i] != x++) {
      cerr << "Error. \n";
      return 1;
    }
  }
  
  SArray1dC<int> test3;
  SArray1dIterC<int> it2(test3);
  if(it2.IsElm()) {
    cerr << "Error. \n";
    return 3;
  }

  // Check the iterators instanciate properly.
  x = 0;
  for(SArray1dIter2C<int,int> itx2(test,test);itx2;itx2++)
    x++;
  
  for(SArray1dIter3C<int,int,int> itx3(test,test,test);itx3;itx3++)
    x++;
  
  for(SArray1dIter4C<int,int,int,int> itx4(test,test,test,test);itx4;itx4++)
    x++;
  
  if(x != 300) {
    cerr << "Error. \n";
    return 1;
  }
  
  cout << "Test completed ok.\n";
  return 0;
}
