// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/Converter.cc"

#include "Ravl/DP/Converter.hh"
#include "Ravl/DP/DataConv.hh"
#include "Ravl/DP/TypeConverter.hh"
#include "Ravl/GraphConnIt.hh"
#include "Ravl/HSet.hh"
#include "Ravl/String.hh"

#define DPDEBUG 0

#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  ///////////////////////
  //: Constructor.
  
  DPConverterBaseBodyC::DPConverterBaseBodyC(const type_info &ninput_type,const type_info &noutput_type,RealT ncost) 
    : input_type(ninput_type),
      output_type(noutput_type),
      cost(ncost)
  { 
    ONDEBUG(cout << "Registering converter: "<<input_type.name() << " to " << output_type.name() << " with cost " << cost << endl);
    DPConverterBaseC me(*this);
    SystemTypeConverter().Insert(me);
  }
  
  ///////////////////////////
  //: Number of args for process.
  
  IntT DPConverterBaseBodyC::Args() const { 
    return 1; 
  }
  
  ////////////////////////////
  //: Type of args.
  
  const type_info &DPConverterBaseBodyC::ArgType(IntT i) const {
    if(i != 0)
      return typeid(void); 
    return input_type;
  }
  
  ////////////////////////////
  //: Output type.
  
  const type_info &DPConverterBaseBodyC::Output() const { 
    return output_type; 
  }
  
  
  ///////////////////////////
  //: Apply conversion.
  
  RCAbstractC DPConverterBaseBodyC::Apply(const RCAbstractC &dat) {
    if(!proc.IsValid())
      proc = CreateProc();
    RavlAssert(proc.IsValid());
    return Apply1(proc,dat);
  }
  
  /////////////////////////////////////////////////////////
  
  static IntT ConvByte2Int(const ByteT &v)
  { return (IntT) v; }

  static IntT ConvInt162Int(const Int16T &v)
  { return (IntT) v; }
  
  static RealT ConvInt2Real(const IntT &v)
  { return (RealT) v; }

  static StringC ConvInt2String(const IntT &v)
  { return StringC(v); }

  static StringC ConvReal2String(const RealT &v)
  { return StringC(v); }
  
  DP_REGISTER_CONVERSION_NAMED(ConvByte2Int,1,"IntT RavlN::Convert(const ByteT &)");
  DP_REGISTER_CONVERSION_NAMED(ConvInt162Int,1,"IntT RavlN::Convert(const Int16T &)");
  DP_REGISTER_CONVERSION_NAMED(ConvInt2Real,1,"RealT RavlN::Convert(const IntT &)");
  DP_REGISTER_CONVERSION_NAMED(ConvInt2String,1,"StringC RavlN::Convert(const IntT &)");
  DP_REGISTER_CONVERSION_NAMED(ConvReal2String,1,"StringC RavlN::Convert(const RealT &)");
  
}
