// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/TypeConverter.cc"

#include "Ravl/DP/TypeConverter.hh"
#include "Ravl/GraphBestRoute.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  TypeConverterBodyC::TypeConverterBodyC()
  {}
  
  GraphNodeHC<StringC,DPConverterBaseC> TypeConverterBodyC::GetTypeNode(const type_info &inf)  {
    StringC typeName(inf.name());
    GraphNodeHC<StringC,DPConverterBaseC> &ret = NodeTab()[typeName];
    if(ret.IsValid())
      return ret;
    ret = ConvGraph().InsNode(typeName);
    return ret;
  }

  //: Test if conversion is possible.
  
  bool TypeConverterBodyC::CanConvert(const type_info &from,const type_info &to) {
    if(from == to)
      return true;
    DListC<GraphEdgeIterC<StringC,DPConverterBaseC> > conv;
#if !(RAVL_COMPILER_VISUALCPP && !RAVL_COMPILER_VISUALCPPNET) || RAVL_COMPILER_VISUALCPPNET_2005
    RealT finalCost;
    // Visual C++ can't handle ptr's to functions with reference args.
    // hopefull we'll find a way aroung this but for now its out.
    conv = GraphBestRoute(ConvGraph(),
			  GetTypeNode(from),
			  GetTypeNode(to),
			  finalCost,
			  &TypeConverterBodyC::EdgeEval);
#else
    RavlAssert(0);
#endif
    return !conv.IsEmpty();
  }

  //: Do conversion through abstract handles.
  
  RCAbstractC TypeConverterBodyC::DoConversion(const RCAbstractC &dat,const type_info &from,const type_info &to) {
    if(from == to || !dat.IsValid())
      return dat;
    ONDEBUG(cout << "Asked to convert " << from.name() << " to " << to.name() << endl);
    DListC<GraphEdgeIterC<StringC,DPConverterBaseC> > conv;  
    //  typedef RealT (*AFuncT)(const DPConverterBaseC &);
#if !(RAVL_COMPILER_VISUALCPP && !RAVL_COMPILER_VISUALCPPNET)  || RAVL_COMPILER_VISUALCPPNET_2005
	// Visual C++ can't handle ptr's to functions with reference args.
    // hopefull we'll find a way aroung this but for now its out.
    RealT finalCost = 0;
    conv = GraphBestRoute(ConvGraph(),
			  GetTypeNode(from),
			  GetTypeNode(to),
			  finalCost,
			  &TypeConverterBodyC::EdgeEval);
#else
    RavlAssert(0);
#endif
    if(conv.IsEmpty()) {
      ONDEBUG(cout << "No conversion from " << from.name() << " to " << to.name() << endl);
      return RCAbstractC();
    }
    
    // Do conversion.
    
    RCAbstractC at = dat;
    for(DLIterC<GraphEdgeIterC<StringC,DPConverterBaseC> > it(conv);it;it++)
      at = it.Data().Data().Apply(at);
    return at;
    
  }
  
  //: Find a conversion.
  // If found the cost of conversion is put into finalCost.
  
  DListC<DPConverterBaseC> TypeConverterBodyC::FindConversion(const type_info &from,const type_info &to,RealT &finalCost)  {
    ONDEBUG(cout << "Asked to convert " << from.name() << " to " << to.name() << endl);
    DListC<GraphEdgeIterC<StringC,DPConverterBaseC> > conv;  
    //  typedef RealT (*AFuncT)(const DPConverterBaseC &);
#if !(RAVL_COMPILER_VISUALCPP && !RAVL_COMPILER_VISUALCPPNET) || RAVL_COMPILER_VISUALCPPNET_2005
    // Visual C++ can't handle ptr's to functions with reference args.
    // hopefull we'll find a way aroung this but for now its out.
    conv = GraphBestRoute(ConvGraph(),
			  GetTypeNode(from),
			  GetTypeNode(to),
			  finalCost,
			  &TypeConverterBodyC::EdgeEval);
#else
    RavlAssert(0);
#endif
    
    if(conv.IsEmpty()) {
      ONDEBUG(cout << "No conversion from " << from.name() << " to " << to.name() << endl);
      return DListC<DPConverterBaseC>(); // Failed to find conversion.
    }
    DListC<DPConverterBaseC> ret;
    for(DLIterC<GraphEdgeIterC<StringC,DPConverterBaseC> > it(conv);it.IsElm();it.Next())
      ret.InsLast(it.Data().Data());
    return ret;
  }
  
  
  RealT TypeConverterBodyC::EdgeEval(const DPConverterBaseC &edge)  { 
    ONDEBUG(cout << "Edge cost " << edge.Cost() << " : " << edge.ArgType(0).name() << " " << edge.Output().name() << endl);
    return edge.Cost(); 
  }
  
  
  //: Find a conversion.
  
  DListC<DPConverterBaseC> TypeConverterBodyC::FindConversion(const type_info &from,const type_info &to) { 
    RealT finalCost = -1;
    return FindConversion(from,to,finalCost);
  } 

  bool TypeConverterBodyC::Insert(DPConverterBaseC &tc) {
    ConvGraph().InsEdge(GetTypeNode(tc.ArgType(0)),GetTypeNode(tc.Output()),tc.Body());
    // FIXME :- Check for duplication ??
    return true;
  }
  
  //: Remove conversion from system.
    
  bool TypeConverterBodyC::Remove(DPConverterBaseC &tc)  {
    // FIXME :- Slow !! 
    ONDEBUG(cerr << "Unegistering converter : "<< tc.ArgType(0).name() << " to " << tc.Output().name() << endl);
    bool ok = false;
    IntT size = 0;
    for(GraphEdgeIterC<StringC,DPConverterBaseC> it(ConvGraph());it.IsElm();it.Next()) {
      if(&it.Data().Body() == &tc.Body()) {
	it.Del();
	ok = true;
	break;
      }
      size++;
    }
    if(!ok)
      cerr << "Failed !!! " << size << "\n";
    return true;
  }
  
  TypeConverterC &SystemTypeConverter() {
    static TypeConverterC tc(true);
    return tc;
  }

}
