// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImageProc

#include "Ravl/Image/ArcDetector.hh"

namespace RavlImageN {

  //: Default constructor.
  
  ArcDetectorC::ArcDetectorC()
    : arcTolerance(2),
      minRadius(4),
      maxRadius(200)
  {}
  
  //: Convert index list to point arrays.
  
  DListC<Array1dC<Point2dC> > ArcDetectorC::List2PntArray(DListC<DListC<Index2dC> > edges,IntT minLength) {
    DListC<Array1dC<Point2dC> > edgeStrs;
    
    // Convert into arrays.
    
    Point2dC off(0.5,0.5);
    for(DLIterC<DListC<Index2dC> > lit(edges);lit;lit++) {
      //cerr << "Chain length=" << lit->Size() << "\n";
      IntT len = lit->Size();
      if(len < minLength)
	continue;
      Array1dC<Point2dC> arr(len);
      Array1dIterC<Point2dC> ait(arr);
      for(DLIterC<Index2dC> it(*lit);it;it++,ait++)
	*ait = Point2dC(*it) + off;
      edgeStrs.InsLast(arr);
    }
    
    return edgeStrs;
  }
  
  //: Check candate arc.
  
  IntT ArcDetectorC::CheckArc(const Arc2dC &arc,const Array1dC<Point2dC> &pixels,int start) {
    RealT oTolerance2 = Sqr(arc.Radius() + arcTolerance);
    RealT iTolerance2 = Sqr(arc.Radius() - arcTolerance);
    IndexRangeC range(start,pixels.Range().Max());
    BufferAccessIterC<Point2dC> it(pixels,range);
    for(;it;it++) {
      RealT dist = it->SqrEuclidDistance(arc.Centre());
      if(dist > oTolerance2 || dist < iTolerance2)
	return (&(*it) - pixels.ReferenceElm())-1; // The one before worked.
    }
    return pixels.Range().Max().V(); // All of them.
  }
  
  
  IntT ArcDetectorC::FindArcs(const Array1dC<Point2dC> &pixels,DListC<Arc2dSegmentC> &arcs) {
    IntT size = pixels.Size();
    cerr << "ArcDetectorC::FindArcs(). Pixels=" << pixels.Size() << "\n";
    SArray1dC<bool> arcStarts(size);
    arcStarts.Fill(false);
    if(size < 8)
      return 0;
    IntT i = 0;
    IntT j = 3;
    IntT k = 7;
    
    Arc2dC arc;
    bool done = false;
    Arc2dSegmentC maxArc;
    IntT maxLen;
    IntT minEnd = 0;
    while(i < size && !done) {
      maxLen = -1;
      while(k < size) {
	bool fitOk = arc.Fit(pixels[i],pixels[j],pixels[k]);
	if(!fitOk || arc.Radius() < minRadius || arc.Radius() > maxRadius) {
	  // Fit failed, try another arc.
	  j++;
	  k += 2;
	  continue;
	}
	
	IntT arcEnd = CheckArc(arc,pixels,i);	
	bool &as = arcStarts[arcEnd];
	if(!as && arcEnd > minEnd) {
	  // This must be the longest arc for this end point.
	  //cerr << "Arc: i=" << i << " j=" << j << " k=" << k << " End=" << arcEnd << "\n";
	  int len = arcEnd - i;
	  if(len > maxLen) {
	    maxArc = Arc2dSegmentC(arc,Array1dC<Point2dC>(pixels,IndexRangeC(i,arcEnd)));
	    maxLen = len;
	    minEnd = arcEnd;
	  }
	}
#if 1
	if(arcEnd > k) {
	  // Start from where we left off.
	  k = arcEnd;
	  j = (i + k)/2;
	  continue;
	}
#endif
	j++;
	k += 2; 	
      }
      if(maxLen > 0) {
	cerr << "Arc: i=" << maxArc.IMin() << " k=" << maxArc.IMax() << " Size=" << maxArc.Edges().Size() <<"\n";
	arcStarts[maxArc.IMax()] = true;
	arcs.InsLast(maxArc);
      }
      // Try next start position.
      i++;
      j = i + 3;
      k = i + 7;
    }
    
    
    
    return 0;
  }
  
  
  //: Given a set of edge lists create a set of arc's.
  
  DListC<Arc2dSegmentC> ArcDetectorC::Apply(DListC<DListC<Index2dC> > edges) {
    DListC<Arc2dSegmentC> ret;
    DListC<Array1dC<Point2dC> > arrLst = List2PntArray(edges,8);
    for(DLIterC<Array1dC<Point2dC> > it(arrLst);it;it++)
      FindArcs(*it,ret);
    return ret;
  }
  
}
