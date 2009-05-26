// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Base/testRavlBase.cc"
//! userlevel=Develop
//! docentry="Ravl.API.Core"

#include "Ravl/RefCounter.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/RCWrap.hh"
#include "Ravl/IndexRange1d.hh"
#include "Ravl/IndexRange2d.hh"
#include "Ravl/IntC.hh"
#include "Ravl/SubIndexRange2dIter.hh"
#include "Ravl/SubIndexRange3dIter.hh"
#include "Ravl/Stream.hh"
#include "Ravl/IndexRange2dIter.hh"
#include "Ravl/IndexRange3dIter.hh"
#include "Ravl/FPNumber.hh"
#include "Ravl/Exception.hh"
#include "Ravl/QInt.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/Float16.hh"

using namespace RavlN;

class TestBodyC
  : public RCBodyVC
{
public:
  TestBodyC()
  {}
};


int testTypes();
int testEndian();
int testIndex();
int testIndex2d();
int testMisc();
int testRefCounter();
int testSubIndexRange2dIter();
int testSubIndexRange3dIter();
int testIndexRange2dIter();
int testIndexRange3dIter();
int testFPNumber();
int testException();
int testQInt();
int testIndexRange2d();
int testRCWrap();
int testFloat16();

template class RCHandleC<TestBodyC>;
template class RCWrapC<IntT>;

int main()
{
#if RAVL_OS_LINUX64
  cerr << "Linux 64 enabled. \n";
#endif
  int ln;
  if((ln = testTypes()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testEndian()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testIndex()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testIndex2d()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testMisc()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testRefCounter()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testSubIndexRange2dIter()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testSubIndexRange3dIter()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testIndexRange2dIter()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testIndexRange3dIter()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testFPNumber()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testException()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testQInt()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testIndexRange2d()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testRCWrap()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testFloat16()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  cout << "Test completed ok. \n";
  return 0;
}

int testTypes()
{
  if(sizeof(Int16T) != 2) return __LINE__;
  if(sizeof(UInt16T) != 2) return __LINE__;
  if(sizeof(Int64T) != 8) return __LINE__;
  if(sizeof(UInt64T) != 8) return __LINE__;
#if RAVL_USE_LARGEFILESUPPORT
  cerr << "Large file support: Enabled. \n";
  if(sizeof(StreamSizeT) < 8) return __LINE__;
  if(sizeof(StreamOffsetT) < 8) return __LINE__;
  if(sizeof(streampos) < 8) return __LINE__;
#else
  cerr << "Large file support: Disabled. \n";
  if(sizeof(StreamSizeT) < 4) return __LINE__;
  if(sizeof(StreamOffsetT) < 4) return __LINE__;
#endif
  return 0;
}

int testEndian() {
  UInt16T x = 0x1234;
#if RAVL_LITTLEENDIAN
cerr << "\n doing little endian test\n" ;
  if(((char *)(&x))[0] != 0x34) return __LINE__;
  if(((char *)(&x))[1] != 0x12) return __LINE__;
#else
cerr << "\n doing big endian test\n" ;
  if(((char *)(&x))[0] != 0x12) return __LINE__;
  if(((char *)(&x))[1] != 0x34) return __LINE__;
#endif
  return 0;
}

int testIndex()
{
  IndexC i(5);
  IndexC j(-4);
  IntT p(3);
  IntT q(-3);
  UIntT u(3);
  // This line is the invariant test defined in ANSII C
  if (i != (i/p)*p + i%p || i != (i/q)*q + i%q || i != (i/u)*u + i%u
      || j != (j/p)*p + j%p || j != (j/q)*q + j%q || j != (j/u)*u + j%u)
    return __LINE__;
  // These 2 lines test the RAVL convention for modulo involving -ve numbers
  if (i/p != 1 || i/q != -1 || i/u != 1 
      || j/p != -2 || j/q != 2 || j/u != -2) return __LINE__;
  if (i%p != 2 || i%q != 2 || i%u != 2 
      || j%p != 2 || j%q != 2 || j%u != 2) return __LINE__;

  IndexRangeC r1(0,3);
  IndexRangeC r2(1,2);
  IndexRangeC r3(r1);
  r3.ClipBy(r2);
  if(!r1.Contains(r3)) {
    cerr << "IndexRange test 1 failed " << r1 << " does not contain " << r3 << "\n";
    return __LINE__;
  }
  if(!r2.Contains(r3)) {
    cerr << "IndexRange test 2 failed. " << r2 << " does not contain " << r3 << "\n";
    return __LINE__;
  }
  
  IndexRangeC xr1(r1);
  IndexRangeC xr2(4,5);
  xr1.ClipBy(xr2);
  if(xr1.Size() != 0) return __LINE__;
  xr1 = r1;
  xr2 = IndexRangeC (-10,-2);
  xr1.ClipBy(xr2);
  if(xr1.Size() != 0) return __LINE__;
  
  if((IndexC(-4) % 3) != 2) return __LINE__;
  
  // Check align within 
  for(int i = 1;i < 8;i++) {
    for(int j = 0;j < 10;j++) {
      for(int k = -10;k < 10;k++) {
        IndexRangeC rng(j,j+k);
        IndexRangeC srng = rng.AlignWithin(i);
        //cerr << "I=" << i << " Rng=" << rng << " SRng=" << srng << " Size=" << srng.Size() <<"\n";
        if(srng.Size() > 0) {
          if(!rng.Contains(srng)) return __LINE__;
          if(srng.Min() % i != 0) return __LINE__;
          if(srng.Size() % i != 0) return __LINE__;
        }
      }
    }
  }
  return 0;
}


int testIndex2d()
{
  cerr << "testIndex2d() \n";
  Index2dC start(5,6);
  
  {
    Index2dC pxx = start;
    pxx = pxx.Step(NEIGH_UP_LEFT);
    if(pxx != (start + Index2dC(-1, -1))) return __LINE__;
    SetZero(pxx);
    if(pxx != Index2dC(0,0)) return __LINE__;
  }
  return 0;
}

int testMisc() {
  if(Abs((IntT) -2) != 2) return __LINE__;
  if(Abs((IntT) 2) != 2) return __LINE__;
  if(Sign((IntT) -2) != -1) return __LINE__;
  if(Sign((IntT) 2) != 1) return __LINE__;
  if(Round(0.3) != 0) return __LINE__;
  if(Round(0.7) != 1) return __LINE__;
  if(Floor(0.3) != 0) return __LINE__;
  if(Floor(0.7) != 0) return __LINE__;
  if(Floor(1.2) != 1) return __LINE__;

  UIntC x = 4;
  UIntC y = 5;
  IntT v = Abs((int) x -  y);
  if(v != 1) return __LINE__;

  return 0;
}


int testRefCounter() {
  // Check atomic counting is sane.
  ravl_atomic_t test = RAVL_ATOMIC_INIT(0);
  if(ravl_atomic_read(&test) != 0)  return __LINE__;
  ravl_atomic_set(&test,1); 
  if(ravl_atomic_read(&test) != 1)  return __LINE__;
  ravl_atomic_inc(&test);
  if(ravl_atomic_read(&test) != 2)  {
    cerr << "Value ="  << ravl_atomic_read(&test) << "\n";
    return __LINE__;
  }
  ravl_atomic_dec(&test);
  if(ravl_atomic_read(&test) != 1)  return __LINE__;
  ravl_atomic_inc(&test);
  if(ravl_atomic_dec_and_test(&test)) return __LINE__;
  if(!ravl_atomic_dec_and_test(&test)) return __LINE__;
  return 0;
}

int testSubIndexRange2dIter() {
  IndexRange2dC rect1(0,6,0,5);
  IndexRange2dC rect2(IndexC(5),IndexC(5));
  //cerr << "Area=" << rect2.Area() << "\n";
  int rects = 0;
  for(SubIndexRange2dIterC it(rect1,rect2);it;it++) {
    if(it.Window().Area() != rect2.Area()) return __LINE__;
    rects++;
  }
  if(rects != 6) return __LINE__;
  return 0;
}

int testSubIndexRange3dIter() {
  IndexRange3dC rect1(0,5,0,6,0,7);
  IndexRange3dC rect2(IndexC(5),IndexC(5),IndexC(5));
  //cerr << "Area=" << rect2.Area() << "\n";
  int rects = 0;
  for(SubIndexRange3dIterC it(rect1,rect2);it;it++) {
    if(it.Window().Volume() != rect2.Volume()) return __LINE__;
    rects++;
  }
  if(rects != 24) return __LINE__;
  return 0;
}

int testIndexRange2dIter() {
  IndexRange2dC rect(2,3);
  int count = 0;
  for(IndexRange2dIterC it(rect);it;it++)
    count++;
  if(rect.Area() != (UIntT) count) return __LINE__;
  return 0;
}

int testIndexRange3dIter() {
  IndexRange3dC rect(2,3,4);
  int count = 0;
  for(IndexRange3dIterC it(rect);it;it++)
    count++;
  if(rect.Volume() != (UIntT) count) return __LINE__;
  return 0;
}

int testFPNumber() {
#if !RAVL_COMPILER_GCC2
  
  // Check conversion an equality.
  FPNumberC<8> p8 = 1;
  if(p8 != 1) return __LINE__;
  if(!(p8 == 1)) return __LINE__;
  FPNumberC<6> p6(p8);
  if(p6 != 1) return __LINE__;
  if(!(p6 == 1)) return __LINE__;
  if(!(p6 == p8)) return __LINE__;
  if(p6 != p8) return __LINE__;
  p6++;
  p8++;
  if(p6 != 2) return __LINE__;
  if(p8 != 2) return __LINE__;
  
  // Check increment and decrement.
  if(p8++ == ++p6) return __LINE__;
  if(p6++ == ++p8) return __LINE__;
  if(p6 != p8) return __LINE__;
  if(p8-- == --p6) return __LINE__;
  if(p6-- == --p8) return __LINE__;
  if(p6 != p8) return __LINE__;
  
  // Check magnitude comparison for positive numbers.
  
  if(p6 > p8) return __LINE__;
  if(p8 > p6) return __LINE__;
  if(!(p6 >= p8)) return __LINE__;
  if(!(p8 >= p6)) return __LINE__;
  if(p6 < p8) return __LINE__;
  if(p8 < p6) return __LINE__;
  if(!(p6 <= p8)) return __LINE__;
  if(!(p8 <= p6)) return __LINE__;
  p8++;
  if(p8 <= p6) return __LINE__;
  if(p8 < p6) return __LINE__;
  if(p6 >= p8) return __LINE__;
  if(p6 > p8) return __LINE__;
  
  if(!(p8 >= p6)) return __LINE__;
  if(!(p8 > p6)) return __LINE__;
  if(!(p6 <= p8)) return __LINE__;
  if(!(p6 < p8)) return __LINE__;
  
  p8 = 0.25;
  p6 = 8;

  // Check Addition
  
  FPNumberC<4> p4;
  p4 = p6 + p8 + p8 + p8 + p8;
  if(p4 != 9) return __LINE__;

  // Check Subtraction
  p4 = p6 + p8;
  p4 = p4 - p8;  
  if(p4 != 8) return __LINE__;
  
  // Check multiplication
    
  p4 = p8 * p6;
  if(p4 != 2) return __LINE__;
  p4 = p6 * p8;
  if(p4 != 2) return __LINE__;
  p4 = p6 * 2;
  //cerr <<"p4=" << p4 <<" p6=" << p6 << " p8=" << p8 <<"\n";
  if(p4 != 16) return __LINE__;
  
  // Check division.
  
  p4 = p6 / p8;
  if(p4 != 32) return __LINE__;
  
  p4 = p6 / 2;
  //cerr <<"p4=" << p4 <<" p6=" << p6 << " p8=" << p8 <<"\n";
  if(p4 != 4) return __LINE__;
  
#endif  
  return 0;
}

#if 0
int testFunc(int i) {
  if(i == 5)
  return 0;
}
#endif

int testException() {
  try {
    throw ExceptionC("test");
    return __LINE__;
  } catch (ExceptionC &ex) {
    if(StringC(ex.Text()) != "test")
      return __LINE__;
  } catch(...) {
    return __LINE__;
  }
  return 0;
}

int testQInt() {
  double values[] = { 0,0.1,-0.25,-3.6 , 1.3,100000.01,1000,-1000 };
  for(int i = 0;i < 5;i++) {
    if(Round(values[i]) != QRound(values[i]))
      return __LINE__;
    if(Floor(values[i]) != QFloor(values[i]))
      return __LINE__;
  }
  
  return 0;
}

int testIndexRange2d() {
  IndexRange2dC start(Index2dC(1,2),Index2dC(9,10));
  cerr << "Rot90=" << start.Rotate90() << "\n";
  cerr << "Rot180=" << start.Rotate180() << "\n";
  cerr << "Rot270=" << start.Rotate270() << "\n";

  cerr << "Rot90 (5,6)=" << start.Rotate90(Index2dC(5,6)) << "\n";
  cerr << "Rot180 (5,6)=" << start.Rotate180(Index2dC(5,6)) << "\n";
  cerr << "Rot270 (5,6)=" << start.Rotate270(Index2dC(5,6)) << "\n";
  
  
  
  return 0;
}

int testRCWrap() {  
  //cerr << "Testing testRCWrap() \n";
  RCWrapC<int> wrap(true);
  if(!wrap.IsValid()) return __LINE__;
  wrap.Data() = 10;
  RCWrapAbstractC aWrap;
  if(aWrap.IsValid()) return __LINE__;
  aWrap = wrap;
  if(!aWrap.IsValid()) return __LINE__;
  RCWrapC<int> newwrap(aWrap,true);
  RCWrapC<float> wrongwrap(aWrap,true);
  if(wrongwrap.IsValid()) return __LINE__;
  if(!newwrap.IsValid()) return __LINE__;
  if(newwrap.Data() != 10) return __LINE__;
  return 0;
}


int testFloat16() {
  
  float t = 1;
  for(int i = 0;i < 24;i++) {
    Float16C val16(t);
    //std::cout << " " << t << " -> " << val16.Float() << "\n";
    if(t != val16.Float()) return __LINE__;
    t /= 2;
  }
  t = -1;
  for(int i = 0;i < 24;i++) {
    Float16C val16(t);
    //std::cout << " " << t << " -> " << val16.Float() << "\n";
    if(t != val16.Float()) return __LINE__;
    t /= 2;
  }
  
  int it = 1;
  for(int i = 0;i < 16;i++) {
    Float16C val16(it);
    //std::cout << " " << it << " -> " << val16.Float() << "\n";
    if(val16.Float() != ((float) it)) return __LINE__;
    it *= 2;
  }
  // Check positive infinity.
  {
    Float16C val16(it);
    //cerr << "Val=" << val16.Float() << " IsInf=" << val16.IsInf() << "\n";
    if(!val16.IsInf()) return __LINE__;
  }
  
  it = -1;
  for(int i = 0;i < 16;i++) {
    Float16C val16(it);
    //std::cout << " " << it << " -> " << val16.Float() << "\n";
    if(val16.Float() != ((float) it)) return __LINE__;
    it *= 2;
  }
  // Check negative infinity.
  {
    Float16C val16(it);
    //cerr << "Val=" << val16.Float() << " IsInf=" << val16.IsInf() << "\n";
    if(!val16.IsInf()) return __LINE__;
  }
  
  UInt8T ui8 = 1;
  for(int i = 0;i < 8;i++) {
    Float16C val16(ui8);
    //cerr << "ui8=" << ((unsigned int) ui8) << " Val=" << val16.Float() << "\n";
    if(val16.Float() != ((float) ui8)) return __LINE__;
    ui8 *= 2;
  }
  
  Int8T i8 = 1;
  for(int i = 0;i < 7;i++) {
    Float16C val16(i8);
    //cerr << "i8=" << (int) i8 << " Val=" << val16.Float() << "\n";
    if(val16.Float() != ((float) i8)) return __LINE__;
    i8 *= 2;
  }
  i8 = -1;
  for(int i = 0;i < 8;i++) {
    Float16C val16(i8);
    //cerr << "i8=" << (int) i8 << " Val=" << val16.Float() << "\n";
    if(val16.Float() != ((float) i8)) return __LINE__;
    i8 *= 2;
  }
  {
    Float16C val16(RavlConstN::nanFloat);
    std::cerr << "Value=" << val16.Float() << "\n";
    if(!val16.IsNan()) return __LINE__;
  }
  return 0;
}
