// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DATASETVECTORLABEL_HEADER
#define RAVL_DATASETVECTORLABEL_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/DataSet2.hh"
#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/PatternRec/SampleLabel.hh"


namespace RavlN {

  //! userlevel=Develop
  //: Data set of labeled vectors.
  
  class DataSetVectorLabelBodyC 
    : public DataSet2BodyC<SampleVectorC,SampleLabelC>
  {
  public:
    DataSetVectorLabelBodyC(const SampleVectorC & vec,
			    const SampleLabelC & lab)
      : DataSet2BodyC<SampleVectorC,SampleLabelC>(vec,lab)
    {}
    //: Constructor
    
    SArray1dC<SampleVectorC> SeperateLabels();
    //: Create a seperate sample for each label.
  };
  
  //! userlevel=Normal
  //: Data set of labeled vectors.
  
  class DataSetVectorLabelC 
    : public DataSet2C<SampleVectorC,SampleLabelC>
  {
  public:
    DataSetVectorLabelC()
    {}
    //: Default constructor.
    
    DataSetVectorLabelC(const SampleVectorC & vec,const SampleLabelC & lab)
      : DataSet2C<SampleVectorC,SampleLabelC>(*new DataSetVectorLabelBodyC(vec,lab))
    {}
    //: Constructor
    
  protected:
    DataSetVectorLabelBodyC &Body()
    { return static_cast<DataSetVectorLabelBodyC &>(DataSetBaseC::Body()); }
    //: Access body.
    
    const DataSetVectorLabelBodyC &Body() const
    { return static_cast<const DataSetVectorLabelBodyC &>(DataSetBaseC::Body()); }
    //: Access body.
    
  public:
    SArray1dC<SampleVectorC> SeperateLabels()
    { return Body().SeperateLabels(); }
    //: Create a seperate sample for each label.
    
  };
}


#endif
