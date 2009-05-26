
#include "Ravl/CUDA/CUDAMemory.hh"
#include "Ravl/Threads/ThreadEvent.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/CallMethodRefs.hh"
#include <rlog/rlog.h>

namespace RavlN { namespace CUDAN {
  using RavlN::ByteT;
  
  //! Construct a simple
  
  CUDAMemoryC::CUDAMemoryC(CUDAContextC &context,size_t size)
    : m_context(&context),
      m_data(0),
      m_size(0),
      m_pitch(0)
  { Alloc(size); }

  
  //! Construct an empty array.
  
  CUDAMemoryC::CUDAMemoryC(CUDAContextC &context)
    : m_context(&context),
      m_data(0),
      m_size(0),
      m_pitch(0)
  {}
   
  //! Destructor.
  
  CUDAMemoryC::~CUDAMemoryC()
  {
    if(m_data != 0) {
      if(m_context->IsContextThread()) 
	m_context->FreeDevMem(m_data);
      else
	m_context->Queue(RavlN::TriggerPtr(m_context,&CUDAContextC::FreeDevMem,m_data));
    }
    m_data = 0;
  }
 
  //! Allocate an array.
  
  bool CUDAMemoryC::Alloc(size_t size) {
    RavlN::ThreadEventC eventDone;
    m_context->Queue(RavlN::TriggerPtr(this,&CUDAMemoryC::DoAlloc,&eventDone,size));
    eventDone.Wait();
    return m_data != 0;
  }
  
  //! Do context thread side of the operation
  
  bool CUDAMemoryC::AllocCopy(const void *data,size_t size) 
  {
    RavlN::ThreadEventC eventDone;
    m_context->Queue(RavlN::TriggerPtr(this,&CUDAMemoryC::DoAllocCopy,&eventDone,data,size));
    eventDone.Wait();
    // Check if allocation worked.
    return m_data != 0;
  }
  
  //! Copy from host to device.
  //! CUDA Thread only
  
  bool CUDAMemoryC::CUDACopyH2D(const void *data,size_t size) 
  {
    RavlAssert(data != 0);
    RavlAssert(m_data != 0);
    RavlAssert(size <= m_size);
    CUresult ret;
    if((ret = cuMemcpyHtoD(m_data,data,size)) != 0) {
      rError("Failed to copy array data to device. '%d'",ret);      
      return false;
    }
    return true;
  }
  
  //! Copy from device to host.
  //! CUDA Thread only
  
  bool CUDAMemoryC::CUDACopyD2H(void *data,size_t size) {
    RavlAssert(data != 0);
    RavlAssert(m_data != 0);
    RavlAssert(size <= m_size);
    CUresult ret;
    
    if((ret = cuMemcpyDtoH(data,m_data,size)) != 0) {
      rError("Failed to copy array data from device. '%d'",ret);
      return false;
    }
    return true;
  }
  

  
  bool CUDAMemoryC::DoAlloc(RavlN::ThreadEventC *eventDone,size_t size) {
    RavlAssert(m_context->IsContextThread());
    CUresult ret;
    if(m_size != size) {
      if(m_data != 0) {
	if((ret = cuMemFree(m_data)) != 0)
	  rError("Failed to free cuda memory '%d' ",ret);
	m_data = 0; // In case alloc fails.
      }
      if((ret = cuMemAlloc(&m_data,size)) != 0) {
	rError("Failed to allocate cuda memory '%d' ",ret);
      } else
	m_size = size;
    }
    eventDone->Post();
    return true;
  }
  
  bool CUDAMemoryC::DoAllocCopy(RavlN::ThreadEventC *eventDone,const void *data,size_t size) {
    RavlAssert(m_context->IsContextThread());
    CUresult ret;
    do {
      if(m_size != size) {
	if(m_data != 0) {
	  if((ret = cuMemFree(m_data)) != 0)
	    rError("Failed to free cuda memory '%d' ",ret);
	  m_data = 0; // In case alloc fails.
	}
	if((ret = cuMemAlloc(&m_data,m_size)) != 0) {
	  rError("Failed to allocate cuda memory '%d' ",ret);
	  break;
	}
	m_size = size;
      }
      if((ret = cuMemcpyHtoD(m_data,data,size)) != 0) {
	rError("Failed to copy array data. '%d'",ret);
	break;
      }
    } while(0) ;
    eventDone->Post();
    return true;
  }

}}
