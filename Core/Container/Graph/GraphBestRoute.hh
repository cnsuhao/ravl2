// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_GRBESTROUTE_HEADER
#define RAVL_GRBESTROUTE_HEADER 1
//////////////////////////////////////////
//! docentry="Ravl.Core.Graphs"
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Graph/GraphBestRoute.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="13/08/98"
//! userlevel=Normal

#include "Ravl/Graph.hh"
#include "Ravl/Hash.hh"
#include "Ravl/DList.hh"
#include "Ravl/PriQueueL.hh"

namespace RavlN {
  
  //////////////////////////////////
  //! userlevel=Normal
  //: Find the shortest route between to nodes in a graph.
  
  template<class NodeT,class EdgeT,class CostT>  
  DListC<GraphEdgeIterC<NodeT,EdgeT> > GraphBestRoute(const GraphC<NodeT,EdgeT> &graph,
						      GraphNodeHC<NodeT,EdgeT> from,
						      GraphNodeHC<NodeT,EdgeT> to,
						      CostT &costOut,
						      CostT (*EvalT)(const EdgeT &dat)) {
    PriQueueLC<CostT,GraphNodeHC<NodeT,EdgeT> > open; // List of open nodes.
    GraphNodeHC<NodeT,EdgeT> at = from;               // Place marker in graph.
    HashC<GraphNodeHC<NodeT,EdgeT>,CostT> dist;     // Cost mapping.
    open.Insert(0,from); // Setup start node.
    dist[from] = 0;
    // Fill all distances until 'to' is found.
    CostT maxdist(0);
    bool found = false;
    while(!open.IsEmpty()) {
      CostT ccost = open.TopKey();
      if(ccost > maxdist)
	maxdist = ccost;
      at = open.GetTop();
      if(at == to) {
	found = true;
	break;
      }
      for(GraphAdjIterC<NodeT,EdgeT> it(at.Out());it.IsElm();it.Next()) {
	RealT val = ccost + EvalT(it.Data());
	if(dist.IsElm(it.OtherNode())) {
	  if(dist[it.OtherNode()] <= val)
	    continue;
      }
	dist[it.OtherNode()] = val;
	open.Insert(val,it.OtherNode());
      }
    }
    if(!found) 
      return DListC<GraphEdgeIterC<NodeT,EdgeT> > (); // Not found, return empty list.
    costOut = dist[to];
    // Backtrack along shortest path.
    DListC<GraphEdgeIterC<NodeT,EdgeT> > ret;
    CostT lastDist = maxdist;
    while(at != from) {
      GraphEdgeIterC<NodeT,EdgeT> back;
      GraphAdjIterC<NodeT,EdgeT> it(at.In());
      while(!dist.IsElm(it.OtherNode())) {
	it++;
	RavlAssert(it); // There should be at least 1 node with a distance.
      }
      CostT mindist = dist[it.OtherNode()] + EvalT(it.Data());
      back = it.Edge();
      at = it.OtherNode();
      for(it++;it;it++) {
	if(!dist.IsElm(it.OtherNode()))
	  continue;
	CostT cv = dist[it.OtherNode()] + EvalT(it.Data());
	if(cv <= mindist) {
	  mindist = cv;
	  back = it.Edge();
	  at = it.OtherNode();
	  // If the cost is equal or smaller than that of the current node we know
	  // we've found the smallest.
	  // Note: It may not be exactly equal because of rounding errors, so if its
	  // more we have to continue until we've checked all posiblities.
	  if(mindist <= lastDist)
	    break; 
	}
      }
      lastDist = mindist;
      RavlAssert(back.IsValid()); // Just to check sanity.
      ret.InsFirst(back);
    }
    return ret;
  }
  
}
#endif
