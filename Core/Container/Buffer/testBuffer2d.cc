// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
// $Id$
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Container/Buffer/testBuffer2d.cc"

#include "Ravl/Buffer2d.hh"
#include "Ravl/SBfAcc2d.hh"
#include "Ravl/RBfAcc2d.hh"

using namespace RavlN;

int main()
{
  BufferC<int> bf1d (6);
  if(bf1d.Size() != 6) {
    cerr << "Size test failed. \n";
    return 1;
  }
  
  IndexRangeC r1(1,3);
  IndexRangeC r2(2,5);
  
  Buffer2dC<int> bf (r1.Size(),r2.Size());
  if(bf.Size1() != r1.Size()) {
    cerr << "Size1 test failed. \n";
    return 1;
  }
  if(bf.Size2() != r2.Size()) {
    cerr << "Size2 test failed. \n";
    return 1;
  }
  
  //cerr << "Buffer at :" << ((void *) bf.Data().ReferenceElm()) << "\n";
  RangeBufferAccess2dC<int> rba(r2);
  rba.Attach(bf,r1);
  
  if(r1 != rba.Range1()) {
    cerr<< "Range 1 incorrect. " << rba.Range1() <<" should be " << r1 << "\n";
    return 1;
  }

  if(r2 != rba.Range2()) {
    cerr<< "Range 2 incorrect. " << rba.Range2() <<" should be " << r2 << "\n";
    return 1;
  }
  
  {
    // Build the access structure.
    const SizeT d2Size = rba.Range2().Size();
    int *at = bf.Data().ReferenceElm() - rba.Range2().Min().V();
    for(BufferAccessIterC<BufferAccessC<int> > it(rba);it;it++,at += d2Size)
      *it = at;
  }
  
  if(&(rba[rba.Range1().Min()][rba.Range2().Min()]) != bf.Data().ReferenceElm()) {
    cerr << "Buffer setup incorrect. Min@" << ((void *)&(rba[rba.Range1().Min()][rba.Range2().Min()])) << "\n";
    return 1;
  }
  
  BufferAccess2dIterC<int> it(rba,r2);
  if(!it.IsElm()) {
    cerr << "Failed to create valid iterator. \n";
    return 1;
  }
  if(&(*it) != &(rba[rba.Range1().Min()][rba.Range2().Min()])) {
    cerr << "Inital iterator position incorrect. " << ((void *) &(*it) ) << " should be " << ((void *) &(rba[rba.Range1().Min()][rba.Range2().Min()])) <<  "\n";
    return 1;
  }
  for(;it;it++)
    *it = 0;
  cerr << "Test passed ok. \n";
  return 0;
}
