// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
// $Id$
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/Slice1d.hh"
#include "Ravl/Buffer.hh"

using namespace RavlN;

int main()
{
  BufferC<UIntT> dataBuff(100);
  Slice1dC<UIntT> s1(10);
  Slice1dC<UIntT> s2(dataBuff,10,0,10);
  for(int i = 0;i < 10;i++)
    s1[i] = i;
  for(Slice1dIter2C<UIntT,UIntT> it(s2,s1);it;it++)
    it.Data1() = it.Data2();
  for(int i = 0;i < 10;i++) {
    if(s2[i] != (UIntT) i) {
      cerr << "Slice test failed. \n";
      return 1;
    }
  }
  return 0;
}

