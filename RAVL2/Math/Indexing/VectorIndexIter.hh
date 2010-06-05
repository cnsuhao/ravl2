// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_VECTORINDEXITER_HEADER
#define RAVL_VECTORINDEXITER_HEADER 1
///////////////////////////////////////////////
//! rcsid="$Id: VectorIndexIter.hh 4130 2004-03-20 15:08:03Z craftit $"
//! author="Luis Molina Tanco and Charles Galambos"
//! file="Ravl/Math/Indexing/VectorIndexIter.hh"
//! lib=RavlMath
//! userlevel=Normal
//! docentry="Ravl.Math.Vector Index"

#include "Ravl/VectorIndex.hh"
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
  //: Iterate through points in a VectorIndex in order of distance from a point
  
  template<class LabelT> 
  class VectorIndexIterC {
  public:
    typedef Tuple2C<VectorC, LabelT> DataT;

    inline VectorIndexIterC(VectorIndexC<LabelT> & thedata,
			    const VectorC & thepoint,int nPnts = 1);
    //: Constructor.
    
    inline void First();
    //: Get ready to return closest point.

    inline bool IsElm() const 
    { return (unsigned int) rat < results.Size(); }
    //: Any points yet to be returned?
  
    operator bool() const
    { return (unsigned int) rat < results.Size(); }
    //: At a valid point ?
    
    inline void Next();
    //: goto next point.
  
    void operator++(int)
    { Next(); }
    //: Goto next point
    
    inline const LabelT &Data() const
    { return results[rat].Data2().Data2(); }
    //: Access label of current closest point. 
  
    inline const LabelT &operator*() const
    { return Data(); }
    //: Access data

    inline LabelT &Data()
    { return results[rat].Data2().Data2(); }
    //: Access label of current closest point. 
    
    inline const LabelT &operator*()
    { return Data(); }
    //: Access data
    
    inline DataT &RawData() 
    { return results[rat].Data2(); }
    //: Access current closest point. 
    
    inline VectorC VectorData() 
    { return results[rat].Data2().Data1(); }
    //: Access label and coordinates of current closest point.
  
  protected:
    bool QueueNextData();
    //: Queue up next lot of data.
  
    void Bubble(RealT dist,const DataT &dat);
    //: Bubble.
    
    inline void AddBin(const VectorC &bin );
    //: Add bin to list.
    
    VectorIndexC<LabelT> &data;
    VectorC centre;
    VectorC projCentre;
    RealT maxDist; // Maximum distance we can trust.
    RealT maxSearchDistance;
    IntT dim;
    RealT min[8],max[8];
    IntT square_size;
    int at, rat;
    SArray1dC<Tuple2C<RealT,DataT> > results;
  };

  ///////////////////////////////////////////////////

  template<class LabelT>
  inline
  VectorIndexIterC<LabelT>::VectorIndexIterC(VectorIndexC<LabelT> &thedata,
					     const VectorC& thepoint,int nPnts)
    : data(thedata),
      centre(thepoint),
      maxDist(0),
      dim(thedata.dim),
      square_size(1),
      at(0),
      rat(0),
      results(nPnts)
  {
    projCentre = centre;
    maxSearchDistance = data.maxSearchDistance;// + data.dist(data.reducer.GetMean (),centre);
    //cerr << "Projected Centre:" << projCentre << " Centre:" << centre << "\n";
    First();
  }
  
  ///////////////////////////////////////////////////
  
  template<class LabelT>
  inline
  void VectorIndexIterC<LabelT>::Bubble(RealT dist,const DataT &dat) {
    if(at == 1) {
      results[0] = Tuple2C<RealT,DataT>(dist,dat);
      return ;
    }
    int i;    
    for(i = at-1;i > 0;i--) {
      if(results[i].Data1() < dist)
	break;
      results[i] = results[i-1];
    }
    i++;
    results[i] = Tuple2C<RealT,DataT>(dist,dat);
  }

  template<class LabelT>
  void VectorIndexIterC<LabelT>::AddBin(const VectorC &abin) {
    DListC<DataT> *point_list = data.bins.GetBin(abin);
    ONDEBUG(cerr << "Search " << abin << " " << ((void *) point_list)<< "\n");
    if(point_list == 0)
      return;  
    
    DLIterC<DataT> point_it(*point_list);
    RealT dist;
    if(results.Size() > 1) {
      // Sort out first points.
      for(;at < ((IntT) results.Size()) && point_it.IsElm();point_it.Next()) {
	dist = data.dist(point_it.Data().Data1(), centre);
	if(at == 0) {
	  results[at++] = Tuple2C<RealT,DataT>(dist,point_it.Data());
	  point_it++;
	  if(!point_it)
	    return ;
	  dist = data.dist(point_it.Data().Data1(), centre);
	}
	results[at].Data1() = dist+1;
	at++;
	Bubble(dist,point_it.Data());
      }
      RealT largestDist = results[results.Size()-1].Data1();
      for(;point_it;point_it++) {
	dist = data.dist(point_it.Data().Data1(), centre);
	if(dist > largestDist)
	  continue;
	Bubble(dist,point_it.Data());
	largestDist = dist;
      }
    } else {
      if(at == 0) {
	if(!point_it.IsElm())
	  return ;
	dist = data.dist(point_it.Data().Data1(), centre);
	results[0] = Tuple2C<RealT,DataT>(dist,point_it.Data());
	at++;
	point_it++;
      }
      RealT largestDist = results[0].Data1();
      for(;point_it;point_it++) {
	dist = data.dist(point_it.Data().Data1(), centre);
	if(dist > largestDist)
	  continue;
	results[0] = Tuple2C<RealT,DataT>(dist,point_it.Data());
	largestDist = dist;
      }
    }
  }

  //: Queue up next lot of data.

  template<class LabelT>
  inline
  bool VectorIndexIterC<LabelT>::QueueNextData() {
    ONDEBUG(cerr << "VectorIndexIterC<LabelT>::QueueNextData(), Called for " << maxDist << "\n");
    const RealT bin_size = data.bins.BinSize()[0];
    const RealT hbin_size = bin_size/2;  
    for(;maxDist < maxSearchDistance;) {
      
      // Find closest limit.
      RealT closest = maxSearchDistance * 2;
      int dir = 0;
      bool incmax = false;
      for(int d = 0;d < dim;d++) {
	RealT ndist1 = projCentre[d] - min[d];
	RealT ndist2 = max[d] - projCentre[d];
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
      ONDEBUG(cerr << "VectorIndexIterC<LabelT>::QueueNextData(), Direction: " << dir  << " Max:" << ((int) incmax) << " MaxDist :" << maxDist << "\n");
      // Add a plane along that direction.
      VectorC ind(dim);    
      int i;
      for(i = 0;i < dim;i++) 
	ind[i] = min[i];
      if(incmax) {
	max[dir] += bin_size; //data.bins.BinSize()[dir]
	ind[dir] = max[dir] - hbin_size;
      } else {
	min[dir] -= bin_size; // data.bins.BinSize()[dir]
	ind[dir] = min[dir] + hbin_size;
      }
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
	ind[i] += bin_size; // data.bins.BinSize()[i];
	if(ind[i] > max[i]) {
	  ind[i] = min[i];
	  i--;
	  continue;
	}
	i = dim-1;
      } 
    
      closest = maxSearchDistance * 2;
      for(int d = 0;d < dim;d++) {
	RealT ndist1 = projCentre[d] - min[d];
	RealT ndist2 = max[d] - projCentre[d];
	if(ndist2 < closest)
	  closest = ndist2;
	if(ndist1 < closest)
	  closest = ndist1;
      }
      maxDist = closest;
      if(at > rat) {
	if(results[rat].Data1() < maxDist)
	  break; // Got some new valid point(s).
      }
    }
    ONDEBUG(cerr << "VectorIndexIterC<LabelT>::QueueNextData(), Max dist now: " << maxDist << "\n");
    return true;
  }
  
  template<class LabelT>
  inline void VectorIndexIterC<LabelT>::First()
  {
    rat = 0;
    at = 0;
    // Get the list of the bin in which point falls
  
    VectorC binCent = data.bins.BinCentre(projCentre);
    RealT hbin_size = data.bins.BinSize()[0]/2;
    
    // Calculate minimum distance.
    // This assumes a homogenous transform.
    VectorC centDist = projCentre - binCent;
    maxDist = Min(hbin_size - Abs(centDist[0]),hbin_size - Abs(centDist[1]));
  
    AddBin(projCentre);
    for(int d = 0;d < dim;d++) {
      min[d] = binCent[d] - hbin_size;
      max[d] = binCent[d] + hbin_size;
    }
    
    ONDEBUG(cerr << "VectorIndexIterC<LabelT>::First(), MaxDist " << maxDist << " Proj:" << projCentre << " Results=" << results.Size() << " at=" << at << " rat=" << rat << "\n");
    if(at > 0) {
      if(results[0].Data1() < maxDist)
	return ;
    }
    QueueNextData();  
  }

  ///////////////////////////////////////////////////

  template<class LabelT>
  inline void VectorIndexIterC<LabelT>::Next() {
    rat++;
    if(rat < at) {
      if(results[rat].Data1() < maxDist)
	return ;
    }
    if(rat >= results.Size())
      return ;
    QueueNextData();
  }
}
#undef ONDEBUG
#undef DODEBUG

#endif
