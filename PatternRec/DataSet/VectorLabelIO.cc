
#include "Ravl/PatternRec/DataSet2.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  DataSet2C<SampleC<VectorC>,SampleC<UIntT> > LoadVectorLabel(const StringC &fn) {
    DataSet2C<SampleC<VectorC>,SampleC<UIntT> > ret;
    IStreamC in(fn);
    if(!in)
      return ret;
    IntT samples;
    in >> samples;
    ONDEBUG(cerr << "Reading " << samples << " samples. \n");
    ret = DataSet2C<SampleC<VectorC>,SampleC<UIntT> >(samples);
    for(int i = 0;i < samples;i++) {
      IntT vs;
      // Read vector.
      in >> vs;
      ONDEBUG(cerr << "Vector size " << vs << " elements. \n");
      if(vs > 1000) {
	cerr << "Unexpectedly large vector. \n";
	return ret;
      }
      
      VectorC nv(vs);
      for(SArray1dIterC<RealT> it(nv);it;it++)
	in >> *it;
      // Read label.
      UIntT label;
      in >> label; 
      if(!in)
	break;
      ret.Append(nv,label);
    }
    return ret;
  }
}
