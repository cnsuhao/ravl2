// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLEDGENONMAXSUP_HEADER
#define RAVLEDGENONMAXSUP_HEADER 1
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/IPStream/Edge/NonMaxSupp.hh"
//! lib=RavlImageProc
//! authors="George Matas, Radek Marik and Charles Galambos"
//! date="04/07/2000"
//! docentry="Ravl.Images.Processing.Edges"

#include "Ravl/Image/Image.hh"
#include "Ravl/Tuple3.hh"
#include "Ravl/Image/Edgel.hh"
#include "Ravl/SArray1d.hh"

namespace RavlImageN {

  class EdgeNonMaxSuppressionC;
  
  //! userlevel=Develop
  //: Linear non-maximal suppression.
  
  class EdgeNonMaxSuppressionBodyC 
    : public RCBodyC
  {
  public:
    EdgeNonMaxSuppressionBodyC(bool ec = false)
      : eightConnectivity(ec)
      {}
    
    bool Apply(const ImageC<RealT> & inDrIm, 
	       const ImageC<RealT> & inDcIm,  
	       const ImageC<RealT> & inGrad,
	       ImageC<RealT> & out,
	       RealT &mean,
	       IntT &edgels
	       );
    //: Apply non-maximal suppression to edge images.
    // This produces a new gradient magnitude image.
    
    bool Apply(const ImageC<RealT> & inDrIm, 
	       const ImageC<RealT> & inDcIm,  
	       const ImageC<RealT> & inGrad,
	       SArray1dC<EdgelC> & outEdges,
	       RealT &mean
	       );
    //: Apply non-maximal suppression to edge images.
    // return a list of edgels.
    
  protected:
    void DoNonMaxSupp(ImageC<RealT> &res,
		      RealT &meanRes,
		      IntT &outCount,
		      const ImageC<RealT> & inDrIm, 
		      const ImageC<RealT> & inDcIm,  
		      const ImageC<RealT> & inGrad,
		      IntT startRow,
		      IntT endRow);
    
    bool eightConnectivity;
    friend class EdgeNonMaxSuppressionC;
  };
  
  //! userlevel=Normal
  //: Linear non-maximal suppression.
  
  class EdgeNonMaxSuppressionC 
    : public RCHandleC<EdgeNonMaxSuppressionBodyC>
  {
  public:
    EdgeNonMaxSuppressionC(bool ec = false)
      : RCHandleC<EdgeNonMaxSuppressionBodyC>(*new EdgeNonMaxSuppressionBodyC(ec))
      {}
    
  protected:
    EdgeNonMaxSuppressionC(EdgeNonMaxSuppressionBodyC &bod)
      : RCHandleC<EdgeNonMaxSuppressionBodyC>(bod)
      {}
    //: Body constructor.
    
    EdgeNonMaxSuppressionBodyC &Body()
      { return RCHandleC<EdgeNonMaxSuppressionBodyC>::Body(); }
    //: Access body.
    
    const EdgeNonMaxSuppressionBodyC &Body() const
      { return RCHandleC<EdgeNonMaxSuppressionBodyC>::Body(); }
    //: Access body.
    
    void DoNonMaxSupp(ImageC<RealT> &res,RealT &meanRes,IntT &count,
		      const ImageC<RealT> & inDrIm, 
		      const ImageC<RealT> & inDcIm,  
		      const ImageC<RealT> & inGrad,
		      int &startRow,int &endRow)
      {  Body().DoNonMaxSupp(res,meanRes,count,inDrIm,inDcIm,inGrad,startRow,endRow); }
    //: Do a stripe.


  public:
    
    bool Apply(const ImageC<RealT> & inDrIm, 
	       const ImageC<RealT> & inDcIm,  
	       const ImageC<RealT> & inGrad,
	       ImageC<RealT> & out,
	       RealT &mean,
	       IntT &edgels
	       )
      { return Body().Apply(inDrIm,inDcIm,inGrad,out,mean,edgels); }
    //: Apply non-maximal suppression to edge images.
    // This produces a new gradient magnitude image.
    
    bool Apply(const ImageC<RealT> & inDrIm, 
	       const ImageC<RealT> & inDcIm,  
	       const ImageC<RealT> & inGrad,
	       SArray1dC<EdgelC> & outEdges,
	       RealT &mean
	       )
      { return Body().Apply(inDrIm,inDcIm,inGrad,outEdges,mean); }
    //: Apply non-maximal suppression to edge images.
    // return a list of edgels.

    
    friend class EdgeNonMaxSuppressionBodyC;
  };
}


#endif
