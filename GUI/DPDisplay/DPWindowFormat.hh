#ifndef RAVLGUI_DPWINDOWFORMAT_HEADER
#define RAVLGUI_DPWINDOWFORMAT_HEADER 1
//////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/DP/FileFormat.hh"
#include "Ravl/GUI/DPDisplayObj.hh"

namespace RavlGUIN {
  
  class DPDisplayObjC;
  
  
  class DPWindowFormatBodyC
    : public FileFormatBodyC
  {
  public:
    DPWindowFormatBodyC();
    //: Default constructor.
    
    virtual const type_info &ProbeSave(const StringC &filename,const type_info &obj_type,bool forceFormat) const;
    //: Probe for Save.
    
    virtual DPOPortBaseC CreateOutput(const StringC &filename,const type_info &obj_type) const;
    //: Create a output port for saving.
    // Will create an Invalid port if not supported.
    
    virtual const type_info &DefaultType() const
    { return typeid(DPDisplayObjC); }
    //: Get prefered IO type.
    
    virtual bool IsStream() const { return true; }
    //: Test if format is a fully streamable.
    // i.e. check if you can read/write more than object object.
    
  };

  class DPWindowFormatC
    : public FileFormatBaseC
  {
  public:
    DPWindowFormatC()
      : FileFormatBaseC(*new DPWindowFormatBodyC())
    {}
    //: Default constructor.
  };

}

#endif
