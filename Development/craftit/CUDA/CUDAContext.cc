
#include "Ravl/CUDA/CUDAContext.hh"
#include "Ravl/CallMethodPtrs.hh"
#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/Type/XMLFactoryRegister.hh"

#include <rlog/rlog.h>


namespace RavlN { namespace CUDAN {
  
  //! Constructor
  
  CUDAContextC::CUDAContextC(int deviceNo)
    : m_deviceNo(deviceNo),
      m_terminate(false),
      m_threadId((UIntT) -1),
      m_eventQ(16),
      m_streamEntries(18),
      m_started(false)
  {
    Init();
  }
  
  //! Factory constructor
  
  CUDAContextC::CUDAContextC(const TypeN::XMLFactoryContextC &node)
    : m_deviceNo(node.AttributeReal("device",0)),
      m_terminate(false),
      m_threadId((UIntT) -1),
      m_eventQ(16),
      m_streamEntries(18),
      m_started(false)
  {
    Init();
  }
  
  //! Destructor.
  
  CUDAContextC::~CUDAContextC()
  {
    rDebug("CUDAContextC::~CUDAContextC, Called. ");
  }

  void CUDAContextC::Init() {
    CUresult ret;
    if((ret = cuInit(0)) != CUDA_SUCCESS) {
      rWarning("Failed to initalise cuda. %d ",ret);
    }
  }
  
  bool CUDAContextC::IsContextThread() const
  { return m_threadId == RavlN::CurrentThreadID(); }

  //! Free CUDA device memory
  //! Context thread only!
  
  void CUDAContextC::FreeDevMem(CUdeviceptr data) {
    CUresult ret;
    if((ret = cuMemFree(data)) != 0) {
      rError("Failed to free memory. Error:%d ",ret);
    }
  }
  
  //! Free CUDA device array
  //! Context thread only!
  
  void CUDAContextC::FreeDevArray(CUarray data) {
    CUresult ret;
    if((ret = cuArrayDestroy(data)) != 0) {
      rError("Failed to free memory. Error:%d ",ret);
    }
  }
  
  
  //! Called when owner handles drop to zero.
  void CUDAContextC::ZeroOwners() {
    //rDebug("CUDAContext, Zero owners. ");
    m_terminate = true;
    RavlN::RCLayerBodyC::ZeroOwners();
  }
  
  //! Start context processing.
  
  bool CUDAContextC::Start() {
    if(m_started)
      return true;
    m_started = true;
    rDebug("Starting CUDA context. ");
    RavlN::LaunchThread(RavlN::TriggerPtr(CUDAContextC::CBRefT(*this),&CUDAContextC::MainThread));
    return true;
  }
 
  bool CUDAContextC::MainThread() {
    CUresult ret;
    rDebug("CUDAContextC::MainThread, Called. ");
    if((ret = cuDeviceGet(&m_device,m_deviceNo)) != CUDA_SUCCESS) {
      rError("Failed to find device %d ",ret);
      return false;
    }

    int flags = 0;
#ifdef CU_CTX_SCHED_YIELD
    flags |= CU_CTX_SCHED_YIELD;
#endif
    
    if((ret = cuCtxCreate(&m_cuContext,flags,m_device)) != CUDA_SUCCESS) {
      rError("Failed to create context %d ",ret);
      return false;
    }
    
    //rDebug("Context thread started. ");
    m_threadId = RavlN::CurrentThreadID();
    
    while(!m_terminate) {
      RavlN::TriggerC trig;
      if(m_eventQ.Get(trig,0.001)) {
	RavlAssert(trig.IsValid());
	trig.Invoke();
      }
      
      // Check if any events have completed.
      while(!m_streamEntries.IsEmpty()) {
	if(!m_streamEntries.First().IsComplete())
	  break; // Oldest is not ready, just continue
	// Post done signal
	m_streamEntries.GetFirst().Post();
	// Go around and check the next entry.
      }
      
    }
    
    m_threadId = (UIntT) -1;
    if((ret = cuCtxDetach(m_cuContext)) != CUDA_SUCCESS) {
      rError("Failed to detach context %d ",ret);
      return false;
    }
    
    //rDebug("Context thread exited. ");
    return true;
  }
  
  static TypeN::XMLFactoryRegisterC<CUDAContextC> g_registerCUDAContext("RavlN::CUDAN::CUDAContextC");
  
}}
