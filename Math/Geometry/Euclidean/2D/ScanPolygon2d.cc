// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/ScanPolygon2d.hh"
#include "Ravl/SArray1dIter2.hh"
#include <stdlib.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  
  ScanPolygon2dC::LineSegmentC::LineSegmentC(const Point2dC *_p1,const Point2dC *_p2) 
    : p1(_p1),
      p2(_p2)
  {}
  
  //: Get column of intersection with row.
  
  bool ScanPolygon2dC::LineSegmentC::IntersectRow(RealT row,RealT &col) const {
    //cerr << "ScanPolygon2dC::LineSegmentC::IntersectRow() " << *p1 << " -> " << *p2 << " @ " << row << "\n";
    return LinePP2dC(*p1,*p2).IntersectRow(row,col);
  }
  
  //: Get row intersection with no checking.
  
  RealT ScanPolygon2dC::LineSegmentC::IntersectRow(RealT row) const {
    RealT col = 0;
    if(!LinePP2dC(*p1,*p2).IntersectRow(row,col))
      cerr << "ScanPolygon2dC::LineSegmentC::IntersectRow(), Failed. \n";
    return col;
  }
  
  //:-----------------------------------------------------
  
  static int ComparRows(const void *e1,const void *e2) {
    Point2dC &p1 =**((Point2dC **) e1); 
    Point2dC &p2 =**((Point2dC **) e2);
    RealT val = p1.Row() - p2.Row();
    //cerr << "val=" << val << "\n";
    // Make sure rounding doesn't screw things up.
    if(val > 0) return 1;
    if(val < 0) return -1;
    // Sort on column next
    val = p1.Col() - p2.Col();
    if(val > 0) return 1;
    if(val < 0) return -1;
    return 0;
  }
  
  //: Get following point on polygon
  
  const Point2dC *ScanPolygon2dC::NextPnt(const Point2dC *pnt) {
    if(pnt == lastPnt) return firstPnt;
    return (pnt + 1);
  }
  
  //: Get previous point on polygon
  
  const Point2dC *ScanPolygon2dC::PrevPnt(const Point2dC *pnt) {
    if(pnt == firstPnt) return lastPnt;
    return (pnt - 1);
  }
  
  //: Quantise row position
  
  RealT ScanPolygon2dC::RowQuant(RealT row) {
    RealT qRow = row / rowStep;
    return Floor(qRow) * rowStep;
  }
  
  //: Goto first polygon in scan.
  
  bool ScanPolygon2dC::First(const Polygon2dC &poly,RealT _rowStep) {
    rowStep = _rowStep;
    
    // Make an array of lines and points
    
    UIntT size = poly.Size();
    SArray1dC<Point2dC> points(size);
    SArray1dC<Point2dC *> ptrs(size);
    SArray1dIter2C<Point2dC,Point2dC *> lit(points,ptrs);
    
    for(DLIterC<Point2dC> it(poly);it;it++,lit++) {
      lit.Data1() = *it;
      lit.Data2() = &lit.Data1();
    }
    firstPnt = &(points[0]);
    lastPnt = &(firstPnt[size-1]);
    qsort((void *) &(ptrs[0]),(size_t) size,sizeof(Point2dC *),&ComparRows);
    
#if DODEBUG
    cerr << " " << size << " points:";
    for(SArray1dIterC<Point2dC *> it(ptrs);it;it++) 
      cerr << " " << *(*it) << ",";
    cerr << "\n";
#endif
    
    pit = ptrs;
    row = RowQuant((*pit)->Row());
    ONDEBUG(cerr << "First row=" << row << " \n");
    ONDEBUG(cerr << " " << *PrevPnt(*pit) << " " << **pit << " " << *NextPnt(*pit) << "\n"); 
    CheckSpans();
    spans.First();
    if(!spans.IsElm())
      return false;
    SetupSpan();
    return true;
  }
  
  //: Setup current 'span'
  
  bool ScanPolygon2dC::SetupSpan() {
    RealT v1 = 0,v2 = 0;
    RavlAssert(spans.IsElm());
    spans->Data1().IntersectRow(row,v1);
    spans->Data2().IntersectRow(row,v2);
    span = RealRangeC(v1,v2);
    return true;
  }
  
  bool ScanPolygon2dC::CheckSpans() {
    ONDEBUG(cerr << "ScanPolygon2dC::CheckSpans() \n");
    while(pit) {
      RealT nrow = (*pit)->Row();
      ONDEBUG(cerr << "ScanPolygon2dC::Next(), pit=" << *(*pit) << " Row=" << row << "\n");
      if(row < nrow)
	break;
      // Is this end or begining of an existing line ?
      const Point2dC *at = *pit;
      bool done = false;
      for(spans.First();spans;spans++) {
	ONDEBUG(cerr << "At=" << (void *) at << 
		" D1.P1()=" << spans->Data1().P1() << 
		" D1.P2()=" << spans->Data1().P2() << 
		" D2.P1()=" << spans->Data2().P1() << 
		" D2.P2()=" << spans->Data2().P2() << "\n");
	
	if(spans->Data1().P1() == at) {
	  RavlAssert(pit);
	  const Point2dC *prev = PrevPnt(*pit);
	  ONDEBUG(cerr << "Prev=" << *prev << "\n");
	  if(prev->Row() > nrow) {
	    ONDEBUG(cerr << "Add segment 1 " << *prev << " " << *spans->Data1().P1() <<  "\n");
	    spans->Data1() = LineSegmentC(prev,spans->Data1().P1());
	  } else {
	    if(spans->Data1().P1() == spans->Data2().P2()) {
	      spans.Del();
	    } else {
	      spans.Del();
	      //RavlAssert(0);
	    }
	  }
	  pit++;
	  done = true;
	  break;
	}
	if(spans->Data2().P2() == at) {
	  RavlAssert(pit);
	  const Point2dC *next = NextPnt(*pit);
	  ONDEBUG(cerr << "Next=" << *next << "\n");
	  if(next->Row() > nrow) {
	    ONDEBUG(cerr << "Add segment 2 " << *spans->Data2().P2() << " " << *next <<  "\n");
	    spans->Data2() = LineSegmentC(spans->Data2().P2(),next);
	  } else {
	    ONDEBUG(cerr << "Merge with next segment. \n");
	    RavlAssert(!spans.IsLast()); // Must be a following span to merge with.
	    spans->Data2() = spans.NextData().Data2();
	    spans.Next();
	    spans.Del();
	  }
	  pit++;
	  done = true;
	  break;
	}
      }
      if(done) {
	ONDEBUG(cerr << "Done. " << spans.List().Size() << "\n");
	continue;
      }
      RavlAssert(pit);
      ONDEBUG(cerr << "Found a spike. \n");
      //: Must be a spike
      // Either split existing span, or create a new one.
      const Point2dC *next = NextPnt(*pit);
      const Point2dC *prev = PrevPnt(*pit);
      if(next->Row() < (*pit)->Row() || prev->Row() < (*pit)->Row()) {
	pit++;
	continue;
      }
      
      LineSegmentC seg1(prev,*pit);
      LineSegmentC seg2(*pit,next);
      RealT prow = (**pit)[0];
      RealT pcol = (**pit)[1];
      RealT testRowAt = prow + 1;
      RealT row1,row2;
      bool newSpike = true;
      if(seg1.IntersectRow(testRowAt,row1) && seg2.IntersectRow(testRowAt,row2))
	newSpike =  row1 < row2 ;
      ONDEBUG(cerr << "Found a spike. New =" << newSpike << " @ " << **pit << "\n");
      if(newSpike) {
	// New segment
	for(spans.First();spans;spans++)
	  if(pcol < spans->Data1().IntersectRow(row))
	    break;
	spans.InsertBef(PairC<LineSegmentC>(seg1,
					    seg2));
      } else {	
	// Split segment
	for(spans.First();spans;spans++)
	  if(pcol > spans->Data1().IntersectRow(row))
	    break;
	RavlAssert(spans); // Should be in a valid span!
	LineSegmentC tmp = spans->Data2();
	spans->Data2() = seg2;
	spans.InsertAft(PairC<LineSegmentC>(seg1,
					    tmp));
	
      }
      pit++;
    }
    return true;
  }

  //: Goto next scan element.
  
  bool ScanPolygon2dC::Next() {
    //ONDEBUG(cerr << "ScanPolygon2dC::Next(), Spans=" << spans.List().Size() << " Row=" << row << "\n");
    spans.Next();
    if(spans) {
      SetupSpan();
      return true;
    }
    row += rowStep;
    //ONDEBUG(cerr << "ScanPolygon2dC::Next(), Row=" << row << "\n"); 
    CheckSpans();
    
    spans.First();
    if(!spans.IsElm())
      return false;
    SetupSpan();
    return true;
  }
  
}
