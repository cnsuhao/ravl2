
#include "Ravl/Graph.hh"

using namespace RavlN;

int main() {

  GraphC<int,int> graph;

  GraphNodeHC<int,int> node1 = graph.InsNode(1);
  GraphNodeHC<int,int> node2 = graph.InsNode(2);
  GraphNodeHC<int,int> node3 = graph.InsNode(3);
  
  GraphEdgeIterC<int,int> edge1 = graph.InsEdge(node1,node2,1);
  GraphEdgeIterC<int,int> edge2 = graph.InsEdge(node1,node3,2);
  
  // Go through edges that leave node1.
  
  for(GraphAdjIterC<int,int> adjIter(node1.Out());adjIter;adjIter++)
    cerr << "Out edge " << adjIter.Data() << "\n";
  
  // Go through edges that enter node2.

  for(GraphAdjIterC<int,int> adjIter(node2.In());adjIter;adjIter++)
    cerr << "In edge " << adjIter.Data() << "\n";
  
  // Go through all nodes in graph.
  
  for(GraphNodeIterC<int,int> nodeIter(graph);nodeIter;nodeIter++) 
    cerr << "Node " << nodeIter.Data() << "\n";
  
  // Go through all edges in graph.

  for(GraphEdgeIterC<int,int> edgeIter(graph);edgeIter;edgeIter++) 
    cerr << "Edge " << edgeIter.Data() << "\n";
  
  return 0;
}
