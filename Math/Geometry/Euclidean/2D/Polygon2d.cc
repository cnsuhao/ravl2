// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Euclidean/2D/Polygon2d.cc"

#include "Ravl/Polygon2d.hh"

namespace RavlN {

   RealT Polygon2dC::Area2() const {

      RealT          sum = 0.0;  // Partial area sum
      DLIterC<Point2dC> ptr(*this);
      DLIterC<Point2dC> pLast(*this);
      pLast.Last();

      Point2dC     o(ptr.Data());
      for (ptr.Next(); ptr != pLast; ptr.Next())
         sum += o.Area2(ptr.Data(), ptr.NextData());
      return sum;
   }
  
   bool Polygon2dC::IsDiagonal(const DLIterC<Point2dC> & a, const DLIterC<Point2dC> & b, bool allowExternal) const {
      if (allowExternal) {
         
         Point2dC ap(a.Data());
         Point2dC bp(b.Data());
         
         // For each edge (k,k+1) of this polygon.
         for (DLIterC<Point2dC> k(*this); k; k++)
            {
               DLIterC<Point2dC> k1(k);
               k1.NextCrc();
               // Skip edges incident to a or b. 
               if ( ! (( k == a ) || ( k1 == a ) ||( k == b ) || ( k1 == b )) )
                  if ( LinePP2dC(ap,bp).HasInnerIntersection(LinePP2dC(k.Data(), k1.Data())) )
                     return false;
            }
         return true;
      }
      else {
         return IsInCone(a,b) && IsDiagonal(a,b,true);
      }
   }

   bool Polygon2dC::IsInCone(const DLIterC<Point2dC> & a, const DLIterC<Point2dC> & b) const {
      Point2dC pa(a.Data());
      Point2dC pan(a.NextCrcData());
      Point2dC pap(a.PrevCrcData());
      Point2dC pb(b.Data());

      // If 'pa' is a convex vertex ['pan' is left or on (pap, pa) ].
      if (LinePP2dC(pap, pa).IsPointToLeftOn(pan))
         return LinePP2dC(pa, pb).IsPointToLeft(pap) && LinePP2dC(pb, pa).IsPointToLeft(pan);
      else
         // Assume (i-1,i,i+1) not collinear.
         // else 'pa' is reflex.
         return !(LinePP2dC(pa, pb).IsPointToLeftOn(pan) && LinePP2dC(pb, pa).IsPointToLeftOn(pap));
   }

   bool Polygon2dC::Contains(const Point2dC & p) const {
      
      // Check singularities.
      SizeT size = Size();
      if (size == 0) return false;
      Point2dC p1(First());
      if (size == 1) return p == p1;
      
      // The point can lie on the boundary of the polygon.
      for (DLIterC<Point2dC> point(*this); point; point++) {
         if (LinePP2dC(point.Data(), point.NextCrcData()).IsPointIn(p))
            return true;
      }
      
      // Take my testline arbitrarily as parallel to y=0. Assumption is that 
      // Point2dC(p[0]+100...) provides enough accuracy for the calculation
      // - not envisaged that this is a real problem
      Point2dC secondPoint(p[0]+100,p[1]);
      LinePP2dC testLine(p, secondPoint);
      
      // Just something useful for later, check whether the last point lies
      // to the left or right of my testline
      bool leftof = testLine.IsPointToLeft(Last());
      
      // For each edge (k,k+1) of this polygon count the instersection
      // with the polygon segments.
      int count = 0;
      for (DLIterC<Point2dC> k(*this); k; k++) {
         LinePP2dC l2(k.Data(), k.NextCrcData());
         
         // If l2 and testline are collinear then either the point lies on an
         // edge (checked already) or it acts as a vertex. I really
         // should check for the case, or it could throw ParInterSection
         if (testLine.IsPointOn(l2.P1())
             && testLine.IsPointOn(l2.P2()));
         
         // Be sure to count each vertex just once
         else if (l2.ParIntersection(testLine) > 0
                  && l2.ParIntersection(testLine) <=1
                  && testLine.ParIntersection(l2) > 0) 
            count++;   
    
         // Examine the case where testline meets polygon at vertex "cusp"
         // iff testline passes through a vertex and yet not into polygon
         // at that vertex _and_ the vertex lies to the right of my test point
         // then we count that vertex twice
         else if (l2.ParIntersection(testLine) == 0 && p.X() <= l2.P1()[0]
                  && leftof == testLine.IsPointToLeft(l2.P2()))
            count++;
    
         // Set the flag for the case of the line passing through 
         // the endpoint vertex
         if (l2.ParIntersection(testLine) ==1)
            leftof = testLine.IsPointToLeft(l2.P1());
      }
  
      return (count%2) == 1;
   }

}
