// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_EDGEDERICHE_HEADER
#define RAVLIMAGE_EDGEDERICHE_HEADER 1
///////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Processing/Edges/EdgeDeriche.hh"
//! authors="George Matas, Radek Marik and Charles Galambos"
//! docentry="Ravl.Images.Edges"
//! lib=RavlImageProc

#include "Ravl/Image/Image.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/Tuple2.hh"

namespace RavlImageN {
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using namespace RavlN;
  using RavlN::RCBodyC;
  using RavlN::RCHandleC;
#endif
  
  class EdgeDericheC;

  //! userlevel=Develop
  //: Deriche edge filter.
  
  class EdgeDericheBodyC  
    : public RCBodyC
  {
  public:
    EdgeDericheBodyC(RealT omega,RealT alpha);
    //: Constructor.
    
    bool Apply(const ImageC<RealT> &inImg,ImageC<RealT> &outDx,ImageC<RealT> &outDy);
    //: Apply operator.

    bool Apply(const ImageC<RealT> &inImg,ImageC<TFVectorC<RealT,2> > &out);
    //: Apply sobol operator to 'img', put result in 'out'
    // This is a little slower than the Apply(inImg,outDx,outDy) for the moment,
    // this will be fixed eventually.

    ImageC<RealT> EdgeMagnitude(const ImageC<RealT> &inImg);
    //: Calculate the edge magnitude only
    
  protected:
    RealT omega,alpha; // User paramiters.
    
    bool Init();
    //: Compute filter paramiters.
    
    bool YDer(ImageC<RealT> &im,ImageC<RealT> &derv);
  
    bool YDer1p(ImageC<RealT> &im,ImageC<RealT> &a2);
    bool YDer1n(ImageC<RealT> &im,ImageC<RealT> &a3);
    bool YDer2p(ImageC<RealT> &im,ImageC<RealT> &a2,ImageC<RealT> &a3);
    bool YDer2n(ImageC<RealT> &im,ImageC<RealT> &a2,ImageC<RealT> &a4);
    
    bool XDer(ImageC<RealT> &im,ImageC<RealT> &derv);
    
    bool XDer1p(ImageC<RealT> &im,ImageC<RealT> &a2);
    bool XDer1n(ImageC<RealT> &im,ImageC<RealT> &a3);
    bool XDer2p(ImageC<RealT> &im,ImageC<RealT> &a2,ImageC<RealT> &a3);
    bool XDer2n(ImageC<RealT> &im,ImageC<RealT> &a2,ImageC<RealT> &a4);
    
    // Paramiters.
    RealT cst,cst0,cst1,cst2;
    RealT ad1,ad2,an1,an2,an3,an4,an11;
    
    friend class EdgeDericheC;  
  };
  
  
  //! userlevel=Normal
  //: Deriche edge filter.
  
  class EdgeDericheC 
    : public RCHandleC<EdgeDericheBodyC>
  { 
  public:
    EdgeDericheC(RealT omega = 0.001 ,RealT alpha = 2.0)
      : RCHandleC<EdgeDericheBodyC>(*new EdgeDericheBodyC(omega,alpha))
    {}
    //: Constructor.
    
  protected:
    EdgeDericheC(EdgeDericheBodyC &bod)
      : RCHandleC<EdgeDericheBodyC>(bod)
    {}
    //: Body constructor.
    
    EdgeDericheBodyC &Body()
    { return static_cast<EdgeDericheBodyC &>(RCHandleC<EdgeDericheBodyC>::Body()); }
    //: Access body.
    
    const EdgeDericheBodyC &Body() const
    { return static_cast<const EdgeDericheBodyC &>(RCHandleC<EdgeDericheBodyC>::Body()); }
    //: Access body.


  public:
    
    bool Apply(const ImageC<RealT> &inImg,ImageC<RealT> &dx,ImageC<RealT> &dy) 
    { return Body().Apply(inImg,dx,dy); }
    //: Apply Deriche operator to 'img' put the results into dx and dy.
    
    bool Apply(const ImageC<RealT> &inImg,ImageC<TFVectorC<RealT,2> > &out)
    { return Body().Apply(inImg,out); }
    //: Apply sobol operator to 'img', put result in 'out'
    // This is a little slower than the Apply(inImg,outDx,outDy) for the moment,
    // this will be fixed eventually.
    
    ImageC<RealT> EdgeMagnitude(const ImageC<RealT> &inImg)
    { return Body().EdgeMagnitude(inImg); }
    //: Calculate the edge magnitude only
    
  protected:
    
    bool YDer1p(ImageC<RealT> &im,ImageC<RealT> &a2)
    { return Body().YDer1p(im,a2); }
    
    bool YDer1n(ImageC<RealT> &im,ImageC<RealT> &a3)
    { return Body().YDer1n(im,a3); }
    
    bool YDer2p(ImageC<RealT> &im,ImageC<RealT> &a2,ImageC<RealT> &a3)
    { return Body().YDer2p(im,a2,a3); }
    
    bool YDer2n(ImageC<RealT> &im,ImageC<RealT> &a2,ImageC<RealT> &a4)
    { return Body().YDer2n(im,a2,a4); }
    
    bool XDer1p(ImageC<RealT> &im,ImageC<RealT> &a2)
    { return Body().XDer1p(im,a2); }
    
    bool XDer1n(ImageC<RealT> &im,ImageC<RealT> &a3) 
    { return Body().XDer1n(im,a3); }
    
    bool XDer2p(ImageC<RealT> &im,ImageC<RealT> &a2,ImageC<RealT> &a3)
    { return Body().XDer2p(im,a2,a3); }
    
    bool XDer2n(ImageC<RealT> &im,ImageC<RealT> &a2,ImageC<RealT> &a4)
    { return Body().XDer2n(im,a2,a4); }

    bool YDer(ImageC<RealT> &im,ImageC<RealT> &derv)
    { return Body().YDer(im,derv); }
    
    bool XDer(ImageC<RealT> &im,ImageC<RealT> &derv)
    { return Body().XDer(im,derv); }  
    
    friend class EdgeDericheBodyC;
  };

}

#endif
