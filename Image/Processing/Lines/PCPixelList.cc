// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImageProc

#include "Ravl/Image/PCPixelList.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/SArr1Iter.hh"

namespace RavlImageN {

  /////////////////////////////
  // Remove points in list from the image.
  // Set the to zero.
  
  bool PCPixelListC::RemoveFromImage(ImageC<ByteT> &img) {
    DLIterC<PCIndex2dC> It(*this);
    for(It.First();It.IsElm();It.Next())
      img[It.Data()] = 0;
    return true;
  }
  

  ////////////////////////////
  // Trim points that are too far appart to code effiecently  and 
  // estimate average distance between points.
  
  IntT PCPixelListC::TrimLine(RealT MaxDist,RealT &DistEst) {
    DLIterC<PCIndex2dC> It(*this);
    RealT TotDist = 0;
    IntT N = 0;
    if(!It.IsElm()) {
      if(List().Size() != 0) {
	cout << "PCPixelListC::TrimLine(), Bad List !!!!! \n";
      }
      DistEst = 1;
      return 0;
    }
    N++; // There's one!
    // Forward.
    PCIndex2dC *cur,*Last = &It.Data();
    It.Next();
    for(;It.IsElm();It.Next()) {
      cur = &It.Data();
      RealT Dist = Last->ClosestPnt().EuclidDistance(cur->ClosestPnt());
      if(Dist > MaxDist) {
	while(It.IsElm())
	  It.DelMoveNext();
	// Cut
	break;
      }
      Last = cur;
      N++;
      TotDist += Dist;
    }
    // Backward
    It = *this;
    Last = &It.Data();
    It.Prev();
    for(;It.IsElm();It.Prev()) {
      cur = &It.Data();
      RealT Dist = Last->ClosestPnt().EuclidDistance(cur->ClosestPnt());
      if(Dist > MaxDist) {
	while(It.IsElm())
	  It.Del();
	// Cut
	break;
      }
      Last = cur;
      N++;
      TotDist += Dist;
    }
    //DBInt.Message(StringC("Trim complete. Size ") + StringC(N) + "\n");
    //DBInt.Wait();
    DistEst = (RealT) TotDist / N;
    return N;
  }
  
  ///////////////////////////////////////
  // Trim points that are too far appart to code effiecently  and 
  // estimate average distance between points. But use the longest
  // segment of pixels without a gap. 
  // Return: Number of pixels in segment.
  
  IntT PCPixelListC::TrimLongest(RealT MaxDist,RealT &DistEst) {
    DLIterC<PCIndex2dC> it(*this);
    IntT Longest  = 0,curLen = 0; 
    RealT totDist = 0;
    RealT LongDist = 0;
    it.First();
    PCIndex2dC *cur,*Last = &it.Data();
    DLIterC<PCIndex2dC> lStart(it),lEnd,CStart(it);
    it.Next();
    for(;it.IsElm();it.Next()) {
      cur = &it.Data();
      RealT Dist = Last->ClosestPnt().EuclidDistance(cur->ClosestPnt());
      if(Dist > MaxDist) {
	if(curLen > Longest) {
	  Longest = curLen;
	  LongDist = totDist;
	  lStart = CStart;
	  lEnd = it;
	}
	CStart = it;
	curLen = 0;
	totDist = 0;
      }
      curLen++;
      totDist += Dist;
      Last = cur;
    }
    if(curLen > Longest) {
      Longest = curLen;
      LongDist = totDist;
      lStart = CStart;
      lEnd = it;
    }
    if(Longest == 0)
      return 0; // Must be zero length line !!
    
    DListC<PCIndex2dC> pnts = List();
    //pnts.Tail(lEnd); // Cut out the tail.
    //pnts.Head(lStart); // Cut out the head of the list.
    lEnd.InclusiveTail();
    lStart.Head();
    First(); // Might as well point to the first element.
    //(*this).Nth(Longest/2); // Setup the mid ptr.
    DistEst = (RealT) LongDist / Longest;
    return Longest;
  }
  
  ////////////////////////////////
  // Turn list into an array.
  
  SArray1dC<Point2dC> PCPixelListC::PointList() const {
    SArray1dC<Point2dC> ret(Size());
    DLIterC<PCIndex2dC> it(*this);
    SArray1dIterC<Point2dC> ait(ret);
    for(it.First();it;it++) 
      *ait = *it;
    return ret;
  }
  
  ///////////////////////////////
  //: Write out appropriate GF header.
  
  bool PCPixelListC::WriteGFHeader(ostream &out) {
    out << "pointset ";
    return true;
  }
  
  
  ///////////////////////////////
  // Write points in GF format.
  
  bool PCPixelListC::WriteGFPnts(ostream &out) const {
    IntT lsize = Size();
    out << lsize << " ";
    DLIterC<PCIndex2dC> It(*this);
    for(It.First();It.IsElm();It.Next()) 
      out << It.Data().Col() << " " << It.Data().Row() << " ";
    return true;
  }

}
