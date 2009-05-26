#ifndef OMNI_CUDA_CUDAMEMORY_HEADER
#define OMNI_CUDA_CUDAMEMORY_HEADER 1

#include "Ravl/CUDA/CUDAContext.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/SArray1d.hh"

namespace RavlN { namespace CUDAN {
  using RavlN::SizeT;
  
  class CUDAMemoryC 
    : public RavlN::RCBodyVC
  {
  public:
    //! Construct a simple
    CUDAMemoryC(CUDAContextC &context,size_t size);
    
    //! Construct an empty array.
    CUDAMemoryC(CUDAContextC &context);
    
    //! Destructor.
    ~CUDAMemoryC();
    
    //! Allocate an array.
    bool Alloc(size_t size);
    
    //! Allocate an array.
    bool AllocCopy(const void *data,size_t size);
    
    template<class DataT>
    bool Set(const RavlN::SArray1dC<DataT> &array) 
    { return AllocCopy(&(array[0]),array.Size() * sizeof(DataT)); }
    
    //! Copy from host to device.
    //! CUDA Thread only
    bool CUDACopyH2D(const void *data,size_t size);
    
    //! Copy from device to host.
    //! CUDA Thread only
    bool CUDACopyD2H(void *data,size_t size);
    
    //! Access array.
    CUdeviceptr Data()
    { return m_data; }
    
    //! Access array.
    const CUdeviceptr Data() const
    { return m_data; }

    //! Access size
    SizeT Size() const
    { return m_size; }
    
    //! Access pitch for 2d allocations
    SizeT Pitch() const
    { return m_pitch; }
    
    typedef RavlN::SmartPtrC<CUDAMemoryC> RefT;
  protected:
    //! Do context thread side of the operation
    bool DoAlloc(RavlN::ThreadEventC *eventDone,size_t size);
    
    //! Do allocate & copy work needed on context thread.
    bool DoAllocCopy(RavlN::ThreadEventC *eventDone,const void *data,size_t size);
    
    //! Copy data back from device to host memory.
    //bool DoCopyTo(void *data,size_t size);
    
    CUDAContextC::RefT m_context;
    CUdeviceptr m_data;
    size_t m_size;
    size_t m_pitch;

  private:
    //! Copy constructor
    CUDAMemoryC(const CUDAMemoryC &)
    { RavlAssert(0); }
  };
}}

#endif
