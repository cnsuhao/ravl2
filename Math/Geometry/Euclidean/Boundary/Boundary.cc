//! author="Radek Marik"
//! date="26.04.1994"
//! rcsid="$Id$"

#include "Ravl/StdMath.hh" //::Abs()
#include "Ravl/Types.hh"
#include "Ravl/CrackCode.hh"
#include "Ravl/Edge.hh"
#include "Ravl/Boundary.hh"
#include "Ravl/Hash.hh"
#include "Ravl/RCHash.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/Pair.hh"

namespace RavlN {

  BoundaryC::BoundaryC(const EdgeListC & edgeList, bool orient)
    : EdgeListC(edgeList), orientation(orient)
  {
    //  cout << "BoundaryC(ListC<EdgeC> & edgeList, bool orient)\n";
  }

  BoundaryC::BoundaryC(const BoundaryC & boundary)
    : EdgeListC(boundary), orientation(boundary.orientation)
  {
    //  cout << "BoundaryC(BoundaryC & boundary)\n";
  }

  BoundaryC::BoundaryC(bool orient)
    : EdgeListC(), orientation(orient) 
  {
    //  cout << "BoundaryC()\n";
  }
    
  BoundaryC::BoundaryC(const IndexRectangleC & rect)
    : EdgeListC(),
      orientation(true) 
  {
    Index2dC     origin(rect.Origin());
    Index2dC     endP(rect.End());
    BVertexC   oVertex(origin);      // to help to GNU C++ 2.6.0
    CrackCodeC cr(CR_RIGHT);
    EdgeC      edge(oVertex, cr);
    for(IndexC cUp=origin.Col(); cUp <= endP.Col(); cUp++) {
      InsLast(edge);
      edge.Step(CR_RIGHT);
    }
    edge.Clock();
    for(IndexC rRight=origin.Row(); rRight <= endP.Row(); rRight++) {
      InsLast(edge);
      edge.Step(CR_DOWN);
    }
    edge.Clock();
    for(IndexC cDown=endP.Col(); cDown >= origin.Col(); cDown--) {
      InsLast(edge);
      edge.Step(CR_LEFT);
    }
    edge.Clock();
    for(IndexC rLeft=endP.Row(); rLeft >= origin.Row(); rLeft--) {
      InsLast(edge);
      edge.Step(CR_UP);
    }
  }
  
  /*
    void
    BoundaryC::Order()
    //========================================================
    {
    // create hashtable
    // make a list of all points with one invalid neighbour
    // start with a point on that list; remove that point from the list
    // trace until the endpoint of that chain; remove that point from the list
    // take another point in the list until it is empty
    }
  */

  /*
    void
    BoundaryC::Order(const EdgeC & firstEdge, bool orient)
    //========================================================
    {
    HashC<BVertexC, PairC<BVertexC> > hashtable(this->Size());
  
    // make entries for all edgels in the hash table
    FOREACH_EDGE(*this, edge){
    BVertexC bvertex1(edge.Data().Begin());
    BVertexC bvertex2(edge.Data().End());
    BVertexC invalid_vertex(-1, -1);

    if (!hashtable.IsElm(bvertex1)){
    hashtable.Update(bvertex1, PairC<BVertexC>(bvertex2, invalid_vertex));
    }
    else {
    BVertexC neighbouring_vertex = hashtable.Lookup(bvertex1)->A();
    hashtable.Update(bvertex1, PairC<BVertexC>(neighbouring_vertex, bvertex2));
    }

    if (!hashtable.IsElm(bvertex2)){
    hashtable.Update(bvertex2, PairC<BVertexC>(bvertex1, invalid_vertex));
    }
    else {
    BVertexC neighbouring_vertex = hashtable.Lookup(bvertex2)->A();
    hashtable.Update(bvertex2, PairC<BVertexC>(neighbouring_vertex, bvertex1));
    }
    }

    // construct the new boundary
    BoundaryC bnd(orient);
    BVertexC present_vertex = firstEdge.Begin();
    BVertexC next_vertex(-1, -1);
    BVertexC previous_vertex(-1, -1);

    BVertexC neighbour1 = hashtable.Lookup(present_vertex)->A();
    BVertexC neighbour2 = hashtable.Lookup(present_vertex)->B();
    if (firstEdge.End()==neighbour1) next_vertex = neighbour1;
    else if (firstEdge.End()==neighbour2) next_vertex = neighbour2;
    bnd.InsLast(EdgeC(present_vertex, next_vertex));
  
    for(;;){
    present_vertex = bnd.Last().End();
    previous_vertex = bnd.Last().Begin();
    neighbour1 = hashtable.Lookup(present_vertex)->A();
    neighbour2 = hashtable.Lookup(present_vertex)->B();

    if (previous_vertex == neighbour1)
    next_vertex = neighbour2;
    else next_vertex = neighbour1;
    
    bnd.InsLast(EdgeC(present_vertex, next_vertex));

    if (next_vertex==bnd.First().Begin()) break; // boundary has been traced
    // need another exit condition in case the boundary is not complete
    }

    BoundaryC::operator=(bnd);
    }
  */

  DListC<BoundaryC> BoundaryC::Order(const EdgeC & firstEdge, bool orient) {
    DListC<BoundaryC> bnds;

    RCHashC<BVertexC, PairC<BVertexC> > hashtable = CreateHashtable();

    DListC<BVertexC> endpoints = FindEndpoints(hashtable);
    if (endpoints.IsEmpty()){
      BoundaryC bnd = OrderContinuous(hashtable, firstEdge, orient);
      bnds.InsLast(bnd);
    }
    else {
      DLIterC<BVertexC> ep_it(endpoints);
      for (ep_it.First(); ep_it.IsElm(); ep_it.Next()){
	BoundaryC bnd = OrderContinuous(hashtable, EdgeC(ep_it.Data(), CrackCodeC(CR_NODIR)) , orient);
	DLIterC<BVertexC> ep2_it(endpoints);
	for (ep2_it.First(); ep2_it.IsElm(); ep2_it.Next()){
	  if (ep2_it.Data()==bnd.Last().End()) ep2_it.Del();
	}
	bnds.InsLast(bnd);
      }
    }

    return bnds;
  }
  
  BoundaryC BoundaryC::Copy() const {
    //  cout << "BoundaryC::Copy()\n";
    return BoundaryC(EdgeListC::Copy(),orientation);
  }
  
  BoundaryC &BoundaryC::BReverse() {
    //  cout << "BoundaryC::BReverse()\n";
    Reverse();
    FOREACH_EDGE(*this, edge)
      edge.Data().Reverse();
    orientation = !orientation;
    return *this;
  }

  RCHashC<BVertexC, PairC<BVertexC> > BoundaryC::CreateHashtable() const {
    RCHashC<BVertexC, PairC<BVertexC> > hashtable;
    FOREACH_C_EDGE(*this, edge){
      BVertexC bvertex1(edge.Data().Begin());
      BVertexC bvertex2(edge.Data().End());
      BVertexC invalid_vertex(-1, -1);

      if (!hashtable.IsElm(bvertex1)){
	hashtable.Insert(bvertex1, PairC<BVertexC>(bvertex2, invalid_vertex));
      }
      else {
	BVertexC neighbouring_vertex = hashtable[bvertex1].A();
	hashtable.Insert(bvertex1, PairC<BVertexC>(neighbouring_vertex, bvertex2));
      }

      if (!hashtable.IsElm(bvertex2)){
	hashtable.Insert(bvertex2, PairC<BVertexC>(bvertex1, invalid_vertex));
      }
      else {
	BVertexC neighbouring_vertex = hashtable[bvertex2].A();
	hashtable.Insert(bvertex2, PairC<BVertexC>(neighbouring_vertex, bvertex1));
      }
    }

    return hashtable;
  }

  BoundaryC BoundaryC::OrderContinuous(const RCHashC<BVertexC, 
				       PairC<BVertexC> > & hashtable, 
				       const EdgeC & firstEdge, 
				       bool orient
				       ) const
  {
    BoundaryC bnd(orient);
    BVertexC present_vertex = firstEdge.Begin();
    BVertexC next_vertex(-1, -1);
    BVertexC previous_vertex(-1, -1);
    BVertexC invalid_vertex(-1, -1);

    BVertexC neighbour1 = hashtable[present_vertex].A();
    BVertexC neighbour2 = hashtable[present_vertex].B();
    if (firstEdge.End()==neighbour1) next_vertex = neighbour1;
    else if (firstEdge.End()==neighbour2) next_vertex = neighbour2;
    else if (neighbour1==invalid_vertex) next_vertex = neighbour2;
    else if (neighbour2==invalid_vertex) next_vertex = neighbour1;
    bnd.InsLast(EdgeC(present_vertex, next_vertex));
  
    for(;;){
      present_vertex = bnd.Last().End();
      previous_vertex = bnd.Last().Begin();
      neighbour1 = hashtable[present_vertex].A();
      neighbour2 = hashtable[present_vertex].B();

      if (previous_vertex == neighbour1)
	next_vertex = neighbour2;
      else next_vertex = neighbour1;
    
      if (next_vertex!=invalid_vertex) 
	bnd.InsLast(EdgeC(present_vertex, next_vertex));

      if (next_vertex==bnd.First().Begin() || next_vertex==invalid_vertex) break;
      // boundary has been traced
    }
  
    return bnd;
  }
  
  DListC<BVertexC> 
  BoundaryC::FindEndpoints(const RCHashC<BVertexC, PairC<BVertexC> > & hashtable) const {
    BVertexC invalid_vertex(-1, -1);
    HashIterC<BVertexC, PairC<BVertexC> > hash_iter(hashtable);
    DListC<BVertexC> endpoints;
    for(hash_iter.First(); hash_iter.IsElm(); hash_iter.Next()){
      BVertexC neighbour1 = hash_iter.Data().A();
      BVertexC neighbour2 = hash_iter.Data().B();
      if (neighbour1==invalid_vertex || neighbour2==invalid_vertex)
	endpoints.InsLast(hash_iter.Key());
    }

    return endpoints;
  }

  ostream & 
  operator<<(ostream & s, const BoundaryC & b) {
    //  s << "\nBoundary: orientation = " << b.Orient() << '\n\n';
    //  s << " row, col, ccode, element, succ, pred , edge \n";
    FOREACH_C_EDGE(b, elm)
      {
	EdgeC edge(elm.Data());
	s << edge << '\n';
	//' ' << &edge << ' ' << elm << '\n';  
      } 
    return s;
  }

  BoundaryC Line2Boundary(const BVertexC & startVertex, const BVertexC & endVertex) {
    BoundaryC boundary;
    BVertexC  vertex(startVertex);
    RealT     startRow = startVertex.Row();
    RealT     startCol = startVertex.Col();
    RealT     k = 0;
    RealT     kk = 0;
    if (endVertex.Row() == startVertex.Row())
      k = 0;
    else if (endVertex.Col() == startVertex.Col()) 
      kk = 0;
    else if (  abs(endVertex.Row() - startVertex.Row())
	       < abs(endVertex.Col() - startVertex.Col())
	       )
      k = ((RealT)(endVertex.Row() - startVertex.Row()))
	/(endVertex.Col() - startVertex.Col());
    else
      kk = ((RealT)(endVertex.Col() - startVertex.Col()))
        /(endVertex.Row() - startVertex.Row());
  
    if (startVertex.Col() < endVertex.Col())
      { // 1 or 2 or 7 or 8 octant
	if (startVertex.Row() > endVertex.Row())
	  { // 1 or 2 octant
	    if ( -(endVertex.Row()-startVertex.Row()) 
		 < (endVertex.Col()-startVertex.Col())
		 )
	      { // 1. octant
		//        cout << "1. octant: " << k << '\n';
		while (vertex.Col() < endVertex.Col())
		  {
		    boundary.InsLast(EdgeC(vertex,CR_RIGHT));
		    vertex.Step(CR_RIGHT);
		    if ( ::Abs(startRow + k *(vertex.Col() - startCol) - vertex.Row())
			 >0.5
			 )
		      {
			boundary.InsLast(EdgeC(vertex,CR_UP));
			vertex.Step(CR_UP);
		      }
		  }
	      }
	    else
	      { // 2. octant
		//        cout << "2. octant: " << kk << '\n';
		while (vertex.Row() > endVertex.Row())
		  {
		    boundary.InsLast(EdgeC(vertex,CR_UP));
		    vertex.Step(CR_UP);
		    if ( ::Abs(startCol + kk *(vertex.Row() - startRow) - vertex.Col())
			 >0.5
			 )
		      {
			boundary.InsLast(EdgeC(vertex,CR_RIGHT));
			vertex.Step(CR_RIGHT);
		      }
		  }
	      }
	  }
	else
	  { // 7 or 8 octant
	    if (  (endVertex.Row()-startVertex.Row()) 
		  < (endVertex.Col()-startVertex.Col())
		  )
	      { // 8. octant
		//        cout << "8. octant: " << k << '\n';
		while (vertex.Col() < endVertex.Col())
		  {
		    boundary.InsLast(EdgeC(vertex,CR_RIGHT));
		    vertex.Step(CR_RIGHT);
		    if ( ::Abs(startRow + k *(vertex.Col() - startCol) - vertex.Row())
			 >0.5
			 )
		      {
			boundary.InsLast(EdgeC(vertex,CR_DOWN));
			vertex.Step(CR_DOWN);
		      }
		  }
	      }
	    else
	      { // 7. octant
		//        cout << "7. octant: " << kk << '\n';
		while (vertex.Row() < endVertex.Row())
		  {
		    boundary.InsLast(EdgeC(vertex,CR_DOWN));
		    vertex.Step(CR_DOWN);
		    if ( ::Abs(startCol + kk *(vertex.Row() - startRow) - vertex.Col())
			 >0.5
			 )
		      {
			boundary.InsLast(EdgeC(vertex,CR_RIGHT));
			vertex.Step(CR_RIGHT);
		      }
		  }
	      }
	  }
      }
    else
      { // 3 or 4 or 5 or 6 octant
	if (startVertex.Row() > endVertex.Row())
	  { // 3 or 4 octant
	    if ( -(endVertex.Row()-startVertex.Row()) 
		 <-(endVertex.Col()-startVertex.Col())
		 )
	      { // 4. octant
		//        cout << "4. octant: " << k << '\n';
		while (vertex.Col() > endVertex.Col())
		  {
		    boundary.InsLast(EdgeC(vertex,CR_LEFT));
		    vertex.Step(CR_LEFT);
		    if ( ::Abs(startRow + k *(vertex.Col() - startCol) - vertex.Row())
			 >0.5
			 )
		      {
			boundary.InsLast(EdgeC(vertex,CR_UP));
			vertex.Step(CR_UP);
		      }
		  }
	      }
	    else
	      { // 3. octant
		//        cout << "3. octant: " << kk << '\n';
		while (vertex.Row() > endVertex.Row())
		  {
		    boundary.InsLast(EdgeC(vertex,CR_UP));
		    vertex.Step(CR_UP);
		    if ( ::Abs(startCol + kk *(vertex.Row() - startRow) - vertex.Col())
			 >0.5
			 )
		      {
			boundary.InsLast(EdgeC(vertex,CR_LEFT));
			vertex.Step(CR_LEFT);
		      }
		  }
	      }
	  }
	else
	  { // 5 or 6 octant
	    if (  (endVertex.Row()-startVertex.Row()) 
		  <-(endVertex.Col()-startVertex.Col())
		  )
	      { // 5. octant
		//        cout << "5. octant: " << k << '\n';
		while (vertex.Col() > endVertex.Col())
		  {
		    boundary.InsLast(EdgeC(vertex,CR_LEFT));
		    vertex.Step(CR_LEFT);
		    if ( ::Abs(startRow + k *(vertex.Col() - startCol) - vertex.Row())
			 >0.5
			 )
		      {
			boundary.InsLast(EdgeC(vertex,CR_DOWN));
			vertex.Step(CR_DOWN);
		      }
		  }
	      }
	    else
	      { // 6. octant
		//        cout << "6. octant: " << kk << '\n';
		while (vertex.Row() < endVertex.Row())
		  {
		    boundary.InsLast(EdgeC(vertex,CR_DOWN));
		    vertex.Step(CR_DOWN);
		    if ( ::Abs(startCol + kk *(vertex.Row() - startRow) - vertex.Col())
			 >0.5
			 )
		      {
			boundary.InsLast(EdgeC(vertex,CR_LEFT));
			vertex.Step(CR_LEFT);
		      }
		  }
	      }
	  }
      }
    //  cout << "Line2Boundary - size:" << boundary.Size() << '\n';
    return boundary;
  }
}



