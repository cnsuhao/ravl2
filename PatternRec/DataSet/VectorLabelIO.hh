#ifndef RAVL_VECTORLABELIO_HEADER
#define RAVL_VECTORLABELIO_HEADER 1

#include "Ravl/PatternRec/DataSet2.hh"

namespace RavlN {
  
  DataSet2C<SampleC<VectorC>,SampleC<UIntT> > LoadVectorLabel(const StringC &fn);
  //: Load a vector label dataset.
}


#endif
