#ifndef RAVLGUIFILESELECTOR_HEADER
#define RAVLGUIFILESELECTOR_HEADER 1
//////////////////////////////////////////////////
//! file="Ravl/GUI/GTK/FileSelector.hh"
//! lib=GUI
//! author="Charles Galambos"
//! date="23/03/99"
//! example=exMenu.cc
//! rcsid="$Id$"
//! docentry="Ravl.GUI.Control"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/String.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/Threads/Signal3.hh"

namespace RavlGUIN {

  class FileSelectorC;
  
  //! userlevel=Develop
  //: FileSelector body
  
  class FileSelectorBodyC
    : public WidgetBodyC
  {
  public:
    FileSelectorBodyC(const StringC &nname,const StringC &filename);
    //: Constructor.
    
    virtual bool Create();
    //: Create the widget.
    
    bool HideOnSelect() const { return hideOnSelect; }
    //: Should file selector be hiden after selection ?
    
    Signal1C<FilenameC> &Selected()
      { return selected; }
    //: Access selected signal.
    
  protected:
    void Destroy();
    //: Dissconnect all signals.
    
    StringC name;
    StringC defaultFN; // Default filename
    bool hideOnSelect; // Hide the fileselector after selection ?
    
    Signal1C<FilenameC> selected;
    
    friend class FileSelectorC;
  };
  
  //! userlevel=Normal
  //: FileSelector
  
  class FileSelectorC 
    : public WidgetC
  {
  public:
    FileSelectorC(const StringC &nname = "File Selector",const StringC &filename = ".")
      : WidgetC(*new FileSelectorBodyC(nname,filename))
      {}
    //: Constructor
    
    FileSelectorC(FileSelectorBodyC &bod)
      : WidgetC(bod)
      {}
    //: Body constructor.
    
  protected:
    FileSelectorBodyC &Body()
      { return static_cast<FileSelectorBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const FileSelectorBodyC &Body() const
      { return static_cast<const FileSelectorBodyC &>(WidgetC::Body()); }
    //: Access body.  
  public:
    
    Signal1C<FilenameC> &Selected()
      { return Body().Selected(); }
    //: Access selected signal.
    
    void SetHideOnSelect(bool val)
      { Body().hideOnSelect = val; }
    //: Set hide on select flag.
    // Thread safe, goes into effect immediatly.
    
  };
  
  //////////////////////////////////////////////////////////////
  
  //: Call a function.

  inline
  FileSelectorC FileSelector(const StringC &fsname,
			     bool (*func)(FilenameC &filename,FileSelectorC &),
			     const FilenameC &filename = StringC())
  { 
    FileSelectorC ret(fsname,filename);
    Connect(ret.Selected(),func,filename,ret);
    return ret;    
  }  

  //: Call a function.

  inline
  FileSelectorC FileSelector(const StringC &fsname,
			     bool (*func)(FilenameC &filename),
			     const FilenameC &filename = StringC())
  {
    FileSelectorC ret(fsname,filename);
    Connect(ret.Selected(),func,filename);
    return ret;    
  }
  
  //: Call a method.
  
  template<class DataT>
  FileSelectorC FileSelector(const StringC &fsname,
			     const DataT &obj,
			     bool (DataT::*func)(FilenameC &filename),const StringC &fn = StringC())
  { 
    FileSelectorC ret(fsname,fn);
    Connect(ret.Selected(),obj,func);
    return ret;    
  }  

  
  //: Call a function.
  
  template<class DataT>
  FileSelectorC FileSelector(const StringC &fsname,
			     const StringC &filename,
			     bool (*func)(FilenameC &filename,FileSelectorC &,DataT &ref),
			     const DataT &dat)
  { 
    FileSelectorC ret(fsname,filename);
    FilenameC fn(filename); // Convert to a real filename.
    Connect(ret.Selected(),func,fn,ret,dat);
    return ret;    
  }  
  
  //: Call a method.
  // Hold only a refrence to the destination class.
  
  template<class DataT>
  FileSelectorC FileSelectorR(const StringC &fsname,
			      DataT &obj,
			      bool (DataT::*func)(FilenameC &filename),const StringC &fn = StringC())
  { 
    FileSelectorC ret(fsname,fn);
    ConnectRef(ret.Selected(),obj,func);
    return ret;    
  }  
  


}


#endif
