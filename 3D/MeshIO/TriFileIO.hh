#ifndef RAVL_TRIFILEIO_HEADER
#define RAVL_TRIFILEIO_HEADER 1
///////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/3D/TriSet.hh"
#include "Ravl/DP/Port.hh"
#include "Ravl/Stream.hh"

namespace Ravl3DN {
  
  //! userlevel=Develop
  //: Tri file IO.
  
  class DPITriFileBodyC
    : public DPIPortBodyC<TriSetC>
  {
  public:
    DPITriFileBodyC(const StringC &fn);
    //: Open file.
    
    DPITriFileBodyC(IStreamC &is);
    //: Open stream.
    
    virtual bool IsGetEOS() const;
    //: Is valid data ?
    
    virtual TriSetC Get();
    //: Get next piece of data.
    
  protected:
    IStreamC inf;
    bool done;
  };
  
  //! userlevel=Advanced
  //: Tri file IO.

  class DPITriFileC
    : public DPIPortC<TriSetC>
  {
  public:
    DPITriFileC(const StringC &fn)
      : DPEntityC(*new DPITriFileBodyC(fn))
    {}
    //: Open file.
    
    DPITriFileC(IStreamC &is)
      : DPEntityC(*new DPITriFileBodyC(is))
    {}
    //: Open a stream.
    
  };

  
  //! userlevel=Develop
  //: Tri file IO.
  
  class DPOTriFileBodyC
    : public DPOPortBodyC<TriSetC>
  {
  public:
    DPOTriFileBodyC(const StringC &fn);
    //: Open file.
    
    DPOTriFileBodyC(OStreamC &is);
    //: Open stream.
    
    virtual bool Put(const TriSetC &dat);
    //: Put data.
    
    virtual bool IsPutReady() const;
    //: Is port ready for data ?
    
  protected:
    OStreamC outf;
    bool done;
  };
  
  //! userlevel=Advanced
  //: Tri file IO.

  class DPOTriFileC
    : public DPOPortC<TriSetC>
  {
  public:
    DPOTriFileC(const StringC &fn)
      : DPEntityC(*new DPOTriFileBodyC(fn))
    {}
    //: Open file.
    
    DPOTriFileC(OStreamC &is)
      : DPEntityC(*new DPOTriFileBodyC(is))
    {}
    //: Open a stream.
    
  };


}


#endif
