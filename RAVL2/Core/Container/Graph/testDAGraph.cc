/////////////////////////////////////////////
// TDAGraph.cc  1/1/97  By Charles Galambos
// $Id$

#include <stdio.h>

#include "amma/DAGraph.hh"
#include "amma/GraphLinearIter.hh"
#include "amma/GrConnIt.hh"

class IntC : public DAGraphMarkerC {
public:
  IntC() {}
  IntC(int n) : v(n) {}
  int v;
};


int main() {
  printf("Test DAGraph. \n");
  
  // Creating a graph.
  {
    DAGraphC<IntC,IntC> G;
    
    GraphNodeIterC<IntC,IntC> From = G.InsNode(IntC(1));
    GraphNodeIterC<IntC,IntC> To = G.InsNode(IntC(2));
    GraphNodeIterC<IntC,IntC> Another = G.InsNode(IntC(3));
    GraphNodeIterC<IntC,IntC> MeTo = G.InsNode(IntC(4));
    printf(" F:%d T:%d A:%d M:%d \n",From.Hash(),To.Hash(),Another.Hash(),MeTo.Hash());
    printf("Making links. F->T,T->M,T->A \n");
    G.InsEdge(From,To,IntC(5));
    G.InsEdge(To,MeTo,IntC(6));
    G.InsEdge(To,Another,IntC(7));
    printf(" ACyclic tests.... \n");
    printf(" Cycle A->F:%d \n",((int) ((bool) G.TryEdge(Another,From))));
    printf(" Cycle F->M:%d \n",((int) ((bool) G.TryEdge(From,MeTo))));
    // G.InsEdge(From,Other,IntC(7));
  }
  // Build a bigger graph.
  {
    int i;
    DAGraphC<IntC,IntC> G;
    const int Nodes = 30;
    const int Edges = 30;
    const int NoMods = 10;
    
    GraphNodeIterC<IntC,IntC> NdArr[Nodes];
    for(i = 0;i < Nodes;i++)
      NdArr[i] = G.InsNode(IntC(i));
    
    GraphEdgeIterC<IntC,IntC> EdArr[Nodes];
    for(i = 0;i < Edges;i++) {
      while(!EdArr[i].IsValid())
	EdArr[i] = G.InsEdge(NdArr[rand() % Nodes],NdArr[rand() % Nodes],i);
    }
    for(int j = 0;j < NoMods;j++) {
      // Test iter.
      for(int k = 0;k < Nodes;k++) {
	int Count = 0;
	for(GraphConnIterC<IntC,IntC> CIt(NdArr[k]);CIt.IsElm();CIt.Next())
	  Count++;
	printf("Node %d Connects to %d other nodes. \n",k,Count);
      }
      
      // Print it out.
      printf("Graph dump: \n");
      for(GraphLinearIterC<IntC,IntC> It(G);It.IsElm();It.Next()) {
	printf("Node %d \n",It.Data().v);
	for(GraphAdjIterC<IntC,IntC> Adj(It.Node().In());Adj.IsElm();Adj.Next()) {
	  printf("  Edge %d->%d (%d) \n",Adj.SourceData().v,Adj.TargetData().v,Adj.Data().v);
	}
      }
      // Change an edge.
      {
	int En = rand() % Edges;
	EdArr[En].Del();
	EdArr[En].Invalidate();
	while(!EdArr[En].IsValid())
	  EdArr[En] = G.InsEdge(NdArr[rand() % Nodes],NdArr[rand() % Nodes],En);
      }
    }
    for(i = 0;i < Nodes;i++) {
      NdArr[i].Del();
      NdArr[i].Invalidate();
    }
    for(i = 0;i < Edges;i++)
      EdArr[i].Invalidate();
    // printf("Val:%d \n",NdArr[0].Data().v);
  }
  
  printf("Test complete.\n");
  return 0;
}
