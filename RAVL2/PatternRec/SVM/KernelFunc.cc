// This file is used in conjunction with RAVL, Recognition And Vision Library
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here

#include "Ravl/PatternRec/KernelFunc.hh"
#include "Ravl/VirtualConstructor.hh"

namespace RavlN
{
using namespace RavlN;

//---------------------------------------------------------------------------
//: Load from stream.
KernelFunctionBodyC::KernelFunctionBodyC(istream &strm)
                    :RCBodyVC(strm)
{
}
//---------------------------------------------------------------------------
//: Load from binary stream.
KernelFunctionBodyC::KernelFunctionBodyC(BinIStreamC &strm)
                    :RCBodyVC(strm)
{
}
//---------------------------------------------------------------------------
//: Writes object to stream
bool KernelFunctionBodyC::Save(ostream &out) const
{
  RavlAssertMsg(0, "KernelFunctionBodyC::Save(ostream &out): KernelFunctionC "
                "is abstract class, this function has to be redefined in "
                "child class");
  return false; // this line here just to make compiler happy
}
//---------------------------------------------------------------------------
//: Writes object to stream
bool KernelFunctionBodyC::Save(BinOStreamC &out) const
{
  RavlAssertMsg(0, "KernelFunctionBodyC::Save(BinOStreamC &out): "
                "KernelFunctionC is abstract class, this function has to be "
                "redefined in child class");
  return false; // this line here just to make compiler happy
}
//---------------------------------------------------------------------------
//: Apply function to vectors data1 and data2
RealT KernelFunctionBodyC::Apply(int Size, const RealT *X1, const RealT *X2) const
{
  RavlAssertMsg(0, "KernelFunctionBodyC::Apply(int Size, const RealT *X1, const "
                "RealT *X2): KernelFunctionC is abstract class, this "
                "function has to be redefined in child class");
  return 0; // this line here just to make compiler happy
}
//---------------------------------------------------------------------------
// Stream load operators defined in RAVL_INITVIRTUALCONSTRUCTOR_FULL macro
// Implementation of 'load from stream' constructors defined there as well
RAVL_INITVIRTUALCONSTRUCTOR_FULL(KernelFunctionBodyC, KernelFunctionC,
                                 RCHandleVC<KernelFunctionBodyC>);
//---------------------------------------------------------------------------
}
