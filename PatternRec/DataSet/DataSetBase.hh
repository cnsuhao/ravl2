// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDATASETBASE_HEADER
#define RAVLDATASETBASE_HEADER 1
//! rcsid="$Id$"
//! author="Kieron Messer"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec

#include "Ravl/Collection.hh"

namespace RavlN {
  
  class DataSetBaseC;
  
  //! userlevel=Develop
  //: Data set 
  
  class DataSetBaseBodyC 
    : public RCBodyC
  {
    
  public:
    DataSetBaseBodyC()
    {}
    //: Default constructor.
    
    DataSetBaseBodyC(const CollectionC<UIntT> &nindex)
      : index(nindex)
    {}
    //: Default constructor.
    
    void ShuffleIP();
    //: In Place shuffle.
    // Randomise the order of this dataset.
    
    CollectionC<UIntT> &Index()
    { return index; }
    //: Access the data index
    
  protected:
    DataSetBaseBodyC(SizeT size);
    //: Setup for sample of 'size' elements.
    
    CollectionC<UIntT> index;
    //: the index into the data
  };
  
  
  //! userlevel=Normal
  //: Data set base class
  
  class DataSetBaseC
    : public RCHandleC<DataSetBaseBodyC >
  {
  public:
    
  protected:
    DataSetBaseC(const CollectionC<UIntT> &nindex)
      : RCHandleC<DataSetBaseBodyC >(*new DataSetBaseBodyC(nindex))
      {}
    //: Create a dataset from a sample and an index.
    
    DataSetBaseC(DataSetBaseBodyC &bod)
      : RCHandleC<DataSetBaseBodyC >(bod)
      { }
    //: Body constructor.
    
    DataSetBaseBodyC &Body()
      { return RCHandleC<DataSetBaseBodyC>::Body(); }
    //: Access body.

    const DataSetBaseBodyC &Body() const
      { return RCHandleC<DataSetBaseBodyC>::Body(); }
    //: Access body.
    
  public:

    CollectionC<UIntT> &Index()
    { return Body().Index(); }
    //: Access the data index
    
    void ShuffleIP()
    { Body().ShuffleIP(); }
    //: In Place shuffle.
    // Randomise the order of this dataset.
    
    friend class DataSetBaseBodyC;
  };
  


}

#endif
