// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlImageProc
//! rcsid="$Id$"
//! authors="George Matas, Radek Marik and Charles Galambos"

#include "Ravl/Stack.hh"
#include "Ravl/Image/EdgeLink.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/SArr1Iter.hh"
#include "Ravl/Image/DrawFrame.hh"

namespace RavlImageN {

  EdgeLinkC HysterisisThreshold(const ImageC<RealT> &img,RealT upThr,RealT downThr) {
    EdgeLinkC ret(img.Rectangle());
    
    for(Array2dIter2C<ByteT,RealT> it(ret,img);it;it++)
      it.Data1() = (it.Data2() <= downThr) ? EDGE_PROC : EDGE_UNPROC;
    
    DrawFrame(ret,(ByteT) EDGE_PROC,ret.Frame());
    
    for(Array2dIter2C<ByteT,RealT> it(ret,img);it;it++)
      if(it.Data2() > upThr && it.Data1() ==  EDGE_UNPROC)
	ret.LabelContour(it.Index());
    
    for(Array2dIterC<ByteT> it(ret);it;it++)
      if(*it == EDGE_UNPROC)
	*it = EDGE_PROC;
    
    return ret;
  }
  
  
  void EdgeLinkC::LabelContour(const Index2dC &spxl) {
    Index2dC pxl(spxl);
    StackC<Index2dC> stack;
    
    stack.Push(pxl);
    PutState(pxl,EDGE_INSTRING); // to avoid loops
    edgeCount++;
    NeighbourOrderT dir[8];
    
    while (!stack.IsEmpty()) {
      pxl = stack.Pop();
      IntT neighbours = 0;
      bool dr = true, ur = true, ul = true, dl = true;
      
      if (IsEdge(pxl.DownN()))  { dir[neighbours++]=NEIGH_DOWN;  dr = dl = false; }
      if (IsEdge(pxl.RightN())) { dir[neighbours++]=NEIGH_RIGHT; dr = ur = false; }
      if (IsEdge(pxl.UpN()))    { dir[neighbours++]=NEIGH_UP;    ur = ul = false; }
      if (IsEdge(pxl.LeftN()))  { dir[neighbours++]=NEIGH_LEFT;  ul = dl = false; }
      
      if (dr && IsEdge(pxl.LowerRightN()))   dir[neighbours++]=NEIGH_DOWN_RIGHT;
      if (ur && IsEdge(pxl.UpperRightN()))   dir[neighbours++]=NEIGH_UP_RIGHT;
      if (ul && IsEdge(pxl.UpperLeftN()))    dir[neighbours++]=NEIGH_UP_LEFT;
      if (dl && IsEdge(pxl.LowerLeftN()))    dir[neighbours++]=NEIGH_DOWN_LEFT;
      
      // put all neighbours not expanded yet stored in dir on stack.
      for(IntT k=0; k < neighbours; k++) {
	Index2dC pxlNext(pxl.Neighbour(dir[k]));
	if (IsNotExpanded(pxlNext)) {
	  stack.Push(pxlNext);
	  PutState(pxlNext,EDGE_INSTRING);
	  edgeCount++;
	}
      }
      
      // label edge point according to the number of neighbours.
      ByteT &val = (*this)[pxl];
      if(neighbours <= 1 || neighbours > 2)
	PutState(val,EDGE_JUNCT);
      else {
	PutDir(val, dir[0], FB_FORWARD);
	PutDir(val, dir[1], FB_BACKWARD);
      }
    }
  }

  //: List all edges in image
  
  SArray1dC<Index2dC> EdgeLinkC::ListEdges() {
    SArray1dC<Index2dC> ret(edgeCount);
    SArray1dIterC<Index2dC> rit(ret);
    for(Array2dIterC<ByteT> it(*this);it;it++) {
      if(*it == EDGE_PROC) {
	RavlAssert(rit);
	*rit = it.Index();
	rit++;
      }
    }
    return ret;
  }
  
  DListC<DListC<Index2dC> >  EdgeLinkC::LinkEdges() {
    DListC<DListC<Index2dC> > strings;
    for(Array2dIterC<ByteT> it(*this);it;it++) {
      if(GetState(*it) != EDGE_INSTRING) 
	continue;
      Index2dC pxl = it.Index();
      DListC<Index2dC> string;
      string.InsFirst(pxl);
      PutState(*it, EDGE_PROC);
      // Go both ways along pixel chain.
      for(IntT dir_num=0; dir_num<=1; dir_num++) {
	NeighbourOrderT dir = GetDir(*it,(FBOrientationT) dir_num);
	Index2dC pxlNext = pxl.Neighbour(dir);
	// Step along pixel chain. 
	while(1) {
	  ByteT &pval = (*this)[pxlNext];
	  if(GetState(pval) != EDGE_INSTRING)
	    break;
	  PutState(pval,EDGE_PROC);
	  if (dir_num == 0)
	    string.InsFirst(pxlNext);
	  else
	    string.InsLast(pxlNext);
	  NeighbourOrderT old_dir = RavlN::Reverse(dir);
	  dir = GetDir(pval, FB_FORWARD);
	  if (dir == old_dir) // Check we're not going back.
	    dir = GetDir(pval, FB_BACKWARD);
	  pxlNext.Step(dir);
	}
	
	// Append the junction point.
	// It can be EDGE_PROC if string is closed.
	if (GetState(pxlNext) == EDGE_JUNCT) {
	  if (dir_num==0)   
	    string.InsFirst(pxlNext);
	  else
	    string.InsLast(pxlNext);
	}
      }
      strings.InsLast(string); 
    }
    // the upper six bit contain information about neigbouring edge direction
    // remove the information                                                
    for(Array2dIterC<ByteT> it(*this);it;it++) {
      // Remove the information about
      // the edge direction.
      *it &= 3;
      if (GetState(*it) == EDGE_JUNCT)
	PutState(*it,EDGE_PROC);
    }
    
    return strings;
  }
}
