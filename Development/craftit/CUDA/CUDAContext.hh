#ifndef OMNI_CUDACONTEXT_HEADER
#define OMNI_CUDACONTEXT_HEADER 1

#include "Ravl/SmartLayerPtr.hh"
#include "Ravl/Threads/MessageQueue.hh"
#include "Ravl/Threads/ThreadEvent.hh"
#include "Ravl/CallMethodPtrs.hh"
#include "Ravl/FixedQueue.hh"
#include "Ravl/XMLFactory.hh"

#include <cuda.h>
#include <rlog/rlog.h>

namespace RavlN { namespace CUDAN {
  
  //! CUDA processing context.
  
  class CUDAContextC
    : public RavlN::RCLayerBodyC
  {
  public:
    //! Constructor.
    CUDAContextC(int deviceNo = 0);
    
    //! Factory constructor
    CUDAContextC(const XMLFactoryContextC &node);
    
    //! Destructor.
    virtual ~CUDAContextC();
    
    //! Start context processing.
    bool Start();
    
    //! Free CUDA device memory
    //! Context thread only!
    void FreeDevMem(CUdeviceptr data);
    
    //! Free CUDA device array
    //! Context thread only!
    void FreeDevArray(CUarray data);
    
    //! Test if we're running on the context thread.
    bool IsContextThread() const;
    
    //! Queue an event to be processed.
    void Queue(const RavlN::TriggerC &trig) { 
      // Don't queue if we're on the context thread already.
      if(IsContextThread()){
	const_cast<RavlN::TriggerC &>(trig).Invoke();
	return ;
      }
      m_eventQ.Put(trig); 
    }
    
    //! Wait for stream to complete, when it does post event.
    //! Note, neither the stream or event may be destroyed before
    //! the event is posted.
    //! Context thread only!
    bool WaitForStream(CUstream &stream,RavlN::TriggerC &event)
    {
      RavlAssert(IsContextThread());
      if(!m_streamEntries.IsSpace()) {
	rWarning("Wait for stream queue full. ");
	// Post event, there may be some busy waits
	// but by the time the memory is copied out things should
	// have completed.
	event.Invoke();
	return false;
      }
      m_streamEntries.InsLast(StreamEntryC(stream,event)); 
      return true; 
    }
    
    //! Owning handle to context.
    typedef RavlN::SmartOwnerPtrC<CUDAContextC> RefT;

    //! Call back handle to context.
    typedef RavlN::SmartCallbackPtrC<CUDAContextC> CBRefT;
    
  protected:
    //! Do initalisation
    void Init();
    
    //! Called when owner handles drop to zero.
    virtual void ZeroOwners();
    
    //! Main processing thread.
    bool MainThread();
    
    int m_deviceNo; //! Device we're attaching to.
    bool m_terminate;
    UIntT m_threadId; //! Id of context thread.
    CUdevice m_device;
    CUcontext m_cuContext;
    
    class StreamEntryC 
    {
    public:
      //! Constructor
      StreamEntryC()
	: m_stream(0)
      {}
      
      //! Constructor
      StreamEntryC(CUstream stream,const RavlN::TriggerC &trig)
	: m_stream(stream),
	  m_event(trig)
      {}
      
      //! Access cuda stream.
      CUstream Stream()
      { return m_stream; }
      
      //! Is stream complete?
      bool IsComplete() const { 
	RavlAssert(m_stream != 0); 
	CUresult ret = cuStreamQuery(m_stream);
	if(ret == CUDA_SUCCESS) return true;
	if(ret == CUDA_ERROR_NOT_READY) return false;
	rError("Error querying cuda stream %d ",ret);
	RavlAssert(0);
	return false; 
      }
      
      //! Post event.
      void Post()
      { m_event.Invoke(); }
      
    protected:
      CUstream m_stream;
      RavlN::TriggerC m_event;
    };
    
    RavlN::MessageQueueC<RavlN::TriggerC> m_eventQ;
    RavlN::FixedQueueC<StreamEntryC> m_streamEntries;
    bool m_started;
  };

  
}}

#endif
