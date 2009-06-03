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
//! docentry="Ravl.API.Core.Arrays.Buffer"
//! author="Charles Galambos"
//! userlevel=Develop

#include "Ravl/Buffer2d.hh"
#include "Ravl/AttachedBuffer2d.hh"
#include "Ravl/SizeBufferAccess2d.hh"
#include "Ravl/RangeBufferAccess2d.hh"
#include "Ravl/SingleBuffer.hh"
#include "Ravl/SingleBuffer2d.hh"
#include "Ravl/Stream.hh"
#include "Ravl/IntC.hh"

#include "Ravl/BufferAccessIter2.hh"
#include "Ravl/BufferAccessIter3.hh"
#include "Ravl/BufferAccessIter4.hh"
#include "Ravl/BufferAccessIter5.hh"
#include "Ravl/BufferAccessIter6.hh"
#include "Ravl/BufferAccessIter7.hh"

#include "Ravl/BufferAccess2dIter2.hh"
#include "Ravl/BufferAccess2dIter3.hh"
#include "Ravl/BufferAccess2dIter4.hh"
#include "Ravl/BufferAccess2dIter5.hh"
#include "Ravl/BufferAccess2dIter6.hh"
#include "Ravl/BufferAccess2dIter7.hh"

using namespace RavlN;

int TestBuffer();
int TestSingleBuffer();
int TestSingleBuffer2d();
int TestBuffer2d();
int TestSizeBuffer2d();

int main()
{
  int ln;
  if((ln = TestBuffer()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = TestSingleBuffer()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = TestBuffer2d()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = TestSingleBuffer2d()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = TestSizeBuffer2d()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";
  return 0;
}

int TestBuffer() {
  for(unsigned  i = 0;i < 20;i++) {
    BufferC<int> buf(i);
    if(buf.Size() != i)
      return __LINE__;
    buf.Fill(i);
    for(unsigned j = 0;j < i;j++) {
      if(buf.ReferenceElm()[j] != (int)i)
        return __LINE__;
    }
  }
  return 0;
}

int TestBuffer2d() {
  IndexRangeC r1(1,3);
  IndexRangeC r2(2,5);
  
  Buffer2dC<int> bf (r1.Size(),r2.Size());
  if(bf.Size1() != (UIntT) r1.Size()) {
    cerr << "Size1 test failed. \n";
    return __LINE__;
  }
  if(bf.Size2() != (UIntT) r2.Size()) {
    cerr << "Size2 test failed. \n";
    return __LINE__;
  }
  
  //cerr << "Buffer at :" << ((void *) bf.Data().ReferenceElm()) << "\n";
  RangeBufferAccess2dC<int> rba;
  rba.Attach(bf,r1,r2,bf.ByteStride());
  
  if(r1 != rba.Range1()) {
    cerr<< "Range 1 incorrect. " << rba.Range1() <<" should be " << r1 << "\n";
    return __LINE__;
  }

  if(r2 != rba.Range2()) {
    cerr<< "Range 2 incorrect. " << rba.Range2() <<" should be " << r2 << "\n";
    return __LINE__;
  }
    
  if(&(rba[rba.Range1().Min()][rba.Range2().Min()]) != bf.ReferenceElm()) {
    cerr << "Buffer setup incorrect. Min@" << ((void *)&(rba[rba.Range1().Min()][rba.Range2().Min()])) << "\n";
    return __LINE__;
  }
  
  BufferAccess2dIterC<int> it(rba);
  if(!it.IsElm()) {
    cerr << "Failed to create valid iterator. \n";
    return __LINE__;
  }
  if(&(*it) != &(rba[rba.Range1().Min()][rba.Range2().Min()])) {
    cerr << "Inital iterator position incorrect. " << ((void *) &(*it) ) << " should be " << ((void *) &(rba[rba.Range1().Min()][rba.Range2().Min()])) <<  "\n";
    return __LINE__;
  }
  int count = 0;
  for(;it;it++) {
    *it = count++;
  }
  int totalSize = r1.Size() * r2.Size();
  if(count != totalSize) {
    std::cerr << "Iterator count mismatch. Counted=" << count << " Size=" << totalSize << "\n";
    return __LINE__;
  }
  // Check numbers are as expected.
  count = 0;
  it.First(rba.BufferAccess(),rba.ByteStride(),rba.Range1(),rba.Range2());
  for(IndexC i = r1.Min();i <= r1.Max();i++) {
    for(IndexC j = r2.Min();j <= r2.Max();j++,count++,it++) {
      // Check values match.
      if(rba[i][j] != count)
        return __LINE__;
      // Check reported index is correct.
      if(rba.IndexOf(*it) != Index2dC(i,j)) {
        std::cerr << "Index mismatch. Got=" <<  rba.IndexOf(*it) << " Expected=" << Index2dC(i,j) << "\n";
        return __LINE__;
      }
    }
  }
  return 0;
}

class TestObjC {
public:
  TestObjC() 
  { val = 123; }
  
  int Value()
  { return val; }
protected:
  int val;
};

int TestSingleBuffer() {
  cerr << "Single Buffer Size=" << sizeof(SingleBufferBodyC<RealT>) - sizeof(RealT) << "\n";

  for(int i = 0;i < 100;i++) {
    SingleBufferC<IntT> buff(i+1);
    //cerr << "UMem=" << ((void *) buff.ReferenceElm()) << "\n";
  }
  for(int i = 0;i < 100;i++) {
    SingleBufferC<SizeT> buff(i+1,16);
    if((((SizeT)((void *) buff.ReferenceElm())) & 0xf) != 0)
      return __LINE__;
    //cerr << "AMem=" << ((void *) buff.ReferenceElm()) << "\n";
  }
  SingleBufferC<IntC> buff2(100);
  IntC *at = buff2.ReferenceElm();
  IntC *end = &(at[buff2.Size()]);
  for(;at != end;at++)
    if(*at != 0) return __LINE__;
  
  SingleBufferC<TestObjC> buff3(100);
  TestObjC *at3 = buff3.ReferenceElm();
  TestObjC *end3 = &(at3[buff3.Size()]);
  for(;at3 != end3;at3++)
    if(at3->Value() != 123) return __LINE__;
  cerr << "Single Buffer Done.\n";
  return 0;
}

int TestSingleBuffer2d() {
  std::cerr << "SingleBuffer2dBodyC<DataT> size=" << sizeof(SingleBuffer2dBodyC<IntT>) << " Alignment Offset=" << SingleBuffer2dBodyC<IntT>::StartAlignmentOffset()<< "\n";
  
  for(unsigned i = 1;i < 20;i++) {
    for(unsigned j = 1;j < 20;j++) {
      //cerr << "Test " << i  << " " << j << "\n";
      // Test unaligned allocation.
      SingleBuffer2dC<IntT> buffc(i,j);
      if(buffc.Size1() != i)
        return __LINE__;
      if(buffc.Size2() != j)
        return __LINE__;
      if(buffc.ByteStride() < static_cast<IntT>(j * sizeof(IntT))) {
        std::cerr << " " << i << " " << j << " Stride = " << buffc.ByteStride() << " " << (j * sizeof(IntT)) << "\n";
        return __LINE__;
      }
      
      // Test aligned allocation.
      SingleBuffer2dC<SizeT> buff(i,j,16);
      if(buff.Size1() != i)
        return __LINE__;
      if(buff.Size2() != j)
        return __LINE__;

      if((((SizeT)((void *) buff.ReferenceElm())) & 0xf) != 0)
        return __LINE__;
      if((buff.ByteStride() & 0xf) != 0)
        return __LINE__;
      if(buff.ByteStride() < static_cast<IntT>(j * sizeof(SizeT)))
        return __LINE__;
    }
  }

  SingleBuffer2dC<IntC> buff2(100,17);
  IntC *ref = buff2.ReferenceElm();
  IntC *at;
  for(int i = 0;i < 100;i++) {
    at = ref;
    for(int j = 0;j < 17;j++,at++) {
      if(*at != 0) return __LINE__;
    }
    ref = ShiftPointerInBytes(ref,buff2.ByteStride());
  }
  
  SingleBuffer2dC<TestObjC> buff3(100,17);
  TestObjC *ref3 = buff3.ReferenceElm();
  TestObjC *at3;
  
  for(int i = 0;i < 100;i++) {
    at3 = ref3;
    for(int j = 0;j < 17;j++,at++) {
      if(at3->Value() != 123) return __LINE__;
    }
    ref3 = ShiftPointerInBytes(ref3,buff3.ByteStride());
  }
  
  std::cerr << "SingleBuffer2dC,  Done. \n";
  return 0;
}


int TestSizeBuffer2d() {
  const int rows = 9;
  const int cols = 10;
  Buffer2dC<int> bf (rows,cols);
  if(bf.ByteStride() < (IntT)(rows * sizeof(int)))
    return __LINE__;
  SizeBufferAccess2dC<int> sba;
  sba.Attach(bf,rows,cols);
  if(sba.Size1() != (SizeT) rows) return __LINE__;
  if(sba.Size2() != (SizeT) cols) return __LINE__;
  if(sba.ReferenceElm() != bf.ReferenceElm())
    return __LINE__;
  if(sba.ByteStride() != bf.ByteStride())
    return __LINE__;
  int place = 0;
  // Write some numbers.
  for(int i = 0;i < rows;i++) {
    for(int j = 0;j < cols;j++) {
      sba[i][j] = place++;
    }
  }
  // Check they're still there.
  place = 0;
  for(int i = 0;i < rows;i++) {
    for(int j = 0;j < cols;j++) {
      if(sba[i][j] != place++)
        return __LINE__;
    }
  }
  // Check basic iteration.
  place = 0;
  int count = 0;
  for(BufferAccess2dIterC<int> it(sba);it;it++,place++) {
    if(*it != place) {
      std::cerr << "Test failed. Got=" << *it << " expected=" << place << "\n";
      return __LINE__;
    }
    count++;
  }
  if(count != (rows * cols))
    return __LINE__;
  return 0;
}


// Check all methods compile.

template class BufferBodyC<IntT>;
template class BufferC<IntT>;
template class AttachedBuffer2dC<IntT>;
template class SizeBufferAccess2dC<IntT>;
template class RangeBufferAccess2dC<IntT>;
template class Buffer2dBodyC<IntT>;
template class Buffer2dC<IntT>;

template class BufferAccess2dIterC<char>;
template class BufferAccess2dIter2C<int,char>;
template class BufferAccess2dIter3C<float,int,char>;
template class BufferAccess2dIter4C<bool,float,int,char>;
template class BufferAccess2dIter5C<unsigned,bool,float,int,char>;
template class BufferAccess2dIter6C<double,unsigned,bool,float,int,char>;
template class BufferAccess2dIter7C<long int,double,unsigned,bool,float,int,char>;
