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
#include "Ravl/Vector2d.hh"

namespace RavlN {

   Point2dC PointSet2dC::Centroid() const {
      // Create return value
      Point2dC centroid;
      // Sum
      for (DLIterC<Point2dC> point(*this); point; point++)
         centroid += point.Data();
      // Divide
      centroid /= Size();
      // Done
      return centroid;      
   }

   static RealT PCot(const Point2dC& oPointA, const Point2dC& oPointB, const Point2dC& oPointC) {
      Vector2dC oBA = oPointA - oPointB;
      Vector2dC oBC = oPointC - oPointB;
      return (oBC.Dot(oBA) / fabs(oBC.Cross(oBA)));
   }
   
   DListC<RealT> PointSet2dC::BCoord(Point2dC& point) const {
      DListC<RealT> oWeights;
      RealT fTotalWeight = 0;
      // For each polygon vertex
      for (UIntT iCurrent(0); iCurrent<Size(); iCurrent++) {
         UIntT iNext = (iCurrent + 1) % Size();
         UIntT iPrev = (iCurrent + Size() - 1) % Size();
         RealT sqDist = Vector2dC(point - Nth(iCurrent)).Modulus();
         sqDist *= sqDist;
         RealT fWeight = (PCot(point,Nth(iCurrent),Nth(iPrev)) + 
                          PCot(point,Nth(iCurrent),Nth(iNext))) / sqDist;
         oWeights.InsLast(fWeight);
         fTotalWeight += fWeight;
      }
      // Normalise weights
      for (DLIterC<RealT> oWeightIter(oWeights); oWeightIter; oWeightIter++) {
         oWeightIter.Data() /= fTotalWeight;
      }
      // Done
      return oWeights;
   }
   
}
