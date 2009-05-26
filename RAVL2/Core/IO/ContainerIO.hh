// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_CONTAINERIO_HEADER
#define RAVL_CONTAINERIO_HEADER 1
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlIO
//! author="Charles Galambos"
//! date="07/07/1998"
//! docentry="Ravl.API.Core.Data Processing.IO"
//! file="Ravl/Core/IO/ContainerIO.hh"

#include "Ravl/DP/Port.hh"
#include "Ravl/DList.hh"
#include "Ravl/DLIter.hh"

namespace RavlN {
  //////////////////////////////
  //! userlevel=Develop
  //: Input list body.
  
  template<class ContainerT>
  class DPIContainerBodyC 
    : public DPIPortBodyC<typename ContainerT::ElementT> 
  {
  public:
    DPIContainerBodyC(const ContainerT &dat);
    //: Constructor.
    
    virtual bool IsGetReady() const
    { return iter; }
    //: Is some data ready ?
    
    virtual bool IsGetEOS() const
    { return iter; }
    //: Has the End Of Stream been reached ?
    // true = yes.
    
    virtual typename ContainerT::ElementT Get();
    //: Get next piece of data.
    
    virtual IntT GetArray(SArray1dC<typename ContainerT::ElementT> &data);
    //: Get an array of data from stream.
    // returns the number of elements processed.
    
    virtual bool Get(typename ContainerT::ElementT &buff);
    //: Try and get next piece of data.
    
  protected:
    ContainerT container;
    typename ContainerT::IteratorT iter;
  };
  
  ///////////////////////////////////////////////////////////////////////////////
  //! userlevel=Develop
  //: Output list body.
  // Append useing the '+=' operator.
  
  template<class ContainerT>
  class DPOContainerBodyC 
    : public DPOPortBodyC<typename ContainerT::ElementT> 
  {
  public:
    DPOContainerBodyC(ContainerT &dat);
    //: Default constructor.
    
    virtual bool Put(const typename ContainerT::ElementT &);
    //: Put data.
    
    virtual IntT PutArray(const SArray1dC<typename ContainerT::ElementT> &data);
    //: Put data into container.
    
    ContainerT &Container() { return container; }
    //: Access list.
    
  protected:
    ContainerT container;
  };
  
  ///////////////////////////////////////////////////////////////////////////////
  //! userlevel=Develop
  //: Output list body.
  // Append useing the '+=' operator.
  
  template<class ContainerT>
  class DPOContainerOverwriteBodyC 
    : public DPOPortBodyC<typename ContainerT::ElementT> 
  {
  public:
    DPOContainerOverwriteBodyC(ContainerT &dat);
    //: Default constructor.
    
    virtual bool Put(const typename ContainerT::ElementT &);
    //: Put data.
    
    virtual IntT PutArray(const SArray1dC<typename ContainerT::ElementT> &data);
    //: Put data into container.
    
    ContainerT &Container() { return container; }
    //: Access list.
    
    virtual bool IsPutReady() const
    { return iter; }
    //: Is port ready for data ?
    
  protected:
    ContainerT container;
    typename ContainerT::IteratorT iter;
  };
  
  /////////////////////////////////
  //! userlevel=Normal
  //: Input from list.
  
  template<class ContainerT>
  class DPIContainerC 
    : public DPIPortC<typename ContainerT::ElementT> 
  {
  public:
    DPIContainerC(const ContainerT &dat)
      : DPEntityC(*new DPIContainerBodyC<ContainerT>(dat))
    {}
    //: Constructor.
  };
  
  ////////////////////////////////////
  //! userlevel=Normal
  //: Output to a container.
  // This class with use the '+=' operator to append items to the
  // container. <p>
  // The container must define 'ElementT'
  
  template<class ContainerT>
  class DPOContainerC 
    : public DPOPortC<typename ContainerT::ElementT> 
  {
  public:
    DPOContainerC(ContainerT &dat)
      : DPEntityC(*new DPOContainerBodyC<ContainerT>(dat))
    {}
    //: Constructor.
    
  inline ContainerT &Container() 
    { return dynamic_cast<DPOContainerBodyC<ContainerT> &>(DPEntityC::Body()).Container(); }
    //: Access list.
  };
  
  ////////////////////////////////////
  //! userlevel=Normal
  //: Output to a container.
  // This class with use the '+=' operator to append items to the
  // container. <p>
  // The container must define 'ElementT'
  
  template<class ContainerT>
  class DPOContainerOverwriteC : public DPOPortC<typename ContainerT::ElementT> {
  public:
    DPOContainerOverwriteC(ContainerT &dat)
      : DPEntityC(*new DPOContainerOverwriteBodyC<ContainerT>(dat))
    {}
    //: Constructor.
    
    inline ContainerT &Container() 
    { return dynamic_cast<DPOContainerBodyC<ContainerT> &>(DPEntityC::Body()).Container(); }
    //: Access list.
  };
  
  ////////////////////////////////////////
  //: Some helper functions.
  
  template<class ContainerT>
  DPOPortC<typename ContainerT::ElementT> DPOContainer(ContainerT &dat)
  { return DPOContainerC<ContainerT>(dat); }
  
  //: Write out stream to container, appending to contents.
  
  template<class ContainerT>
  DPOPortC<typename ContainerT::ElementT> DPOContainerOverwrite(ContainerT &dat)
  { return DPOContainerOverwriteC<ContainerT>(dat); }
  
  //: Write out stream to container, overwriting existing contents.
  
  template<class ContainerT>
  DPIPortC<typename ContainerT::ElementT> DPIContainer(const ContainerT &dat)
  { return DPIContainerC<ContainerT>(dat); }
  
  //: Use container as source for stream.
  
  template<class DataT>
  DPOContainerC<DListC<DataT> > DPOList(DListC<DataT> &dat)
  { return DPOContainerC<DListC<DataT> >(dat); }
  
  template<class DataT>
  DPIContainerC<DListC<DataT> > DPIList(const DListC<DataT> &dat)
  { return DPIContainerC<DListC<DataT> >(dat); }
  
  ////////////////////////////////////////////////////////
  
  template<class ContainerT>
  DPIContainerBodyC<ContainerT>::DPIContainerBodyC(const ContainerT &dat)
    : container(dat),
      iter(const_cast<ContainerT &>(dat))
  {}

  template<class ContainerT>
  typename ContainerT::ElementT DPIContainerBodyC<ContainerT>::Get() {
    const typename ContainerT::ElementT &dat = iter.Data();
    iter++;
    return dat;
  }
  
  template<class ContainerT>
  bool DPIContainerBodyC<ContainerT>::Get(typename ContainerT::ElementT &buff) {
    if(!iter)
      return false;
    buff = *iter;
    iter++;
    return true;
  }
  
  template<class ContainerT>
  IntT DPIContainerBodyC<ContainerT>::GetArray(SArray1dC<typename ContainerT::ElementT> &data) {
    for(SArray1dIterC<typename ContainerT::ElementT> it(data);it;it++) {
      if(!iter)
	return it.Index().V();
      *it = *iter;
      iter++;
    }
    return data.Size();
  }

  /////////////////////////////////////////
  
  template<class ContainerT>
  DPOContainerBodyC<ContainerT>::DPOContainerBodyC(ContainerT &dat) 
    : container(dat)
  {}
  
  template<class ContainerT>
  bool DPOContainerBodyC<ContainerT>::Put(const typename ContainerT::ElementT &dat) {
    container += dat; 
    return true;
  }
  
  template<class ContainerT>
  IntT DPOContainerBodyC<ContainerT>::PutArray(const SArray1dC<typename ContainerT::ElementT> &data) {
    for(SArray1dIterC<typename ContainerT::ElementT> it(data);it;it++)
      container += *it;
    return data.Size();
  }
  
  /////////////////////////////////////////
  
  template<class ContainerT>
  DPOContainerOverwriteBodyC<ContainerT>::DPOContainerOverwriteBodyC(ContainerT &dat) 
    : container(dat),
      iter(dat)
  {}
  
  template<class ContainerT>
  bool DPOContainerOverwriteBodyC<ContainerT>::Put(const typename ContainerT::ElementT &dat) {
    if(!iter)
      return false;
    *iter = dat; 
    iter++;
    return true;
  }
  
  template<class ContainerT>
  IntT DPOContainerOverwriteBodyC<ContainerT>::PutArray(const SArray1dC<typename ContainerT::ElementT> &data) {
    for(SArray1dIterC<typename ContainerT::ElementT> it(data);it;it++) {
      if(!iter)
	return it.Index().V();
      *iter = *it; 
      iter++;
    }
    return data.Size();
  }
}

#endif
