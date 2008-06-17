// This file is used in conjunction with RAVL, Recognition And Vision Library
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here

#include "Ravl/PatternRec/Classifier2.hh"

namespace RavlN
{
using namespace RavlN;

//---------------------------------------------------------------------------
// Load from stream.
Classifier2BodyC::Classifier2BodyC(istream &Strm)
                 :ClassifierBodyC(Strm)
{
}
//---------------------------------------------------------------------------
// Load from binary stream.
Classifier2BodyC::Classifier2BodyC(BinIStreamC &Strm)
                 :ClassifierBodyC(Strm)
{
}
//---------------------------------------------------------------------------
// Destructor.
Classifier2BodyC::~Classifier2BodyC()
{
}
//---------------------------------------------------------------------------
// Writes object to stream
bool Classifier2BodyC::Save(ostream &Out) const
{
  if(!ClassifierBodyC::Save(Out))
    throw ExceptionOperationFailedC("Classifier2BodyC::Save:"
                                    "error in ClassifierBodyC::Save call.");
  return true;
}
//---------------------------------------------------------------------------
// Writes object to stream, can be loaded using constructor
bool Classifier2BodyC::Save(BinOStreamC &Out) const
{
  if(!ClassifierBodyC::Save(Out))
    throw ExceptionOperationFailedC("Classifier2BodyC::Save:"
                                    "error in ClassifierBodyC::Save call.");
  return true;
}
//---------------------------------------------------------------------------
// Classifier vector 'data' return the most likely label.
UIntT Classifier2BodyC::Classify(const VectorC &Data) const
{
  return Classify2(Data) > 0;
}
//---------------------------------------------------------------------------
// Classifier vector 'data' return the most likely label.
UIntT Classifier2BodyC::Classify(const RealT* Data) const
{
  return Classify2(Data) > 0;
}
//---------------------------------------------------------------------------
// Classifier vector 'Data' return value of descriminant function
RealT Classifier2BodyC::Classify2(const VectorC &Data) const
{
  return Classify2(Data.DataStart());
}
//---------------------------------------------------------------------------
// Classifier vector 'Data' return value of descriminant function
RealT Classifier2BodyC::Classify2(const RealT* Data) const
{
  throw ExceptionOperationFailedC("Classifier2BodyC::Classify2:"
                                  "This is an abstract method");
}
//---------------------------------------------------------------------------
// Get vector length of classifier
IntT Classifier2BodyC::GetDataSize() const
{
  throw ExceptionOperationFailedC("Classifier2BodyC::GetDataSize:"
                                  "This is an abstract method");
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

}
