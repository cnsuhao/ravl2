// This file is used in conjunction with RAVL, Recognition And Vision Library
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here

#include <math.h>

#include "Ravl/PatternRec/CommonKernels.hh"

namespace RavlN
{
using namespace RavlN;

//-- Linear kernel ------------------------------------------------------------
//: Load from stream.
LinearKernelBodyC::LinearKernelBodyC(istream &strm)
                  :KernelFunctionBodyC(strm)
{
  IntT version;
  strm >> version;
  if(version != 0)
    throw ExceptionOperationFailedC("LinearKernelBodyC::LinearKernelBodyC(istream &strm), Unrecognised version number in stream.");
  strm >> scale;
}
//---------------------------------------------------------------------------
//: Load from binary stream.
LinearKernelBodyC::LinearKernelBodyC(BinIStreamC &strm)
                  :KernelFunctionBodyC(strm)
{
  IntT version;
  strm >> version;
  if(version != 0)
    throw ExceptionOperationFailedC("LinearKernelBodyC::LinearKernelBodyC(BinIStreamC &strm), Unrecognised version number in stream.");
  strm >> scale;
}
//---------------------------------------------------------------------------
// Writes object to stream
bool LinearKernelBodyC::Save(ostream &out) const
{
  if(!RCBodyVC::Save(out))
    return false;
  const IntT version = 0;
  out << ' ' << version << ' ' << scale;
  return true;
}
//---------------------------------------------------------------------------
// Writes object to stream
bool LinearKernelBodyC::Save(BinOStreamC &out) const
{
  if(!RCBodyVC::Save(out))
    return false;
  const IntT version = 0;
  out << version << scale;
  return true;
}
//---------------------------------------------------------------------------
// Apply function to 'data' vectors supposed to be of the same size
RealT LinearKernelBodyC::Apply(int Size, const RealT *X1, const RealT *X2) const
{
  long double sum = 0.;
  const RealT* endPtr = X1 + Size;
  while(X1 < endPtr)
    sum += *X1++ * *X2++;

  return scale * sum;
}
//---------------------------------------------------------------------------

//-- Quadratic kernel ------------------------------------------------------------
//: Load from stream.
QuadraticKernelBodyC::QuadraticKernelBodyC(istream &strm)
                    : KernelFunctionBodyC(strm)
{
  IntT version;
  strm >> version;
  if(version != 0)
    throw ExceptionOperationFailedC("QuadraticKernelBodyC::QuadraticKernelBodyC(istream &strm), Unrecognised version number in stream.");
  strm >> scale;
}
//---------------------------------------------------------------------------
//: Load from binary stream.
QuadraticKernelBodyC::QuadraticKernelBodyC(BinIStreamC &strm)
                    : KernelFunctionBodyC(strm)
{
  IntT version;
  strm >> version;
  if(version != 0)
    throw ExceptionOperationFailedC("QuadraticKernelBodyC::QuadraticKernelBodyC(BinIStreamC &strm), Unrecognised version number in stream.");
  strm >> scale;
}
//---------------------------------------------------------------------------
// Writes object to stream
bool QuadraticKernelBodyC::Save(ostream &out) const
{
  if(!RCBodyVC::Save(out))
    return false;
  const IntT version = 0;
  out << ' ' << version << ' ' << scale;
  return true;
}
//---------------------------------------------------------------------------
// Writes object to stream
bool QuadraticKernelBodyC::Save(BinOStreamC &out) const
{
  if(!RCBodyVC::Save(out))
    return false;
  const IntT version = 0;
  out << version << scale;
  return true;
}
//---------------------------------------------------------------------------
// Apply function to 'data' vectors supposed to be of the same size
RealT QuadraticKernelBodyC::Apply(int Size, const RealT *X1, const RealT *X2) const
{
  const RealT *p1 = X1;
  const RealT *p2 = X2;
  const RealT *p1end = p1 + Size;
  long double retVal = 0;
  while(p1 != p1end)
  {
    const RealT v1 = *p1++;
    const RealT v2 = *p2++;
    retVal += v1 * (v2 + v1 * v2 * v2);
  }
  return scale * retVal;
}
//---------------------------------------------------------------------------

//-- Polynomial kernel ------------------------------------------------------------
//: Load from stream.
PolynomialKernelBodyC::PolynomialKernelBodyC(istream &strm)
                      :KernelFunctionBodyC(strm)
{
  IntT version;
  strm >> version;
  if(version != 0)
    throw ExceptionOperationFailedC("PolynomialKernelBodyC::PolynomialKernelBodyC(istream &strm), Unrecognised version number in stream.");
  strm >> power;
  strm >> scale;
  strm >> b;
}
//---------------------------------------------------------------------------
//: Load from binary stream.
PolynomialKernelBodyC::PolynomialKernelBodyC(BinIStreamC &strm)
                      :KernelFunctionBodyC(strm)
{
  IntT version;
  strm >> version;
  if(version != 0)
    throw ExceptionOperationFailedC("PolynomialKernelBodyC::PolynomialKernelBodyC(BinIStreamC &strm), Unrecognised version number in stream.");
  strm >> power;
  strm >> scale;
  strm >> b;
}
//---------------------------------------------------------------------------
// Writes object to stream
bool PolynomialKernelBodyC::Save(ostream &out) const
{
  if(!RCBodyVC::Save(out))
    return false;
  const IntT version = 0;
  out << ' ' << version << ' ' << power << ' ' << scale << ' ' << b;
  return true;
}
//---------------------------------------------------------------------------
// Writes object to stream
bool PolynomialKernelBodyC::Save(BinOStreamC &out) const
{
  if(!RCBodyVC::Save(out))
    return false;
  const IntT version = 0;
  out << version << power << scale << b;
  return true;
}
//---------------------------------------------------------------------------
// Apply function to 'data' vectors supposed to be of the same size
RealT PolynomialKernelBodyC::Apply(int Size, const RealT *X1, const RealT *X2) const
{
  long double sum = 0.0;
  const RealT* endPtr = X1 + Size;
  while(X1 < endPtr)
    sum += *X1++ * *X2++;
  //if(sum < 0.)
  //  printf("sum<0:%g\n", float(sum));
  return pow(scale * static_cast<double>(sum) + b, power);
}
//---------------------------------------------------------------------------

//-- Radial basis kernel ------------------------------------------------------
//: Load from stream.
RBFKernelBodyC::RBFKernelBodyC(istream &strm)
               :KernelFunctionBodyC(strm)
{
  IntT version;
  strm >> version;
  if(version != 0)
    throw ExceptionOperationFailedC("RBFKernelBodyC::RBFKernelBodyC(istream &strm), Unrecognised version number in stream.");
  strm >> gamma;
}
//---------------------------------------------------------------------------
//: Load from binary stream.
RBFKernelBodyC::RBFKernelBodyC(BinIStreamC &strm)
               :KernelFunctionBodyC(strm)
{
  IntT version;
  strm >> version;
  if(version != 0)
    throw ExceptionOperationFailedC("RBFKernelBodyC::RBFKernelBodyC(BinIStreamC &strm), Unrecognised version number in stream.");
  strm >> gamma;
}
//---------------------------------------------------------------------------
// Writes object to stream
bool RBFKernelBodyC::Save(ostream &out) const
{
  if(!RCBodyVC::Save(out))
    return false;
  const IntT version = 0;
  out << ' ' << version << ' ' << gamma;
  return true;
}
//---------------------------------------------------------------------------
// Writes object to stream
bool RBFKernelBodyC::Save(BinOStreamC &out) const
{
  if(!RCBodyVC::Save(out))
    return false;
  const IntT version = 0;
  out << version << gamma;
  return true;
}
//---------------------------------------------------------------------------
// Apply function to 'data' vectors supposed to be of the same size
RealT RBFKernelBodyC::Apply(int Size, const RealT *X1, const RealT *X2) const
{
  long double sum = 0.;
  const RealT* endPtr = X1 + Size;
  while(X1 < endPtr)
  {
    RealT t = *X1++ - *X2++;
    sum -= t * t;
  }

  return exp(sum / gamma);
}
//---------------------------------------------------------------------------
}

