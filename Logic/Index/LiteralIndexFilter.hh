// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGICLITERALINDEXFILTER_HEADER
#define RAVLLOGICLITERALINDEXFILTER_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Logic.Index"
//! lib=RavlLogic

#include "Ravl/Logic/LiteralIndexFilterBase.hh"
#include "Ravl/Logic/LiteralIndex.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Index filter.
  
  template<class DataT>
  class LiteralIndexFilterBodyC 
    : public LiteralMapIterBodyC<DataT>,
      public LiteralIndexFilterBaseBodyC 
  {
  public:
    LiteralIndexFilterBodyC(const LiteralIndexC<DataT> &ind,const LiteralC &filter)
      : LiteralIndexFilterBaseBodyC(ind,filter)
    {}
    
    virtual bool Next()
    { return LiteralIndexFilterBaseBodyC::Next(); }
    //: Goto next data element.
    // returns true if next element is valid.
    
    virtual bool First()
    { return LiteralIndexFilterBaseBodyC::First(); }
    //: Goto first data element.
    // returns true if next element is valid.
    
    virtual bool IsElm() const
    { return LiteralIndexFilterBaseBodyC::IsElm(); }
    //: At a valid element ?
    // returns true if iterator is at a valid
    // element.
    
    virtual LiteralC Data()
    { return LiteralIndexFilterBaseBodyC::Data().Key(); }
    //: At a valid element.
    
    virtual DataT &MappedData()
    { return LiteralIndexLeafDataC<DataT>(LiteralIndexFilterBaseBodyC::Data()).Data(); }
    //: Access data.
    
    virtual const DataT &MappedData() const
    { return LiteralIndexLeafDataC<DataT>(LiteralIndexFilterBaseBodyC::Data()).Data(); }
    //: Access data.
    
  protected:
    
  };
  
  //! userlevel=Normal
  //: Index filter
  
  template<class DataT>
  class LiteralIndexFilterC 
    : public LiteralMapIterC<DataT>
  {
  public:
    LiteralIndexFilterC(const LiteralIndexC<DataT> &ind,const LiteralC &filter)
      : LiteralMapIterC<DataT>(*new LiteralIndexFilterBodyC<DataT>(ind,filter))
    {}
    
  protected:
    LiteralIndexFilterC(LiteralMapIterBodyC<DataT> &bod)
      : LiteralMapIterC<DataT>(bod)
    {}
    //: Body constructor.
    
    LiteralMapIterBodyC<DataT> &Body()
    { return static_cast<LiteralMapIterBodyC<DataT> &>(LiteralIterC::Body()); }
    //: Access body.
    
    const LiteralMapIterBodyC<DataT> &Body() const
    { return static_cast<const LiteralMapIterBodyC<DataT> &>(LiteralIterC::Body()); }
    //: Access body.
    
  public:
    
  };
  
}


#endif
