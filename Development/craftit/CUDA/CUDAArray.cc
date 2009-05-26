
#include "Ravl/CUDA/CUDAArray.hh"
#include "Ravl/Threads/ThreadEvent.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/CallMethodRefs.hh"
#include <rlog/rlog.h>

namespace RavlN { namespace CUDAN {
  using RavlN::ByteT;
  
  //! Construct a simple
  
  CUDAArrayC::CUDAArrayC(CUDAContextC &context,
                         const std::type_info &datatype,
                         int height,int width,
                         bool useBilinearFiltering
                         )
    : m_context(&context),
      m_array(0),
      m_useBilinearFiltering(useBilinearFiltering),
      m_height(0),
      m_width(0),
      m_elementSize(0)
  { Alloc(width,height,datatype); }
  
  
  //! Construct an empty array.
  
  CUDAArrayC::CUDAArrayC(CUDAContextC &context)
    : m_context(&context),
      m_array(0),
      m_useBilinearFiltering(false),
      m_height(0),
      m_width(0),
      m_elementSize(0)
  {}
  
  //! Destructor.
  
  CUDAArrayC::~CUDAArrayC()
  {
    if(m_array != 0) {
      if(m_context->IsContextThread()) // Are we on the context thread already?
	m_context->FreeDevArray(m_array);
      else
	m_context->Queue(RavlN::TriggerPtr(m_context,&CUDAContextC::FreeDevArray,m_array));
    }
  }
  
  static bool GetArrayDesc(CUDA_ARRAY_DESCRIPTOR &desc,
			   const std::type_info &datatype,
			   int &elementSize) 
  {
    if(datatype == typeid(RavlN::ByteT)) {
      desc.Format = CU_AD_FORMAT_UNSIGNED_INT8; 
      desc.NumChannels = 1;
      elementSize = sizeof(RavlN::ByteT);
    } else if(datatype == typeid(RavlN::Int16T)) {
      desc.Format = CU_AD_FORMAT_SIGNED_INT16; 
      desc.NumChannels = 1;
      elementSize = sizeof(RavlN::Int16T);
    } else if(datatype == typeid(RavlN::IntT)) {
      desc.Format = CU_AD_FORMAT_SIGNED_INT32; 
      desc.NumChannels = 1;
      elementSize = sizeof(RavlN::IntT);
    } else if(datatype == typeid(float)) {
      desc.Format = CU_AD_FORMAT_FLOAT; 
      desc.NumChannels = 1;
      elementSize = sizeof(float);
    } else if(datatype == typeid(RavlN::Tuple2C<ByteT,ByteT>)) {
      desc.Format = CU_AD_FORMAT_UNSIGNED_INT8;
      desc.NumChannels = 2;      
      elementSize = sizeof(RavlN::Tuple2C<ByteT,ByteT>);
    } else {
      rError("Unknown data format %s ",RavlN::TypeName(datatype));
      RavlAssert(0);
      return false;
    }    
    //rDebug("GetArrayDesc, ElementSize=%d  Type=%s",elementSize,RavlN::TypeName(datatype));
    return true;
  }

  static UIntT ElementSizeInBytes(CUarray_format fmt) {
    switch(fmt) {
    case CU_AD_FORMAT_UNSIGNED_INT8:  return 1;
    case CU_AD_FORMAT_UNSIGNED_INT16: return 2;
    case CU_AD_FORMAT_UNSIGNED_INT32: return 4;
    case CU_AD_FORMAT_SIGNED_INT8:    return 1;
    case CU_AD_FORMAT_SIGNED_INT16:   return 2;
    case CU_AD_FORMAT_SIGNED_INT32:   return 4;
    case CU_AD_FORMAT_HALF:   return 2;
    case CU_AD_FORMAT_FLOAT:  return 4;
    default:
      RavlAssert(0);
      break;
    }
    return 0;
  }
  
  
  //! Allocate an array.
  
  bool CUDAArrayC::Alloc(int height,int width,const std::type_info &datatype) {
    m_height = height;
    m_width = width;
    CUDA_ARRAY_DESCRIPTOR desc;
    if(!GetArrayDesc(desc,datatype,m_elementSize))
      return false;
    if(m_context->IsContextThread()) {
      DoAlloc(0,desc);
    } else {
      RavlN::ThreadEventC eventDone;
      m_context->Queue(RavlN::TriggerPtr(this,&CUDAArrayC::DoAlloc,&eventDone,desc));
      eventDone.Wait();
    }
    return m_array != 0;
  }
  
  //! Do context thread side of the operation
  
  bool CUDAArrayC::AllocCopy(int height,int width,const std::type_info &datatype,const void *data,int dataStride) 
  {
    m_height = height;
    m_width = width;
    CUDA_ARRAY_DESCRIPTOR desc;
    if(!GetArrayDesc(desc,datatype,m_elementSize))
      return false;
    if(m_context->IsContextThread()) {
      DoAllocCopy(0,desc,data,dataStride);
    } else {
      RavlN::ThreadEventC eventDone;
      m_context->Queue(RavlN::TriggerPtr(this,&CUDAArrayC::DoAllocCopy,&eventDone,desc,data,dataStride));
      eventDone.Wait();
    }
    // Check if allocation worked.
    return m_array != 0;
  }
  

  
  bool CUDAArrayC::DoAlloc(RavlN::ThreadEventC *eventDone,CUDA_ARRAY_DESCRIPTOR &desc) {
    RavlAssert(m_context->IsContextThread());
    RavlAssert(m_elementSize > 0);
    CUresult ret;
    if(m_array != 0) {
      if((ret = cuArrayDestroy(m_array)) == 0) {
	rError("Failed to free old array '%d' ",ret);
      }
      m_array = 0;
    }
    desc.Width = m_width;
    desc.Height = m_height;
    if((ret = cuArrayCreate(&m_array,&desc)) != 0) {
      rError("Failed to allocate cuda array '%d' ",ret);
    }
    if(eventDone != 0)
      eventDone->Post();
    return true;
  }
  
  bool CUDAArrayC::DoAllocCopy(RavlN::ThreadEventC *eventDone,
                               CUDA_ARRAY_DESCRIPTOR &desc,
			       const void *data,
                               int dataStride
                               ) 
  {
    RavlAssert(m_context->IsContextThread());
    RavlAssert(m_elementSize > 0);
    CUresult ret;
    do {
      // Check there;s not already some memory allocated.
      if(m_array != 0) {
	if((ret = cuArrayDestroy(m_array)) == 0) {
	  rError("Failed to free old array '%d' ",ret);
	}
	m_array = 0;
      }
      // Allocate array 
      desc.Width = m_width;
      desc.Height = m_height;
      if((ret = cuArrayCreate(&m_array,&desc)) != 0) {
	rError("Failed to allocate cuda array '%d' ",ret);
	RavlAssert(0);
	break;
      }
      //rDebug("CUDAArrayC::DoAllocCopy, Width=%d Height=%d Stride=%d ElemSize=%d ",m_width,m_height,dataStride,m_elementSize);
      if(dataStride == 0 || dataStride == m_width) {
	if((ret = cuMemcpyHtoA(m_array,0,data,
                               m_width * m_height * m_elementSize)
	    ) != 0) {
	  rError("Failed to copy array data. '%d'",ret);
	  break;
	}        
      } else {
#if 0
	if((ret = cudaMemcpy2DToArray(m_array,0,0,data,dataStride,
				      m_width,m_height,
				      cudaMemcpyHostToDevice)
	    ) != 0) {
	  rError("Failed to copy array data. '%d'",ret);
	  break;
	}
#else
        UIntT elementSizeInBytes = desc.NumChannels * ElementSizeInBytes(desc.Format);
        
        CUDA_MEMCPY2D memcpyInfo;
        memset(&memcpyInfo,0,sizeof(CUDA_MEMCPY2D));
        
        memcpyInfo.srcXInBytes = 0;
        memcpyInfo.srcY = 0;
        memcpyInfo.srcMemoryType = CU_MEMORYTYPE_HOST;
        memcpyInfo.srcHost = data;
        memcpyInfo.srcPitch = dataStride;
        
        // These are used as: Start = (void*)((char*)srcHost+srcY*srcPitch + srcXInBytes);
        
        memcpyInfo.dstXInBytes = 0;
        memcpyInfo.srcY = 0;
        memcpyInfo.dstMemoryType = CU_MEMORYTYPE_ARRAY;
        memcpyInfo.dstArray = m_array;
        
        memcpyInfo.WidthInBytes = m_width * elementSizeInBytes; 
        memcpyInfo.Height = m_height;
        
        if((ret = cuMemcpy2D(&memcpyInfo)) != 0) {
	  rError("Failed to copy array data. '%d'",ret);
	  break;          
        }
#endif
      }
    } while(0) ;
    if(eventDone != 0)
      eventDone->Post();
    return true;
  }

}}
