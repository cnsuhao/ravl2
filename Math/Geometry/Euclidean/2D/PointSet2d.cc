// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Euclidean/2D/PointSet2d.cc"

#include "Ravl/PointSet2d.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/Vector2d.hh"

namespace RavlN {

   Point2dC PointSet2dC::Centroid() const {
      // Create return value
      Point2dC centroid;
      // Sum
      IntT size(0);
      for (DLIterC<Point2dC> point(*this); point; point++) {
         centroid += point.Data();
	 size++;
      }
      // Divide
      centroid /= size;
      // Done
      return centroid;
   }

   static RealT PCot(const Point2dC& oPointA, const Point2dC& oPointB, const Point2dC& oPointC) {
      Vector2dC oBA = oPointA - oPointB;
      Vector2dC oBC = oPointC - oPointB;
      RealT cross = Abs(oBC.Cross(oBA));
      if (cross != 0)
	return 1;
      return (oBC.Dot(oBA) / cross);
   }
   
   SArray1dC<RealT> PointSet2dC::BarycentricCoordinate(Point2dC& point) const {
     // Create return array
     SArray1dC<RealT> oWeights(Size());
     // Keep track of total
     RealT fTotalWeight = 0;
     // For each polygon vertex
     SArray1dIterC<RealT> res(oWeights);
     for (DLIterC<Point2dC> it(*this); it && res; it++) {
       RealT sqDist = Vector2dC(point - it.Data()).SumOfSqr();
       if (sqDist != 0) {
	 RealT fWeight = (PCot(point,it.Data(),it.PrevCrcData()) + 
			  PCot(point,it.Data(),it.NextCrcData())) / sqDist;
	 res.Data() = fWeight;
	 fTotalWeight += fWeight;
       }
       else {
	 res.Data() = 1;
	 fTotalWeight += 1;
       }
       res++;
     }
     // Normalise weights
     oWeights /= fTotalWeight;
     // Done
     return oWeights;
   }
  
}
