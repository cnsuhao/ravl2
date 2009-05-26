// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_VECTORINDEX_HEADER
#define RAVL_VECTORINDEX_HEADER 1
/////////////////////////////////////////////////////////////////////////////
//! docentry = "Statistics.Histograms"
//! userlevel = Normal
//! rcsid=     "$Id$"
//! author="Luis Molina Tanco"
//! file="Ravl/Math/Indexing/VectorIndex.hh"
//! lib=RavlMath
//! date=""

#include "Ravl/DList.hh"
#include "Ravl/Vector.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/IndexNd.hh"
#include "Ravl/BinList.hh"
#include "Ravl/PriQueueL.hh"
#include "Ravl/StdConst.hh"

namespace RavlN {

  template<class LabelT> class VectorIndexIterC; // forward declaration
  template<class LabelT> class VectorIndexIterNC; // forward declaration

  //: Class to find the closest point in a bunch of data to a new point provided by the user.
  // Note: The bin size should be equal to or larger than the maximum search distance.
  
  template<class LabelT> 
  class VectorIndexC {
  
  public:

    typedef Tuple2C<VectorC, LabelT> DataC;
    // This class expects the data points to 
    // come in this form.

    inline  VectorIndexC(RealT (*DistanceEvalF)(const VectorC & , const VectorC &),
			 IntT indDim,
			 RealT nBinSize = 1,
			 RealT nMaxSearchDistance = 1)
      : bins(VectorC(indDim)),
	dist(DistanceEvalF),
	binSize(binSize),
	dim(indDim),
	maxSearchDistance(nMaxSearchDistance)
    {
      RavlAssert(nMaxSearchDistance <= nBinSize);
      VectorC binsize(dim);
      binsize.Fill(binSize);
      bins.SetBinSize(binsize);
    }
    //: Constructor
    //!param:DistanceEvalF -  distance metric to use.
    //!param:indDim - Number of dimentions to index.
    //!param:nBinSize - Size of bins.
    //!param:nMaxSearchDistance - Maximum search size to support. This must be smaller or equal to the bin size.
    
    inline  VectorIndexC(const DListC<DataC> & data, 
			 RealT (*DistanceEvalF)(const VectorC & , const VectorC &),
			 IntT indDim,
			 RealT nBinSize = 1,
			 RealT nMaxSearchDistance = -1)
      : bins(VectorC(indDim)),
	dist(DistanceEvalF),
	binSize(nBinSize),
	dim(indDim),
	maxSearchDistance(nMaxSearchDistance)
    { 
      RavlAssert(nMaxSearchDistance <= nBinSize);
      Initialise(data); 
    }
    //: Constructor
    //!param:DistanceEvalF -  distance metric to use.
    //!param:indDim - Number of dimentions to index.
    //!param:nBinSize - Size of bins.
    //!param:nMaxSearchDistance - Maximum search size to support. This must be smaller or equal to the bin size.
    
    inline DataC Closest(const VectorC &point);
    //: Find the closest couple (Vector, Label) to a given point
  
    inline DListC<DataC> NClosest(const VectorC &point, int N);
    //: Find the N closest couple (Vector, Label) to a given point
    
    inline void Insert(const VectorC &point,LabelT &data)
    { bins.Insert(point,Tuple2C<VectorC,LabelT>(point,data)); }
    //: Insert a point into the table.
    
  protected:
  
    void Initialise(const DListC<DataC> &data) {
      VectorC binsize(dim);
      binsize.Fill(binSize);
      bins.SetBinSize(binsize);
      for(DLIterC<DataC> it(data);it;it++)
	bins.Insert(it->Data1(),*it);
    }
    // Fills the bin table with the data provided by the
    // user.
    
    BinListC<VectorC, IndexNdC, DataC> bins;
    // VectorC is the Table index
    // Index2dC is the discrete index of the bin table.
    // Each bin is a list of DataC objects. 

    RealT (*dist)(const VectorC &, const VectorC &);
    
    RealT binSize;
    IntT dim;
    RealT maxSearchDistance;
  
    friend class VectorIndexIterC<LabelT>;
    friend class VectorIndexIterNC<LabelT>;

  private:

    VectorIndexC(const VectorIndexC & oth) {} 
    //: Not allowed to copy until I implement it!
    
    VectorIndexC & operator=(const VectorIndexC & oth) { 
      return *this; }
    //: Not allowed to copy until I implement it!
  };
  
}

#include "Ravl/VectorIndexIter.hh"

namespace RavlN {
  
  // Find the closest couple (Vector, Label) to a given point (VectorC)
  template<class LabelT>
  Tuple2C<VectorC, LabelT> VectorIndexC<LabelT>::Closest(const VectorC &point) {
    VectorIndexIterC<LabelT> it(*this, point);
    if (it) return it.RawData();
    cerr << "WARNING: No point found. \n";
    return DataC();
  }


  // Find the N closest couple (Vector, Label) to a given point (VectorC)
  template<class LabelT>
  DListC<Tuple2C<VectorC, LabelT> > VectorIndexC<LabelT>::NClosest(const VectorC &point, int N) {
    RavlAssert(N>0);
    DListC<DataC> result;
    VectorIndexIterC<LabelT> it(*this, point);
    
    int successfulN = 0;
    if(maxSearchDistance >= 0) {
      for (;it;it++) {
	Tuple2C<VectorC, LabelT> temp(it.VectorData());
	if (dist(temp.Data1(), point) <= maxSearchDistance)  {
	  result.InsLast(temp);
	  if (++successfulN == N) break;
	}
      }
    } else {
      for (;it;it++) {
	Tuple2C<VectorC, LabelT> temp(it.VectorData());
	result.InsLast(temp);
	if (++successfulN == N) 
	  break;
      }
    }
    return result;
  }
}

#endif
