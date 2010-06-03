// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_VECTORINDEXITERN_HEADER
#define RAVL_VECTORINDEXITERN_HEADER 1
///////////////////////////////////////////////
//! rcsid="$Id: VectorIndexIterN.hh 4130 2004-03-20 15:08:03Z craftit $"
//! file="Ravl/Math/Indexing/VectorIndexIterN.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Charles Galambos"
//! date="04/10/2000"
//! docentry="Ravl.Math.Vector Index"

#include "Ravl/VectorIndex.hh"
#include "Ravl/PriQueueL.hh"
#include "Ravl/PriQueue.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/HSet.hh"
#include "Ravl/StdMath.hh"

#include "Ravl/Assert.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //! userlevel=Normal
  //: Iterate through the N closest points in a VectorIndex.
  
  template<class LabelT> 
  class VectorIndexIterNC {
  public:
    typedef Tuple2C<VectorC, LabelT> DataT;

    inline VectorIndexIterNC(VectorIndexC<LabelT> & thedata,
			     const VectorC & thepoint);
    //: Constructor.

    inline void First();
    //: Get ready to return closest point.

    inline bool IsElm() const 
    { return ordered.IsElm(); }
    //: Any points yet to be returned?
  
    inline operator bool() const
    { return IsElm(); }
    //: At a valid point ?
    
    inline void Next();
    //: Goto next point.
    
    inline void operator++(int)
    { Next(); }
    //: Goto next point
    
    inline LabelT &Data() { return ordered.Top().Data2(); }
    //: Access label of current closest point. 
    
    inline const LabelT &Data() const { return ordered.Top().Data2(); }
    //: Access label of current closest point. 
    
    inline DataT &RawData() { return ordered.Top(); }
    //: Access label of current closest point. 
    
    inline const VectorC &VectorData() const
    {return ordered.Top().Data1(); }
    //: Access label and coordinates of current closest point.
    // Once this data is returned it cannot be accessed again
  
  protected:
    bool QueueNextData();
    //: Queue up next lot of data.

    inline void AddBin(const VectorC &bin );
  
    VectorIndexC<LabelT> &data;
    VectorC centre;
    RealT maxDist; // Maximum distance we can trust.
    RealT maxSearchDistance;
    IntT dim;
    RealT min[8],max[8];
    IntT square_size;
    PriQueueC<RealT, DataT > ordered;
  };

  ///////////////////////////////////////////////////

  template<class LabelT>
  inline
  VectorIndexIterNC<LabelT>::VectorIndexIterNC(VectorIndexC<LabelT> &thedata,
					       const VectorC& thepoint)
    : data(thedata),
      centre(thepoint),
      maxDist(0),
      dim(thedata.dim),
      square_size(1),
      ordered(128)
  {
    maxSearchDistance = data.maxSearchDistance;
    RavlAssert(dim < 8);
    //cerr << "Centre:" << centre << "\n";
    First();
  }
  

  ///////////////////////////////////////////////////

  template<class LabelT>
  inline 
  void VectorIndexIterNC<LabelT>::AddBin(const VectorC &abin) {
    DListC<DataT> *point_list = data.bins.GetBin(abin);
    ONDEBUG(cerr << "Search " << abin << " Bin=" << ((void *) point_list) << "\n");
    if(point_list == 0)
      return;  
    DLIterC<DataT> point_it(*point_list);
    for(;point_it;point_it++)
      ordered.Insert(data.dist(point_it.Data().Data1(), centre), point_it.Data());
  }
  
  //: Queue up next lot of data.
  
  template<class LabelT>
  inline
  bool VectorIndexIterNC<LabelT>::QueueNextData() {
    ONDEBUG(cerr << "VectorIndexIterNC<LabelT>::QueueNextData(), Called for " << maxDist << "\n");
    RealT hbin_size = data.bins.BinSize()[0]/2;  
    RealT bin_size = data.bins.BinSize()[0];
    for(;maxDist < maxSearchDistance;) {
      
      // Find closest limit.
      RealT closest = maxSearchDistance * 2;
      int dir = 0;
      bool incmax = false;
      for(int d = 0;d < dim;d++) {
	RealT ndist1 = centre[d] - min[d];
	RealT ndist2 = max[d] - centre[d];
	if(ndist2 < ndist1) {
	  if(closest > ndist2) {
	    closest = ndist2;
	    dir = d;
	    incmax = true;
	  }
	} else {
	  if(closest > ndist1) {
	    closest = ndist1;
	    dir = d;
	    incmax = false;
	  }
	}
      }
      ONDEBUG(cerr << "VectorIndexIterNC<LabelT>::QueueNextData(), Direction: " << dir  << " Max:" << ((int) incmax) << " MaxDist :" << maxDist << "\n");
      // Add a plane along that direction.
      RealT addAt;
      if(incmax) {
	max[dir] += data.bins.BinSize()[dir];
	addAt = max[dir] - hbin_size;
      } else {
	min[dir] -= data.bins.BinSize()[dir];
	addAt = min[dir] + hbin_size;
      }
      VectorC ind(dim);    
      int i;
      for(i = 0;i < dim;i++) 
	ind[i] = min[i];
      ind[dir] = addAt;
      for(i = dim-1;i >= 0;) {
	if(i==(dim-1)) {
	  //...Inner;
	  if(i == dir) {
	    AddBin(ind);
	    i--;
	    continue;
	  }
	  // Do the inner loop quickly.
	  for(;ind[i] < max[i];ind[i] += bin_size)
	    AddBin(ind);
	  i--;
	  continue;
	}
	if(i == dir) {
	  i--;
	  continue;
	}
	ind[i] += data.bins.BinSize()[i];
	if(ind[i] > max[i]) {
	  ind[i] = min[i];
	  i--;
	  continue;
	}
	i = dim-1;
      } 
    
      closest = maxSearchDistance * 2;
      for(int d = 0;d < dim;d++) {
	RealT ndist1 = centre[d] - min[d];
	RealT ndist2 = max[d] - centre[d];
	if(ndist2 < closest)
	  closest = ndist2;
	if(ndist1 < closest)
	  closest = ndist1;
      }
      maxDist = closest;
      if(ordered.IsElm())
	if(ordered.TopKey() < maxDist)
	  break; // Got some new valid points.
    }
    ONDEBUG(cerr << "VectorIndexIterNC<LabelT>::QueueNextData(), Max dist now: " << maxDist << "\n");
    return true;
  }

  template<class LabelT>
  inline void VectorIndexIterNC<LabelT>::First()
  {
    // Get the list of the bin in which point falls
  
    VectorC binCent = data.bins.BinCentre(centre);
    RealT hbin_size = data.bins.BinSize()[0]/2;  
    
    // Calculate minimum distance.
    
    VectorC centDist = centre - binCent;
    maxDist = Min(hbin_size - Abs(centDist[0]),hbin_size - Abs(centDist[1]));
    
    AddBin(centre);
    for(int d = 0;d < dim;d++) {
      min[d] = binCent[d] - hbin_size;
      max[d] = binCent[d] + hbin_size;
    }
    
    ONDEBUG(cerr << "VectorIndexIterNC<LabelT>::First(), MaxDist " << maxDist <<" Proj:" << centre << " \n");
    if(ordered.IsElm())
      if(ordered.TopKey() < maxDist)
	return ; // Done.
    QueueNextData();  
  }

  ///////////////////////////////////////////////////

  template<class LabelT>
  inline void VectorIndexIterNC<LabelT>::Next() {
    RavlAssert(ordered.IsElm());
    ordered.DelTop();
    if(ordered.IsElm())
      if(ordered.Top().Data1() < maxDist) 
	return ;
    QueueNextData();
  }

}
#undef ONDEBUG
#undef DODEBUG

#endif
