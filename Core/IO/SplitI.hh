// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DPSPLITI_HEADER
#define RAVL_DPSPLITI_HEADER 1
/////////////////////////////////////////////////
//! docentry="Ravl.Core.Data Processing.Split"
//! lib=RavlIO
//! example=exDPSplit.cc
//! rcsid="$Id$"
//! file="Ravl/Core/IO/SplitO.hh"
//! author="Charles Galambos"
//! date="21/07/98"

#include "Ravl/DP/Port.hh" 
#include "Ravl/BlkQueue.hh" 
#include "Ravl/DList.hh" 
#include "Ravl/DLIter.hh" 
#include "Ravl/BlkQueue.hh"
#include "Ravl/Threads/Mutex.hh"

namespace RavlN { 

  //: some foward  delarations 

  template<class DataT> class DPSplitIPortBodyC;
  template<class DataT> class DPSplitIBodyC;
  template <class DataT> class DPSplitIC;  
  template<class DataT> class DPSplitIPortC;
  
  //template <class DataT> class DP ; 



////////////////////////////////////////////////////////////////////////////////////////////
//! userlevel=Develop
//: Split body.
// See DPSplitIC for details.
template<class DataT>
class DPSplitIBodyC : public DPEntityBodyC {
public:
  DPSplitIBodyC(const DPIPortC<DataT> &src);
  //: Constructor.

  ~DPSplitIBodyC();
  //: Destructor.
  
  DPSplitIPortC<DataT> NewPort();
  //: Make a new port.
  
  bool GetNext();
  //: Get next piece of data from source.
  
  bool IsGetNextReady() const;
  //: Get next ready ?
  
protected:
  bool Remove(DPSplitIPortC<DataT> &oth);
  //: Remove output port.
  
  DPIPortC<DataT> source;
  DListC<DPSplitIPortC<DataT> > ports; // List of ports.
  MutexC access; // Control access to SplitI.
  
  friend class DPSplitIC<DataT>;
};





/////////////////////////////////////////////////////////////////////////////////////////////
//! userlevel=Develop
//: SplitI port body.
// See DPSplitIPortC for details.

template<class DataT>
class DPSplitIPortBodyC : public DPIPortBodyC<DataT> {
public:
  DPSplitIPortBodyC();
  //: Default constructor.
  
  ~DPSplitIPortBodyC();
  //: Destructor.
  
  bool Disconnect();
  //: Disconnect from Split body.
  
  virtual bool IsGetReady() const;
  //: Ready to get more data ?
  
  virtual DataT Get();
  //: Get next piece of data.
  // May block if not ready, or it will return a constructed
  // with the default constructor.
  
  virtual bool Get(DataT &buff);
  //: Try and get next piece of data.
  // This may not NOT block, if no data is ready
  // it will return FALSE, and not set buff.
  
  virtual IntT GetArray(SArray1dC<DataT> &data);
  //: Get an array of data from stream.
  // returns the number of elements unsuccesfully processed.
  // i.e. if array is filled, the result will be 0.
  
protected:
  DPSplitIPortBodyC(DPSplitIC<DataT> &src);
  //: Constructor.
  
  bool Put(const DataT &dat);
  //: Put next piece of data.
  
private:  
  DPSplitIC<DataT> source;
  BlkQueueC <DataT> q;
  MutexC q_access;
  friend class DPSplitIBodyC<DataT>;
  friend class DPSplitIPortC<DataT>;
};






/////////////////////////////////////////////////////////////////////////////////////////////////////////
//! userlevel=Normal
//: SplitI input handle
// This is a split input handle it contains a handle
// the the actual input, and list of clients using it
// every time a client empties its input queue and requires
// more data it is retrieved from the input stream and 
// placed in all the clients input streams.

template<class DataT>
class DPSplitIC : public DPEntityC {
public:
  DPSplitIC(const DPIPortC<DataT> &src);
  //: Create new split.
  
  DPSplitIC(const DPSplitIC<DataT> &oth);
  //: Copy constructor.
  
  DPSplitIC();
  //: Default constructor.
  
  DPSplitIPortC<DataT> NewPort();
  //: Make a new port.
  
  operator DPIPortC<DataT> ()
  { return NewPort(); }
  
  bool GetNext();
  //: Get next.
  
  bool IsGetNextReady() const;
  //: Get next ready ?
  
protected:
  DPSplitIC(DPSplitIBodyC<DataT> &oth);
  //: Constructor.
  
  DPSplitIBodyC<DataT> &Body();
  //: Access body.
  
  const DPSplitIBodyC<DataT> &Body() const;
  //: Access body.

  bool Remove(DPSplitIPortC<DataT> &oth);
  //: Remove output port.
    
  friend class DPSplitIBodyC<DataT>;
  friend class DPSplitIPortBodyC<DataT>;
};





/////////////////////////////////////////////////////////////////////////////////////////////////////
//! userlevel=Normal
//: SplitI  output handle.
// This is a single port from which client can use Get(),
// as normal.  If there is no data in the local queue,
// a new item is retrieved from the input, and places in
// the other clients listening queue.

template<class DataT>
class DPSplitIPortC : public DPIPortC<DataT> {
public:
  DPSplitIPortC() {}
  //: Default constructor.
  
  bool Disconnect();
  //: Disconnect from Split body.
  
protected:
  DPSplitIPortC(DPSplitIC<DataT> &split);
  //: Constructor.
  
  DPSplitIPortC(DPSplitIPortBodyC<DataT> &split);
  //: Body Constructor.
  
  DPSplitIPortBodyC<DataT> &Body();
  //: Access body.
  
  const DPSplitIPortBodyC<DataT> &Body() const;
  //: Access body.
  
  bool Put(const DataT &dat);
  //: Put next piece of data.
  
  friend class DPSplitIPortBodyC<DataT>;
  friend class DPSplitIBodyC<DataT>;
};








/////////////////////////////////////////////////////////////////////////////////////////////////
//: Composition

template<class DataT>
DPIPortC<DataT> operator>>(const DPIPortC<DataT> &in,DPSplitIC<DataT> &out) {
  if(out.IsValid()) {
    cerr << "DPSplitIC already assigned!\n";
    return in;
  }
  out = DPSplitIC<DataT>(in);
  return out.NewPort();
}

#if 1
template<class InT,class OutT> class DPProcessC;
template<class InT,class OutT>
DPIPortC<OutT> operator>>(DPSplitIC<InT> &out,const DPProcessC<InT,OutT> &proc)
{ return out.NewPort() >> proc; }
#endif

/////////////////////////////////////////////

template<class DataT>
DPSplitIBodyC<DataT>::DPSplitIBodyC(const DPIPortC<DataT> &src)
  : source(src)
{}

template<class DataT>
DPSplitIBodyC<DataT>::~DPSplitIBodyC() 
{
  MutexLockC lock(access);
  for(DLIterC<DPSplitIPortC<DataT> > it(ports);it.IsElm();it.Next())
    it.Data().Disconnect();
}

template<class DataT> 
DPSplitIPortC<DataT> 
DPSplitIBodyC<DataT>::NewPort() 
{
  MutexLockC lock(access);
  DPSplitIC<DataT> tmp(*this);
  DPSplitIPortC<DataT> newun(tmp);
  ports.InsLast(newun);
  return newun;
}

template<class DataT>
bool 
DPSplitIBodyC<DataT>::Remove(DPSplitIPortC<DataT> &oth)
{
  MutexLockC lock(access);
  for(DLIterC<DPSplitIPortC<DataT> > it(ports);it.IsElm();it.Next()) {
    if(it.Data() == oth) {
      it.Del();
      return TRUE;
    }
  }
  return FALSE;
}

template<class DataT>
bool 
DPSplitIBodyC<DataT>::IsGetNextReady() const
{ 
  MutexLockC lock(access);
  return source.IsGetReady(); 
}

template<class DataT> 
bool 
DPSplitIBodyC<DataT>::GetNext() 
{
  MutexLockC lock(access);
  DataT tmp;
  if(!source.Get(tmp))
    return false;
  for(DLIterC<DPSplitIPortC<DataT> > it(ports);it.IsElm();it.Next())
    it.Data().Put(tmp);
  return TRUE;
}

//////////////////////////////

template<class DataT>
DPSplitIPortBodyC<DataT>::DPSplitIPortBodyC()
{}

template<class DataT>
DPSplitIPortBodyC<DataT>::DPSplitIPortBodyC(DPSplitIC<DataT> &src)
  : source(src)
{}

template<class DataT>
DPSplitIPortBodyC<DataT>::~DPSplitIPortBodyC()
{ Disconnect(); }

template<class DataT>
bool 
DPSplitIPortBodyC<DataT>::Disconnect() 
{
  if(source.IsValid()) {
    DPSplitIPortC<DataT> tmp(*this);
    source.Remove(tmp);
  }
  source = DPSplitIC<DataT>();
  return TRUE;
}

template<class DataT>
bool 
DPSplitIPortBodyC<DataT>::IsGetReady() const
{
  MutexLockC q_lock(q_access);
  if(!q.IsEmpty())
    return TRUE;
  q_lock.Unlock();
  return source.IsGetNextReady();
}

template<class DataT>
DataT 
DPSplitIPortBodyC<DataT>::Get() 
{
  MutexLockC q_lock(q_access);
  if(q.IsEmpty()) {
    // Unlock to allow data to be added to list.
    q_lock.Unlock(); 
    if(!source.GetNext())
      return DataT();
    q_lock.Lock();
  }
  return q.GetFirst();
}

template<class DataT>
bool DPSplitIPortBodyC<DataT>::Get(DataT &buff)
{
  MutexLockC q_lock(q_access);
  if(q.IsEmpty()) {
    // Unlock to allow data to be added to list.
    q_lock.Unlock(); 
    if(!source.GetNext())
      return false;
    q_lock.Lock();
  }
  buff = q.GetFirst();
  return true;
}

template<class DataT>
IntT DPSplitIPortBodyC<DataT>::GetArray(SArray1dC<DataT> &data)
{
  MutexLockC q_lock(q_access);
  for(SArray1dIterC<DataT> it(data);it;it++) {
    if(q.IsEmpty()) {
      // Unlock to allow data to be added to list.
      q_lock.Unlock(); 
      if(!source.GetNext())
	return it.Index().V();
      q_lock.Lock();
    }
    *it = q.GetFirst();
  }
  q_lock.Unlock(); 
  return data.Size();
}

template<class DataT>
bool 
DPSplitIPortBodyC<DataT>::Put(const DataT &dat) 
{
  MutexLockC q_lock(q_access);
  q.InsLast(dat);
  return TRUE;
}

//////////////////////////////////////////////


template<class DataT> 
DPSplitIPortC<DataT>::DPSplitIPortC(DPSplitIC<DataT> &split)
  : DPEntityC(*new DPSplitIPortBodyC<DataT>(split))
{}


template<class DataT>
DPSplitIPortC<DataT>::DPSplitIPortC(DPSplitIPortBodyC<DataT> &split)
  : DPEntityC(split)
{}

template<class DataT>
DPSplitIPortBodyC<DataT> &
DPSplitIPortC<DataT>::Body()
{ return dynamic_cast<DPSplitIPortBodyC<DataT> &>(DPEntityC::Body()); }

template<class DataT>
const DPSplitIPortBodyC<DataT> &
DPSplitIPortC<DataT>::Body() const
{ return dynamic_cast<const DPSplitIPortBodyC<DataT> &>(DPEntityC::Body()); }

template<class DataT> 
bool 
DPSplitIPortC<DataT>::Disconnect()
{ return Body().Disconnect(); }

template<class DataT>
bool 
DPSplitIPortC<DataT>::Put(const DataT &dat)
{ return Body().Put(dat); }

/////////////////////////////////////////

template<class DataT>
DPSplitIC<DataT>::DPSplitIC(const DPIPortC<DataT> &src)
  : DPEntityC(*new DPSplitIBodyC<DataT>(src))
{}

template<class DataT>
DPSplitIC<DataT>::DPSplitIC(const DPSplitIC<DataT> &oth)
  : DPEntityC(oth)
{}

template<class DataT>
DPSplitIC<DataT>::DPSplitIC()
  : DPEntityC(true)
{}

template<class DataT>
DPSplitIC<DataT>::DPSplitIC(DPSplitIBodyC<DataT> &oth)
  : DPEntityC(oth)
{}

template<class DataT>
DPSplitIBodyC<DataT> &
DPSplitIC<DataT>::Body()
{ return static_cast<DPSplitIBodyC<DataT> &>(DPEntityC::Body()); }

template<class DataT>
const DPSplitIBodyC<DataT> &
DPSplitIC<DataT>::Body() const
{ return static_cast<const DPSplitIBodyC<DataT> &>(DPEntityC::Body()); }

template<class DataT>
bool
DPSplitIC<DataT>::GetNext() 
{ return Body().GetNext(); }

template<class DataT>
bool DPSplitIC<DataT>::IsGetNextReady() const
{ return Body().IsGetNextReady(); }

template<class DataT>
DPSplitIPortC<DataT> 
DPSplitIC<DataT>::NewPort() 
{ return Body().NewPort(); }

template<class DataT>
bool 
DPSplitIC<DataT>::Remove(DPSplitIPortC<DataT> &oth) 
{ return Body().Remove(oth); }






}; //RavlN 



#endif 
