// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLTYPECONVERTER_HEADER
#define RAVLTYPECONVERTER_HEADER 1
/////////////////////////////////////////////////////////////
//! docentry="Ravl.Core.IO.Formats" 
//! author="Charles Galambos"
//! rcsid="$Id$"

#include "Ravl/RefCounter.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Graph.hh"
#include "Ravl/DList.hh"

namespace RavlN {
  
  //! userlevel=Advanced
  //: Type converter body.
  
  class TypeConverterBodyC 
    : public RCBodyVC
  {
  public:
    TypeConverterBodyC();
    //: Constructor.
    
    DListC<DPConverterBaseC> FindConversion(const type_info &from,const type_info &to,RealT &finalCost);
    //: Find a conversion.
    // If found the cost of conversion is put into finalCost.
    
    DListC<DPConverterBaseC> FindConversion(const type_info &from,const type_info &to);
    //: Find a conversion.
    
    bool CanConvert(const type_info &from,const type_info &to);
    //: Test if conversion is possible.
    
    RCAbstractC DoConvertion(const RCAbstractC &dat,const type_info &from,const type_info &to);
    //: Do conversion through abstract handles.
    
    bool Insert(DPConverterBaseC &tc);
    //: Insert new conversion.
    
    bool Remove(DPConverterBaseC &tc);
    //: Remove old conversion.
    
  protected:
    static RealT EdgeEval(const DPConverterBaseC &edge);
    
    GraphC<StringC,DPConverterBaseC> &ConvGraph()
      { return convGraph; }
    //: Access conversion graph.
    
    HashC<StringC,GraphNodeHC<StringC,DPConverterBaseC> > &NodeTab()
      { return nodeTab; }
    //: Type -> Node mapping.
    
    GraphNodeHC<StringC,DPConverterBaseC> GetTypeNode(const type_info &inf);
    //: Get the graph node associated with a type_info.
    
    GraphC<StringC,DPConverterBaseC> convGraph; // Converstion graph.
    HashC<StringC,GraphNodeHC<StringC,DPConverterBaseC> > nodeTab; // Type to node mapping.
  };


  //! userlevel=Advanced
  //: Type converter.
  
  class TypeConverterC
    : public RCHandleC<TypeConverterBodyC>
  {
  public:
    TypeConverterC()
      {}
    //: Default constructor.

    TypeConverterC(bool)
      : RCHandleC<TypeConverterBodyC>(*new TypeConverterBodyC())
      {}
    //: Constructor.
    
  public:
    DListC<DPConverterBaseC> FindConversion(const type_info &from,const type_info &to,RealT &finalCost)
      { return Body().FindConversion(from,to,finalCost); }
    //: Find a conversion.
    // If found the cost of conversion is put into finalCost.
    
    DListC<DPConverterBaseC> FindConversion(const type_info &from,const type_info &to)
      { return Body().FindConversion(from,to); }
    //: Find a conversion.
    
    bool CanConvert(const type_info &from,const type_info &to)
      { return Body().CanConvert(from,to); }
    //: Test if conversion is possible.
    
    RCAbstractC DoConvertion(const RCAbstractC &dat,const type_info &from,const type_info &to)
      { return Body().DoConvertion(dat,from,to); }
    //: Do conversion through abstract handles.
    
    bool Insert(DPConverterBaseC &tc)
      { return Body().Insert(tc); }
    //: Insert new conversion.
    
    bool Remove(DPConverterBaseC &tc)
      { return Body().Remove(tc); }
    //: Remove old conversion.
    
    template<class InT,class OutT>
    bool TypeConvert(const InT &inraw,OutT &outraw) {
      RCAbstractC result = DoConvertion(RCWrapC<InT>(inraw).Abstract(),typeid(InT),
					typeid(OutT));
      RCWrapC<OutT> out(result);
      if(!out.IsValid())
	return false; // Did conversion succeed ?
      outraw = out.Data();
      return true;
    }
    
    template<class OutT>
    bool TypeConvert(const RCWrapAbstractC &in,OutT &outraw) {
      RCAbstractC result = DoConvertion(const_cast<RCWrapAbstractC &>(in).Abstract(),in.DataType(),
					typeid(OutT));
      RCWrapC<OutT> out(result);
      if(!out.IsValid())
	return false; // Did conversion succeed ?
      outraw = out.Data();
      return true;
    }
  };

  TypeConverterC &SystemTypeConverter();
  //: Default type converter used by the system.
  
}


#endif
