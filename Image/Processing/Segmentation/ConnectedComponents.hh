// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef IPCONNCOMP_HEADER
#define IPCONNCOMP_HEADER 1
////////////////////////////////////////////////////////////////////////////
//! docentry="Image.Image Processing.Operators"
//! rcsid="$Id$"
//! author="Radek Marik, modified by Charles Galambos"
//! lib=RavlImage
//! date="17/10/2000"

#include "Ravl/Types.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/DP/Process.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/RCHash.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/SArr1Iter.hh"
#include "Ravl/Array2dSqr2Iter.hh"
#include "Ravl/Array2dSqr2Iter2.hh"

namespace RavlImageN {
  using namespace RavlN;
  
  class ConnectedComponentsBaseBodyC {
  public:
    ConnectedComponentsBaseBodyC(UIntT nmaxLabel=1000, bool ignore=false)
      : maxLabel(nmaxLabel), 
	ignoreZero(ignore)
    {}
    //: Constructor.
    
    static UIntT RelabelTable(SArray1dC<UIntT> &labelTable, UIntT currentMaxLabel);
    
  protected:
    SizeT maxLabel;
    bool ignoreZero;
  };
  
  
  //: Connected component labeling.
  
  template <class DataTypeT>
  class ConnectedComponentsBodyC
    : public RCBodyC,
      public ConnectedComponentsBaseBodyC
  {
  public:
    ConnectedComponentsBodyC (UIntT nmaxLabel = 10000, bool ignoreZero=false)
      : ConnectedComponentsBaseBodyC(nmaxLabel, ignoreZero)
    {}
    //: Constructor
    // (See handle class ConnectedComponentsC)
    
    virtual Tuple2C<ImageC<UIntT>,UIntT> Apply (const ImageC<DataTypeT> &im);
    //: Performs the connected component labelling
    
  protected:
    
  };
  
  ///////////////////////////////////////////////////
  
  
  // --------------------------------------------------------------------------
  // **********  ConnectedComponentsC  ********************************************
  // --------------------------------------------------------------------------
  
  //! userlevel=Normal
  //: Class for using connected component labelling. 
  
  template <class DataTypeT>
  class ConnectedComponentsC
    : public RCHandleC<ConnectedComponentsBodyC<DataTypeT> >
  {
  public:
    
    ConnectedComponentsC (bool ignoreZero=false)
      : RCHandleC<ConnectedComponentsBodyC<DataTypeT> >(*new ConnectedComponentsBodyC<DataTypeT>(10000, ignoreZero))
    {}
    //: Constructor.  Set ignoreZero if you want to ignore the zeros on the input image
  };
  
  
  /////////////////////////////////////////////////////////////////////////
  // Implementation:
  
  template <class DataTypeT>
  Tuple2C<ImageC<UIntT>,UIntT> ConnectedComponentsBodyC<DataTypeT>::Apply (const ImageC<DataTypeT> &ip) { 
    SizeT jnr;
    SArray1dC<UIntT> labelTable(maxLabel+1);
    // If there are two labels for the same component, the bigger label bin
    // contains the value of the smaller label.
    
    ImageC<UIntT> jp(ip.Rectangle());
    
    // Label the first row.
    labelTable[0] = 0; // usually a special label
    UIntT lab = 1; // the last used label 
    {
      labelTable[lab] = lab; // Setup first label.
      Array2dIter2C<DataTypeT,UIntT> it1(ip,jp);
      if(!it1.IsElm())
	return Tuple2C<ImageC<UIntT>,UIntT>(jp,0); // Zero size image.
      it1.Data2() = lab; // Label first pixel in the image.
      DataTypeT lastValue = it1.Data1();
      for (;it1.RNext();) { // Only iterate through the first row.
	if(it1.Data1() == lastValue) 
	  it1.Data2() = lab;
	else { // a new component
	  lab++;
	  RavlAssert(lab < maxLabel);
	  it1.Data2() = lab;
	  labelTable[lab] = lab;
	}
	lastValue = it1.Data1();
      }
    }
    
    for(Array2dSqr2Iter2C<DataTypeT,UIntT> it(ip,jp);it;) {
      // Label the first column pixel.
      if (it.DataBR1() == it.DataTR1())
	it.DataBR2() = it.DataTR2();
      else {
	++lab;
	RavlAssert(lab < maxLabel);
	it.DataBR2() = lab;
	labelTable[lab] = lab;
      }
      // DataU() = jp[ix-1][iy]
      // DataB() = jp[ix][iy-1]
      
      for(;it.RNext();) { // The rest of the image row.
	if (it.DataBR1() == it.DataTR1()) { 
	  // The upper pixel belongs to the same component.
	  if (!(it.DataBR1() == it.DataBL1())) {
	    // The processed pixel belongs to the upper component.
	    it.DataBR2() = it.DataTR2();
	    continue;
	  }
	  // The left pixel belongs to the same component.
	  // All pixels belong to the old created component.
	  it.DataBR2() = it.DataBL2(); 
	  UIntT upperRoot = labelTable[it.DataTR2()];
	  UIntT leftRoot = labelTable[it.DataBL2()];
	  if (upperRoot == leftRoot) {
	    // The processed pixel belongs to the upper component.
	    continue; // Same label, just get on with it.
	  }
	  
	  // There are two root labels for the same component.
	  // Find the root labels.
	  for (; upperRoot != labelTable[upperRoot];
	       upperRoot  = labelTable[upperRoot])
	    ;
	  for (; leftRoot != labelTable[leftRoot];
	       leftRoot  = labelTable[leftRoot])
	    ;
	  
	  // Join both tree of labels.
	  UIntT newRoot = (upperRoot >= leftRoot) ? leftRoot : upperRoot;
	  labelTable[upperRoot] = newRoot;
	  labelTable[leftRoot]  = newRoot;
	  
	  // Relabel both branches in the trees.
	  UIntT il = it.DataTR2();
	  for (UIntT hl = labelTable[il];
	       il != newRoot;
	       hl = labelTable[il = hl])
	  labelTable[il] = newRoot;
	  il = it.DataBL2();
	  for (UIntT hhl = labelTable[il];
	       il != newRoot;
	       hhl = labelTable[il = hhl])
	    labelTable[il] = newRoot;
	  // DataU() = jp[ix-1][iy]
	// DataB() = jp[ix][iy-1]
	  continue;
	}
	// The upper pixel belongs to the different component.
	if (it.DataBR1() == it.DataBL1()) { // The left pixel belongs to the same component.
	  // The processed pixel belongs to the left component.
	  it.DataBR2() = it.DataBL2(); 
	  continue;
	}
	// The left pixel belongs to the different component.
	// The processed pixel belongs to the new component.
	lab++;
	it.DataBR2() = lab; 
	labelTable[lab] = lab;
	// +2 according to the first column pixel
	if (lab + 2 > maxLabel)  { // Try condensate the 'labelTable'.
	  UIntT newLastLabel = RelabelTable(labelTable,lab);
	  
	  // Change labels in the processed part of the image.
	  ImageRectangleC subRect(jp.Rectangle());
	  IndexC ix = it.Row();
	  subRect.BRow() = ix - 1;
	  for(Array2dIterC<UIntT> its(jp,subRect);its;its++)
	    *its = labelTable[*its];
	  
	  IndexC iy = it.Col();
	  
	  // Change labels in the processed part of the row.
	  for (IndexC jy = ip.Rectangle().Origin().Col(); jy <= iy; ++jy)
	    jp[ix][jy] = labelTable[jp[ix][jy]];
	  
	  // Create the correct label scheme.
	  if (((float) newLastLabel * 1.5) > maxLabel) { 
	    //cerr << "Resizing label table. Max:" << maxLabel << "\n";
	    // The size of the 'labelTable' is too small.
	    maxLabel *= 2; // Double the size of the table.
	    labelTable = SArray1dC<UIntT>(maxLabel+1);
	    labelTable.Fill(((UIntT) -1)); // Debug measure...
	  }
	  // Create an identity label set.
	  UIntT ll = 0;
	  for(SArray1dIterC<UIntT> it(labelTable,newLastLabel+1);it;it++,ll++)
	    *it = ll;
	  lab = newLastLabel;
	}
      }
    }
    
    // relabel the whole image
    if (lab == 0) 
    return Tuple2C<ImageC<UIntT>,UIntT>(jp,lab);
    
    UIntT newLastLabel = RelabelTable(labelTable,lab);
    // change labels in the have been processed area
    for(Array2dIterC<UIntT> it(jp);it;it++) 
      *it = labelTable[*it];  
    jnr = newLastLabel+1;
    
    
    //: The user may of requested to ignore the empty pixels (eg. zeros) in the original image
    if(ignoreZero) {
      SArray1dC<IntT>arr(lab+2);
      arr.Fill(-1);
      DataTypeT zero = 0;
      UIntT curr=1;
      for(Array2dIter2C<DataTypeT, UIntT> it(ip, jp);it;it++) {
	if(it.Data1()==zero) it.Data2() = 0;
	else {
	  if(arr[it.Data2()]==-1) {
	    arr[it.Data2()] = curr;
	    curr++;
	  }
	  it.Data2() = arr[it.Data2()];
	}
      }
      lab=curr;
    }
    
    return Tuple2C<ImageC<UIntT>,UIntT>(jp,lab);
  }

}
#endif
