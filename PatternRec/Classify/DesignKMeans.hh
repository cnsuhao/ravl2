// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNKMEANS_HEADER
#define RAVL_DESIGNKMEANS_HEADER 1
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.Pattern Recognition.Cluster"
//! example=exKMeansCluster.cc

#include "Ravl/PatternRec/DesignClassifierUnsupervised.hh"
#include "Ravl/PatternRec/DistanceSqrEuclidean.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Design a k means classifer.
  
  class DesignKMeansBodyC
    : public DesignClassifierUnsupervisedBodyC
  {
  public:
    DesignKMeansBodyC(UIntT nk,const DistanceC &distanceMetric = DistanceSqrEuclideanC())
      : distance(distanceMetric),
	k(nk)
    {}
    //: Constructor.
    
    DesignKMeansBodyC(istream &strm);
    //: Load from stream.
    
    DesignKMeansBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor

    virtual FunctionC Apply(const SampleC<VectorC> &in);
    //: Create a clasifier.
    
    UIntT K() const
    { return k; }
    //: Access number of clusters.
    
  protected:
    DistanceC distance;
    UIntT k;
  };

  //! userlevel=Normal
  //: Design a k means classifer.
  
  class DesignKMeansC 
    : public  DesignClassifierUnsupervisedC
  {
  public:
    DesignKMeansC()
    {}
    //: Default constructor.
    // Creates an invalid constructor.
    
    DesignKMeansC(UIntT k,const DistanceC &distanceMetric = DistanceSqrEuclideanC())
      : DesignClassifierUnsupervisedC(*new DesignKMeansBodyC(k,distanceMetric))
    {}
    //: Default constructor.
    // Creates an invalid constructor.
    
    DesignKMeansC(istream &strm);
    //: Load from stream.
    
    DesignKMeansC(BinIStreamC &strm);
    //: Load from binary stream.
    
  protected:
    DesignKMeansC(DesignKMeansBodyC &bod)
      : DesignClassifierUnsupervisedC(bod)
    {}
    //: Body constructor.

    DesignKMeansC(DesignKMeansBodyC *bod)
      : DesignClassifierUnsupervisedC(bod)
    {}
    //: Body ptr constructor.
    
    DesignKMeansBodyC &Body()
    { return static_cast<DesignKMeansBodyC &>(DesignClassifierUnsupervisedC::Body()); }
    //: Access body.

    const DesignKMeansBodyC &Body() const
    { return static_cast<const DesignKMeansBodyC &>(DesignClassifierUnsupervisedC::Body()); }
    //: Access body.
    
  public:
    UIntT K() const
    { return Body().K(); }
    //: Access number of clusters.
    
  };
  
  inline istream &operator>>(istream &strm,DesignKMeansC &obj) {
    obj = DesignKMeansC(strm);
    return strm;
  }
  //: Load from a stream.
  // Uses virtual constructor.
  
  inline ostream &operator<<(ostream &out,const DesignKMeansC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
  inline BinIStreamC &operator>>(BinIStreamC &strm,DesignKMeansC &obj) {
    obj = DesignKMeansC(strm);
    return strm;
  }
  //: Load from a binary stream.
  // Uses virtual constructor.
  
  inline BinOStreamC &operator<<(BinOStreamC &out,const DesignKMeansC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.

}


#endif
