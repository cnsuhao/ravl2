#ifndef RAVL_QTIMAGEIPORT_HEADER
#define RAVL_QTIMAGEIPORT_HEADER 1

#include "Ravl/DP/Port.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/DP/FixedBuffer.hh"
#include "Ravl/Threads/MessageQueue.hh"
#include "Ravl/SmartPtr.hh"

namespace RavlImageN {
  class QTCaptureThreadBodyC;

  //! Base class for capture threads
  class DPPortQTImageImplBaseC
    : virtual public RavlN::RCBodyVC
  {
  public:
    DPPortQTImageImplBaseC(const StringC &name,const std::type_info &pixelType);

    //! Start capture.
    virtual bool StartCapture();

    //! Stop capture.
    virtual bool StopCapture();

    //! has capture been started ?
    bool IsStarted() const
    { return m_isStarted; }

    typedef RavlN::SmartPtrC<DPPortQTImageImplBaseC> RefT;
  protected:

    bool m_isStarted;
  };

  template<class PixelT>
  class DPPortQTImageImplC
    : public DPPortQTImageImplBaseC
  {
  public:
    DPPortQTImageImplC(const StringC &name,int bufferSize)
     : DPPortQTImageImplBaseC(name,typeid(PixelT)),
       m_queue(bufferSize)
    {}

    //! Access message queue
    MessageQueueC<ImageC<PixelT> > &Queue()
    { return m_queue; }

    //! Reference to this handle
    typedef RavlN::SmartPtrC<DPPortQTImageImplC<PixelT> > RefT;

  protected:
    MessageQueueC<ImageC<PixelT> > m_queue;
  };


  // Find the correct implementation and open it
  bool OpenQTImageImpl(const StringC &name,const std::type_info &pixelType,int buffSize,DPPortQTImageImplBaseC::RefT &handle);

  template<typename PixelT>
  class DPIPortQTImageBodyC
    : public DPIPortBodyC<ImageC<PixelT> >
  {
  public:
    // Constructor.
    DPIPortQTImageBodyC(const StringC &name,int buffSize)
    {
      DPPortQTImageImplBaseC::RefT bimpl;
      if(OpenQTImageImpl(name,typeid(PixelT),buffSize,bimpl))
        m_impl = &dynamic_cast<DPPortQTImageImplC<PixelT> &>(*bimpl);
    }

    //! Destructor.
    ~DPIPortQTImageBodyC()
    {
      if(m_impl.IsValid())
        m_impl->StopCapture();
    }

    virtual bool IsReady() const
    { return m_impl.IsValid(); }
    //: Return true if there's data ready.

    virtual ImageC<PixelT> Get()
    {
      if(!m_impl->IsStarted())
        m_impl->StartCapture();
      return m_impl->Queue().Get();
    }
    //: Get next piece of data.

    virtual bool Get(ImageC<PixelT> &d)
    {
      if(!m_impl->IsStarted())
        m_impl->StartCapture();
      d = m_impl->Queue().Get();
      return true;
    }
    //: Get next piece of data.

    virtual IntT GetArray(SArray1dC<ImageC<PixelT> > &dat)
    {
      if(!m_impl->IsStarted())
        m_impl->StartCapture();
      for(SArray1dIterC<ImageC<PixelT> > it(dat);it;it++)
        *it = m_impl->Queue().Get();
      return dat.Size();
    }
    //: Get an array of data.

  protected:
    SmartPtrC<DPPortQTImageImplC<PixelT> > m_impl;
  };

  //! Handle to port.
  template<typename PixelT>
  class DPIPortQTImageC
  : public DPIPortC<ImageC<PixelT> >
  {
  public:
    DPIPortQTImageC(const StringC &name,int bufferSize)
    : DPEntityC(new DPIPortQTImageBodyC<PixelT>(name,bufferSize))
    {}

  };

}

#endif
