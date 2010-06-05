#ifndef RAVLGRAPHCONNITER_HEADER 
#define RAVLGRAPHCONNITER_HEADER 1
//////////////////////////////////////////////////////////////
//! file="amma/Contain/Graph/GrConnIt.hh"
//! lib=Mgraph
//! userlevel=Normal
//! author="Charles Galambos"
//! date="2/1/1997"
//! docentry="Ravl.Core.Graphs"
//! rcsid="$Id: GrConnIt.hh 4 2001-04-11 12:45:55Z craftit $"

#include "Ravl/GrBConIt.hh"
#include "Ravl/GraphNode.hh"

namespace RavlN {
  
  //: Connected node iterator.
  // Iterate all nodes that maybe reached from the given starting 
  // point. This does not necessarily include the start point itself.
  
  template<class NodeT,class EdgeT>
  class GraphConnIterC 
    : public GraphBaseConnIterC 
  {
  public:
    GraphConnIterC(GraphNodeIterC<NodeT,EdgeT> &Nd) :
      GraphBaseConnIterC(Nd.BaseNodeIter()) {}
    // Constructor
    
    GraphConnIterC(GraphConnIterC<NodeT,EdgeT> &Oth) :
      GraphBaseConnIterC(Oth) {}
    // Copy constructor
    
    inline GraphNodeIterC<NodeT,EdgeT> Node()
      {  return GraphNodeIterC<NodeT,EdgeT>(GraphBaseConnIterC::Data()); }
    // Get a node iterator.
    
    inline NodeT &Data()
      { return static_cast<GraphNodeDatC<NodeT,EdgeT> &>(GraphBaseConnIterC::Data().NodeRep()).Data();  }
    // Get some data.  
    
    inline bool operator==(const GraphNodeIterC<NodeT,EdgeT> &Nd) const
      { return (&Nd.BaseNodeIter().NodeRep() == &GraphBaseConnIterC::Data().NodeRep()); }
    // At a particular node ?
    
    void AddOpen(const GraphNodeIterC<NodeT,EdgeT> &Nd) 
      { GraphBaseConnIterC::AddOpen(Nd.BaseNodeIter()); }
    // Add node to open list.
    
  };
  
}

#endif
