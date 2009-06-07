// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore

//#define RAVL_ARRAY1D_USE_SINGLEBUFFER 1

#include "Ravl/SingleBuffer.hh"
#include "Ravl/Array2d.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Option.hh"

using namespace RavlN;

template<class DataT>
class BlockArray2dC {
public:
  BlockArray2dC(UIntT rows,UIntT cols) 
    : buff(SingleBufferC<DataT>(rows * cols)),
      rng(rows,cols),
      stride(cols)
  { ptr = buff.ReferenceElm(); }
  //: Constructor.
  
  DataT &Access(IndexC r,IndexC c) { 
    return ptr[r.V() * stride + c.V()]; 
  }
  //: Access point in array.
  
#if 1
  inline const RangeBufferAccessC<DataT> operator[](IndexC i) const
  { return RangeBufferAccessC<DataT>(rng.Range2(),&ptr[i.V() * stride]); }
  //: return the item array[(i)]
  
  inline RangeBufferAccessC<DataT> operator[](IndexC i)
  { return RangeBufferAccessC<DataT>(rng.Range2(),&ptr[i.V() * stride]); }
  //: return the item array[(i)]
#else
  inline DataT *operator[](IndexC i)
  { return &(ptr[i.V() * stride]); }
  //: return the item array[i]
#endif
  
  SizeT Size1() const
  { return rng.Range1().Size(); }

  SizeT Size2() const
  { return rng.Range2().Size(); }
  
protected:
  BufferC<DataT> buff;
  IndexRange2dC rng;
  IntT stride;
  DataT *ptr;
};


void loopArray() {
  BlockArray2dC<UIntT> ba(1024,1024);
  UIntT count = 0;
  SizeT size1 = ba.Size1();
  SizeT size2 = ba.Size2();
  for(IndexC r = 0;r < size1;r++) {
    for(IndexC c = 0;c < size2;c++) {
      ba[r][c.V()] = count++;
    }
  }
  
  UIntT sum = 0;
  for(IndexC c = 0;c < size2;c++) {
    for(IndexC r = 0;r < size1;r++) {
      sum += ba[r][c.V()];
    }
  }
}


void loopArray2() {
  Array2dC<UIntT> ba(1024,1024);
  SizeT size1 = ba.Range1().Size();
  SizeT size2 = ba.Range2().Size();
  UIntT count = 0;
  for(IndexC r = 0;r < size1;r++) {
    for(IndexC c = 0;c < size2;c++) {
      ba[r][c] = count++;
    }
  }
  
  UIntT sum = 0;
  for(IndexC c = 0;c < size2;c++) {
    for(IndexC r = 0;r < size1;r++) {
      sum += ba[r][c];
    }
  }
}

void ArrayAlloc() {
#if 1
  for(int i = 0;i < 1000000;i++) {
    Array2dC<UIntT> array(100,100);
  }
#else
  Array1dC<UIntT> array(1); 
#endif
}

int main(UIntT nargs,char **argv) {
  OptionC opt(nargs,argv);
  UIntT loops = opt.Int("l",100,"Interations ");
  bool block = opt.Boolean("b",false,"Use simple block access.");
  bool testAlloc = opt.Boolean("a",false,"Test allocation speed ");
  bool verbose = opt.Boolean("v",false,"Verbose mode.");
  opt.Check();
  if(testAlloc) {
    ArrayAlloc();
    return 0;
  }
  if(block) {
    if(verbose)
      std::cerr << "Array2dC.. \n";
    for(int i = 0;i < loops;i++)
      loopArray2();
  } else {
    if(verbose)
      std::cerr << "BlockArray2dC.. \n";
    for(int i = 0;i < loops;i++)
      loopArray();
  }
  return 0;
}


