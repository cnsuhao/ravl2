#ifndef OMNI_CUDA_CUDAARRAY_HEADER
#define OMNI_CUDA_CUDAARRAY_HEADER 1

#include "Ravl/CUDA/CUDAContext.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/Array2d.hh"
#include "Ravl/SArray2d.hh"

namespace RavlN { namespace CUDAN {
  
  class CUDAArrayC 
    : public RavlN::RCBodyVC
  {
  public:
    //! Construct a simple
    CUDAArrayC(CUDAContextC &context,
               const std::type_info &typeId,
               int height,int width,
               bool useBilinearFiltering = false
               );
    
    //! Construct an empty array.
    CUDAArrayC(CUDAContextC &context);
    
    //! Destructor.
    ~CUDAArrayC();
    
    //! Allocate an array.
    bool Alloc(int height,int width,const std::type_info &typeId);

    //! Allocate an array.
    //! Note: dataStride is in bytes
    bool AllocCopy(int height,int width,const std::type_info &typeId,const void *data,int dataStride);
    
    template<class DataT>
    bool Set(const RavlN::SArray2dC<DataT> &array) {
      if(array.Frame().Area() == 0)
	return true;
      return AllocCopy(array.Rows(),array.Cols(),typeid(DataT),&(array[0][0]),array.Stride());
    }
    
    template<class DataT>
    bool Set(const RavlN::Array2dC<DataT> &array) {
      if(array.Frame().Area() == 0)
	return true;
      return AllocCopy(array.Frame().Rows(),array.Frame().Cols(),typeid(DataT),&(array[array.Frame().Origin()]),array.Stride());
    }
    
    //! Access array.
    CUarray Array()
    { return m_array; }
    
    //! Access array.
    const CUarray Array() const
    { return m_array; }
    
    //! Handle to array
    typedef RavlN::SmartPtrC<CUDAArrayC> RefT;
    
  protected:
    //! Do context thread side of the operation
    bool DoAlloc(RavlN::ThreadEventC *eventDone,CUDA_ARRAY_DESCRIPTOR &desc);
    
    //! Do allocate & copy work needed on context thread.
    bool DoAllocCopy(RavlN::ThreadEventC *eventDone,CUDA_ARRAY_DESCRIPTOR &desc,const void *data,int dataStride);
    
    CUDAContextC::RefT m_context;
    CUarray m_array;
    bool m_useBilinearFiltering;
    
    int m_height;
    int m_width;
    int m_elementSize;

  private:
    //! Copy constructor
    CUDAArrayC(const CUDAArrayC &)
    { RavlAssert(0); }
    
  };
}}

#endif
